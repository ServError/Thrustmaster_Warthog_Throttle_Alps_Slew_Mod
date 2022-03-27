

/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
*
* \brief  AVR290: Avoiding TWI Clock Stretching in ATtiny AVRs
*
*
* \par Application note:
*      AVR290:Avoiding TWI Clock Stretching in ATtiny AVRs
*
*
* \author
*      Name : Marv Kausch
*      Atmel Corporation: http://www.atmel.com \n
*      Support email: touch@atmel.com
*
* $Revision: 1.0 $
* $Date: 2011_02_23  $  \n
* Copyright (c) 2011, Atmel Corporation All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. The name of ATMEL may not be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
* SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

/************************************************************************//**
 * include files
****************************************************************************/
#include "avr/io.h"
#include "twi_slave.h"

                        
/* General TWI Master status codes */                      
#define TWI_ADDRESS_STOP_MATCH            0x40  // Address/Stop Match has received  
#define TWI_BUS_COLLISION                 0x08  // Bus Collision 
#define TWI_BUS_ERROR                     0x04  // Bus Error 
#define TWI_SLAVE_STATUS                  TWSSRA
#define TWI_RD_WR_DIR                     TWDIR
#define TWI_SLAVE_CTRLA                   TWSCRA
#define TWI_SLAVE_CTRLB                   TWSCRB
#define TWI_SLAVE_CMD0                    TWCMD0
#define TWI_SLAVE_CMD1                    TWCMD1
#define TWI_SLAVE_DATA                    TWSD
#define TWI_INTERFACE_ENAB                TWEN
#define TWI_SDI_HOLD_EANB                 TWSHE
#define TWI_DATA_INT_ENAB                 TWDIE
#define TWI_ADDR_STOP_INT_ENAB            TWASIE
#define TWI_STOP_INT_ENAB                 TWSIE


/*! \brief  TWI slave's initialization function
 *
 *  This function initializes the AVR TWI module to allow
 *  the TWI Master to write or read the Slave
 *  \note  The peripheral must be initialized in advance.
 *
 */
void twi_slave_initialise(void){    
   TWSA = (uint8_t)(TWI_ADDR << 1);     // Set TWI slave address. 
   TWI_SLAVE_DATA = 0xFF;               // Default content = SDA released.
   TWI_SLAVE_CTRLA = (uint8_t)((1<<TWI_INTERFACE_ENAB)|(1<<TWI_SDI_HOLD_EANB)|              // Enable TWI interface and release TWI pins.
           (1<<TWI_DATA_INT_ENAB)|(1<<TWI_ADDR_STOP_INT_ENAB)|(1<<TWI_STOP_INT_ENAB));      // Enable TWI Interrupts. No Stop interrupt
} 


/*! \brief  TWI Interrupt Service Routine
 *
 *Input  : twi_data_from_master();  gets data, sends it to main demo code\n
 *Output : twi_data_to_master(); gets data from main demo code, sends it to master via this ISR\n
 *
 *Asserts ACK, holds clock low until execution of a write to TWI_SLAVE_CTRLB register
 *
****************************************************************************/
ISR(TWI_SLAVE_vect)
{
        uint8_t status = TWI_SLAVE_STATUS & 0xC0;
        
        if (status & TWI_DATA_INTERRUPT) {
                if (TWI_SLAVE_STATUS & (1<<TWI_RD_WR_DIR)) {
                        /*Master Reads data from slave*/
                        TWI_SLAVE_DATA = twi_data_to_master(); // This function gets data from the application and loads it into the TWI_SLAVE_DATA (Two Wire Send Data) register             
                  
                        TWI_SLAVE_CTRLB = (uint8_t) ((1<<TWI_SLAVE_CMD1)|(1<<TWI_SLAVE_CMD0)); // release SCL
                } else {
                        /* Master Write */
                        /* Here we read the base address */
                        /* If the base address is with in the range save it, else NACK the Master */
                        TWI_SLAVE_CTRLB = (uint8_t) ((1<<TWI_SLAVE_CMD1)|(1<<TWI_SLAVE_CMD0));
                        twi_data_from_master(TWI_SLAVE_DATA);  // Callback function: data from master to application                       
                }
        } else if (status & TWI_ADDRESS_STOP_MATCH) {
                /* Address match can happen due to Collision */
                if (TWI_SLAVE_STATUS & TWI_BUS_COLLISION) {
                        /* Clear the Collision Flag */
                        TWI_SLAVE_STATUS = TWI_SLAVE_STATUS;
                        /* Wait for any Start Condition */
                        TWI_SLAVE_CTRLB = (uint8_t) (1<<TWI_SLAVE_CMD1);
                } else {
                        /* Address Match */
                        if (TWI_SLAVE_STATUS & (1<<TWAS)) {
                                /* Execute ACK and then receive next byte or set TWDIF to send the data */                      
                                TWI_SLAVE_CTRLB = (uint8_t)((1<<TWI_SLAVE_CMD1)|(1<<TWI_SLAVE_CMD0));
                                twi_address_callback();
                        }  else {
                                /* Stop Condition */
                                /* Wait for any Start Condition */
                                TWI_SLAVE_CTRLB = (uint8_t) (1<<TWI_SLAVE_CMD1);
								twi_stop_callback();
                        }
                }
        }
}

/*! \brief  TWI_bus_error_status function
 *
 *  Purpose: checks for any TWI bus error\n
 *  the TWI Master to write or read the Slave
 *  \note  The peripheral must be initialized in advance.
 *  no inputs or outputs
 *  A twi bus error will result in disabling TWI Interface and re-Initialising the TWI Slave
 */

void twi_bus_error_check (void)
{
   if (TWI_SLAVE_STATUS & TWI_BUS_ERROR)
   {
      /* Clear all Flags */
      TWI_SLAVE_STATUS = TWI_SLAVE_STATUS;
      /* Disable TWI Interface */
      TWSCRA = 0x00u;

      /* Re-Initialise TWI Slave */ 
      twi_slave_initialise();      
   }    
}
