
/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
*
* \brief  AVR290:avoid clock stretch with Tiny AVR
*
*
* \par Application note:
*      AVR290:avoid clock stretch with Tiny AVR
*
*
* \author
*      Name : Marv Kausch
*      Atmel Corporation: http://www.atmel.com \n
*      Support email: touch@atmel.com
*
* $Revision: 1.0 $
* $Date: 2011-03-02   $  \n
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
#include "avr/interrupt.h"

/*!TWI Address */
#define TWI_ADDR                          0x41 //0x20 //0xA0
  
#define TWI_DATA_INTERRUPT                0x80 


/************************************************************************//**
 * prototypes
****************************************************************************/
//void twi_slave_initialise( void );


/*!  \brief  TWI slave twi_data_to_master driver callback function
 * 
 *   This is an example of a command-specific response logic
 *   to demonstrate how the TWI driver gets data from the application main code
 *   Input: none
 *   Output: this function returns a value in count1 or ~count1 based on the
 *   value of command, previously sent from the master to the slave and this code
 */
uint8_t twi_data_to_master(void);


/*!  \brief  TWI slave twi_data_from_master driver callback function
 *
 *   This is an example oc command-specific response logic
 *   to demonstrate how the driver sends data back to the user's code
 *   The following function is called by the TWI slave when it gets data
 *   from the master.
 *   Input: data from master via the tiny20/40 slave
 *   Output: this function places data into the application code
 *
 */
void twi_data_from_master(uint8_t data);


/*! \brief  TWI slave's initialization function
 *
 *  This function initializes the AVR TWI module to allow
 *  the TWI Master to write or read the Slave
 *  \note  The peripheral must be initialized in advance.
 *
 */
void twi_slave_initialise( void );


/*! \brief  TWI Error Condition checking function
 *
 *  This function tests for errors due to mutiple TWI devices
 *  attempting to use the TWI bus at the same time.  I.e. collisions.
 *  \note  For this demo, only one Master is implimented.
 *
 */
void twi_bus_error_check(void);

void twi_stop_callback(void);

void twi_address_callback(void);
