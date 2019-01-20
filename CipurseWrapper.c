
#include "CipurseWrapper.h"


/* Buffer used for CBP communication */
uint8_t g_rgui1CommsCBPBuffer[CTL_COMMS_BUFF_SIZE];

/* Buffer to hold session manager, secure session and crypto API session information*/									 
uint8_t g_rgui1SMBuffer[CTL_SM_BUF_SIZE];

/* RAM buffer which is required to perform crypto operations */
uint8_t g_rgui1CryptoApiBuffer[CTL_CRYPTO_BUF_SIZE];

/* Buffer required to perform crypto operations*/
Blob_t g_sCryptoAPIBuffer;

/* Structure for holding the CBP and SAM communication handle*/
pCommunicationHandler_t g_psCommsCBPHandle;

/* Global pointer to the logger handle */
pLoggerHandler_t g_psLoggerHandle;

/* Global pointer to the session handle */
pSessionManager_t g_psSessionHandle;

/* Global pointer to the SYMCrypto handle */
pSymCryptoHandler_t g_psSYMCryptoHandle = NULL;

/* Handler for crypto API  */
uint8_t g_rgui1SYMCRYPTO[CTL_SIZE_Of_SYMCRYPTOHANDLR]= {0x00};


/**
    @brief Interface used to initialize the targets.
*/
STATUS InitializeTargets()
{
#define ATR_BUF_SIZE 30

	STATUS ui2RetStatus;
	uint8_t rgui1ATR[ATR_BUF_SIZE];
	Blob_t sATR;

	do
	{
		sATR.prgui1Buffer = rgui1ATR;
		sATR.ui2Length = sizeof(rgui1ATR);
		
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Establish communication with target(s) --------------");

	   /* Get the communication handle for reader CBP */
		g_psCommsCBPHandle = Comms_Open((int8_t *)NULL, g_rgui1CommsCBPBuffer, &ui2RetStatus);

		if(ui2RetStatus != CTL_SUCCESS)
			break;

		do
		{
		/*  Reset CBP Card */
			ui2RetStatus = Comms_Reset(g_psCommsCBPHandle, WARM_RESET, &sATR);
		}while(ui2RetStatus != CTL_SUCCESS);
		//if(ui2RetStatus != CTL_SUCCESS)
		//	break;

		g_psSYMCryptoHandle	= SymCrypto_Open(g_rgui1SYMCRYPTO, &ui2RetStatus);

		if(ui2RetStatus != CTL_SUCCESS)
			break;
		
		g_sCryptoAPIBuffer.prgui1Buffer = g_rgui1CryptoApiBuffer;
		g_sCryptoAPIBuffer.ui2Length = sizeof(g_rgui1CryptoApiBuffer);
		
		ui2RetStatus = InitializeSession(	&g_psSessionHandle,
											g_rgui1SMBuffer,
											eSW_SAM,
											eCIPURSE,
											g_psCommsCBPHandle,
											NULL,
											g_psLoggerHandle,
											g_psSYMCryptoHandle,
											NULL,
											&g_sCryptoAPIBuffer);	
	}while(CTL_FALSE);
	
	return ui2RetStatus;

#undef ATR_BUF_SIZE
}


/**
    @brief Interface to perform CIPURSE Mutual Authentication.
*/
STATUS PerformAuthentication(uint16_t key_number)    
{	
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	KeyDiversificationInfo_t g_sAuthKeyInfo;

	/* Authenticate with PRIVACY_KEY  */
    g_sAuthKeyInfo.ui2KeyID = key_number;
    g_sAuthKeyInfo.psDiversificationData = NULL;
    g_sAuthKeyInfo.eDiversificationMode = eNO_KEY_DIVERSIFICATION;

    LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Perform Authentication  --------------");
    ui2RetStatus = EstablishSecureChannel(key_number, &g_sAuthKeyInfo, &ui2StatusWord);
	if(ISO_STATUS_OK != ui2StatusWord)
      ui2RetStatus = CTL_INT_ERROR;
  
	return ui2RetStatus;  
}

/**
    @brief Interface to configure secure message level.
*/
STATUS ConfigureSetSMIValue(SMLevel_t eSMLevel)
{
	return SetSMIValue(eSMLevel);
}

/**
    @brief Interface to Select an CIPURSE Application.
*/
STATUS SelectApplication(Blob_t * p_aid_value)
{
	STATUS ui2RetStatus = CTL_INT_ERROR;
	uint16_t ui2StatusWord = 0x0000;
	uint8_t response_data[20];
	ApduResponse_t g_sRAPDU;
		
	g_sRAPDU.prgui1Buffer = response_data;
    g_sRAPDU.ui2Length = 20;
	
	LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Select an Application  --------------");
    ui2RetStatus = SelectFileByAID(SELECT_P2_00, p_aid_value, (int16_t)LENOTREQUIRED, &g_sRAPDU);
    READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
    if(ui2StatusWord != ISO_STATUS_OK)
		ui2RetStatus = CTL_INT_ERROR;
    return ui2RetStatus;
}


/**
    @brief Interface to perform read operation on binary file.
*/
STATUS PerformReadBinary(uint16_t file_id, uint16_t file_offset, uint16_t bytes_to_read, pApduResponse_t response_data)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	uint16_t responsedata_length = response_data->ui2Length;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Read Binary --------------");
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, response_data))
		  break;
		READU16(&response_data->prgui1Buffer[response_data->ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;

		response_data->ui2Length = responsedata_length;
		if( CTL_SUCCESS != ReadBinary(CURRENT_SEL_FILE,file_offset,bytes_to_read,response_data))
		  break;
	  
		READU16(&response_data->prgui1Buffer[response_data->ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}

/**
    @brief Interface to perform update operation on binary file.
*/
STATUS PerformUpdateBinary(uint16_t file_id, uint16_t file_offset, Blob_t * p_new_data)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	
	uint8_t response_data[20];
	ApduResponse_t g_sRAPDU;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Update Binary --------------");
		
		g_sRAPDU.prgui1Buffer = response_data;
		g_sRAPDU.ui2Length = sizeof(response_data);	
	
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, &g_sRAPDU))
		  break;
	  
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)				
		  break;
		
		if( CTL_SUCCESS != UpdateBinary(CURRENT_SEL_FILE, file_offset, p_new_data, &ui2StatusWord))
		  break;
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}

/**
    @brief Interface to perform read record operation on Record file.
*/
STATUS PerformReadRecord(uint16_t file_id, uint8_t record_num, pApduResponse_t response_data)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	uint16_t responsedata_length = response_data->ui2Length;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Read Record --------------");
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, response_data))
		  break;
		READU16(&response_data->prgui1Buffer[response_data->ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;	  
  
		response_data->ui2Length = responsedata_length;
		if( CTL_SUCCESS != ReadRecord(CURRENT_SEL_FILE, record_num, eSINGLE_RECORD, 0x0000, response_data))
		  break;
	  
		READU16(&response_data->prgui1Buffer[response_data->ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		{
		  ui2RetStatus = CTL_OPERATION_NOT_ALLOWED;	
		  break;
		}
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}

/**
    @brief Interface to perform update record operation on Record file.
*/
STATUS PerformUpdateRecord(uint16_t file_id, uint8_t record_num, Blob_t * p_new_data)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	
	uint8_t response_data[20];
	ApduResponse_t g_sRAPDU;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Update Record --------------");
		
		g_sRAPDU.prgui1Buffer = response_data;
		g_sRAPDU.ui2Length = 20;	
	
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, &g_sRAPDU))
		  break;
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;

		if( CTL_SUCCESS != UpdateRecord(CURRENT_SEL_FILE, record_num, eSINGLE_RECORD, p_new_data, &ui2StatusWord))
		  break;
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}

/**
    @brief Interface to perform append record operation on Cyclic Record file.
*/
STATUS PerformAppendRecord(uint16_t file_id, Blob_t * p_new_data)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	
	uint8_t response_data[20];
	ApduResponse_t g_sRAPDU;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Append Record --------------");
		
		g_sRAPDU.prgui1Buffer = response_data;
		g_sRAPDU.ui2Length = 20;	
	
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, &g_sRAPDU))
		  break;
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;

		if( CTL_SUCCESS != AppendRecord(CURRENT_SEL_FILE, p_new_data, &ui2StatusWord))
		  break;
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}


/**
    @brief Interface to perform read value operation on Value Record file.
*/
STATUS PerformReadValue(uint16_t file_id, uint8_t record_num, pApduResponse_t response_data)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	uint16_t responsedata_length = response_data->ui2Length;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Read Value --------------");
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, response_data))
		  break;
		READU16(&response_data->prgui1Buffer[response_data->ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;	  
  
		response_data->ui2Length = responsedata_length;
		if( CTL_SUCCESS != ReadValue(eSINGLE_VALUE, CURRENT_SEL_FILE, record_num, 0x04, response_data))
		  break;
	  
		READU16(&response_data->prgui1Buffer[response_data->ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}

/**
    @brief Interface to perform Increase Value operation on Value Record file.
*/
STATUS PerformIncreaseValue(uint16_t file_id, uint8_t record_num, int32_t value_to_increase, int32_t * updated_value)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	
	uint8_t response_data[20];
	ApduResponse_t g_sRAPDU;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Increase Value --------------");
		
		g_sRAPDU.prgui1Buffer = response_data;
		g_sRAPDU.ui2Length = sizeof(response_data);	
	
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, &g_sRAPDU))
		  break;
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;

		g_sRAPDU.ui2Length = sizeof(response_data);		  
		if( CTL_SUCCESS != IncreaseValue(CURRENT_SEL_FILE, record_num, value_to_increase, 0x0004, &g_sRAPDU))
		  break;
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		//Convert response to  updated_value
		READU32(g_sRAPDU.prgui1Buffer, *updated_value);
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}


/**
    @brief Interface to perform Decrease Value operation on Value Record file.
*/
STATUS PerformDecreaseValue(uint16_t file_id, uint8_t record_num, int32_t value_to_decrease, int32_t * updated_value)
{
	uint16_t ui2StatusWord = 0x0000;
	STATUS ui2RetStatus = CTL_INT_ERROR;
	
	uint8_t response_data[20];
	ApduResponse_t g_sRAPDU;
	
	do
	{
		LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Decrease Value --------------");
		
		g_sRAPDU.prgui1Buffer = response_data;
		g_sRAPDU.ui2Length = sizeof(response_data);	
	
		if( CTL_SUCCESS != SelectFileByFID(SELECT_P2_00, file_id, (int16_t)LENOTREQUIRED, &g_sRAPDU))
		  break;
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;

		g_sRAPDU.ui2Length = sizeof(response_data);		  
		if( CTL_SUCCESS != DecreaseValue(CURRENT_SEL_FILE, record_num, value_to_decrease, 0x0004, &g_sRAPDU))
		  break;
		READU16(&g_sRAPDU.prgui1Buffer[g_sRAPDU.ui2Length-SIZE_OF_SW], ui2StatusWord);
		if(ui2StatusWord != ISO_STATUS_OK)
		  break;
	  
		//Convert response to  updated_value
		READU32(g_sRAPDU.prgui1Buffer, *updated_value);
	  
		ui2RetStatus = CTL_SUCCESS;
	}while(CTL_FALSE);
	
	return ui2RetStatus;
}

/**
    @brief Interface to perform commit operation.
*/
STATUS PerformCommitOperation()
{
	uint16_t ui2StatusWord = 0x0000;
	
	LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------ Perform Transaction --------------");
	
	STATUS ui2RetStatus = PerformTransaction(&ui2StatusWord); 	
	if(ui2StatusWord != ISO_STATUS_OK)
	{
		  ui2RetStatus = CTL_INT_ERROR;
	}
	
	return ui2RetStatus;
}
