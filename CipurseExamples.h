

#ifndef __IFXCTL_EXAMPLE_H_
#define __IFXCTL_EXAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "CipurseWrapper.h"


#define	CIPURSE_OPERATION_ERROR		0x5001

STATUS ReadFileOperations(unsigned char *response_data_buf);

STATUS UpdateFileOperations(unsigned char *data,uint16_t);

//STATUS UpdateFileOperations(uint16_t file_id, uint8_t record_num, int32_t value_to_increase);

//STATUS GetHashValues( );

#ifdef __cplusplus
}
#endif

#endif
