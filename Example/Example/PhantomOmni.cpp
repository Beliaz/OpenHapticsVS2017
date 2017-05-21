/*****************************************************************************
* PhantomOmni.cpp
*   
* Description: This file initializes the haptic device, set up the callback function.
*   
* Computer Haptic Proseminar SS 2016
*
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************************/

/* Standard include*/
#include <iostream>

/* Openhaptic library */
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

using namespace std;

/*-----------------------------------------------------*/

/* Scheduler operation handle. */
HDSchedulerHandle gCallbackHandle = 0;

/*  End-effector position   */
hduVector3Dd position;

/*  End-effector velocity   */
hduVector3Dd velocity;
/*  Rendering force   */
hduVector3Dd force;

/* Maximum rendering force*/
const float MAX_FORCE = 2.0f;

/* Error infor*/
HDErrorInfo error;

/* Haptic device*/
HHD hHD;

/* Program control */
bool run = true;
char c;

/******************************************************************
/*
 * Saturation
 *
 * Saturate the output force to device for safety reason
 */
void Saturation(double *force){
    if (force[0]<-MAX_FORCE) force[0]=-MAX_FORCE;
    if (force[1]<-MAX_FORCE) force[1]=-MAX_FORCE;
    if (force[2]<-MAX_FORCE) force[2]=-MAX_FORCE;
    if (force[0]>MAX_FORCE) force[0]=MAX_FORCE;
    if (force[1]>MAX_FORCE) force[1]=MAX_FORCE;
    if (force[2]>MAX_FORCE) force[2]=MAX_FORCE;
}
/******************************************************************
* PhantomCallback
*
*
* Callback function for updating haptic effect 
/******************************************************************/
HDCallbackCode HDCALLBACK PhantomCallback(void *pUserData){

    /* Begin Haptic frame */
    hdBeginFrame(hdGetCurrentDevice());

    /* Get Omni device states */



    /* Calculating rendering force */


    /* Saturate rendering force */
    Saturation(force);

    /* Set rendering force to devices  */
    hdSetDoublev(HD_CURRENT_FORCE, force);  /* Temporary commented out for safety reason */

    /* End Haptic frame */
    hdEndFrame(hdGetCurrentDevice());

    /* Check if an error occurred while attempting to render the force */
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        cout << " Error during PhantomCallback!!!!" << endl;
        return HD_CALLBACK_DONE;
    }

    return HD_CALLBACK_CONTINUE;
}

int main(int argc, char* argv[])
{
    /* Initialize communication with device */
    hHD = hdInitDevice(HD_DEFAULT_DEVICE);
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to initialize haptic device");
        return -1;
    }
    /* Schedules an operation  */
    gCallbackHandle = hdScheduleAsynchronous(PhantomCallback, 0, HD_MAX_SCHEDULER_PRIORITY);

    /* Enable force output */
    hdEnable(HD_FORCE_OUTPUT);

    /* Start the haptic rendering loop. */
    hdStartScheduler();
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to start scheduler");
        return -1;
    }

    /* Waiting for exit*/
    cout << "Press Q(q) for exit.....!!" << endl;
    while (run){
        cin >> c;
        if ((c == 'Q') || (c == 'q'))
        {
            run = false;
        }
    }
    /* Stop scheduler*/
    hdStopScheduler();
    hdUnschedule(gCallbackHandle);
    return 0;
}
