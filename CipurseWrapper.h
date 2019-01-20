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

@file CipurseWrapper.h
@brief This file consists of wrapper interfaces for CIPURSE Terminal Library.
		
@date 2019
@version 1.0.4
*/

#ifndef __IFXCTL_WRAPPER_H__
#define __IFXCTL_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-- Include Section -------------------------------------------------*/
#include "IFXCTL_CipurseInterfaces.h"
#include "IFXCTL_Logger.h"
#include "IFXCTL_PAL.h"


/* P2 value for select*/
#define SELECT_P2_00							   	0x00

/* Indicator for the le not required*/
#define LENOTREQUIRED							   	0x8000

/* Indicator for the current file selection*/
#define CURRENT_SEL_FILE						   	0x00

/* Length of status word */
#define SIZE_OF_SW									0x02

/* Password length */
#define ISO_STATUS_OK								0x9000


/* Global pointer to the session handle */
extern pSessionManager_t g_psSessionHandle;

//Note: For successfull operation CTL_SUCCESS returned else CTL_INT_ERROR except special case on Read Record on Cyclic File

/**
	@details Interface used to initialize the Cipurse Terminal Library and initialize the target.

	@return Success or Error	
 */
STATUS InitializeTargets();

/**
    @details Interface to perform CIPURSE Mutual Authentication.
			
	@param[in] key_number - ADF key number to be used for authentication
	
	@return Success or Error
*/
STATUS PerformAuthentication(uint16_t key_number);

/**
    @details Interface to configure secure message level.
			
	@param[in] eSMLevel - SMI value to be used to wrap the command and un-wrap the response
	
	@return Success or Error
*/
STATUS ConfigureSetSMIValue(SMLevel_t eSMLevel);

/**
    @details Interface to Select an CIPURSE Application.
			
	@param[in] p_aid_value - Holds the application AID value
	
	@return Success or Error
*/
STATUS SelectApplication(Blob_t * p_aid_value);

/**
    @details Interface to perform read operation on binary file.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] file_offset 	- Offset into binary file from there data to be read
	@param[in] bytes_to_read - Number of bytes to read from file, max limit is 180 bytes
	@param[out] response_data - Holds the read file content and status word (last 2 bytes)
	
	@return Success or Error
*/
STATUS PerformReadBinary(uint16_t file_id, uint16_t file_offset, uint16_t bytes_to_read, pApduResponse_t response_data);

/**
    @details Interface to perform update operation on binary file.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] file_offset 	- Offset into binary file from there data to be updated
	@param[in] p_new_data 	- Holds the data to be updated
	
	@return Success or Error
*/
STATUS PerformUpdateBinary(uint16_t file_id, uint16_t file_offset, Blob_t * p_new_data);

/**
    @details Interface to perform read record operation on Record file.
	Try to read record which is not created will throw CTL_OPERATION_NOT_ALLOWED error.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] record_num 	- Record to be read
	@param[out] response_data - Holds the read record content and status word (last 2 bytes)
	
	@return Success or Error
*/
STATUS PerformReadRecord(uint16_t file_id, uint8_t record_num, pApduResponse_t response_data);

/**
    @details Interface to perform update record operation on Record file.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] record_num 	- Record to be updated
	@param[in] p_new_data   - Holds the record content to be updated
	
	@return Success or Error
*/
STATUS PerformUpdateRecord(uint16_t file_id, uint8_t record_num, Blob_t * p_new_data);


/**
    @brief Interface to perform append record operation on Cyclic Record file.
						
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] p_new_data   - Holds the record content to be appended
	
	@return Success or Error	
*/
STATUS PerformAppendRecord(uint16_t file_id, Blob_t * p_new_data);


/**
    @details Interface to perform read value operation on Value Record file.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] record_num 	- Record from value to be read
	@param[out] response_data - Holds the read value and status word (last 2 bytes)
	
	@return Success or Error
*/
STATUS PerformReadValue(uint16_t file_id, uint8_t record_num, pApduResponse_t response_data); 

/**
    @details Interface to perform Increase Value operation on Value Record file.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] record_num 	- Record on which increase operation has to be performed
	@param[in] value_to_increase   - Value to be increased in the value record file 
	@param[out] updated_value   - Updated value after increase operation
	
	@return Success or Error
*/
STATUS PerformIncreaseValue(uint16_t file_id, uint8_t record_num, int32_t value_to_increase, int32_t * updated_value);

/**
    @details Interface to perform Decrease Value operation on Value Record file.
			
	@param[in] file_id 		- file identifier of file to be selected
	@param[in] record_num 	- Record on which decrease operation has to be performed
	@param[in] value_to_decrease   - Value to be decreased in the value record file 
	@param[out] updated_value   - Updated value after decrease operation
	
	@return Success or Error
*/
STATUS PerformDecreaseValue(uint16_t file_id, uint8_t record_num, int32_t value_to_decrease, int32_t * updated_value);

/**
    @details Interface to perform commit operation.
	
	@return Success or Error
*/
STATUS PerformCommitOperation(); 

#ifdef __cplusplus
}
#endif

#endif
