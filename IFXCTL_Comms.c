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

@file IFXCTL_Comms.c
@brief Interface to perform communication operations

@date 2017
@version 1.0.4
*/



#include "IFXCTL_CommonData.h"
#include "IFXCTL_PAL.h"

#if (CONNECTION_TYPE == PCSC)
/* lint -e(322) */
#include<winscard.h>
/* lint +e(322) */

#include "IFXCTL_Comms.h"
static SCARDCONTEXT hCardContext = 0;
static SCARDHANDLE  hCardHandle = 0;
SCARD_IO_REQUEST pgsProtocolTypeT0OrT1;
#endif



#if (CONNECTION_TYPE == PN532)
	
#include "Adafruit_PN532.h"

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
    @brief Interface used to open the communication channel.
*/
pCommunicationHandler_t Comms_Open(_in_ const int8_t *Pprgui1ReaderName, _in_ uint8_t *Pprgui1CommsBuffer, _out_ uint16_t * Ppui2Status)
{
	pCommunicationHandler_t PpsHandle;
	
	/*Set the communication handler to point to the input comms buffer */
	PpsHandle = (pCommunicationHandler_t)Pprgui1CommsBuffer;	
	
#if (CONNECTION_TYPE == CTL_PCSC)
	LPCVOID			lpRFU1 = NULL;
	LPCVOID			lpRFU2 = NULL;
	DWORD			dwActProtocol;
	DWORD			dwProtocol = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;


	/* Set the error status word */
	*Ppui2Status =  CTL_COMMS_TXRX_ERROR;


	do
	{		
		#if (VALIDATE_NULL_PTR == ENABLE)
			/*Validate the pointers for the NULL */
			if( (NULL == Pprgui1ReaderName)		|| 
				(NULL == Pprgui1CommsBuffer))
			{
				*Ppui2Status = CTL_NULL_PTR;
				break;
			}
		#endif

		/* Establish the context(scope) with which operations are performed */
		if( SCARD_S_SUCCESS != SCardEstablishContext((DWORD)SCARD_SCOPE_USER, lpRFU1, lpRFU2, &hCardContext)) 
		{
			break;
		}

		/* Establish the communication with the reader */
		if( SCARD_S_SUCCESS != SCardConnect(hCardContext, (LPCSTR)Pprgui1ReaderName, (DWORD)SCARD_SHARE_SHARED,
											dwProtocol, (LPSCARDHANDLE)&(PpsHandle->uiHandle),
											&dwActProtocol) )
		{
			break;
		}

		pgsProtocolTypeT0OrT1.cbPciLength = 0x08;
		pgsProtocolTypeT0OrT1.dwProtocol = dwActProtocol;

		/* Set the communication status value */
		*Ppui2Status = CTL_COMMS_SUCCESS;

	}while( CTL_FALSE );


#endif

#if (CONNECTION_TYPE == CTL_PN532)
	call_Adafruit_PN532_begin();
	uint32_t versiondata = call_Adafruit_PN532_getFirmwareVersion();
	// if (! versiondata) {
		// while (1); // halt
	// }

	// Set the max number of retry attempts to read from a card
	// This prevents us from waiting forever for a card, which is
	// the default behaviour of the PN532.
	call_Adafruit_PN532_setPassiveActivationRetries(0xFF);

	// // configure board to read RFID tags
	call_Adafruit_PN532_SAMConfig();
	
	/* Set the communication status value */
	*Ppui2Status = CTL_COMMS_SUCCESS;
		
#endif /*IFXCTL_USE_PCSC */

	/* Return the status value to the caller */
	return PpsHandle;
}


/**
    @brief Interface used to send command to target card and receive response for a command.
*/
STATUS TransReceive(_in_ pCommunicationHandler_t PpsHandle, _in_ pBlob_t PpsCommand, _out_ pBlob_t PpsResponse)
{
	/* Set the error status word */
	STATUS ui2RetStatus = CTL_COMMS_TXRX_ERROR;
#if (IFXCTL_USE_PCSC == ENABLE)
	
	LONG lstatus;
	DWORD ui4RspLength, ui4CmdLength;

    do
    {
		#if (VALIDATE_NULL_PTR == ENABLE)
			/* Validate for the null pointers*/
			if( (NULL == PpsHandle)					|| 
				(NULL == PpsCommand)				||
				(NULL == PpsCommand->prgui1Buffer)  ||
				(NULL == PpsResponse)				||
				(NULL == PpsResponse->prgui1Buffer) )
			{
				ui2RetStatus = CTL_NULL_PTR;
				break;
			}
		#endif

		ui4RspLength = PpsResponse->ui2Length;
		ui4CmdLength = PpsCommand->ui2Length;

		/* Send the command to the target card and receive the response for a command */
	    if( SCARD_S_SUCCESS != (lstatus = SCardTransmit((SCARDHANDLE)PpsHandle->uiHandle,
								&pgsProtocolTypeT0OrT1, PpsCommand->prgui1Buffer,
								ui4CmdLength, NULL, PpsResponse->prgui1Buffer, &ui4RspLength)))
		{
			break;
		}

		PpsResponse->ui2Length = (uint16_t)ui4RspLength;

        /* The response length should be at least the length of the status word(SW) which is 2 bytes */
        if( PpsResponse->ui2Length < RESP_SW_LEN )
        {
            break;
        }

		/* Set the status value */
        ui2RetStatus = CTL_COMMS_SUCCESS;
    }while( CTL_FALSE );

#endif

#if (CONNECTION_TYPE == CTL_PN532)
	uint8_t respLength = 255;
	call_Adafruit_PN532_inDataExchange
		(PpsCommand->prgui1Buffer, (uint8_t)PpsCommand->ui2Length, PpsResponse->prgui1Buffer, &respLength);
	PpsResponse->ui2Length = respLength;
    ui2RetStatus = CTL_COMMS_SUCCESS;	
#endif /*IFXCTL_USE_PCSC*/

	/* Return the status value to the caller */
    return ui2RetStatus;
}

/**
    @brief Interface used to reset the target. This interface supports both COLD and WARM reset operations.
*/
/*TODO: This interface need to enhance it for the COLD and WARM reset operations.*/
STATUS Comms_Reset(_in_ pCommunicationHandler_t PpsHandle, _in_ ResetMode_t PeResetMode, _out_ pBlob_t PpsATR)
{
#if (IFXCTL_USE_PCSC == ENABLE)
	DWORD			dwProtocol = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;
	DWORD			dwActProtocol = 1;
	LONG lstatus;
	DWORD ui4AtrLength;
	
	/* Set the error status word */
	STATUS ui2RetStatus = CTL_COMMS_TXRX_ERROR;

	do
	{
		#if (VALIDATE_NULL_PTR == ENABLE)
			/* Validate the null pointers*/
			if( (NULL == PpsHandle)				|| 
				(NULL == PpsATR)				||
				(NULL == PpsATR->prgui1Buffer) )
			{
				ui2RetStatus = CTL_NULL_PTR;
				break;
			}
		#endif

		if( SCARD_S_SUCCESS != (lstatus = SCardReconnect((SCARDHANDLE)PpsHandle->uiHandle, (DWORD)SCARD_SHARE_SHARED, dwProtocol,
											PeResetMode, &dwActProtocol)))
			break;

		pgsProtocolTypeT0OrT1.dwProtocol = dwActProtocol;

		/* Set the length of the input attribute */
		ui4AtrLength = PpsATR->ui2Length;

		/* This function retrieves the current reader attributes for the given handle */
		if( SCARD_S_SUCCESS != SCardGetAttrib ((SCARDHANDLE)PpsHandle->uiHandle, (DWORD)SCARD_ATTR_ATR_STRING, 
			PpsATR->prgui1Buffer, &ui4AtrLength) )
		{
			break;
		}

		PpsATR->ui2Length = (uint16_t)ui4AtrLength;
		
		/* Set the status value */
        ui2RetStatus = CTL_COMMS_SUCCESS;

	}while( CTL_FALSE );
	
	/* Return the status value to the caller */
	return ui2RetStatus;

#endif

#if (CONNECTION_TYPE == CTL_PN532)
	#define PN532_MIFARE_ISO14443A              (0x00)

	STATUS ui2RetStatus = CTL_COMMS_TXRX_ERROR;
	uint8_t success;
	
	uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned UID
	uint8_t uidLength;

	// Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
	// 'uid' will be populated with the UID, and uidLength will indicate
	// if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
	//success = call_Adafruit_PN532_readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
	
	success = call_Adafruit_PN532_inListPassiveTarget();
	
	if(success == 0x01)
		ui2RetStatus = CTL_SUCCESS;	
	
	return ui2RetStatus;
#endif /*IFXCTL_USE_PCSC */
}

/**
    @brief Interface used to close the communication channel.
*/
STATUS Comms_Close(_in_ pCommunicationHandler_t PpsHandle)
{
#if (IFXCTL_USE_PCSC == ENABLE)
	STATUS ui2RetStatus = CTL_COMMS_TXRX_ERROR;

	do
	{	
		#if (VALIDATE_NULL_PTR == ENABLE)
			/* Validate the null pointers*/
			if(NULL == PpsHandle)	
			{
				ui2RetStatus = CTL_NULL_PTR;
				break;
			}
		#endif

		if( SCARD_S_SUCCESS != SCardDisconnect((SCARDHANDLE)PpsHandle->uiHandle, (DWORD)SCARD_LEAVE_CARD ) )
		{
			break;
		}

		if( SCARD_S_SUCCESS != SCardReleaseContext(hCardContext) )
		{
			break;
		}

		/* Set the status value */
        ui2RetStatus = CTL_COMMS_SUCCESS;
	}while( CTL_FALSE );

	/* Return the status value to the caller */
	return ui2RetStatus;
#else
	/* Note: Parameter PpsHandle will not be used
	for cross compilation using KEIL C251,KEIL ARM and GCC */
	return 0x0;
#endif /*IFXCTL_USE_PCSC */
}

#ifdef __cplusplus
}
#endif
