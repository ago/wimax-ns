/**************************************************************************
Copyright (c) 2007-2008, Intel Corporation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 3. Neither the name of the Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/

// to force recompilation of this file everytime configure is run which can change some macros used in this file
#include "wns-version.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <pthread.h>
#define _XOPEN_SOURCE 600
#include <semaphore.h>
#include <ctype.h>
#include <syslog.h>
#include <unistd.h>

// Netlink socket header file
#include <wimaxll.h>
// L3L4 Header Definition
#include <linux/wimax/i2400m.h>

#include "wimax_osal_primitives.h"

#include "TraceModule.h"
#include "Act.h"
#include "L4MsgProxy.h"
#include "L3L4CommonDefines.h"
#include "L3L4TlvTypes.h"
#include "L4ConfigurationManager.h"
#include "KDapiForLinuxNlsock.h"
#include "L4BufMan_L3L4Structs_Desc.h"
#include "L4BufMan_L3L4Structs.h"
#include "Services_Ctrl.h"

#define MAX_DATA_SIZE_SET_NORMAL 100

/*
EVP firmware does not like L4_L3_OPCODE_CMD_INIT send more than once
Until the firmware problem is solved the INIT command is simulated at this level
*/

// #define BLOCK_INIT_COMMAND_FOR_EVP

// KDAPI will try this no of times to open wimax nl read handle
// It takes long because firmware loading can take long, so we try a
// few times if -ENODEV is being returned
#define KDAPI_TRY_TO_OPEN_WMX_HANDLE 20

//#define DEBUG_DEVELOPER
#ifdef DEBUG_DEVELOPER
#define printk printf
#else
#define printk(format,args...)
#endif

extern BOOL g_enable_driver_msg;

#define TR_MOD_KDAPI_FOR_LINUX_NLSOCK TR_MOD_KDAPI

/*
This case can come to use only in "internal" supplicant case

Sometimes firmware asks for the key second time before processing the key sent before
After the connection is established, sending the key second time seems to reset the
firmware to Ready State.

By making note of device status "Data path connected", the supplicant wrapper (wmx_sup_impl.c)
won't send the key second time

g_Connected needs to be defined in global place so that can be accessed in
this file and wmx_sup_impl.c, so it is defined in wmx_supp_impl.c

FIXME:
	Go and uncomment the INTERNAL_SUPPLICANT_DONT_SEND_KEY_SECONDTIME_IF_ALREADY_CONNECTED
	in wmx_sup_impl.c and here for it to work
*/

// #define INTERNAL_SUPPLICANT_DONT_SEND_KEY_SECONDTIME_IF_ALREADY_CONNECTED

/*
To include code for   PIPE
*/
//#define PIPE_FOR_TRACES

static KDAPI_StatusIndicationHandler KDAPI_status_ind_handler;
// static pthread_mutex_t KDAPI_device_write_lock_mutex;
static OSAL_mutex_t KDAPI_device_write_lock_mutex = NULL;
//static unsigned int g_connectmode = 0;
//static int oidResponseResult;
//static char* oidResponseBuffer;
//static int oidResponseSize;

// wimax read response/indication thread
static OSAL_thread_t driver_check_status_handle;

// Kill event for the thread
static OSAL_event_t KDAPI_thread_kill_event = NULL;

static OSAL_mutex_t KDAPI_stop_sending_indications_mutex = NULL;
static volatile BOOL KDAPI_stop_sending_indications = TRUE;

static sem_t sem_for_send_rcv_msg;
static struct i2400m_l3l4_hdr *send_rcv_msg;
static size_t rcv_msg_size = 0;

// trace read thread
static KDAPI_TraceIndicationHandler KDAPI_trace_ind_handler = NULL;

// static OSAL_thread_t trace_read_thread_handle;
// static OSAL_event_t trace_read_thread_kill_event = NULL;

static OSAL_mutex_t KDAPI_stop_sending_traces_mutex = NULL;
static volatile BOOL KDAPI_stop_sending_traces = TRUE;
static BOOL use_traces = FALSE;
//static char indicationsBuf[STATUS_INDICATION_PAYLOAD_MAX_SIZE];
static int turning_on_radio_for_first_time = 0;
//static char InBuffer[30];
//static char OutBuffer[30];
//static struct wimax_handle *g_wmx_write_handle;

#ifdef INTERNAL_SUPPLICANT_DONT_SEND_KEY_SECONDTIME_IF_ALREADY_CONNECTED
extern int g_Connected;
#endif

// wimax device handle
// Read Hanlde
struct wimaxll_handle *g_wmx_read_handle;
// Write Hanlde
struct wimaxll_handle *g_wmx_write_handle;
// wimax trace pipe handle
int g_wmx_trace_pipe_handle = 0;
// Link up redundant will mask second linkup
// Reset it as device may have restarted
extern int linkup_redundant;

//int g_Connected = 0;

#define ENABLE_NETLINK_HANDLE_CHECKING

// ########### DEBUG ###################

#ifdef ENABLE_NETLINK_HANDLE_CHECKING

static struct wimaxll_handle *nl_handlecopy[11];

#define CHECK_NL_HANDLE()	\
	if ( nl_handlecopy[5] != g_wmx_read_handle ) \
	{ \
	TRACE(TR_MOD_KDAPI, TR_SEV_ERR, \
	      "netlink socket handle has corrupted.");\
	}

#else

#define CHECK_NL_HANDLE()

#endif

// ########### DEBUG ###################
static int bEnableRawTracing = 0;

#define ENABLE_FW_TRACE_LOGGING

#ifdef ENABLE_FW_TRACE_LOGGING

static char *fw_trace_file = PKG_VAR_LOG_DIR "/fwtrace.trc";
static FILE *ptracefile = NULL;

#endif

// ########### DEBUG ###################

/* local function delclarations*/
static UINT32 turn_on_off_device_radio(unsigned short *InBuffer,
				  int InBufferSize,
				  unsigned short *Buffer,
				  int OutBufferSize, UINT32 * pBytesWritten);

static int set_device_mode_to_normal();
static UINT32 KDAPI_send_io_control(IN void *pInBuffer, IN UINT32 inBufSize,
				  OUT void *pOutBuffer, IN UINT32 outBufSize,
				  OUT UINT32 * pBytesWritten,
				  IN BOOL WaitOnIRP);
// Prints in hex the traffic up and down appsrv
//#ifdef DEBUG_DEVELOPER
static void print_hex(unsigned char *data, int data_len);
//#endif

/* Function Definitions */
void CheckForDriverFailed()
{

}

/*
*This function sends the l3l4 message to driver and wait for the drivers response. Before sending data to
*driver, it locks the device interface via mutex, so that no new query is sent until response is recieved
*for the last query. This is a limitation of firmware.
*
*Return value: This function returns zero if suceess, a -1 if not.
*/
static int send_recieve_message_to_driver(IN UINT32 Command,
			      IN void *pInBuffer,
			      IN UINT32 inBufSize,
			      OUT void *pOutBuffer,
			      OUT UINT32 * pWrittenOutBufSize)
{
	ssize_t result;
#if 0
	static unsigned char rawConnectCmd[] = { 0x04, 0x46, 0x38, 0x00, 0x42, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x00, 0x0c, 0x00,
0x00, 0x00, 0x04, 0x00, 0x00, 0xe1, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xb6, 0x00, 0x08, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8f, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00,
0xc0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x04, 0x00,
0x04, 0x00, 0x00, 0x00 };

#endif // 1

#ifdef _DEBUG
	// static unsigned char GET_STATE_L4L3_MSG[] =
	//      { 0x05, 0x52, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#endif // _DEBUG
	//int value;

	// pthread_mutex_lock(&KDAPI_device_write_lock_mutex);
	OSAL_lock_mutex(KDAPI_device_write_lock_mutex);
	send_rcv_msg = NULL;
	rcv_msg_size = 0;
	struct i2400m_l3l4_hdr *wmx_in_buffer =
	    (struct i2400m_l3l4_hdr *)pInBuffer;
	TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG,
	      "Sending Msg to Driver: command:0x%x size:%d", Command,
	      inBufSize);

	// When there is a connect command from layers above
	// Device must be already got disconnected. So let us reset
	// the flag so that next LINK_UP is accepted for dhcp req
	// This will be useful in fast reconnect scenario where firmware is
	// failing to send LINK_DOWN before sending a LINK_UP
	if(wmx_in_buffer->type == wimaxll_cpu_to_le16(L4_L3_OPCODE_CMD_CONNECT))
	{
		linkup_redundant = 0;
	}

	if (*((UINT16 *) pInBuffer) == wimaxll_cpu_to_le16(0x4604))	// enable raw logging during connect
	{
		 bEnableRawTracing = 1;
		//g_Connected = 0;
#if 0
		pInBuffer = rawConnectCmd;
		inBufSize = sizeof(rawConnectCmd);
#endif
	}



	if ((bEnableRawTracing) || (*((UINT16 *) pInBuffer) == wimaxll_cpu_to_le16(0x6201))) {
#ifdef _DEBUG1
		if (inBufSize == 2088) {
			// Probe to check if the device has already rebooted before sending this large packet down
			pInBuffer = (void *)GET_STATE_L4L3_MSG;
			inBufSize = sizeof(GET_STATE_L4L3_MSG);
		}
#endif
		if (*((UINT16 *) pInBuffer) == wimaxll_cpu_to_le16(0x6201))
			DumpHexString("Gatekeeper (TLS Out): ", pInBuffer, inBufSize);
		else {
			DumpHexString("Gatekeeper (out) : ", pInBuffer, inBufSize);
		}
	}
#ifdef DEBUG_DEVELOPER
	printk("<<< Send Message To Driver: 0x%x\n", Command);
	unsigned char *indication_to_driver;
	indication_to_driver = (unsigned char *)pInBuffer;
	print_hex(indication_to_driver, inBufSize);
#else
    if (g_enable_driver_msg == TRUE) {
        printf(">>> [MSG 0x%x][%d]\n", Command, inBufSize);
        unsigned char *indication_to_driver;
        indication_to_driver = (unsigned char *) pInBuffer;
        print_hex(indication_to_driver, inBufSize);
    }
#endif
	CHECK_NL_HANDLE();

	    result =
	    wimaxll_msg_write(g_wmx_write_handle, NULL, (const void *)wmx_in_buffer,
			    inBufSize);
	if (result < 0) {
		printk("Unable to send the command to driver \n");
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
		      "Unable to send the command to driver");
		goto error_msg_send_command;
	}
	printk("Waiting for the response \n");
	//sem_getvalue(&sem_for_send_rcv_msg, &value);
	//printk("SendRcvMsg The value of the semaphors is %d\n", value);
	sem_wait(&sem_for_send_rcv_msg);
	printk("Got the response \n");
	if (send_rcv_msg != NULL && rcv_msg_size != 0) {
		if (send_rcv_msg->type != *(unsigned short *)pInBuffer) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
			      "Incorrect response recieved %x expected %x\n",
			      wimaxll_le16_to_cpu(send_rcv_msg->type),
			      wimaxll_le16_to_cpu(*(unsigned short *)pInBuffer));
			printk("Incorrect response recieved %x expected %x\n",
			       wimaxll_le16_to_cpu(send_rcv_msg->type),
			       wimaxll_le16_to_cpu(*(unsigned short *)pInBuffer));
			free(send_rcv_msg);
			send_rcv_msg = NULL;
			goto error_msg_send_command;
		}
		memcpy(pOutBuffer, send_rcv_msg, rcv_msg_size);
		*pWrittenOutBufSize = rcv_msg_size;
		printk("Response recieved: size(%d) status(%x)\n", rcv_msg_size, wimaxll_le16_to_cpu(send_rcv_msg->status));

#ifndef DEBUG_DEVELOPER
        if(g_enable_driver_msg == TRUE) {
            printf("<<< [RSP 0x%x][%d]\n", Command, rcv_msg_size);
            print_hex((unsigned char *)send_rcv_msg, rcv_msg_size);
        }
#endif
		// free the memory allocated by send_msg_response_to_l4
		free(send_rcv_msg);
		send_rcv_msg = NULL;

		if (bEnableRawTracing) {
			if (*((UINT16 *) pInBuffer) == wimaxll_cpu_to_le16(0x6201))
				DumpHexString("Gatekeeper (TLS IN): ", pOutBuffer, rcv_msg_size);
			else
				DumpHexString("Gatekeeper (in): ", pOutBuffer, rcv_msg_size);
		}
// #if 1
//              if ( *((UINT16 *)pInBuffer) == wimaxll_cpu_to_le16(0xd002) )
//              {
//                      UINT16 *pTmp = pInBuffer;

//                      // Set the global system state
//                      if ( * (pTmp + 12) == 8 )
//                              g_Connected = 1;
//              }
// #endif // 1
#ifdef INTERNAL_SUPPLICANT_DONT_SEND_KEY_SECONDTIME_IF_ALREADY_CONNECTED
		if (*((UINT16 *) pInBuffer) == wimaxll_cpu_to_le16(0xd002)) {
			UINT16 *pTmp = pInBuffer;
			// Set the global system state
			if (*(pTmp + 12) == 8) {
				printk("ALready Connected  \n");
				g_Connected = 1;
			}
		}
#endif
		// wimaxll_msg_free(send_rcv_msg);
	} else {
		// ERROR Response Bufer is NULL or Resoponse buffer size is 0
		goto error_msg_send_command;
	}
	// pthread_mutex_unlock(&KDAPI_device_write_lock_mutex);
	// Return success
	OSAL_unlock_mutex(KDAPI_device_write_lock_mutex);

	return 0;
	// Return error
      error_msg_send_command:
	// pthread_mutex_unlock(&KDAPI_device_write_lock_mutex);
	OSAL_unlock_mutex(KDAPI_device_write_lock_mutex);
	return -1;

}

/*
* get the L4M version from the firmware
*
* RETURN zero if success, -1 if failed
*/
static int get_L4M_version()
{
	struct i2400m_l3l4_hdr cmd;
	int res = 0;
	unsigned short response_from_driver[30];
	UINT32 tempByteWritten = 30;

	memset(&cmd, 0, sizeof(cmd));
	cmd.type = wimaxll_cpu_to_le16(I2400M_MT_GET_LM_VERSION);
	cmd.version = wimaxll_cpu_to_le16(I2400M_L3L4_VERSION);

	res =
	    send_recieve_message_to_driver(0, &cmd, sizeof(cmd), response_from_driver,
			       &tempByteWritten);

	return res;

}

// Kalyan 5.0.09 merge, this function is not required right now
#if 0
static KDAPI_RESULT SimulateInitCommandforEvp(unsigned short *InBuffer,
					      int InBufferSize,
					      unsigned short *OutBuffer,
					      int OutBufferSize,
					      UINT32 * pBytesWritten)
{

	// int res = 0;
	struct i2400m_l3l4_hdr *ack;
	struct i2400m_l3l4_hdr *cmd;

	if (OutBuffer == NULL) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ALERT, "OutBuffer is NULL");
		return KDAPI_NOT_ACTIVE;
	}
	ack = (struct i2400m_l3l4_hdr *)OutBuffer;
	cmd = (struct i2400m_l3l4_hdr *)InBuffer;
	// Null all the header
	memset(OutBuffer, 0, 12);
	*pBytesWritten = 12;
	ack->type = L4_L3_OPCODE_CMD_INIT;
	ack->length = 0;
	ack->version = cmd->version;
	ack->resv1 = cmd->resv1;
	ack->status = L3L4_RESPONSE_STATUS_SUCCESS_DONE;
	ack->resv2 = cmd->resv2;

	return KDAPI_SUCCESS;
}
#endif

/*
* Turn ON/Off the device radio
*
* RETURN zero if success, -1 if failed
*/
static KDAPI_RESULT turn_on_off_device_radio(unsigned short *InBuffer,
					int InBufferSize,
					unsigned short *Buffer,
					int OutBufferSize,
					UINT32 * pBytesWritten)
{

	int res = 0;
	//struct L3L4Header header;
	//int                   fd = socket(AF_INET, SOCK_DGRAM, 0);
	//struct besor_ioctl_context    ioctl_context;
	//struct ifreq          ifr;

	if (!turning_on_radio_for_first_time) {
		//printk("Set Mode to Normal \n");
		res = set_device_mode_to_normal();
		//if(res != TRUE)
		//      {
		//              return KDAPI_NOT_ACTIVE;
		//      }
		turning_on_radio_for_first_time = 1;
	}
	res =
	    send_recieve_message_to_driver(L4_L3_OPCODE_CMD_RF_CONTROL, InBuffer,
			       InBufferSize, Buffer, pBytesWritten);

	if (res != 0) {
		return KDAPI_NOT_ACTIVE;
	} else {
		return KDAPI_SUCCESS;
	}

}

/*
* This function calls send_recieive_message_to_driver to send and recieve L4 messages. In addition to that
*function calls seperate methods to that need more than just sending recieiving the message.
*
* RETURN zero if success, -1 if failed
*/
static KDAPI_RESULT KDAPI_send_io_control(IN void *pInBuffer,
					IN UINT32 inBufSize,
					OUT void *pOutBuffer,
					IN UINT32 outBufSize,
					OUT UINT32 * pBytesWritten,
					IN BOOL WaitOnIRP)
{
	//UINT32 waitRes;
	//UINT32 errorCode = ERROR_SUCCESS;
	//UINT32 notRealBytesWritten = 0;
	int ioctlRes;
	UINT32 res;
	unsigned short type;
	struct L3L4Header *header;
	UINT32 BytesWritten = 0;
	//RWL_LockWrite(&kdapiforlinuxLock);

	//printk("*");

	type = wimaxll_le16_to_cpu(*(unsigned short *)pInBuffer);
	printk("KK Ioctl Sending L4 Message type %d\n", type);

	TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG, "Sending DeviceIoControl with ioctl");

	header = (struct L3L4Header *)pInBuffer;

	if (type == L4_L3_OPCODE_CMD_RF_CONTROL) {
		res =
		    turn_on_off_device_radio(pInBuffer, inBufSize, pOutBuffer,
					outBufSize, &BytesWritten);
		if (res != KDAPI_SUCCESS) {
			printk("KK Ioctl Failed \n");
		}
		*pBytesWritten = BytesWritten;
		// pthread_mutex_unlock(&KDAPI_device_write_lock_mutex);
		// OSAL_unlock_mutex(KDAPI_device_write_lock_mutex);
		//RWL_UnlockWrite(&kdapiforlinuxLock);
		return res;
	}
#ifdef BLOCK_INIT_COMMAND_FOR_EVP
	if (type == L4_L3_OPCODE_CMD_INIT) {
		res =
		    SimulateInitCommandforEvp(pInBuffer, inBufSize, pOutBuffer,
					      outBufSize, &BytesWritten);
		*pBytesWritten = BytesWritten;
		if (res != KDAPI_SUCCESS) {
			printk("KK Ioctl Failed \n");
		}

		return res;
	}
#endif

	/*
	   if(header->Opcode == wimaxll_cpu_to_le16(L4_L3_OPCODE_SET_SCAN_PARAM))
	   {
	   //memset((char *)pInBuffer + 28, 0xff, 16);
	   }
	 */

	ioctlRes =
	    send_recieve_message_to_driver(wimaxll_le16_to_cpu(*(unsigned short *)pInBuffer), pInBuffer,
			       inBufSize, pOutBuffer, &BytesWritten);
	if (ioctlRes != 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
		      "DeviceIoControl() failed. error code = %x", ioctlRes);
		printk("KK Ioctl Failed \n");
		//RWL_UnlockWrite(&kdapiforlinuxLock);

		return KDAPI_NOT_ACTIVE;
	}

	*pBytesWritten = BytesWritten;
	//ioctlRes = ERROR_SUCCESS;
	//close(fd);
	//RWL_UnlockWrite(&kdapiforlinuxLock);

	return KDAPI_SUCCESS;
}

/*
* Set the device mode to normal
*
* TODO check this function is still required by the firmware
* RETURN zero if success, -1 if failed
*/
static int set_device_mode_to_normal()
{
	BOOL retStatus;
	char *message, retMsg[MAX_DATA_SIZE_SET_NORMAL];
	struct ModeOfOperationCommand modeCommand;
	struct L3L4Header header;
	int msgSize = 0;
	UINT32 retLen = 0;

	int res = 0;

	msgSize = sizeof(header) + sizeof(modeCommand);
	message = (char *)malloc(msgSize);
	if ((message == NULL)) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "malloc error");
		printk("malloc Error \n");
		return -1;
	}
	//assemble radio-on message
	//setup header
	header.Opcode = wimaxll_cpu_to_le16(L4_L3_OPCODE_CMD_MODE_OF_OPERATION);	//setup message type
	header.Length = wimaxll_cpu_to_le16(sizeof(struct ModeOfOperationCommand));	//setup message length. rest of the fields are irrelevant
	memcpy(message, (char *)&header, sizeof(header));

	//setup message body
	modeCommand.type = wimaxll_cpu_to_le16(L3L4_TLV_TYPE_MODE_OF_OPERATION);	//setup rf operatig_wmx_handleon TLV type
	modeCommand.length = wimaxll_cpu_to_le16(sizeof(struct RfControl) - 4);		//setup rf operation TLV length
	modeCommand.modeCommand = wimaxll_cpu_to_le32(E_MODE_OF_OPERATION_NORMAL);	//setup rf operation to ON
	memcpy(message + sizeof(header), (char *)&modeCommand,
	       sizeof(modeCommand));

	//send message down

	//retStatus = send_recieve_message_to_driver(L4_L3_OPCODE_CMD_MODE_OF_OPERATION,message, msgSize,retMsg, retLen);
	//send message down
	//retStatus = KDAPI_send_io_control((void *)message, msgSize, (void *)retMsg, retLen, &BytesWritten, 0);

	res =
	    send_recieve_message_to_driver(L4_L3_OPCODE_CMD_MODE_OF_OPERATION, message,
			       msgSize, retMsg, &retLen);
	//printk("KK ioctl RF COntrol %d return is %d \n",InBuffer[8], res);

	free(message);
	header = *(struct L3L4Header *)retMsg;
	if ((header.Status != wimaxll_cpu_to_le16(L3L4_RESPONSE_STATUS_SUCCESS_DONE))
	    && (header.Status != wimaxll_cpu_to_le16(L3L4_RESPONSE_STATUS_SUCCESS_IN_PROCESS))) {
		retStatus = 0;
		printk
		    ("Got status response other than SUCCESS_DONE or SUCCESS_IN_PROCESS\n");
	} else {
		retStatus = -1;
		printk("Got failed response from ioctl \n");
	}

	return retStatus;
}

#if 0
static void prepare_nl_iface()
{
	ssize_t result;
	//struct wimax_handle *wmx;
	struct i2400m_l3l4_hdr cmd, *ack;
	//struct wimax_msg_get_version *ack_get_version;

	/* open command: Send a raw request */
	memset(&cmd, 0, sizeof(cmd));
	cmd.type = wimaxll_cpu_to_le16(I2400M_MT_OPEN);
	cmd.version = wimaxll_cpu_to_le16(I2400M_L3L4_VERSION);
	result = wimaxll_msg_write(g_wmx_write_handle,NULL ,&cmd, sizeof(cmd));
	if (result < 0) {
		printk(stderr, "E: libwimax: can't send open message: %d\n",
		       result);
		return;
	}

	/* open command: get the ack */
	result = wimax_msg_read(g_wmx_read_handle, (void **)&ack);

	if (wimaxll_le16_to_cpu(ack->type) != I2400M_MT_OPEN) {
		printk(stderr,
		       "E: libwimax: wrong reply 0x%04x to OPEN command\n",
		       (ack->type));
		return;
	}
	wimaxll_msg_free(ack);
}
#endif

/*
*This function also gets L4M version from the device , except that there is no thread waiting
*for the response. This function waits in a loop for response. Used during initialization
*
* RETURN zero if success, -1 if failed
*/
static int get_L4M_version_no_thread()
{
	ssize_t result;
	//struct wimax_handle *wmx;
	struct i2400m_l3l4_hdr cmd, *ack;
	//struct wimax_msg_get_version *ack_get_version;

	/* get l4m version: Send a raw request */
	printk("get l4m version: Send a raw request \n");
	memset(&cmd, 0, sizeof(cmd));
	cmd.type = wimaxll_cpu_to_le16(I2400M_MT_GET_LM_VERSION);
	cmd.version = wimaxll_cpu_to_le16(I2400M_L3L4_VERSION);

	CHECK_NL_HANDLE();

	result = wimaxll_msg_write(g_wmx_write_handle, NULL,&cmd, sizeof(cmd));
	if (result < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
		      "Can't send get l4m version message: %d\n", result);
		return -1;
	}

	/* get l4m version: get the ack */

	while (1) {

		CHECK_NL_HANDLE();

		    result = wimaxll_msg_read(g_wmx_read_handle,NULL, (void **)&ack);
		if (result < 0) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
			      "Error wimax read messsage: %d\n", result);
			return -1;
		}
		if (wimaxll_le16_to_cpu(ack->type) == I2400M_MT_GET_LM_VERSION) {
			printk
			    ("Nlsock: correct reply 0x%04x to get l4m version command\n",
			     (ack->type));
			wimaxll_msg_free(ack);
			break;
		}
		wimaxll_msg_free(ack);
	}
	return 0;
}


static
int device_wait_fw_loaded(void)
{
	int result;
	struct i2400m_l3l4_hdr cmd;
	unsigned retry_count = 10;

#ifdef HAVE_WIMAXLL_STATE_GET
	/*
	 * Need to make sure the device is, at least, done loading
	 * firmware.
	 *
	 * We check the wimax_dev status, and if it is still below
	 * UNINITIALIZED, the firmware still hasn't fully loaded. In
	 * said case, we hold a wee bit and retry.
	 *
	 * NOTE: We could just wait for a callback, and wait on a
	 * completion, but I don't feel like messing with condvars in
	 * this environment.
	 */
	while (--retry_count) {
		result = wimaxll_state_get(g_wmx_handle);
		TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
		      "wimax_dev is in state %s (%d)\n",
		       wimaxll_state_to_name(result), result);
		if (result == -EOPNOTSUPP) {
			TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
			      "State-get not supported, trying other method\n");
			goto use_EL3RST;
		}
		if (result < 0) {
			syslog(LOG_ERR,
			       "Failed to read wimax_dev state: %d - %s\n",
			       result, strerror(-result));
			return -1;
		}
		if (result < WIMAX_ST_UNINITIALIZED) {
			TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
			      "wimax_dev is still in state %s (%d)\n",
			       wimaxll_state_to_name(result), result);
			/* FW upload can take a few secs, so this is ok */
			sleep(1);
		} else {
			TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
			      "wimax_dev is now in state %s (%d)\n",
			       wimaxll_state_to_name(result), result);
			break;
		}
	}
	if (retry_count == 0) {
		syslog(LOG_ERR,
		       "Waited too long for device to finish loading "
		       "firmware (transitioning out of DOWN state)\n");
		return -1;
	}
	return 0;

use_EL3RST:
#endif
	/*
	 * Hmm, the kernel doesn't support wimax-state-get; let's just
	 * send an inocuous command (get status report) until we don't
	 * get a -EL3RST back.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.type = wimaxll_cpu_to_le16(L4_L3_OPCODE_GET_STATE);
	cmd.version = wimaxll_cpu_to_le16(I2400M_L3L4_VERSION);

	retry_count = 10;
	while(--retry_count) {
		result = wimaxll_msg_write(g_wmx_write_handle, NULL,
					   &cmd, sizeof(cmd));
		if (result == 0) {
			TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
			      "wimax_dev is now accepting commands\n");
			break;
		}
		if (result == -EL3RST) {
			TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
			      "wimax_dev is still initializing\n");
			/* FW upload can take a few secs, so this is ok */
			sleep(1);
		}
		if (result < 0) {
			TRACE(TR_MOD_KDAPI_FOR_LINUX_NLSOCK, TR_SEV_INFO,
			      "wimax_dev returned error %d (%s) - retrying\n",
			      result, strerror(-result));
			/* FW upload can take a few secs, so this is ok */
			sleep(1);
		}
	}
	if (retry_count == 0) {
		syslog(LOG_ERR,
		       "Waited too long for device to finish loading "
		       "firmware (don't return -EL3RST to messages)\n");
		return -1;
	}
	return 0;
}


/*
*This function  This function waits in a loop for response. Used during initialization
*
* RETURN zero if success, -1 if failed
*/
static int init_device()
{
	ssize_t result;
	//struct wimax_handle *wmx;
	struct i2400m_l3l4_hdr cmd, *ack;
	//struct wimax_msg_get_version *ack_get_version;

	/* init device: Send a raw request */
	memset(&cmd, 0, sizeof(cmd));
	cmd.type = wimaxll_cpu_to_le16(L4_L3_OPCODE_CMD_INIT);
	cmd.version = wimaxll_cpu_to_le16(I2400M_L3L4_VERSION);

	CHECK_NL_HANDLE();

	    result = wimaxll_msg_write(g_wmx_write_handle,NULL, &cmd, sizeof(cmd));
	if (result < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
		      "Can't send init message: %d\n", result);
		printk("Can not send init messsage \n");
		return -1;
	}

	DumpHexString("Init device command L4_L3_OPCODE_CMD_INIT:", (unsigned char *)
			     &cmd,sizeof(struct i2400m_l3l4_hdr) );

	// Wait in the loop for the response
	// You may get the indication in between
	while (1) {

		CHECK_NL_HANDLE();

		    /* init device: get the ack */
		    result = wimaxll_msg_read(g_wmx_read_handle,NULL, (void **)&ack);
		if (result < 0) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
			      "Error wimax read message : %d\n", result);
			return -1;
			printk("Error wimax read message \n");
		}

		if ((ack->type) == wimaxll_cpu_to_le16(L4_L3_OPCODE_CMD_INIT)) {
			wimaxll_msg_free(ack);
			break;
		}
		wimaxll_msg_free(ack);
	}

	return 0;
}

static int preinit_device()
{
	// Request Fields
	UINT8 *requestBuffer;
	UINT32 requestBufferSize;
	L4BUFMAN_Status_t res;
	struct i2400m_l3l4_hdr *ack;

	// Response Fields
	UINT8 *responseBuffer;
	UINT32 responseBufferSize;
	char *OpcodeName;
	int result = 0;

	//GetState_type getState;
	SetPreInitConfiguration_type ledConfigurationStruct;
	L4BM_Init_SetPreInitConfiguration(&ledConfigurationStruct);
	if(!Populate_PreInitConfigurationStruct(&ledConfigurationStruct))
	{
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "there are no config param values");
		return -1;
	}

	// allocate the request buffer
	requestBufferSize = SetPreInitConfiguration_Funcs.getBufferSizeFunc( &ledConfigurationStruct );
	requestBuffer = (UINT8*)malloc( requestBufferSize );
	if (NULL == requestBuffer)
	{
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "pre config - malloc failed");
		return -1;
	}

	// fill the request buffer
	res = SetPreInitConfiguration_Funcs.setFunc( requestBuffer, &ledConfigurationStruct  );
	if (L4BUFMAN_ST_OK != res)
	{
		free(requestBuffer);
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "pre config - setFunc faild");
		return -1;
	}

	OpcodeName = GetL4Opcode(requestBuffer);
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "Op code name for preconfig=%s", OpcodeName);

	// allocate the response buffer
	responseBufferSize = SetPreInitConfiguration_Funcs.getMaxBufferSizeFunc();
	responseBuffer = (UINT8*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(requestBuffer);
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "wmx_GetSystemState - MALLOC FAILD");
		return -1;
	}

	CHECK_NL_HANDLE();

	result = device_wait_fw_loaded();
	if (result < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "failed to wait for fw loaded after 10 secs wait");
		return -1;
	}

	result = wimaxll_msg_write(g_wmx_write_handle,NULL,(const void *)requestBuffer, requestBufferSize);
	if (result < 0) {
	        TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Can't send init message: %d\n", result);
	        printk("Can not send init messsage \n");
		free(requestBuffer);
		free(responseBuffer);
		return -1;
	}

	DumpHexString("Init device command L4_L3_OPCODE_SET_PREINIT_CONFIG:", 
		      (unsigned char *)requestBuffer, requestBufferSize );

	// Wait in the loop for the response
	// You may get the indication in between
	while (1) {

		CHECK_NL_HANDLE();

		    /* init device: get the ack */
		    result = wimaxll_msg_read(g_wmx_read_handle,NULL, (void **)&ack);
		if (result < 0) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Error wimax read message : %d\n", result);
			free(requestBuffer);
			free(responseBuffer);
			printk("Error wimax read message \n");
			return -1;
		}

 		if ((ack->type) == wimaxll_cpu_to_le16(L4_L3_OPCODE_SET_PREINIT_CONFIG)) {
			wimaxll_msg_free(ack);
			break;
		}

		wimaxll_msg_free(ack);
	}

	free(requestBuffer);
	free(responseBuffer);

	return 0;
}

/*
*This function sends a stop trace command to firmware. Otherwise traces were flooding during
*initialization
*
* RETURN zero if success, -1 if failed
*/
static int stop_trace()
{
	ssize_t result;
	struct {
		struct i2400m_l3l4_hdr hdr;
		struct i2400m_tlv_hdr tlv;
		unsigned char val;
	} __attribute__ ((packed)) cmd;

	//struct i2400m_l3l4_hdr *ack;
	/* stop trace: Send a raw request */
	printk("stop trace: Send a raw request \n");
	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.type = wimaxll_cpu_to_le16(I2400M_MT_CMD_MONITOR_CONTROL);
	cmd.hdr.length = wimaxll_cpu_to_le16(sizeof(cmd) - sizeof(cmd.hdr));
	cmd.hdr.version = wimaxll_cpu_to_le16(I2400M_L3L4_VERSION);
	cmd.tlv.type = wimaxll_cpu_to_le16(0x4002);
	cmd.tlv.length = wimaxll_cpu_to_le16(1);
	cmd.val = 1;

	CHECK_NL_HANDLE();

	    result = wimaxll_msg_write(g_wmx_write_handle,NULL, &cmd, sizeof(cmd));
	if (result < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
		      "Can't send stop trace message: %d\n", result);
		return -1;
	}
	//FIXME:
	//Let us not wait for the return message
	//Driver is not sending the response
	/* stop trace: get the ack */
	/*while(1)
	   {
	   result = wimaxll_msg_read(g_wmx_read_handle,NULL, (void **) &ack);

	   if ((ack->type) == 0x5605) {
	   printk("Nlsock: Correct reply 0x%04x to stop trace command\n",
	   (ack->type));
	   wimaxll_msg_free(ack);
	   break;
	   }
	   wimaxll_msg_free(ack);
	   } */
	return 0;
}

/*
*This function takes hex buffer and prints in hex and char format to console.
*
* RETURN nothing
*
*NOTE
*Wimaxd needs to run in console mode and DEBUG_DEVELOPER macro need to be enabled to use this function
*/
//#ifdef DEBUG_DEVELOPER
static void print_hex(unsigned char *data, int data_len)
{
	char buffer[100];
	int lineLen = 16;
	int offset = 0;
	int i;

	memset(buffer, 0, sizeof(buffer));

	while (data_len > 0) {
		if (lineLen > data_len) {
			lineLen = data_len;
		}

		for (i = 0; i < lineLen; i++) {
			sprintf(&buffer[i * 3], "%02x ", data[offset + i]);
		}

		for (i = lineLen; i < 16; i++) {
			sprintf(&buffer[i * 3], "   ");
		}

		buffer[16 * 3] = ' ';

		for (i = 0; i < lineLen; i++) {
			if ((data[offset + i] > 0)
			    && (isprint(data[offset + i])))
				sprintf(&buffer[16 * 3 + 1 + i], "%c", data[offset + i]);
			else
				sprintf(&buffer[16 * 3 + 1 + i], "%c", '.');
		}

		buffer[16 * 3 + 1 + lineLen] = 0;
		printf("%s\n", buffer);
		offset += 16;
		data_len -= 16;
	}

}
//#endif

/*
*This function checks the incoming L3L4 message format. If the message is not proper, this function
* dumps the message.
*
* RETURN zero if success, -1 if failed
*/
int sanity_check_message_from_l3(const struct i2400m_l3l4_hdr *l3l4, size_t size)
{
	unsigned type, length, status, version;
	unsigned payload_ok = 1;
	const char *payload;

	if (size < sizeof(*l3l4)) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,"msg %p (%zu bytes): short header",
			l3l4, size);
		printk("msg %p (%zu bytes): short header \n", l3l4, size);
		return -1;
	}
	type = wimaxll_le16_to_cpu(l3l4->type);
	length = wimaxll_le16_to_cpu(l3l4->length);
	status = wimaxll_le16_to_cpu(l3l4->status);
	version = wimaxll_le16_to_cpu(l3l4->version);
	if (sizeof(*l3l4) + length > size) {
		payload = " (SHORT)";
		payload_ok = 0;
	}
	else if (sizeof(*l3l4) + length < size) {
		payload = " (LONG)";
		payload_ok = 1;
	}
	else {
		payload = "";
		payload_ok = 1;
	}
	if ( payload_ok == 0)
	{
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,"msg %p (%zu bytes): legth is zero or payload is not okay ",l3l4, size);
		printk("msg %p (%zu bytes): legth is zero or payload is not okay \n",l3l4, size);
		printk("payload %s", payload);
		return -1;
	}

	return 0;
}

/*
*This function sends the incoming L3L4 message to the layers above.
*If the message is an indication the indication call back function is called. If the message is
* L3L4 reply sempahore is signalled to wake up send_recieve_message_to_driver. If the message is
* of above then it is ERROR. This function still wakes up the send_recieve_message_to_driver with
* response buffer as NULL
*
* RETURN Nothing
*/
void send_msg_response_to_l4(const struct i2400m_l3l4_hdr *l3l4, size_t size)
{
	unsigned type, length, status, version;
	type = wimaxll_le16_to_cpu(l3l4->type);
	length = wimaxll_le16_to_cpu(l3l4->length);
	status = wimaxll_le16_to_cpu(l3l4->status);
	version = wimaxll_le16_to_cpu(l3l4->version);
	// int result = 0;
	UINT32 statusID = STATUS_INTEL_80216_CUSTOM;


	// static is safe here as callback from driver wont re-enter
	static STATUS_ENTRY statusEntry; 	// @@@ : JSS : New format of arguments for status indications to L4

	if (!(type & L3L4_INDICATION_MASK)) {
		TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
		      "Received Response Message From Driver: RESULT:%d LENGTH:%d",
		      size, length);
		send_rcv_msg = (struct i2400m_l3l4_hdr *)malloc(size);
		if (send_rcv_msg == NULL) {
		 	TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "malloc failed");
			return;
		}
		memcpy(send_rcv_msg, l3l4, size);
		rcv_msg_size = size;
#ifdef DEBUG_DEVELOPER
		printk(">>> Received Response Message From Driver\n");
		print_hex((unsigned char *)send_rcv_msg, size);
#endif

		// FIXME: Do we need to know is someone waiting for resonse or not
		//sem_getvalue(&sem_for_send_rcv_msg, &value);
		//printk("The value of the semaphors is %d\n", value);
		sem_post(&sem_for_send_rcv_msg);
		printk(" semphaore posted \n");
	} else if (type & L3L4_INDICATION_MASK) {
		TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
		      "Received Indicatoin Message From Driver");
#ifdef DEBUG_DEVELOPER
		printk(">>> Received Indicatoin Message From Driver %d\n",size);
		print_hex((unsigned char *)l3l4, size);
#else
    if(g_enable_driver_msg == TRUE) {
            printf("<<< [IND 0x%x][%d]\n", type, size);
            print_hex((unsigned char *)l3l4, size);
        }
#endif

		if (bEnableRawTracing) {
			DumpHexString
			    ("Gatekeeper (in - indication):", (unsigned char *)
			     l3l4, size);
#ifdef ENABLE_FW_TRACE_LOGGING
			if (*((UINT16 *)
			      l3l4) == 0xd003) {
				if (ptracefile != NULL) {
					fwrite (l3l4, sizeof(unsigned char), size, ptracefile);
				}
#endif
			}
		}
		// OSAL_lock_mutex(KDAPI_stop_sending_indications_mutex);
		// Check whether we can send indications are not
		if (KDAPI_status_ind_handler != NULL) {
			if (KDAPI_stop_sending_indications == FALSE) {
				//OSAL_unlock_mutex(KDAPI_stop_sending_indications_mutex);
				// Send indications
				printk("Sending indication above %d\n",size);

				//memset(&statusEntry, 0, sizeof(statusEntry));
				statusEntry.status = statusID;
				memcpy(statusEntry.statusBuf, l3l4, size);
				statusEntry.statusBufLen = size;
				KDAPI_status_ind_handler(&statusEntry);
			} else {
				TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
		      		"Not sending indication as KDAPI stop was called");
			}
		} else {
			TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
		      	"Not sending indication as indfunc was NULL");
		}

	} else {
		// Wrong message type from header
		// Forget it
		// FIXME: Continue or quit
		send_rcv_msg = NULL;
		rcv_msg_size = 0;
		sem_post(&sem_for_send_rcv_msg);

	}
}

/*
*This function sends the incoming TRACE message to the layers above.
*The indication call back function is called if any. Otherwise message is dropped
*
* RETURN Nothing
*/
void send_trace_response_to_l4(const struct i2400m_l3l4_hdr *l3l4, size_t size)
{
	static int print_trace = 0;
	if (KDAPI_trace_ind_handler != NULL) {
		print_trace = 0;
		if (KDAPI_stop_sending_traces == FALSE) {
			KDAPI_trace_ind_handler(size, (void *)l3l4 );
		} else {
			TRACE(TR_MOD_KDAPI, TR_SEV_ALL, "KDAPI was asked to stop sending traces");
		}
	} else {
		if (print_trace == 0) {
			TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG, "Trace_ind_handler is not registered");
			print_trace = 1;
		}
	}
}


/*
*This function is the call back for recieving device messages registered with wimax-tools.
*
* RETURNS  	if success zero
*		if error -1
*/
int driver_response_cb(struct wimaxll_handle *wmx,
	  void *_ctx,
	  const char *pipe_name,
			const void *data,
			size_t size )
{
	int result;
	printk("driver response callback is called \n");
	if (pipe_name != NULL) {
		result = sanity_check_message_from_l3(data, size);
		if (result < 0) {
			printk("Error in Msg is %s \n", pipe_name);
			return -1;
		}
		if (!strcmp(pipe_name, "msg")) {
			printk("Msg is %s \n", pipe_name);
			send_msg_response_to_l4(data, size);
		}
		else if (!strcmp(pipe_name, "trace")) {
			printk("Msg is %s \n", pipe_name);
			send_trace_response_to_l4(data,size);
		}
		else {
			printk("Msg is not trace and not msg %s \n", pipe_name);
			// Ignore the respnse
		}
	}
	else {
		printk("Pipe Msg is NULL \n");
		result = sanity_check_message_from_l3(data, size);
		if (result < 0) {
			printk("Error in Msg is %s \n", pipe_name);
			return -1;
		}
			printk("Msg is of name %s \n", pipe_name);
			send_msg_response_to_l4(data, size);
	}
	return 0;
}

/*
*This function Checks for any incoming message. If any wimaxll_recv is called to get the message.
*
* RETURNs if Success zero -- returns zero even if there nothing is recieved
* 	 if failed -1
*/
int check_for_indication_response(fd_set * p_read_fds, int * fd)
{
	int result = 0;
	// struct i2400m_l3l4_hdr *report_from_driver;
	// UINT32 statusID = STATUS_INTEL_80216_CUSTOM;
	// int fd;

	// TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "Waiting for the driver response");
	// printk("WMX_ETIMEDOUT: Waiting for driver response \n");
	CHECK_NL_HANDLE();

	// printk("Waiting for response \n");

	/* Read for ever, ctrl-c is good enough to finish... */
	result = select(FD_SETSIZE, p_read_fds, NULL, NULL, NULL);
	if (result < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "select failed: %m");
		printk("select failed \n");
		return -1;
	}
	if (FD_ISSET(*fd, p_read_fds) == 0)
	{
		// printk("Success \n");
		return 0;
	}
	// TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "got the driver response");
	printk("Got a response from driver going to check response \n");
	result = wimaxll_recv(g_wmx_read_handle);
	if (result < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "reading failed: %d", result);
		printk("wimaxll_recv failed \n");
		return -1;
	}
	return 0;
}

/*
*This function is a thread. Thread waits on thread kill event for zero seconds.
* If the event is triggered thread quits
*On time out, Then calls check_for_indication_response to see if there is an incoming message
*.
*
* RETURN Nothing
*/
static void *KDAPI_wait_for_data_from_driver_thread(void *lpParameter)
{
	int result = 0;
	int fd;
	fd_set pipe_fds, read_fds;

	fd = wimaxll_recv_fd(g_wmx_read_handle);
	FD_ZERO(&pipe_fds);
	FD_SET(fd, &pipe_fds);

	for (;;) {
		switch (OSAL_wait_event(KDAPI_thread_kill_event, 0)) {
		case 0:	// Stop
			{
				TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
				      "Stop Event Signaled - Thread Aborting");
				printk(" Stop Event called \n");
				return 0;
				break;
			}
		case WMX_ETIMEDOUT:
			{
				read_fds = pipe_fds;
				result = check_for_indication_response(&read_fds, &fd);
				if (result != 0) {
					return (void *)result;
				}
				break;
			}
		default:	//WAIT_FAILED
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Wait failed!");
			//pFuncs->pfnSendErrorReport(TR_MOD_KDAPI, INTERNAL_PROBLEM);TODO - handle this everywhere
			return (void *)0xFFFFFFFF;
		}		// end of switch

	}			// end of for loop
}

static void start_sending_indication()
{
	// start sending indications
	OSAL_lock_mutex(KDAPI_stop_sending_indications_mutex);
	KDAPI_stop_sending_indications = FALSE;
	OSAL_unlock_mutex(KDAPI_stop_sending_indications_mutex);

	if (use_traces) {
		// Start sending traces
		OSAL_lock_mutex(KDAPI_stop_sending_traces_mutex);
		KDAPI_stop_sending_traces = FALSE;
		OSAL_unlock_mutex(KDAPI_stop_sending_traces_mutex);
	}
}

static void stop_sending_indication()
{
	// stop sending indications
	OSAL_lock_mutex(KDAPI_stop_sending_indications_mutex);
	KDAPI_stop_sending_indications = TRUE;
	OSAL_unlock_mutex(KDAPI_stop_sending_indications_mutex);

	if (use_traces) {
		// stop sending traces
		OSAL_lock_mutex(KDAPI_stop_sending_traces_mutex);
		KDAPI_stop_sending_traces = TRUE;
		OSAL_unlock_mutex(KDAPI_stop_sending_traces_mutex);
	}
}

/*
*KDAPI_Start is called by ACT. KDAPI module starts sending indications after this
*.
* RETURN KDAPI_SUCCESS
*/
KDAPI_RESULT KDAPI_Start()
{
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Start (IN)");
	start_sending_indication();
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Start (OUT)");
	return KDAPI_SUCCESS;
}


/*
*KDAPI_Stop is called by ACT. KDAPI module stops sending indications after this
*.
* RETURNs Nothing
*/
void KDAPI_Stop()
{
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Stop (IN)");
	stop_sending_indication();
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Stop (OUT)");
}


/*
*KDAPI_Fini is called by KDAPI_ADAPTER. KDAPI module Fini uninitializes everything and
* frees the resources allocated
*.
* RETURN KDAPI_SUCCESS
*/
KDAPI_RESULT KDAPI_Fini()
{
	int ret = 0;
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Fini (IN)");

	OSAL_unlock_mutex(KDAPI_device_write_lock_mutex);
	OSAL_delete_mutex(KDAPI_device_write_lock_mutex);

	OSAL_unlock_mutex(KDAPI_stop_sending_indications_mutex);
	OSAL_delete_mutex(KDAPI_stop_sending_indications_mutex);

	sem_post(&sem_for_send_rcv_msg);
	sem_destroy(&sem_for_send_rcv_msg);

#ifdef ENABLE_FW_TRACE_LOGGING
	if (ptracefile != NULL) {
		fclose(ptracefile);
		ptracefile = NULL;
	}
#endif

	if ((g_wmx_read_handle) != NULL)
		wimaxll_close(g_wmx_read_handle);
	if(g_wmx_write_handle!= NULL)
		wimaxll_close(g_wmx_write_handle);

	OSAL_set_event(KDAPI_thread_kill_event);
	if (0 != driver_check_status_handle) {
		ret = OSAL_timedjoin_thread(driver_check_status_handle, SHUTDOWN_TIMEOUT, NULL);
		if (ret != 0) {
			OSAL_kill_thread(driver_check_status_handle);
		}
		driver_check_status_handle = 0;
	}

	OSAL_delete_event(KDAPI_thread_kill_event);
	KDAPI_thread_kill_event = NULL;
	KDAPI_status_ind_handler = 0;

	if (use_traces) {
		OSAL_unlock_mutex(KDAPI_stop_sending_traces_mutex);
		OSAL_delete_mutex(KDAPI_stop_sending_traces_mutex);
		KDAPI_stop_sending_traces = TRUE;
		KDAPI_trace_ind_handler = NULL;
	}

	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Fini (OUT)");
	return KDAPI_SUCCESS;

}

/*
*KDAPI_Connect is called by KDAPI_ADAPTER. KDAPI module Connect just checks if
*KDAPI is communicate with device or not
*.
* RETURNs  On Success KDAPI_SUCCESS
*	   On failure KDAPI_ERROR
*/
KDAPI_RESULT KDAPI_Connect()
{
	int ret;
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Connect (IN)");
	printk("Inside KDAPI_Connect.\n");

	ret = get_L4M_version();
	if (ret != 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ALERT, "Driver is not Accessible");
		goto error_wimax_open;
	}
	else {
		TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "Driver is Accessible");
	}

	printk("KDAPI_Connect - Success.\n");
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Connect (OUT)");
	return KDAPI_SUCCESS;
      error_wimax_open:
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Connect (OUT)");
	printk("KDAPI_Connect - Failed.\n");
	return KDAPI_ERROR;
}

/*
* Just a place holdder does nothing
*/
void KDAPI_Disconnect()
{
	// Do Nothing in Linux
}

/*
*This function tries to get a wimax handle with the device/driver. It tries to
* get a handle in a loop with a small delay. This is required as the on power up fimrware
* take some time to get into ready state. . This function is called KDAPI_Init
*
* RETURNs If Success zero
*	  If not -1
*/
int wimax_handle_open_in_loop()
{
	int i = 0;
	char ifname[DEFULT_STR_SIZE];

	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "wimax_handle_open_in_loop (IN)");

	linkup_redundant = 0;

	L4Configurations_getInterfaceName(ifname);

	for (i = 0; i < KDAPI_TRY_TO_OPEN_WMX_HANDLE; i++) {
		g_wmx_read_handle = wimaxll_open(ifname);
		if (g_wmx_read_handle != NULL) {
			TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "Successfully opened wimax nl read handle");
			g_wmx_write_handle = wimaxll_open(ifname);
			if(g_wmx_write_handle != NULL) {
				TRACE(TR_MOD_KDAPI, TR_SEV_INFO, " Successfully opened wimax nl write hanlde");
				return 0;
			}
			else {
				wimaxll_close(g_wmx_read_handle);
				TRACE(TR_MOD_KDAPI, TR_SEV_ALERT, "Could not open wimax nl write hanlde");
			}
		}
		OSAL_sleep(250); // Sleep for 250 msec
	}
	return -1;
}

/*
*This function is the main initialization function for KDAPI. It gets a wimax handle, intializes
*the hardware, initilaizes mutexs and sempahores and starts the thread to listen for incoming messages.
*
* RETURNs If Success KDAPI_SUCCESS
*	  If not KDAPI_ERROR
*/
KDAPI_RESULT
KDAPI_Init( KDAPI_StatusIndicationHandler	statusHandler,
	    KDAPI_TraceIndicationHandler	traceHandler,
	    char **				traceMsgBuffer,
	    PUINT32				detailedResult,
	    BOOL				withDebug)
{
	int ret;
	linkup_redundant = 0;
	use_traces = withDebug;

	TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG, "KDAPI_Init (IN)");
	printk("KDAPI Init Started \n");

	if (statusHandler == NULL) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Status handler is NULL");
		printk("status handler is NULL");
		goto exit_error;
	}

	KDAPI_status_ind_handler = statusHandler;
	KDAPI_stop_sending_indications = FALSE;

	ret = OSAL_create_mutex(&KDAPI_device_write_lock_mutex, 0, NULL);
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create device-write-lock mutex.");
		printk("Can't create device-write-lock mutex \n");
		goto exit_error;
	}

	ret = OSAL_create_mutex(&KDAPI_stop_sending_indications_mutex, 0, NULL);
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create stop-sending-indications mutex.");
		printk("Can't create stop-sending-indications mutex \n");
		goto exit_error_mutex;
	}

	ret = sem_init(&sem_for_send_rcv_msg, 0, 0);
	if (ret == -1) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create send-rcv-msg semaphore.");
		printk("Can't create send-rcv-msg sempahore \n");
		goto exit_error_sem;
	}

	ret = OSAL_create_event(&KDAPI_thread_kill_event, FALSE, FALSE, NULL);
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create thread kill event.");
		printk("Can't create thread kill event \n");
		goto exit_error_event;
	}

	printk("Calling the wimaxll_open function \n");
	ret = wimax_handle_open_in_loop();
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Unable to open Wimax handle");
		printk("Unable to opne wimax handle \n");
		goto exit_error_wmx_handle;
	}

#ifdef ENABLE_NETLINK_HANDLE_CHECKING
	memset(nl_handlecopy, 0, sizeof(nl_handlecopy));
	nl_handlecopy[5] = g_wmx_read_handle;
#endif

	ret = device_wait_fw_loaded();
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "failed to wait for fw loaded after 10 secs wait");
		goto exit_error_device;
	}
	//TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
	//      "Sending pre-Initilaize configuration command to the driver.");
	//ret = preinit_device();
	//if (ret < 0) {
	//	TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Unable to complete preinit device");
	//	goto exit_error_device;
	//}

	// Initialiazation routines for Device
	//TRACE(TR_MOD_KDAPI, TR_SEV_INFO,
	//      "Sending init command to the driver.");
	//ret = init_device();
	//if (ret < 0) {
	//	TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Unable to send init command to device");
	//	goto exit_error_device;
	//}

	ret = stop_trace();
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Unable to send stop trace command to device");
		goto exit_error_device;
	}

	ret = get_L4M_version_no_thread();
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Unable to send version query to device");
		goto exit_error_device;
	}

	ret = OSAL_create_thread(KDAPI_wait_for_data_from_driver_thread, NULL, &driver_check_status_handle);
	if (ret != 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create wait-for-data-from-driver thread");
		goto exit_error_device;
	}

	wimaxll_set_cb_msg_to_user(g_wmx_read_handle, driver_response_cb, NULL);

#ifdef ENABLE_FW_TRACE_LOGGING
	ptracefile = fopen(fw_trace_file, "w+");
#endif
	
	if(use_traces) {
		TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "trace is enabled. Initializing traces...");

		if (traceHandler == NULL) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR,"TRACE indication hanlder is NULL.");
			// TODO: WTPL: should it return failure or continue??
		}

		KDAPI_trace_ind_handler = traceHandler;
		KDAPI_stop_sending_traces = FALSE;

		ret = OSAL_create_mutex(&KDAPI_stop_sending_traces_mutex, 0, NULL);
		if (ret < 0) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create stop-sending-traces Mutex.");
			printk("Cannot create stop-sending-traces Mutex.\n");
			goto exit_error_trace_mutex;
		}
	} else {
		TRACE(TR_MOD_KDAPI, TR_SEV_ALERT, "trace is disabled");
	}

	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "init finished successfully.");
	TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG, "KDAPI_Init (OUT)");
	return KDAPI_SUCCESS;

exit_error_trace_mutex:
	KDAPI_trace_ind_handler = NULL;
	KDAPI_stop_sending_traces = TRUE;
      exit_error_device:
	wimaxll_close(g_wmx_read_handle);
	wimaxll_close(g_wmx_write_handle);
      exit_error_wmx_handle:
	OSAL_delete_event(KDAPI_thread_kill_event);
	KDAPI_thread_kill_event = 0;
      exit_error_event:
	sem_destroy(&sem_for_send_rcv_msg);
exit_error_sem:
	OSAL_delete_mutex(KDAPI_stop_sending_indications_mutex);
      exit_error_mutex:
	OSAL_delete_mutex(KDAPI_device_write_lock_mutex);
exit_error:
	KDAPI_stop_sending_indications = TRUE;
	KDAPI_status_ind_handler = NULL;
	printk("KDAPI Init failed \n");
	TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "init failed");
	TRACE(TR_MOD_KDAPI, TR_SEV_INFO, "KDAPI_Init (OUT)");
	return KDAPI_ERROR;
}

/*
*This function is called by KDAPI ADAPTER to send recieive messages. This function calls
*KDAPI_send_io_control and translates its error codes to error codes of KDAPI_ADAPTER
*
* RETURNs If Success KDAPI_SUCCESS
*	  If not
*		 KDAPI_BAD_ARGUMENTS -- if argumens are bad
		 KDAPI_NOT_ACTIVE -- if adapter is not active
*/
// pOIDBuf - INOUT buffer. Query's results will also be copied into this buffer.
//           Contains OID's struct and slack space incase the response for the
//           query is larger then the struct. OID's struct starts at buffer
//           offset 0.
// oidStructSize - The size of the OID's struct at the begining of the buffer
// oidBufSize - The size of the buffer including the OID's struct size.
//              Always bufSize >= oidStructSize
// pBytesWritten - Points to the number of bytes that were written
//                 by the driver to the pBuf and result of the query
KDAPI_RESULT KDAPI_SendQueryOID(UINT32 oidNum,
				void *pInBuf,
				void *pOutBuf,
				UINT32 oidStructSize,
				UINT32 oidBufSize,
				UINT32 * pBytesWritten, UINT32 * detailedResult)
{
	KDAPI_RESULT res = 0;
	//UINT32 inBufLen               = 0;
	//UINT32 totalBufLen    = 0;
	//PWCHAR pBuf = NULL;
	//UINT32 bytesWritten = 0;
	//U08* pData                    = 0;
	//UINT32 bytesWrittenAdjusted;
	//UINT32 bytesToCopy;

	if ((pInBuf == NULL) || (pOutBuf == NULL) || (oidStructSize < 0)
	    || (oidBufSize <= 0) || (pBytesWritten == NULL)) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR,
		      "Cannot send oid. Bad argument.");
		return KDAPI_BAD_ARGUMENTS;
	}

	if (oidNum == OID_INTEL_80216_CUSTOM) {
		TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG, "OID_INTEL_80216_CUSTOM");
		res = KDAPI_send_io_control(pInBuf,
					  oidStructSize,
					  pOutBuf,
					  oidBufSize, pBytesWritten, TRUE);
		if (res != ERROR_SUCCESS) {
			//free(pBuf);
			//pBuf = NULL;
			*detailedResult = res;
			printk("Send Rcv message Failure \n");
			return KDAPI_NOT_ACTIVE;
		}
		return KDAPI_SUCCESS;
	} else {
		// NDIS OIDs are not supported by Linux Driver
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "NDIS Oids are not supported");
		printk("NDIS Oids are not supported \n");
		return KDAPI_BAD_ARGUMENTS;
	}
}

/*
*This function is the main initialization function for KDAPI Trace adapter.
* And it hooks the trace hanlder function.
*
* RETURNs If Success KDAPI_SUCCESS
*	  If not KDAPI_ERROR
*/
KDAPI_RESULT KDAPI_TraceInit(IN KDAPI_TraceIndicationHandler traceHandler,
			     IN OUT char **msgBuffer,
			     OUT UINT32 * detailedResult)
{
	int ret;
	UNREFERENCED_PARAMETER(detailedResult);

	if (traceHandler == NULL) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "TRACE indication hanlder was NULL.");
	}

	KDAPI_stop_sending_traces = FALSE;

	ret = OSAL_create_mutex(&KDAPI_stop_sending_traces_mutex, 0, NULL);
	if (ret < 0) {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "Cannot create stop-sending-traces Mutex.");
		printk("Cannot create stop-sending-traces Mutex.\n");
		goto exit_error_mutex;
	}

	KDAPI_trace_ind_handler = traceHandler;
	return KDAPI_SUCCESS;
exit_error_mutex:
	printk("KDAPI Trace Init failed \n");
	KDAPI_stop_sending_traces = TRUE;
	TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "KDAPI Trace Init failed .");
	return KDAPI_ERROR;
}


/*
*KDAPI_TraceFinalize is called by KDAPI_ADAPTER. KDAPI_TraceFinalize uninitializes everything and
* frees the resources allocated
*.
* RETURN KDAPI_SUCCESS
*/
KDAPI_RESULT KDAPI_TraceFinalize()
{
	OSAL_unlock_mutex(KDAPI_stop_sending_traces_mutex);
	OSAL_delete_mutex(KDAPI_stop_sending_traces_mutex);
	KDAPI_stop_sending_traces = TRUE;
	KDAPI_trace_ind_handler = NULL;
	return KDAPI_SUCCESS;
}


/*
* Just a place holdder does nothing
*/
void KDAPI_TraceDisconnect()
{
	// Do Nothing for Linux
}

/*
* Just a place holdder does nothing
*/
KDAPI_RESULT KDAPI_TraceConnect()
{
	return KDAPI_SUCCESS;
}

/*
*KDAPI_TraceStop is called by ACT. KDAPI Trace module stops sending Trace indications after this
*.
* RETURN KDAPI_SUCCESS
*/
KDAPI_RESULT KDAPI_TraceStop()
{
	// Start sending indications
	OSAL_lock_mutex(KDAPI_stop_sending_traces_mutex);
	KDAPI_stop_sending_traces = TRUE;
	OSAL_unlock_mutex(KDAPI_stop_sending_traces_mutex);
	return KDAPI_SUCCESS;
}


/*
*KDAPI_TraceStart is called by ACT. KDAPI Trace module starts sending Trace indications after this
*.
* RETURN KDAPI_SUCCESS
*/
KDAPI_RESULT KDAPI_TraceStart()
{
	OSAL_lock_mutex(KDAPI_stop_sending_traces_mutex);
	// Start sending indications
	KDAPI_stop_sending_traces = FALSE;
	OSAL_unlock_mutex(KDAPI_stop_sending_traces_mutex);

	return KDAPI_SUCCESS;
}

/*
* Just a place holdder does nothing
*/
void KDAPI_ResetDevice()
{
	int ret;

	if (g_wmx_write_handle != NULL) {
		ret = wimaxll_reset(g_wmx_write_handle);
		if (ret < 0) {
			TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "device reset failed: ret=%d", ret);
		}
	}
	else {
		TRACE(TR_MOD_KDAPI, TR_SEV_ERR, "device reset failed - invalid handle");
	}
}	

/*
* Just a place holdder does nothing
*/
KDAPI_RESULT KDAPI_ClearDevice(OUT UINT32 * detailedResult)
{
	// TODO clear the device
	*detailedResult = KDAPI_SUCCESS;
	return KDAPI_SUCCESS;
}

/*
* Just a place holdder does nothing
*/
KDAPI_RESULT KDAPI_DriverStatusRegister( IN ULONG statusID, OUT PUINT32 detailedResult )
{
	// TODO::OSAL-WORK::IMPORTANT - KDAPI_DriversStatusRegister - to be implemented - new KDAPI interface
	return KDAPI_SUCCESS;

}

/*
* Just a place holdder does nothing
*/
KDAPI_RESULT KDAPI_DriverStatusUnRegister( IN ULONG statusID, OUT PUINT32 detailedResult )
{
	// TODO::OSAL-WORK::IMPORTANT - KDAPI_DriversStatusUnRegister - to be implemented - new KDAPI interface
	return KDAPI_SUCCESS;

}

KDAPI_RESULT KDAPI_RestartDriverConnection()
{
	Act_DriverDeviceStatus(DRIVER_DOWN);
	stop_sending_indication();
	start_sending_indication();
	Act_DriverDeviceStatus(DRIVER_UP);
}
