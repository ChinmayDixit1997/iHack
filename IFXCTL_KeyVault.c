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

@file IFXCTL_KeyVault.c

@brief Get key value Interface

@date 2017
@version 1.0.4
*/

#include <stdio.h>
#include "IFXCTL_CommonData.h"
#include "IFXCTL_CmdBuilder.h"
#include "IFXCTL_KeyVault.h"

/*#if (CONFIG_SAM == SWSAM_ENABLE) */

const KeyPair_t g_rgsKeyValueTable[TOTAL_KEYS] =
{
#if (KEY_VAULT == ENABLE)
	{ 0x0001, { 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91 } }, /* Key ID = 0x0001 */
	{ 0x0002, { 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92 } }, /* Key ID = 0x0002 */
	{ 0x0003, { 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93 } }, /* Key ID = 0x0003 */
	{ 0x0004, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0004 */
	{ 0x0005, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0005 */
	{ 0x0006, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0006 */
	{ 0x0007, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0007 */
	{ 0x0008, { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F } }, /* Key ID = 0x0008 */
	{ 0x0009, { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F } }, /* Key ID = 0x0009 */
	{ 0x000A, { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F } }	/* Key ID = 0x000A */

#else
	{ 0x0001, { 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91 } }, /* Key ID = 0x0001 */
	{ 0x0002, { 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92 } }, /* Key ID = 0x0002 */
	{ 0x0003, { 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93 } }, /* Key ID = 0x0003 */
	{ 0x0004, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0004 */
	{ 0x0005, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0005 */
	{ 0x0006, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0006 */
	{ 0x0007, { 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73 } }, /* Key ID = 0x0007 */
	{ 0x0008, { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F } }, /* Key ID = 0x0008 */
	{ 0x0009, { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F } }, /* Key ID = 0x0009 */
	{ 0x000A, { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F } }, /* Key ID = 0x000A */
	{ 0x000B, { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F } }, /* Key ID = 0x000B */
	{ 0x000C, { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F } }  /* Key ID = 0x000C */
#endif
};


/*Implementation Note:-
 * - Search Key ID in the key vault
 * - If found copy the key value else return CTL_KEY_NOT_FOUND error
*/
/**
@brief Interface used to get key value from Key Vault.
*/
STATUS GetKeyValue(	_in_ uint16_t Pui2KeyID,
					_out_ pBlob_t const PpsKeyValue)
{
	uint16_t ui2LoopIndex;
	STATUS ui2RetStatus = CTL_KEY_NOT_FOUND;	
	
	do
	{
		#if (VALIDATE_NULL_PTR == ENABLE)
		if((NULL == PpsKeyValue) || (NULL == PpsKeyValue->prgui1Buffer) )
		{
			ui2RetStatus = CTL_NULL_PTR;
			break;
		}
	    #endif

		/* Loop is for the searching the key from the key vault with the given key id*/
		for (ui2LoopIndex = 0; ui2LoopIndex < TOTAL_KEYS; ui2LoopIndex++)
		{
			if (g_rgsKeyValueTable[ui2LoopIndex].ui2KeyID == Pui2KeyID)
			{
				PpsKeyValue->ui2Length = KEY_AES128_LEN;
				MemoryCopy(PpsKeyValue->prgui1Buffer, g_rgsKeyValueTable[ui2LoopIndex].rgui1KeyValue, KEY_AES128_LEN);
				ui2RetStatus = CTL_SUCCESS;
				break;
			}		
		}
	}while(CTL_FALSE);
	/*Return the status value */
	return ui2RetStatus;
}

/*#endif */ /*SWSAM_ENABLE */
