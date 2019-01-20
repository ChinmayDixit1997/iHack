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

@file IFXCTL_CommsInt.h
@brief Interface to perform communication operations

@date 2017
@version 1.0.4
*/

#ifndef __IFXCTL_COMMSINT_H__
#define __IFXCTL_COMMSINT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-- Include Section -------------------------------------------------*/


/*!
 * @addtogroup COMMS
 * @{
 * @ingroup  PAL_MODULE
 */
 
/*-- Macro Definition -------------------------------------------------*/

/*-- Define Section --------------------------------------------------*/

/*-- Extern Section --------------------------------------------------*/

/*-- Program Section --------------------------------------------------*/

/**
	@details Interface used to open the communication channel.
	
	@param[in] Pprgui1ReaderName	- Communication reader name
	@param[in] Pprgui1CommsBuffer	- Comms buffer and size of this buffer should be size of the 
										CommunicationHandler_t structure
	@param[out] Ppui2Status			- Buffer to hold Api return status word
	
	Note: 1)This interface can be changed as per the platform.
		  2) passing NULL for the parameter Ppui2Status leads to NULL pointer exception,because NULL pointer check is not taken care

	@return   
		\li<B>API status code:</B>
		- @ref CTL_COMMS_SUCCESS
		- @ref CTL_NULL_PTR		

		\li<B>PAL Layer API status code:</B>
		- @ref CTL_COMMS_TXRX_ERROR
*/
pCommunicationHandler_t Comms_Open(_in_ const int8_t *Pprgui1ReaderName, _in_ uint8_t *Pprgui1CommsBuffer, _out_ uint16_t * Ppui2Status);

/**
	@details Interface used to reset the target. This interface supports both COLD and WARM reset operations.
	
	@param[in] PpsHandle - Communication handle
	@param[in] PeResetMode - Reset type : COLD or WARM reset
	@param[out] PpsATR - Structure hold ATR value
	
	Note: This interface can be changed as per the platform.

	@return   
		\li<B>API status code:</B>
		- @ref CTL_COMMS_SUCCESS
		- @ref CTL_NULL_PTR		

		\li<B>PAL Layer API status code:</B>
		- @ref CTL_COMMS_TXRX_ERROR
*/
STATUS Comms_Reset(_in_ pCommunicationHandler_t PpsHandle, _in_ ResetMode_t PeResetMode, _out_ pBlob_t PpsATR);

/**
	@details Interface used to close the communication channel.
	
	@param[in] PpsHandle - Communication handler
	
	Note: This interface can be changed as per the platform.

	@return   
		\li<B>API status code:</B>
		- @ref CTL_COMMS_SUCCESS
		- @ref CTL_NULL_PTR		

		\li<B>PAL Layer API status code:</B>
		- @ref CTL_COMMS_TXRX_ERROR
*/
STATUS Comms_Close(_in_ pCommunicationHandler_t PpsHandle);

#ifdef __cplusplus
}
#endif

#endif /* __IFXCTL_COMMSINT_H__*/

/*! @}*/
