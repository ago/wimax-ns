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
#define _XOPEN_SOURCE 600
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/sysinfo.h>


#include "wimax_osal_primitives.h"
#include "wimax_osal_trace.h"
#include "windows_error.h"
#include "wimax_consts.h"

#define TIMEVAL_TO_TIMESPEC(tv, ts)	{	\
	(ts)->tv_sec = (tv)->tv_sec;	\
	(ts)->tv_nsec = (tv)->tv_usec * 1000; 	\
}

extern int linux_to_wimax_err(int err);

struct master_event_internal
{
  pthread_cond_t master_cond_var;
  pthread_mutex_t master_cond_mutex; 
  pthread_mutex_t master_mutex;
};

struct event_internal
{
  struct master_event_internal * master_event;
  pthread_mutex_t null_protect_mutex; 
  volatile BOOL event_safe_delete;
  BOOL event;
  BOOL manual_reset;
  char * name;
  sem_t * named_sem;
};

//#define DEVELOPER_DEBUG 1
#ifdef DEVELOPER_DEBUG
#define printk printf
#else
#define printk(format, arg...)
#endif


int OSAL_create_event(OSAL_event_t* p_evt , BOOL manual_reset, BOOL initialState, char *name)
{

	if ( p_evt == NULL )
		return -1;

#ifdef WINDOWS_WAIT_METHODS
	
	*p_evt = CreateEvent(NULL, FALSE, FALSE, NULL);

	if ( *p_evt == NULL ) 
		return -1;

	return 0;
	
#else
	int oflag = O_CREAT;		// create if not existent else open it.
	mode_t mode = S_IRWXU;		// read, write, execute
	int ret = -1;

	struct event_internal * event = (struct event_internal *)calloc(1, sizeof( struct event_internal) );

	if ( event == NULL ) 
		return -1;


  // printf("create_lin_event \n");
  event->event = FALSE;
  event->master_event = NULL;
	pthread_mutex_init(&event->null_protect_mutex,NULL);
	event->event_safe_delete = TRUE;
	event->manual_reset = manual_reset;

	if ( name != NULL )
	{
		event->name = strdup(name);
		if ( event->name == NULL )
			goto exit;

		if ( (event->named_sem = sem_open(name, oflag, mode, 0)) == SEM_FAILED) 
		{
			ret = errno;
			goto exit;
		}
	}

	*p_evt = event;	


	// @@@ : JSS : Quick hack (should be reviewed in future)
	// If initialState is requested to be signalled, just set the event. 
	if (  initialState )
	{
		OSAL_set_event(*p_evt);	
	}

	ret = 0;
exit:
	if ( ret != 0 )
		if ( event->name != NULL)
			free(event->name);
	return ret;
#endif

}

int OSAL_create_event_with_security_attributes(OSAL_event_t* p_evt , BOOL manual_reset, BOOL initialState, char *name)
{
	return OSAL_create_event(p_evt , manual_reset, initialState, name);
}

// According to WIN this function should return non zero if succeeds
int OSAL_set_event(OSAL_event_t evt )
{
#ifdef WINDOWS_WAIT_METHODS

	return SetEvent(evt);

#else
	struct event_internal * event = (struct event_internal *)evt;

  // printf("set_lin_event \n");
  if(event == NULL)
    {
      printk("Invalid Input parameters\n");
      return -1;
    }


	if ( event->name != NULL )
	{
		int ret = sem_post(event->named_sem);

		if ( ret != 0 )
			OSALTRACE(OSAL_ERROR, ("Failed to post semaphore. Error: %d", errno));

		// This line is commented as
		// Now return is zero for success
		// ret = (ret == 0 );	// this method's return convention..
 
		return ret;			

    }

  if(event->master_event != NULL)
    {
			
      		if(pthread_mutex_trylock (&event->null_protect_mutex) == 0) {
      //printk("Setting the event and waking up the cond var \n");
      //Set the event
      			if ((event->master_event!=NULL)&&(pthread_mutex_lock(&event->master_event->master_mutex)!=0)) {
				event->event= TRUE;
      			
				goto exit_no_master_mutex;
			}
      				
      			
      event->event= TRUE;
	
     	if(event->master_event != NULL) {
				if (pthread_mutex_unlock(&event->master_event->master_mutex) != 0) {
					
      			
					goto exit_no_master_mutex;
				}
	} else {
		goto exit_no_master_mutex;
	}
			
      			

      // Fire the conditional variable
	if(event->master_event != NULL) {
				if(pthread_mutex_lock(&event->master_event->master_cond_mutex) != 0) {
					//printf("ERROR in mutex operations \n");
					goto exit_no_master_mutex;
				}
	} else {
		goto exit_no_master_mutex;
	}
			
      			
	if(event->master_event != NULL) {
				if(pthread_cond_signal(&event->master_event->master_cond_var)!=0) {
					//printf("ERROR in mutex operations \n");
					goto exit_no_master_mutex;
				}
	} else {
		goto exit_no_master_mutex;
	}
			
      			
	if(event->master_event != NULL) {
				if(pthread_mutex_unlock(&event->master_event->master_cond_mutex)!=0) {
					//printf("ERROR in mutex operations \n");
					goto exit_no_master_mutex;
				}
	} else {
		goto exit_no_master_mutex;
	}
		} else {
			event->event = TRUE;
			// return zero for success
			return 0;
		}
    	}
  	else {
      		printk("Setting the event variable \n");
     		event->event = TRUE;
		// return zero for success
		return 0;
    }
exit_no_master_mutex:
	pthread_mutex_unlock(&event->null_protect_mutex);
  // Return zero for sucess
  return 0;

#endif

}


// According to WIN this function should return non zero if succeeds
int OSAL_reset_event(OSAL_event_t evt)
{

#ifdef WINDOWS_WAIT_METHODS
	
	ResetEvent(evt);
#else

	struct event_internal *event = (struct event_internal *)evt;

   if(event == NULL)
    {
      printk("Invalid Input parameters\n");
      // return -1 for failure
      return -1;
    }


	if ( event->name != NULL )
	{
		if (event->manual_reset == TRUE) {
			int i = -1;
			int ret;
			// get the old value of teh semaphore
			if ((ret = sem_getvalue(event->named_sem, &i)) != 0) {
				return -1;
			}
			if (i > 0) {
				// just try wait and reduce tehe count
				if ((ret = sem_trywait(event->named_sem)) != 0) {
					return -1;
				}
				return 0;
			}
	}
	else
		return 0;

    }


	if ( event->name != NULL )
	{
		if (event->manual_reset == TRUE) {
			int i = -1;
			int ret;
			// get the old value of teh semaphore
			if ((ret = sem_getvalue(event->named_sem, &i)) != 0) {
				return -1;
			}
			while(i>0) {
				// just try wait and reduce tehe count
				if ((ret = sem_trywait(event->named_sem)) != 0) {
					return -1;
				}
				// decrement count	
				i--;
				
			}
				return 0;
	}
	else
		return 0;

	}
  	if(event->master_event != NULL) {
	
		if(pthread_mutex_trylock (&event->null_protect_mutex) == 0) {
      //printk("Setting the event and waking up the cond var \n");
      //Set the event
			if(pthread_mutex_lock(&event->master_event->master_mutex)!=0) {
				event->event= FALSE;
				//printf("ERROR in mutex operations \n");
				pthread_mutex_unlock(&event->null_protect_mutex);
				goto exit_no_master_mutex;
			}
      event->event= FALSE;
	  if(event->master_event != NULL){	
				if(pthread_mutex_unlock(&event->master_event->master_mutex)!=0) {
					//printf("ERROR in mutex operations \n");
					pthread_mutex_unlock(&event->null_protect_mutex);
					goto exit_no_master_mutex;
				}				
			}
			pthread_mutex_unlock(&event->null_protect_mutex);
		} else {
			event->event = FALSE;
	  }
      // Fire the conditional variable
      /*
	pthread_mutex_lock(&event->master_event->master_cond_mutex);
	pthread_cond_signal(&event->master_event->master_cond_var);
	pthread_mutex_unlock(&event->master_event->master_cond_mutex);
      */
    }
  else
    {
      printk("Setting the event variable \n");
      event->event = FALSE;
    }
exit_no_master_mutex:
  // Return zero for success
  return 0;
#endif

}

int OSAL_delete_event(OSAL_event_t evt)
{

#ifdef WINDOWS_WAIT_METHODS

	CloseHandle(evt);

#else
	struct event_internal *event = (struct event_internal *)evt;

   if(event == NULL)
    {
      printk("Input parameters are NULL \n");
      return -1;
    }

	
	if ( event->master_event != NULL )
	{
		int retries = 3;
		while (retries && (event->event_safe_delete == FALSE) )
		{
			OSAL_sleep(5);
			retries--;
		}
	}


  event->master_event = NULL;
  event->event = FALSE;
  while(pthread_mutex_destroy(&event->null_protect_mutex));
	if ( event->name != NULL )
	{
		sem_close(event->named_sem);

		free(event->name);
	}

	free(event);
  // return 0 for success
  return 0;

#endif 
}
int OSAL_wait_event (OSAL_event_t evt , unsigned int time_out_milli_sec)
{

#ifdef WINDOWS_WAIT_METHODS

	return WaitForSingleObject(evt, time_out_milli_sec);

#else

	struct event_internal * event = (struct event_internal *)evt;
	int ret, retVal;

  //printf("WaitForSingleEvent \n");
  if(event == NULL)
    {
      printk("Invaild input parameters \n");
      return -1;
    }


	if ( event->name != NULL )
	{
		if (time_out_milli_sec  <= 0) {
			ret = sem_trywait(event->named_sem);
		} else if (time_out_milli_sec == INFINITE) {
			// wait inifinate time and return with once get signaled
			ret  = sem_wait(event->named_sem);
		} else {
			struct timespec ts;
			struct timeval tv;

			gettimeofday(&tv, NULL);
			TIMEVAL_TO_TIMESPEC(&tv, &ts);

			// Split the incoming millisecs into seconds and nano-seconds struct
			//  as required by the timedjoin method

			ts.tv_sec += (time_out_milli_sec / 1000);
			ts.tv_nsec += ((time_out_milli_sec % 1000) * 1000 * 1000);	// 1 ms = 1000000 ns
		
			if (ts.tv_nsec >= 1000000000) {
				ts.tv_nsec -= 1000000000;
				++ts.tv_sec;
			}

			ret = sem_timedwait(event->named_sem, &ts);
		}
			
		if ( ret == 0  )
		{
			retVal = ret;
			OSALTRACE(OSAL_DEBUG, ("wait succeeded."));

			// If manual reset, post it right away so the event stays in signalled state
			if ( event->manual_reset == TRUE ) 
				sem_post(event->named_sem);
		}
		else
		{
			retVal = linux_to_wimax_err(errno);
			OSALTRACE(OSAL_DEBUG, ("wait failed/timed out. sem_xxxwait return is %d, errno: %d.", ret, errno));
		}

		return retVal;

    }

  printk("Calling WaitForMultipleEvents from WaitFromSingleEvent \n");
  return  OSAL_multiple_wait_event(1,&evt, FALSE, time_out_milli_sec);

#endif

}


// Note: 
// This do NOT handle named events yet... an error will be returned if a named event is passed to it.
int OSAL_multiple_wait_event(int count, OSAL_event_t evts[], BOOL wait_for_all_or_not, UINT32 time_out_milli_sec)
{

#ifdef WINDOWS_WAIT_METHODS

	return WaitForMultipleObjects(count, evts, wait_for_all_or_not, time_out_milli_sec);

#else
	struct event_internal **event = (struct event_internal **)evts;

  struct master_event_internal master;
  int res = WMX_EINVAL; 
  struct timespec delay;
  int i;
  
  unsigned char event_state[count];

  // printf("WaitForMultipleEvents \n");
  if((count == 0)||(event == NULL))
    {
      printk("Invalid input parameters \n");
      return res; 
    }
  for(i = 0;i < count; i++)
    {
      if(*(event+i) == NULL)
	{
	  printk("Invalid input parameters \n");
	  return res; 
	}
    }
  printk("Input Parameters count = %d wait for all = %d time_out_milli_sec = %d \n",count, wait_for_all_or_not, time_out_milli_sec);
  // Intialize master event
  pthread_mutex_init(&master.master_mutex, NULL);
  pthread_mutex_init(&master.master_cond_mutex, NULL);
  pthread_cond_init (&master.master_cond_var, NULL);

  // printk("time out %d", time_out_milli_sec);
  // Check whether any event was fired before calling this function
  pthread_mutex_lock(&master.master_mutex);  
  // to and with event states
  // First intialize event's master_event elements
  for(i = 0;i < count; i++)
    {
	(*(event + i))->event_safe_delete = FALSE;
      (*(event+i))->master_event = &master;
      // (*event+i)->event = FALSE;      
      // Initialize event state
      event_state[i] = 0;
    }
  if(wait_for_all_or_not==FALSE)
    {
      for(i = 0;i < count; i++)
	{
     	  // Check if something is already signalled
	  if((*(event+i))->event == TRUE)
	    {
	      res = i + WAIT_OBJECT_0;
	      goto exit_with_mutex_lock;
	    }
	  
	}
    }
  else
    {
      res = 1;
      // Check if all are signalled before 
      for(i = 0;i < count; i++)
	{
	  res = res & (*(event+i))->event;
	}
      if(res == 1)
	{
	  res =  0;	// successful wait
	  goto exit_with_mutex_lock;
	}
    }
  //None of the events are signalled before 
  pthread_mutex_lock(&master.master_cond_mutex);
  pthread_mutex_unlock(&master.master_mutex);
  
 
  // Check whether timeout is infinite or not
  // printk("time out %d", time_out_milli_sec);
  // printk("time out %d %d\n", time_out_milli_sec, INFINITE);

  int first_itreation = 1;
	
  if(time_out_milli_sec == INFINITE)
    {
      do
	{
	  // Take the mutex and wait on the conditional variable
	  //pthread_mutex_lock(&master.master_cond_mutex);
	  
	  if (!first_itreation) {
				pthread_mutex_lock(&master.master_cond_mutex);
			}
	  first_itreation = 0;
		
	  pthread_cond_wait(&master.master_cond_var,&master.master_cond_mutex);
	  pthread_mutex_unlock(&master.master_cond_mutex);
      
	  printk("Wokeup from infinite wait \n");
	  
	  // Check whether to wait on all or not
	  if(wait_for_all_or_not == FALSE)
	    {
	      pthread_mutex_lock(&master.master_mutex);
		for(i = 0;i < count; i++)
		{
		  if((*(event+i))->event == TRUE)
		    {
		      res = i + WAIT_OBJECT_0;
			if ( (*(event+i))->manual_reset == FALSE )
			      (*(event+i))->event = FALSE;

		    }
		  //(*(event+i))->master_event = NULL;	      
		}
	      pthread_mutex_unlock(&master.master_mutex);
	      goto exit_safe;
	    }
	  else
	    {
	      printk("Wait for all time = Infinite\n");
	      int exit_now = 1;
	      pthread_mutex_lock(&master.master_mutex);
	      for(i = 0;i < count; i++)
		{		  
		  if((*(event+i))->event == TRUE)
		    {
			if ( (*(event+i))->manual_reset == FALSE )
		      		(*(event+i))->event = FALSE;
		      //(*(event+i))->master_event = NULL;
		      event_state[i] = 1;
		    }		 		   
		  exit_now = exit_now & event_state[i];
		}
	     
	      pthread_mutex_unlock(&master.master_mutex);
	      if(exit_now == 1)
		{
		  res = 0;
		  goto exit_safe;
		}
	    }
	}while(1);
    }
  else // if time_out_milli_sec != INFINITE
    {
      struct timeval current_time;
      struct timeval starting_time;
	if (!first_itreation) {
				pthread_mutex_lock(&master.master_cond_mutex);
	}
	first_itreation = 0;
      // get the starting time store it even in the current time
      // if(wait_for_all_or_not != FALSE)
	 {
	   gettimeofday(&starting_time, NULL);
	   gettimeofday(&current_time, NULL);
	   printk("starting time sec %ld, usec %ld \n",starting_time.tv_sec, starting_time.tv_usec);
	 }
      do
	{
	  if(time_out_milli_sec/1000 > 0)
	    {
	      delay.tv_sec = current_time.tv_sec + time_out_milli_sec/1000;
	      delay.tv_nsec = current_time.tv_usec * 1000 + 1000 * 1000 * (time_out_milli_sec%1000);
	      if(delay.tv_nsec >= 1000000000)
		{
		  delay.tv_nsec -= 1000000000;
		  delay.tv_sec++;
		}
	      printk("delay in seconds  %ld nsec %ld \n", delay.tv_sec, delay.tv_nsec);	      
	    }
	  else
	    {
	      delay.tv_sec = current_time.tv_sec; 
	      delay.tv_nsec = current_time.tv_usec * 1000 + 1000 * 1000 * (time_out_milli_sec);
	      if(delay.tv_nsec >= 1000000000)
		{
		  delay.tv_nsec -= 1000000000;
		  delay.tv_sec++;
		}
	      printk("delay in seconds  %ld nsec %ld \n", delay.tv_sec, delay.tv_nsec);	
	    }
	  // pthread_mutex_lock(&master.master_cond_mutex);
	  printk("Delayed wait \n");
	  // pthread_cond_timedout takes absolute time
	  res = pthread_cond_timedwait(&master.master_cond_var,&master.master_cond_mutex,&delay);
	  pthread_mutex_unlock(&master.master_cond_mutex);
	  // if timed-out return 
	  if(res == ETIMEDOUT)
	     {
	       res = WMX_ETIMEDOUT;
	       printk("Wait is abandoned due to timeout\n");
	       goto exit_safe;
	     }
	  if(res == EINVAL)
	    {
	      res = WMX_EINVAL;
	      //printf("Wait is abandoned due to invalid absolute time passed \n");
	      //printf("The delay parameter to pthread_cond_timedwait is \n");
	      //printf("The delay_sec %ld, dleay_nsec %ld \n", delay.tv_sec, delay.tv_nsec);
	      goto exit_safe;
	    }
	      
	  if(wait_for_all_or_not == FALSE)
	    {
	      // if res!= ETIMEDOUT
	      printk("Wait for one within specified time \n");
	      pthread_mutex_lock(&master.master_mutex);
	      for(i = 0;i < count; i++)
		{
		  if((*(event+i))->event == TRUE)
		    {
		      res = i;	// TODO::Non-Critical @JSS - Find a better way of communicating these return codes so as not 
				// to get them confused with genuine error conditions/codes. 

			if ( (*(event+i))->manual_reset == FALSE ) {
		      		(*(event+i))->event = FALSE;
		    }
		    }
		 // (*(event+i))->master_event = NULL;	      
		}
	      pthread_mutex_unlock(&master.master_mutex);
	      goto exit_safe;
	    }	  
	  else
	    {
	      long time_elapsed_in_msec = 0;
	      gettimeofday(&current_time, NULL);
	      printk("Wait for all time = specified time\n");
	      int exit_now = 1;
	      pthread_mutex_lock(&master.master_mutex);
	      for(i = 0;i < count; i++)
		{		  
		  if((*(event+i))->event == TRUE)
		    {
			if ( (*(event+i))->manual_reset == FALSE ) {
		      		(*(event+i))->event = FALSE;
			}
		      //(*(event+i))->master_event = NULL;
		      event_state[i] = 1;
		    }		 		   
		  exit_now = exit_now & event_state[i];
		}
	     
	      pthread_mutex_unlock(&master.master_mutex);
	      if(exit_now == 1)
		{
		  res = 0;
		  goto exit_safe;
		}
	      // Calculate the time spent till now
	      time_elapsed_in_msec = 
		(current_time.tv_sec - starting_time.tv_sec)*1000
		+ (current_time.tv_usec - starting_time.tv_usec)/ 1000;
	      // I hope this never happens
	      if(time_elapsed_in_msec < 0 )
		{
		  time_elapsed_in_msec = 0;
		}
	      // Find out the time left
	      printk("time left %ld %ld", time_out_milli_sec, time_elapsed_in_msec);
	      time_out_milli_sec = time_out_milli_sec - time_elapsed_in_msec;
	      printk("time left %ld %ld", time_out_milli_sec, time_elapsed_in_msec);
	      if(time_out_milli_sec < 0)
		{
		   res = WMX_ETIMEDOUT;
		   printk("Wait is abandoned due to all the events are not set\n");
		   goto exit_safe;
		}
	    }
	}while(1);
      
    }

 
 exit_with_mutex_lock:  
  pthread_mutex_unlock(&master.master_mutex);
 exit_safe:
  //pthread_mutex_lock(&master.master_mutex);  
 
  
  delay.tv_sec = 0;
  delay.tv_nsec = 10;
  nanosleep(&delay, NULL);
 // OSAL_sleep(1);
  // to and with event states
  //  if(wait_for_all_or_not==FALSE)
  //{
  for(i = 0;i < count; i++)
    {
	pthread_mutex_lock(&((*(event+i))->null_protect_mutex));
      // Null all references to master event
	if ( (*(event+i))->manual_reset == FALSE )
      		(*(event+i))->event = FALSE;
      (*(event+i))->master_event = NULL;	   	 
	pthread_mutex_unlock(&((*(event+i))->null_protect_mutex));   	 
	(*(event + i))->event_safe_delete = TRUE; 
    }
  // }
  //pthread_mutex_unlock(&master.master_mutex);
	while (pthread_mutex_destroy(&master.master_mutex));  	
  	while (pthread_cond_destroy(&master.master_cond_var));
  	while (pthread_mutex_destroy(&master.master_cond_mutex));
  
 
  printk("Result of WaitForMultipleEvents %ld \n", res);
  return res;

#endif


}
