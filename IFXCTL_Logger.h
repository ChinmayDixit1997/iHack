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

@file IFXCTL_Logger.h
@brief Interfaces to perform logging operations

@date 2017
@version 1.0.4
*/

#ifndef __IFXCTL_LOGGER_H__
#define __IFXCTL_LOGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-- Include Section -------------------------------------------------*/

/*!
 * @addtogroup LOGGER
 * @{
 * Following are the details of the macro definitions and interfaces of logger
 * @ingroup  PAL_MODULE
 */
 
#if (CONFIG_LOGGER == ENABLE)

/*Note: Please do not terminate the LOG_MSG with the semicolon to suppress the lint warning. 
Example: Use as LOG_MSG(g_psLoggerHandle,(uint8_t *)"Test Message")
*/
/**
 * @brief log the string message.
 */
#define LOG_MSG(_LOGHDL_,_STRING_MSG_)			/*lint -e534 */					\
												LogMessage(_LOGHDL_,_STRING_MSG_);	\
												/*lint +e534 */
/**
 * @brief log the byte array value in hex format.
 */
#define LOG_BYTARR(_LOGHDL_,_BLOB_T_)					/*lint -e534 */					\
														LogByteArray(_LOGHDL_,_BLOB_T_);	\
														/*lint +e534 */
/**
 * @brief log the byte array value in hex format by taking length and array as parameter
 */
#define LOG_BYTARR_LEN(_LOGHDL_,_UINT16_T_,_ARRAY_)					/*lint -e534 */					\
																	LogByteArrayLength(_LOGHDL_,_UINT16_T_,_ARRAY_); \
																	/*lint +e534 */
/**
 * @brief log the string message and the byte array value in hex format.
 */


#define LOG_MSG_BYTARR(_LOGHDL_,_STRING_MSG_,_BLOB_T_)			/*lint -e534 */					\
																LogMsgByteArray(_LOGHDL_,_STRING_MSG_,_BLOB_T_); \
																/*lint +e534 */

/**
 * @brief log the string message and the byte array value in hex format by taking length and array as parameter.
 */
#define LOG_MSG_BYTARR_LEN(_LOGHDL_,_STRING_MSG_,_UINT16_T_,_ARRAY_)	/*lint -e534 */					\
																		LogMsgByteArrayLength(_LOGHDL_,_STRING_MSG_,_UINT16_T_,_ARRAY_);	\
																		/*lint +e534 */

/**
	@brief Interface used to log the byte value in hex format.
*/
#define LOG_MSG_BYTE(_LOGHDL_,_STRING_MSG_,_UINT8_T_)				/*lint -e534 */					\
																	LogMsgByte(_LOGHDL_,_STRING_MSG_,_UINT8_T_); \
																	/*lint +e534 */
/**
	@brief Interface used to log the short value in hex format.
*/
#define LOG_MSG_SHORT(_LOGHDL_,_STRING_MSG_,_UINT16_T_)					/*lint -e534 */					\
																		LogMsgShort(_LOGHDL_,_STRING_MSG_,_UINT16_T_); \
																		/*lint +e534 */
/**
	@brief Interface used to log the integer value in hex format.
*/
#define LOG_MSG_INT(_LOGHDL_,_STRING_MSG_,_UINT32_T_)					/*lint -e534 */					\
																		LogMsgInt(_LOGHDL_,_STRING_MSG_,_UINT32_T_);	\
																		/*lint +e534 */

#else

#define LOG_MSG(_LOGHDL_,_STRING_MSG_)			/*lint -e534 */					\
												call_Println(_STRING_MSG_);	\
												/*lint +e534 */						
#define LOG_BYTARR(_STATUS_,_LOGHDL_,_BLOB_T_)	
#define LOG_BYTARR_LEN(_LOGHDL_,_UINT16_T_,_ARRAY_)
#define LOG_MSG_BYTARR(_LOGHDL_,_STRING_MSG_,_BLOB_T_)	
#define LOG_MSG_BYTARR_LEN(_LOGHDL_,_STRING_MSG_,_UINT16_T_,_ARRAY_)
#define LOG_MSG_BYTE(_LOGHDL_,_STRING_MSG_,_UINT8_T_)
#define LOG_MSG_SHORT(_LOGHDL_,_STRING_MSG_,_UINT16_T_)
#define LOG_MSG_INT(_LOGHDL_,_STRING_MSG_,_UINT32_T_)

#endif /* (CONFIG_LOGGER == ENABLE) */

/**
 * @brief Size of the Logger handler Buffer.This size is used to create one instance of the Logger handler buffer during initialization.
 */
#define CTL_LOG_BUF_SIZE							   sizeof(LoggerHandler_t)

/**
	@details Interface used to log the byte array value in hex format.
	
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] PpsByteArray - Byte array to be logged
	
	@return   
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR	- PpsLoggerHandle ,PpsByteArray and PpsByteArray->prgui1Buffer are NULL

*/
STATUS LogByteArray(_in_ const LoggerHandler_t * PpsLoggerHandle,
					_in_ const Blob_t * PpsByteArray);


/**
	@details Interface used to log the string message.
	
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] PpsMsg - string message to be logged
	
	@return   
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR	- PpsLoggerHandle ,PpsMsg are NULL

*/
STATUS LogMessage(_in_ const LoggerHandler_t * PpsLoggerHandle,
			  _in_ const uint8_t * PpsMsg);


/**
	@details Interface used to log the byte array value in string format.
	
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] PpsMsg - string message to be logged
	@param[in] PpsByteArray - Byte array to be logged
	
	@return   
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR	- PpsLoggerHandle ,PpsMsg, PpsByteArray and PpsByteArray->prgui1Buffer are NULL

*/
STATUS LogMsgByteArray(_in_ const LoggerHandler_t * PpsLoggerHandle,
					   _in_ const uint8_t * PpsMsg,
					   _in_ const Blob_t * PpsByteArray);

/**
	@details Interface used to log the byte array value in hex format by taking length and array .
	
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] Pui2Length - Length of message to be logged
	@param[in] PpsByteArray - Array of Byte data to be logged 
	
	@return 
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR - PpsLoggerHandle ,PpsByteArray are NULL

*/
STATUS LogByteArrayLength(	_in_ const LoggerHandler_t * PpsLoggerHandle,
							_in_ const uint16_t Pui2Length, 
							_in_ const uint8_t * PpsByteArray);

/**
	@details Interface used to log the byte array value in string format by taking length and Array as parameters.
	
	@param[in] PpsLoggerHandle	- Logger handle
	@param[in] PpsMsg			-  string message to be logged
	@param[in] Pui2Length		- Length of message to be logged
	@param[in] PpsByteArray		- Array of Byte data to be logged 
	
	@return 
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR - PpsLoggerHandle,PpsMsg ,PpsByteArray are NULL
	
	
*/
STATUS LogMsgByteArrayLength(	_in_ const LoggerHandler_t * PpsLoggerHandle,
								_in_ const uint8_t * PpsMsg,
								_in_ const uint16_t Pui2Length, 
								_in_ const uint8_t * PpsByteArray);

/**
	@details Interface used to log the byte value in hex format.
	
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] PpsMsg - string message to be logged
	@param[in] Pui1Byte - Byte value to be logged
	
	@return 
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR - PpsLoggerHandle ,PpsMsg are NULL

*/
STATUS LogMsgByte(	_in_ const LoggerHandler_t * PpsLoggerHandle,
					_in_ const uint8_t * PpsMsg,
					_in_ const uint8_t Pui1Byte);

/**
	@details Interface used to log the short value in hex format.
		
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] PpsMsg - string message to be logged
	@param[in] Pui2Short - Short value to be logged
	
	@return 
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR - PpsLoggerHandle ,PpsMsg are NULL
*/
STATUS LogMsgShort(	_in_ const LoggerHandler_t * PpsLoggerHandle,
					_in_ const uint8_t * PpsMsg,
					_in_ const uint16_t Pui2Short);

/**
	@details Interface used to log the integer value in hex format.
		
	@param[in] PpsLoggerHandle - Logger handle
	@param[in] PpsMsg - string message to be logged
	@param[in] Pui4Int - Integer value to be logged
	
	@return 
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR - PpsLoggerHandle ,PpsMsg are NULL
*/
STATUS LogMsgInt(	_in_ const LoggerHandler_t * PpsLoggerHandle,
					_in_ const uint8_t * PpsMsg,
					_in_ const uint32_t Pui4Int);
					
#ifdef __cplusplus
}
#endif

#endif /* __IFXCTL_LOGGER_H__*/
/*! @}*/
