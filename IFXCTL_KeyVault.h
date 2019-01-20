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

@file IFXCTL_KeyVault.h
@brief Get key value Interface

@date 2017
@version 1.0.4
*/

#ifndef __IFXCTL_KEYVAULT_H__
#define __IFXCTL_KEYVAULT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-- Include Section -------------------------------------------------*/
#include "IFXCTL_CommonData.h"
#include "IFXCTL_CmdBuilder.h"
#include "IFXCTL_Utils.h"

/*!
 * @addtogroup KEYVAULT
 * @{
 * Following are the details of the macros,structures and functions of KeyVault
 * @ingroup  PAL_MODULE
 */

/*-- Macro Definition -------------------------------------------------*/
/**
 * @brief Indicate the AES128 key length.
 */
#define KEY_AES128_LEN   16

/**
 * @brief Indicate the total keys present in the key vault for test suite.
 */
#if (KEY_VAULT==ENABLE)
#define TOTAL_KEYS		 0x0A
#else
#define TOTAL_KEYS		 12
#endif


/*-- Define Section --------------------------------------------------*/
/**
* @details Structure to hold Key id and key value
*/
typedef struct KeyPair
{
	uint16_t ui2KeyID;
	uint8_t rgui1KeyValue[KEY_AES128_LEN];
}KeyPair_t, *pKeyPair_t;

/*-- Extern Section --------------------------------------------------*/
extern const KeyPair_t g_rgsKeyValueTable[];

/*-- Program Section --------------------------------------------------*/

/**
	@details Interface used to get key value from Key Vault.

	@param[in] Pui2KeyID - Key Identifier
	@param[out] PpsKeyValue - Structure to hold key value and length

	@return   
		\li<B>API status code:</B>
		- @ref CTL_SUCCESS
		- @ref CTL_NULL_PTR	
		- @ref CTL_KEY_NOT_FOUND
*/
STATUS GetKeyValue(	_in_ uint16_t Pui2KeyID,
					_out_ pBlob_t const PpsKeyValue);

#ifdef __cplusplus
}
#endif

#endif /* __IFXCTL_KEYVAULT_H__*/

/*! @}*/
