/**
 * @file softReset.cpp
 * @author Ashutosh Singh Parmar (ashutoshsingh291999@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#if defined( ARDUINO_AVR_UNO )
//#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)

#include "softReset.h"
#include "avr/interrupt.h"

/**
 * @brief : This function is used to jump execution to start of application section.
 * @param : None
 * @return : None
*/
void applicationReset( void )
{
    uint16_t ramend = RAMEND;
    uint8_t _sph = ( ramend << 8 ) & 0xff;
    uint8_t _spl = ramend & 0xff;

    uint8_t temp = 0x00;
  
    /* Disable interrupt response */
    cli();

    /* Clear all pending interrupts */

    /* Relocate interrupt vector table to starting of application section */
    MCUCR = 0x00;
    
    /* clear status register */
    asm( "out 0x3f, %0 \n\t" :: "r" (temp) );
    
    /* re-initialize stack pointer */
    asm(  "out 0x3d, %0 \n\t" \
          "out 0x3e, %1 \n\t" \
          :: "r" (_spl), "r" (_sph) );
    
    /* jump to start of application section (Reset handler)*/
    asm( "jmp 0 \n\t" :: );
}/*applicationReset*/

#else
#error This board type is NOT supported
#endif 
