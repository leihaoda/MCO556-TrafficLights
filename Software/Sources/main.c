/// \file       main.c
/// \author     William Huang
/// \brief      MCO556 Project - Traffic Control System.
///
/// \date       03/11/2016
///
/// \revisions
///     03/11/2016  - Shell of state machine
///     04/11/2016  - Added left turn state
///     08/11/2016  - Start walk states to display on LCD
///     10/11/2016  - Finished flashing of North/South and East-West walk
///     17/11/2016  - Imported SCI interface to incorporate PC control of timing
///     18/11/2016  - Finished processing info. from PC terminal to check if valid or invalid messages.
///     18/11/2016a - Updated timing of states after valid message completed.
///                     !!!!!Check if timing of state can be changed while in state!!!!
///     18/11/2016b - Added definitions SCI2_BAUD and SCI2_INT_ENABLE to common.h
///                 - Changed StateTimeControl.c to use these added definitions (inside init(void))
///                 - Started Traffic Counter module
///     21/11/2016  - Changed architecture to match system diagram
///                 - Started to add traffic count. :=> Clarify w/ GV every 15 or 30 seconds to upload? !!! -> 30 seconds !!!
///     21/11/2016a - NS Traffic Count Setup for 1 second..
///     21/11/2016b - Updated comments. Re-coded TrafficNSCount to GetCount(dir, buffer)
///                 - Added East West traffic count
///     22/11/2016  - Traffic Conut previously displayed numbers backward, now fixed it to display correctly
///                 - Started temperature sensor
///     22/11/2016a - Properly able to get temperature (-5 to +45 degree range) using XFER function
///     22/11/2016b - (Untested) : Added temperature to display on LCD
///                                 !! TESTED -> wrong position on LCD + previous characters left behind !!
///     22/11/2016c - (Untested) (Incl. 22/11/2016b) :
///                             !! TESTED and WORKS !!
///                         -   In TrafficControl.c, added static global variable 'static unsigned ints stateTime'
///                             to be used for each state to store the original time of each state.
///                             This should prevent sudden changes due to updating of state time from PC and temp. sensor.
///                   (Untested) : Added changing FLASH and YELLOW times based on ambient temperatured
///                             !! NOW TESTED IN 24/11/2016 version !!
///     24/11/2016  - Moved StateTimeISR to main file with associated flags
///                 - Handled rounding of temperature.
///                 - Tested changing of FLASH and YELLOW times based on ambient temperature
///                 - Correctly displaying temperature on LCD
///     24/11/2016a - Finished!!!!!!!!!!!!!
///
/// \bug
///     1 - (Unverified) Walk request sometimes not working. 
///         Suspect GROUND alligator clip is shorting to other test points, some of which are for the KEYPAD

#include <hidef.h>      /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "main.h"
#include "lcd.h"
#include "serial.h"
#include "Timer.h"
#include "analog.h"
#include "TrafficControl.h"
#include "StateTimeController.h"
#include "TrafficCounter.h"

#define PERIOD 15625U

unsigned char TempSensorFlag;	// Flag for Temperature Sensor
unsigned char TrafficCountFlag;	// Flag to send traffic data to PC
static unsigned char TrafficDataBuffer[6] = {2, '0', '0', '0', '0', 3}; // Initialize with STX - Empty Data (4 Bytes) - ETX

// Static Function Prototypes
static void Init(void);

void main(void)
{
    SOPT_COPE = 0;      // Disable watchdog
    Init();
    EnableInterrupts;   // Global Enable Interrupts
    
    for(;;)
    {

        // Run Traffic Controller State Machine
        TrafficCTL.StateMachine();      
        
        // Update state times depending on control terminal and temperature sensor
        // Temp sensor not implemented yet
        StateTimeCTL.UpdateStateTime();
        
        // Get Traffic Count and use SCI to send count to PC
        // !! VERY IMPORTANT !!
        // TrafficDataBuffer[1] and [2] for North South, TrafficDataBuffer[3] and [4] for East West
        // TrafficDataBuffer[0] for STX, TrafficDataBuffer[5] for ETX
        if(TrafficCountFlag)
        {
            TrafficCountFlag = 0;
            TrafficCounter.GetCount(1, &TrafficDataBuffer[2]);  // Get North South Count
            TrafficCounter.GetCount(0, &TrafficDataBuffer[4]);  // Get East West Count
            SCI2puts(TrafficDataBuffer);
        }
    }

}

/// !!DESCRIPTION HERE!
static void Init(void)
{
    // Configure Timer 2 to use Bus Clock / 8
    // Required for LCD and Keypad Operation
    TIM2_Open(BUS_CLK, 3, 0);
    LCDopen();
    LCDclear(0);
    
    // Iniially display NS on line 1 and EW on line 3
    LCDline(1);
    LCDputs("NS");
    LCDline(3);
    LCDputs("EW");
    
    // Configure Timer 1 to use Bus Clock / 128.
    // Disable interrupt and
    // Set Channel 2 and software output compare, comparing every 100ms. Used for timing systems
    TIM1_Open(BUS_CLK, 7, 0);       
    TIM1C2_Open(OUTPUT_COMPARE, OUTPUTCOMPARE_SOFTWARE, 1, PERIOD);
 
    SCI2open(2400, 1);
    
    TrafficCTL.Init();
    StateTimeCTL.Init();
    TrafficCounter.Init();
    
}

/// brief ISR for controlling various timings of the system.
///
/// Assumes output compare at every 0.1 seconds.
/// - Increase the state machine's timecount (timeCount) by 1
/// - If LCD flashing is required, increment flashTime.
///     - If flashTime reaches TOGGLETIME (5), meaning toggling at a rate of 0.5 Hz, set lcdFlashState to 1
///     - lcdFlashState is cleared outside of ISR
/// - Increment TrafficCountTime (used for timing of sending traffic data to PC)
///     - Set flag for traffic counter
/// - Increment TempCountTime (used for reading temperature sensor on ADC1)
///     - Set flag for temperature sensor adc reading
interrupt void StateTimeISR(void)
{
	#define TOGGLETIME  5U		// For LCD Flashing operations. Toggle display every 0.5second
	#define TRAFFICTIME 300U	// Send traffic count to PC every 30 seconds
	#define TEMPTIME	10U		// Start ADC sampling every 1 second
    static unsigned int TrafficCountTime;
    static unsigned char TempCountTime, FlashTime;
    
    TPM1C2SC_CH2F = 0;
    TPM1C2V += PERIOD;
    
    // For state machine
    timeCount++;
    
    // For LCD Dislay, if message flashing is required for that state
    if(lcdFlashFlag)
    {
        FlashTime++;
        if(FlashTime >= TOGGLETIME)
        {
            FlashTime = 0;
            lcdFlashState = 1;
        }
    }
    
    // For Traffic Data
    TrafficCountTime++;
    if(TrafficCountTime >= TRAFFICTIME)
    {
        TrafficCountFlag = 1;
        TrafficCountTime = 0;
    }
    
    // For Temperature Sensor
    TempCountTime++;
    if(TempCountTime >= TEMPTIME)
    {
		ADCstart(1);
        TempSensorFlag = 1;
        TempCountTime = 0;
    }

}
