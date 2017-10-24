/// \file       WalKRequest.c
/// \author     William Huang
/// \brief      walk request interface for traffic control state machine
///
/// \date       14/11/2016

#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative information */
#include "keypad.h"
#include "WalkRequest.h"

static void Init(void);
static void CheckRequest(void);
static unsigned char GetRequestStatus(void);
static void ClearRequestStatus(void);

static unsigned char requestStatus = 0;

/// \brief Initializes required modules for Walk Request
///
/// Walk request uses Keypad driver
static void Init(void)
{
    KPopen();
}

/// \brief Checks if there is a valid walk request
///
/// If a key has been hit and there are no outstanding requests, set a walk request.
static void CheckRequest(void)
{
    unsigned char keyPressed;
    if(KPhit() && !requestStatus)
    {
        keyPressed = KPgetch();
        // Determine if key hit is between '5' - '8'
        // If it is, then a walk has been requested. (Set walkRequested)
        // Otherwise no walk has been requested.
        if((keyPressed >= '5') && (keyPressed <= '8'))
        {
            requestStatus = 1;
        }
        else
        {
            requestStatus = 0;
        }
        
    }
    KPflush();  // Discard any keys pressed
    
}

/// \brief Returns to current status of the walk request
///
/// \return requestStatus
static unsigned char GetRequestStatus(void)
{
    return requestStatus;
}

/// \brief Clears the current status of the walk request
static void ClearRequestStatus(void)
{
    requestStatus = 0;
}

WalkReqInterface WalkRequest =
{
        &Init,
        &CheckRequest,
        &GetRequestStatus,
        &ClearRequestStatus
};
