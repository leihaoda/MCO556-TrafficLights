/// \file       Timer.c
/// \author     William Huang
/// \brief      Interface for the Timer modules
///
/// \date       01/11/2016

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "common.h"
#include "Timer.h"

/// \brief Opens and configure Timer1 module.
///
/// Opens and configures Timer1 according to the parameters.
///
/// \param prescaler The prescaler used to divide the clock source. Prescaler = 2^n where n = 3-bit value
/// \param clockSource Selects clock source for the Timer. Disable = 0, 1 = Bus Clock, 2 = Disabled, 3 = External
/// \param interruptEn Enables or Disable timer interrupt on overflow. 0 = Disable,  1 = Enable
void TIM1_Open(TIM_CLK_SRC clockSource, unsigned char prescaler, unsigned char interruptEn)
{

    TPM1SC = 0x00;  // Resets Timer to known value
	TPM1SC = (interruptEn << 6) | (clockSource << 3) | (prescaler << 0);
	
}

/// \brief Configures Timer 1 Channel 1 module.
///
/// Configures Timer 1 Channel 1 module according to the parameters. 
/// Refer to datasheet page 37 for register and parameter descriptions.
/// 
/// \param  modeSelect      1 = Output compare
/// \param  edgeLevelSelect 0 = Software compare, 1 = Toggle output.
/// \param  interruptEn     0 = Disable, 1 = Enable
/// \param  chVal           16-bit value that sets the value for the channel counter
void TIM1C1_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal)
{
    TPM1C1SC = 0x00;
    TPM1C1SC = (modeSelect << 4) | (edgeLevelSelect << 2) | (interruptEn << 6);
    
    if(interruptEn) // Initially sets value channel counter
    {
        if (modeSelect == OUTPUT_COMPARE)
        {
            TPM1C1V = TPM1CNT + chVal;
        }
        TPM1C1SC_CH1F = 0;          // Clear flag
    }
}

/// \brief Configures Timer 1 Channel 2 module.
///
/// Configures Timer 1 Channel 2 module according to the parameters. 
/// Refer to datasheet page 37 for register and parameter descriptions.
/// 
/// \param  modeSelect      1 = Output compare
/// \param  edgeLevelSelect 0 = Software compare, 1 = Toggle output.
/// \param  interruptEn     0 = Disable, 1 = Enable
/// \param  chVal           16-bit value that sets the value for the channel counter
void TIM1C2_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal)
{
    TPM1C2SC = 0x00;
    TPM1C2SC = (modeSelect << 4) | (edgeLevelSelect << 2) | (interruptEn << 6);
    
    if(interruptEn) // Initially sets value channel counter
    {
        if (modeSelect == OUTPUT_COMPARE)
        {
            TPM1C2V = TPM1CNT + chVal;
        }
        TPM1C2SC_CH2F = 0;          // Clear flag
    }
}

/// \brief Configures Timer 1 Channel 0 module.
///
/// Configures Timer 1 Channel 0 module according to the parameters. 
/// Refer to datasheet page 37 for register and parameter descriptions.
/// 
/// \param  modeSelect      1 = Output compare
/// \param  edgeLevelSelect 0 = Software compare, 1 = Toggle output.
/// \param  interruptEn     0 = Disable, 1 = Enable
/// \param  chVal           16-bit value that sets the value for the channel counter
void TIM1C0_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal)
{
    TPM1C0SC = 0x00;
    TPM1C0SC = (modeSelect << 4) | (edgeLevelSelect << 2) | (interruptEn << 6);
    
    if(interruptEn) // Initially sets value channel counter
    {
        if (modeSelect == OUTPUT_COMPARE)
        {
            TPM1C0V = TPM1CNT + chVal;
        }
        TPM1C0SC_CH0F = 0;          // Clear flag
    }
}

/// \brief Opens and configure Timer 2 module.
///
/// Opens and configures Timer 2 according to the parameters.
///
/// \param prescaler The prescaler used to divide the clock source. Prescaler = 2^n where n = 3-bit value
/// \param clockSource Selects clock source for the Timer. Disable = 0, 1 = Bus Clock, 2 = Disabled, 3 = External
/// \param interruptEn Enables or Disable timer interrupt on overflow. 0 = Disable,  1 = Enable
void TIM2_Open(TIM_CLK_SRC clockSource, unsigned char prescaler, unsigned char interruptEn)
{

    TPM2SC = 0x00;  // Resets Timer to known value
    TPM2SC = (interruptEn << 6) | (clockSource << 3) | (prescaler << 0);
    
}

/// \brief Configures Timer 2 Channel 0 module.
///
/// Configures Timer 2 Channel 0 module according to the parameters. 
/// Refer to datasheet page 37 for register and parameter descriptions.
/// 
/// \param  modeSelect      1 = Output compare
/// \param  edgeLevelSelect 0 = Software compare, 1 = Toggle output.
/// \param  interruptEn     0 = Disable, 1 = Enable
/// \param  chVal           16-bit value that sets the value for the channel counter
void TIM2C0_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal)
{
    TPM2C0SC = 0x00;
    TPM2C0SC = (modeSelect << 4) | (edgeLevelSelect << 2) | (interruptEn << 6);
    
    if(interruptEn) // Initially sets value channel counter
    {
        if (modeSelect == OUTPUT_COMPARE)
        {
            TPM2C0V = TPM2CNT + chVal;
        }
        TPM2C0SC_CH0F = 0;          // Clear flag
    }
}
