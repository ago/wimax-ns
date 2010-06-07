/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
//
// Taken from ntstatus.h
//

#ifndef _SVSTATUS_
#define _SVSTATUS_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef WIN32_NO_STATUS // winnt
// begin_ntsecapi

/*lint -save -e767 */  // Don't complain about different definitions // winnt

//
// The success status codes 0 - 63 are reserved for wait completion status.
// FacilityCodes 0x5 - 0xF have been allocated by various drivers.
//
#define STATUS_SUCCESS                          (0x00000000L) // ntsubauth


//
// MessageId: STATUS_UNSUCCESSFUL
//
// MessageText:
//
//  {Operation Failed}
//  The requested operation was unsuccessful.
//
#define STATUS_UNSUCCESSFUL              (0xC0000001L)

//
// MessageId: STATUS_DEVICE_NOT_READY
//
// MessageText:
//
//  {Drive Not Ready}
//  The drive is not ready for use; its door may be open.
//  Please check drive %hs and make sure that a disk is inserted and that the drive door is closed.
//
#define STATUS_DEVICE_NOT_READY          (0xC00000A3L)

//
// MessageId: STATUS_NO_MORE_ENTRIES
//
// MessageText:
//
//  {No More Entries}
//  No more entries are available from an enumeration operation.
//
#define STATUS_NO_MORE_ENTRIES           (0x8000001AL)

//
// MessageId: STATUS_INVALID_PARAMETER
//
// MessageText:
//
//  An invalid parameter was passed to a service or function.
//
#define STATUS_INVALID_PARAMETER         (0xC000000DL)

//
// MessageId: STATUS_INVALID_BUFFER_SIZE
//
// MessageText:
//
//  The size of the buffer is invalid for the specified operation.
//
#define STATUS_INVALID_BUFFER_SIZE       (0xC0000206L)

//
// MessageId: STATUS_BUFFER_TOO_SMALL
//
// MessageText:
//
//  {Buffer Too Small}
//  The buffer is too small to contain the entry. No information has been written to the buffer.
//
#define STATUS_BUFFER_TOO_SMALL          (0xC0000023L)

//
// MessageId: STATUS_BUFFER_OVERFLOW
//
// MessageText:
//
//  {Buffer Overflow}
//  The data was too large to fit into the specified buffer.
//
#define STATUS_BUFFER_OVERFLOW           (0x80000005L)

//
// MessageId: STATUS_INVALID_PARAMETER
//
// MessageText:
//
//  An invalid parameter was passed to a service or function.
//
#define STATUS_INVALID_PARAMETER         (0xC000000DL)

//
// MessageId: STATUS_NOT_SUPPORTED
//
// MessageText:
//
//  The request is not supported.
//
#define STATUS_NOT_SUPPORTED             (0xC00000BBL)


/*lint -restore */  // Resume checking for different macro definitions // winnt
// end_ntsecapi

#endif // WIN32_NO_STATUS // winnt
#endif // _SVSTATUS_

