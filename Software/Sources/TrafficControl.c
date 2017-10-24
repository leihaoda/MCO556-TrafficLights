/// \file       TrafficControl.c
/// \author     William Huang
/// \brief      State machine for the traffic lights
///
/// \date       03/11/2016


//#define DEVELOPMENT

#include <hidef.h>      /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "TrafficControl.h"
#include "Lights.h"
#include "lcd.h"
#include "WalkRequest.h"
#include "StateTimeController.h"
#include "main.h"

/// Static function prototypes
static void Init(void);
static void StateNSRED4W(void);
static void StateNSLEFT(void);
static void StateNSGREEN(void);
static void StateNSWALKFLASH(void);
static void StateNSYELLOW(void);
static void StateEWRED4W(void);
static void StateEWGREEN(void);
static void StateEWWALK(void);
static void StateEWWALKFLASH(void);
static void StateEWYELLOW(void);
static void ChangeTimeGREEN(unsigned int timeNS, unsigned int timeEW);
static void ChangeTimeFLASH(unsigned int timeNS, unsigned int timeEW);
static void ChangeTimeYELLOW(unsigned int timeNS, unsigned int timeEW);

/// ====================== STATE MACHINE RELATED ================= ///
/// \brief Enumerating all states of the traffic control machine
typedef enum
{
    NS_RED4W,
    NS_LEFT,
    NS_GREEN,
    NS_WALKFLASH,
    NS_YELLOW,
    EW_RED4W,
    EW_GREEN,
    EW_WALK,
    EW_WALKFLASH,
    EW_YELLOW,
    NUM_STATES
}TRAFFICSTATES;

/// \brief Enumerating all inputs of the traffic control machine
typedef enum
{
    NOINPUT,
    TIMEUP,
    LEFTTURN,
    WALK_REQ,
    NUM_INPUTS
}TRAFFICINPUT;

/// \brief  Function pointer to be used to pointing to State functions
/// \sa     struct TRAFFICSTATE
typedef void (*pStateAction)(void);

/// \brief  Struct containing individual state information and settings
typedef struct
{
    pStateAction Action;
    unsigned int StateT_100ms;
    TRAFFICSTATES NextState[NUM_INPUTS];
}TRAFFICSTATE;

/// \brief  State Transition table for the traffic control state machine.
static TRAFFICSTATE TrafficStateTable[NUM_STATES] =
{
      //                       ===>  INPUTS TO NEXT STATE   <====
      // STATE ACTION     TIME       NOINPUT        TIMEUP              LEFTTURN        WALK_REQ  
        {&StateNSRED4W,     20,     {NS_RED4W,      NS_GREEN,           NS_LEFT,        NS_RED4W}       },  // North-South  4-Way Red
        {&StateNSLEFT,      40,     {NS_LEFT,       NS_GREEN,           NS_GREEN,       NS_LEFT}        },  // North-South  Left
        {&StateNSGREEN,     100,    {NS_GREEN,      NS_WALKFLASH,       NS_GREEN,       NS_GREEN}       },  // North-South  Green/Walk
        {&StateNSWALKFLASH, 30,     {NS_WALKFLASH,  NS_YELLOW,          NS_WALKFLASH,   NS_WALKFLASH}   },  // North-South  Green/Walk Flash
        {&StateNSYELLOW,    30,     {NS_YELLOW,     EW_RED4W,           NS_YELLOW,      NS_YELLOW}      },  // North-South  Yellow/NoWalk
        {&StateEWRED4W,     20,     {EW_RED4W,      EW_GREEN,           EW_RED4W,       EW_WALK}        },  // East-West    4-Way Red
        {&StateEWGREEN,     100,    {EW_GREEN,      EW_YELLOW,          EW_GREEN,       EW_GREEN}       },  // East-West    Green/Don't Walk
        {&StateEWWALK,      100,    {EW_WALK,       EW_WALKFLASH,       EW_WALK,        EW_WALK}        },  // East-West    Green/Walk
        {&StateEWWALKFLASH, 30,     {EW_WALKFLASH,  EW_YELLOW,          EW_WALKFLASH,   EW_WALKFLASH}   },  // East-West    Green/Walk Flash
        {&StateEWYELLOW,    30,     {EW_YELLOW,     NS_RED4W,           EW_YELLOW,      EW_YELLOW}      },  // East-West    Yellow/NoWalk
};


static TRAFFICSTATES   CurrentState;    /// \brief  Holder for name of current state
static TRAFFICSTATES   NextState;       /// \brief  Holder for name of next state
static TRAFFICINPUT    CurrentInput;    /// \brief  Holder for name of current input
static TRAFFICSTATES   PrevState;       /// \brief  Holder for name of previous state
static unsigned char   StateEntry;      /// \brief  Flag for determining if the state has been entered

volatile unsigned int timeCount = 0;    
unsigned char stateEntry = 0;                   
static unsigned char leftTurnFlag = 0;
static unsigned int stateTime;    // Actual time to stay in this state


/// ====================== LCD DISPLAY RELATED ================= ///
#define LCDMSG_WALK     "      WALK      "
#define LCDMSG_NOWALK   "   DON'T WALK   "
#define LCDMSG_NS       "N-S"
#define LCDMSG_EW       "E-W"
#define LCDLINE_NS      1U
#define LCDLINE_NS_MSG  2U
#define LCDLINE_EW      3U
#define LCDLINE_EW_MSG  4U

typedef enum
{
    NS,
    EW,
}TRAFFICDIRECTION;

volatile unsigned char lcdFlashFlag;
volatile unsigned char lcdFlashState;

/// \brief  Initializes the state machine.
/// 
/// \parblock
/// Initializes the state machine for traffic control. Initializes required peripherals used by the traffic lights intersection.
/// Initial state should be RED4WAY_NS.
///
/// \endparblock
static void Init(void)
{

    WalkRequest.Init();
    
    // Set starting state to North/South Red 4-Way, no input to state.
    CurrentState = NS_RED4W;
    CurrentInput = NOINPUT;
    StateEntry = 0;
}

/// \brief  Executes the state machine of the Traffic Control
void StateMachine(void)
{
    
        CurrentInput = NOINPUT;     // Need to set CurrentInput to NOINPUT befire executing state action
        TrafficStateTable[CurrentState].Action();   // Execute Current State Action
        NextState = TrafficStateTable[CurrentState].NextState[CurrentInput]; // Get Next State based on current input
        PrevState = CurrentState;   // Remember what was the previous state
        CurrentState = NextState;   // Set Current State to Next State
        
        WalkRequest.CheckRequest();
        
        
#ifdef DEVELOPMENT
        // Turn on LED if a walk request has been detected
        if(WalkRequest.GetRequestStatus())
        {
            LEDG_LED4 = 1;
        }
        else
        {
            LEDG_LED4 = 0;
        }
#endif

}

/// \brief  State for North-South 4-Way Red.
/// 
/// State duration is fixed 2 seconds
/// North/South and East/West lights are Red
/// North/South and East/West LCD is "DON'T WALK"
/// After time is up, determine if there is a left turn car in lane
///     If there is,    CURRENTINPUT = LEFTTURN
///     Otherwise,      CURRENTINPUT = TIMEUP
static void StateNSRED4W(void)
{
#define CAR_DETECT  SW_SW0
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateEntry = 1;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
    }
    
    // State Action
    Lights.CtlEW(1, 0, 0);
    Lights.CtlNS(1, 0, 0, 0);
    
    // State Exit Condition
    if(timeCount >= TrafficStateTable[NS_RED4W].StateT_100ms) 
    {
        stateEntry = 0;
        timeCount = 0;
        if(CAR_DETECT)
        {
            CurrentInput = LEFTTURN;
            leftTurnFlag = 1;
        }
        else
        {
            CurrentInput = TIMEUP;
        }
    }
}

/// \brief  State for North-South Green
///
/// State duration is fixed 4 seconds
/// North/South is RED with left turn GREEN and East/West lights are Red
/// North/South LCD is "WALK" and East/West LCD is "DON'T WALK"
static void StateNSLEFT(void)
{
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateEntry = 1;
        
        stateTime = TrafficStateTable[NS_LEFT].StateT_100ms;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
    }
    
    // State Action
    Lights.CtlEW(1, 0, 0);
    Lights.CtlNS(1, 0, 0, 1);
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief  State for North-South Green
///
/// State duration is variable from 10 to 20 seconds, less 4 seconds from left turn, less NS WALK Flash state
/// North/South is GREEN and East/West lights are Red
/// North/South LCD is "WALK" and East/West LCD is "DON'T WALK"
/// After time is up, CURRENTINPUT = TIMEUP (next state is NS_WALKFLASH)
static void StateNSGREEN(void)
{
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateEntry = 1;
        
        stateTime = TrafficStateTable[NS_GREEN].StateT_100ms;
        
        // Display WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_WALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // If left turn flag was set, decrease state time by NS_LEFT state time
        if(leftTurnFlag)
        {
            stateTime -= TrafficStateTable[NS_LEFT].StateT_100ms;
            leftTurnFlag = 0;
        }
        
        // Update actual time to stay in this state by subtracting from next state's time
        stateTime -= TrafficStateTable[NS_WALKFLASH].StateT_100ms;
    }

    // State Action
    Lights.CtlEW(1, 0, 0);
    Lights.CtlNS(0, 0, 1, 0);
    
    // State Exit Condition and Actions
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief  State for North-South Green and Walk Flashing
///
/// State duration is variable from 3 to 6 seconds, depending on ambient temperature
/// North/South is GREEN and East/West lights are Red
/// North/South LCD is "DON'T WALK", flashing at 1 HZ and East/West LCD is "DON'T WALK"
static void StateNSWALKFLASH(void)
{
    static unsigned char lcdDisplayMsg = 0;
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateEntry = 1;
        stateTime = TrafficStateTable[NS_WALKFLASH].StateT_100ms;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        lcdFlashFlag = 1;
    }
    
    // State Action
    Lights.CtlEW(1, 0, 0);
    Lights.CtlNS(0, 0, 1, 0);
    
    if(lcdFlashState)
    {
        lcdFlashState = 0;

        if(lcdDisplayMsg)
        {
            LCDclear(LCDLINE_NS_MSG);
            LCDline(LCDLINE_NS_MSG);
            LCDputs(LCDMSG_NOWALK);
        }
        else
        {
            LCDclear(LCDLINE_NS_MSG);
        }
        
        lcdDisplayMsg ^= 1;
    }
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        lcdFlashFlag = 0;
        CurrentInput = TIMEUP;
    }
}
/// \brief  State for North-South Yellow
///
/// State duration variable from 3 to 6 seconds as determined by temperature
/// North/South Lights is YELLOW, East/West Lights are RED
/// North/South and East/West LCD is "DON'T WALK"
static void StateNSYELLOW(void)
{
    if(!stateEntry)
    {
        stateEntry = 1;
        stateTime = TrafficStateTable[NS_YELLOW].StateT_100ms;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
    }
    
    // State Action
    Lights.CtlEW(1, 0, 0);
    Lights.CtlNS(0, 1, 0, 0);
    
    // State Exit Condition
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief  State for East-West 4-Way Red
///
/// East-West Red is ON, North South Red is ON.
/// East-West and North-South LCD "NO WALK"
/// Upon time up, check if a there is a walk request. if there is, move to EW_WALK state, otherwise move to EW_GEEN
static void StateEWRED4W(void)
{
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateEntry = 1;
        stateTime = TrafficStateTable[EW_RED4W].StateT_100ms;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
    }
    
    // State Action
    Lights.CtlEW(1, 0, 0);
    Lights.CtlNS(1, 0, 0, 0);
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        // Fork from WALK or NO WALK signal
        if(WalkRequest.GetRequestStatus())
        {
            CurrentInput = WALK_REQ;
        }
        else
        {
            CurrentInput = TIMEUP;
        }
    }
}

/// \brief  State for East-West Green/No Walk
///
/// EW green/No Walk state.
/// N-S Light is RED. E-W Light is Green
/// N-S LCD is "NO WALK". E-W LCD is "NO WALK"
static void StateEWGREEN(void)
{
    
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateTime = TrafficStateTable[EW_GREEN].StateT_100ms;
        stateEntry = 1;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
    }
    
    // State Action
    Lights.CtlEW(0, 0, 1);
    Lights.CtlNS(1, 0, 0, 0);
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief State for East-West Walk
///
/// E-W Light is Green and LCD is "WALK"
/// N-S Light is Red and LCD is "NO WALK"
static void StateEWWALK(void)
{
    
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateTime = TrafficStateTable[EW_WALK].StateT_100ms - TrafficStateTable[EW_WALKFLASH].StateT_100ms;
        stateEntry = 1;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_WALK);
        
        WalkRequest.ClearRequestStatus();
    }
    
    // State Action
    Lights.CtlEW(0, 0, 1);
    Lights.CtlNS(1, 0, 0, 0);
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief State for East-West Walk Flash
///
/// EW Light is Green, LCD is flashing "NO WALK"
/// NS Light is Red, LCD is "NO WALK"
static void StateEWWALKFLASH(void)
{
    static unsigned char lcdDisplayMsg = 0;
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateTime = TrafficStateTable[EW_WALKFLASH].StateT_100ms;
        stateEntry = 1;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        lcdFlashFlag = 1;
    }
    
    // State Action
    Lights.CtlEW(0, 0, 1);
    Lights.CtlNS(1, 0, 0, 0);
    
    if(lcdFlashState)
    {
        lcdFlashState = 0;

        if(lcdDisplayMsg)
        {
            LCDclear(LCDLINE_EW_MSG);
            LCDline(LCDLINE_EW_MSG);
            LCDputs(LCDMSG_NOWALK);
        }
        else
        {
            LCDclear(LCDLINE_EW_MSG);
        }
        
        lcdDisplayMsg ^= 1;
    }
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief  State for East-West Yellow
///
/// E-W Light is Yellow, LCD is "NO WALK"
/// N-S Light is RED, LCD is "NO WALK"
static void StateEWYELLOW(void)
{
    // State Entry
    // Execute this part of code once.
    if(!stateEntry)
    {
        stateTime = TrafficStateTable[EW_YELLOW].StateT_100ms;
        stateEntry = 1;
        // Display DON'T WALK on NS
        LCDclear(LCDLINE_NS_MSG);
        LCDline(LCDLINE_NS_MSG);
        LCDputs(LCDMSG_NOWALK);
        
        // Display DON'T WALK on EW
        LCDclear(LCDLINE_EW_MSG);
        LCDline(LCDLINE_EW_MSG);
        LCDputs(LCDMSG_NOWALK);
    }
    
    // State Aciton
    Lights.CtlEW(0, 1, 0);
    Lights.CtlNS(1, 0, 0, 0);
    
    // State Exit
    if(timeCount >= stateTime) 
    {
        stateEntry = 0;
        timeCount = 0;
        CurrentInput = TIMEUP;
    }
}

/// \brief Updates time of Green Light States
///
/// Update time for NS_GREEN, EW_GREEN, and EW_WALK
static void ChangeTimeGREEN(unsigned int timeNS, unsigned int timeEW)
{
    TrafficStateTable[NS_GREEN].StateT_100ms    = timeNS * 10;
    TrafficStateTable[EW_GREEN].StateT_100ms    = timeEW * 10;
    TrafficStateTable[EW_WALK].StateT_100ms     = timeEW * 10;
}

/// \brief Updates time of Green Light States
///
/// Update time for Don't walk flashing states. Can be either 3 or 5 seconds depending on ambient
static void ChangeTimeFLASH(unsigned int timeNS, unsigned int timeEW)
{
    TrafficStateTable[NS_WALKFLASH].StateT_100ms    = timeNS * 10;
    TrafficStateTable[EW_WALKFLASH].StateT_100ms    = timeEW * 10;
}

/// \brief Updates time of Green Light States
///
/// Update time for YELLOW states. Can be either 3 or 5 seconds depending on ambient
static void ChangeTimeYELLOW(unsigned int timeNS, unsigned int timeEW)
{
    TrafficStateTable[NS_YELLOW].StateT_100ms    = timeNS * 10;
    TrafficStateTable[EW_YELLOW].StateT_100ms    = timeEW * 10;
}

/// \brief Interface for TrafficControl
TrafficCTLInterface TrafficCTL = 
{
        &Init,
        &StateMachine,
        &ChangeTimeGREEN,
        &ChangeTimeFLASH,
        &ChangeTimeYELLOW
};
