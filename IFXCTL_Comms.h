/** THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". INFINEON
TECHNOLOGIES MAKES NO OTHER WARRANTY OF ANY KIND,WHETHER EXPRESS,IMPLIED OR,
STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.

THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. INFINEON TECHNOLOGIES
RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.

INFINEON TECHNOLOGIES SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.

(C)Copyright INFINEON TECHNOLOGIES All rights reserved

@file IFXCTL_Comms.h
@brief Interface to perform communication operations

@date 2017
@version 1.0.4
*/

#ifndef __IFXCTL_COMMS_H__
#define __IFXCTL_COMMS_H__

// #ifdef __cplusplus
// extern "C" {
// #endif

#include "IFXCTL_CommsInt.h"

/*-- Include Section -------------------------------------------------*/
/**
	@addtogroup PAL_MODULE
	
	@details Defines Interface to perform communication operations,logging operations,Sym Crypto operations,Key Vault operations

*/

/*!
 * @addtogroup COMMS
 * @{
 * Following are the details of the functions of communication module
 * @ingroup  PAL_MODULE
 */
 
/*-- Macro Definition -------------------------------------------------*/
/**
 * @brief Length of the status word.
 */
#define RESP_SW_LEN	  0x02

/**
 * @brief Size of Communication handler buffer.This size is used to create one instance of the communication handler buffer during initialization.
 */
#define CTL_COMMS_BUFF_SIZE		sizeof(CommunicationHandler_t)

/*-- Define Section --------------------------------------------------*/

/*-- Extern Section --------------------------------------------------*/

/*-- Program Section --------------------------------------------------*/

/**
	@details Interface used to send command to target card and receive response for a command.
	
	@param[in] PpsHandle - Communication handle
	@param[in] PpsCommand - Structure holds the command to be transmitted and total length of 
							bytes to be transmitted
	@param[out] PpsResponse - Structure hold response length and response APDU
	
	Note: The signature of this interface should not be changed since this function is invoked by interfaces of CIPURSE&trade; Terminal Library 
	
	@return   
		\li<B>API status code:</B>
		- @ref CTL_COMMS_SUCCESS
		- @ref CTL_NULL_PTR		

		\li<B>PAL Layer API status code:</B>
		- @ref CTL_COMMS_TXRX_ERROR
*/
STATUS TransReceive(_in_ pCommunicationHandler_t PpsHandle, _in_ pBlob_t PpsCommand, _out_ pBlob_t PpsResponse);

// #ifdef __cplusplus
// }
// #endif

#endif /* __IFXCTL_COMMS_H__*/

/*! @}*/
