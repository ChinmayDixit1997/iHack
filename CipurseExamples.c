

#include "CipurseWrapper.h"
#include "CipurseExamples.h"

uint8_t g_rgui1CipurseAppAid[7]={ 0xD2, 0x76, 0x00, 0x00, 0x04, 0xFE, 0x01 };
uint8_t g_rgui1HashAppAid[7]={ 0xD2, 0x76, 0x00, 0x00, 0x04, 0xFE, 0x02 };
Blob_t g_sCipurseAppAid = {sizeof(g_rgui1CipurseAppAid), g_rgui1CipurseAppAid};
Blob_t g_sHashAppAid = {sizeof(g_rgui1HashAppAid), g_rgui1HashAppAid};


STATUS ReadFileOperations(unsigned char *response_data_buf )
{

  STATUS ui2RetStatus = CTL_INT_ERROR;
  uint8_t ui1RecNum = 0x01;
  uint16_t ui2StatusWord = 0x0000;
  
  ApduResponse_t response_apdu;
//  uint8_t response_data_buf[240];
  
  LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n--------- Read File Operation Begins -------------\n")
  do
  {

    /* InitializeTargets */   
    if( CTL_SUCCESS != (ui2RetStatus = InitializeTargets()) )
      break;

  /* Select CIPURSE Application */   
  if( CTL_SUCCESS != (ui2RetStatus = SelectApplication( &g_sCipurseAppAid)))
  {
    break;
  }

  /* Authenticate with key 2 */   
    ui2RetStatus = PerformAuthentication(0x0002);
    if( CTL_SUCCESS !=  ui2RetStatus ) 
      break;
  
  /* Configure SMI to MAC_MAC */ 
  if( CTL_SUCCESS != (ui2RetStatus = ConfigureSetSMIValue(eSM_MAC_MAC) ))
    break;
  
  /* Read Binary File command */  
    response_apdu.prgui1Buffer = response_data_buf;
    response_apdu.ui2Length = 0x40;
  ui2RetStatus = PerformReadBinary(0x7211, 0x0000, 0xDC, &response_apdu);
  if( CTL_SUCCESS !=  ui2RetStatus ) 
      break;
  
  /* Read Linear Record File command  */   
  
//    response_apdu.ui2Length = 0x80;
//    ui2RetStatus = PerformReadRecord(0x7221,0, &response_apdu);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;  
//  
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//  
//    /* Read Value Record File command  */  
//  for(int count = 1; count < 10; count++)
//  { 
//    response_apdu.ui2Length = 0x80;
//    ui2RetStatus = PerformReadValue(0x7231, count, &response_apdu);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break; 
//  } 
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//  
//  /* Read Cyclic Record File command  */  
//  for(int count = 1; count < 6; count++)
//  { 
//    response_apdu.ui2Length = sizeof(response_data_buf);
//    ui2RetStatus = PerformReadRecord(0x7241, count, &response_apdu);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;  
//  }
//  
//  /* Configure SMI to ENC_ENC */ 
//  if( CTL_SUCCESS != (ui2RetStatus = ConfigureSetSMIValue(eSM_ENC_ENC) ))
//    break;
//  
//  /* Read Binary File command */  
//    response_apdu.prgui1Buffer = response_data_buf;
//    response_apdu.ui2Length = sizeof(response_data_buf);
//  ui2RetStatus = PerformReadBinary(0x7218, 0x0000, 0xDC, &response_apdu);
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;
//  
//  /* Read Linear Record File command  */   
//  for(int count = 1; count < 17; count++)
//  {   
//    response_apdu.ui2Length = sizeof(response_data_buf);
//    ui2RetStatus = PerformReadRecord(0x7228, count, &response_apdu);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;  
//  }
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//  
//    /* Read Value Record File command  */  
//  for(int count = 1; count < 10; count++)
//  { 
//    response_apdu.ui2Length = sizeof(response_data_buf);
//    ui2RetStatus = PerformReadValue(0x7238, count, &response_apdu);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break; 
//  } 
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//  
//  /* Read Cyclic Record File command  */  
//  for(int count = 1; count < 6; count++)
//  { 
//    response_apdu.ui2Length = sizeof(response_data_buf);
//    ui2RetStatus = PerformReadRecord(0x7248, count, &response_apdu);
//    if( CTL_SUCCESS !=  ui2RetStatus )    
//      break;  
//  }

  }while(CTL_FALSE);

  
  if(CTL_SUCCESS == ui2RetStatus) 
  {
    LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------Read File Operation executed successfully--------------\n")
  }
  else
  {
    LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------Read File Operation is failed--------------\n")

    /*Returns this error in case of any failure from Cipurse Terminal Library*/
    ui2RetStatus = CIPURSE_OPERATION_ERROR;
  }

  LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n---------------------------------------------------------------\n")
  

  /* Return the status value.*/
  return ui2RetStatus;
     
}
              

STATUS UpdateFileOperations( unsigned char *data,uint16_t len)
{

  STATUS ui2RetStatus = CTL_INT_ERROR;
  uint8_t ui1RecNum = 0x01;
  uint16_t ui2StatusWord = 0x0000;
  int32_t value_to_increase = 0x04;
  int32_t value_to_decrease = 0x02;
  int32_t updated_value = 0x0;
  
  Blob_t new_data;
  //uint8_t data[200];
  
  LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n--------- Update File Operation Begins -------------\n")
  do
  {
  //for(int offset = 0; offset < sizeof(data); offset++)
    //data[offset] = offset;

    /* InitializeTargets */   
    if( CTL_SUCCESS != (ui2RetStatus = InitializeTargets()) )
      break;

  /* Select CIPURSE Application */   
  if( CTL_SUCCESS != (ui2RetStatus = SelectApplication( &g_sCipurseAppAid)))
  {
    break;
  }

  /* Authenticate with key 3 */   
    ui2RetStatus = PerformAuthentication(0x0003);
    if( CTL_SUCCESS !=  ui2RetStatus ) 
      break;
  
  /* Configure SMI to MAC_MAC */ 
  if( CTL_SUCCESS != (ui2RetStatus = ConfigureSetSMIValue(eSM_MAC_MAC) ))
    break;
  
  /* Update Binary command  */ 
    new_data.prgui1Buffer = data;
    new_data.ui2Length = sizeof(data);
  ui2RetStatus = PerformUpdateBinary(0x7211, 0x0000, &new_data);
  if( CTL_SUCCESS !=  ui2RetStatus ) 
      break; 
  
  /* Update Record on linear record file  */ 
  
//    new_data.prgui1Buffer = data;
//    new_data.ui2Length = 0x1;    //1 byte record    
//    
//    ui2RetStatus = PerformUpdateRecord(0x7221, 0, &new_data);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break; 
//  
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//
//  /* Perform Increase and Decrease operations */
//  for(int count = 1; count < 10; count++)
//  {  
//    ui2RetStatus = PerformIncreaseValue(0x7231, count, value_to_increase, &updated_value);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 














//      break;
//
//    call_PrintValue(updated_value);
//    ui2RetStatus = PerformDecreaseValue(0x7231, count, value_to_decrease, &updated_value);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;      
//    call_PrintValue(updated_value);
//  }
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//  
//  /* Append Record on Cyclic record file  */ 
//  for(int count = 1; count < 6; count++)
//  {  
//    new_data.prgui1Buffer = data;
//    new_data.ui2Length = 0x40;    //64 byte record
//    ui2RetStatus = PerformAppendRecord(0x7241, &new_data);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;  
//  }
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;
//  
//  /* Configure SMI to ENC_ENC */ 
//  if( CTL_SUCCESS != (ui2RetStatus = ConfigureSetSMIValue(eSM_ENC_ENC) ))
//    break;
//  
//  /* Update Binary command  */ 
//    new_data.prgui1Buffer = data;
//    new_data.ui2Length = sizeof(data);
//  ui2RetStatus = PerformUpdateBinary(0x7218, 0x0000, &new_data);
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;
  
//  /* Update Record on linear record file  */ 
//  for(int count = 1; count < 17; count++)
//  {
//    new_data.prgui1Buffer = data;
//    new_data.ui2Length = 0x40;    //64 byte record    
//    
//    ui2RetStatus = PerformUpdateRecord(0x7228, count, &new_data);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break; 
//  }
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//
//  /* Perform Increase and Decrease operations */
//  for(int count = 1; count < 10; count++)
//  {  
//    ui2RetStatus = PerformIncreaseValue(0x7238, count, value_to_increase, &updated_value);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;
//
//    call_PrintValue(updated_value);
//    ui2RetStatus = PerformDecreaseValue(0x7238, count, value_to_decrease, &updated_value);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;      
//    call_PrintValue(updated_value);
//  }
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;  
//  
//  /* Append Record on Cyclic record file  */ 
//  for(int count = 1; count < 6; count++)
//  {  
//    new_data.prgui1Buffer = data;
//    new_data.ui2Length = 0x40;    //64 byte record
//    ui2RetStatus = PerformAppendRecord(0x7248, &new_data);
//    if( CTL_SUCCESS !=  ui2RetStatus ) 
//      break;  
//  }
//  if( CTL_SUCCESS !=  ui2RetStatus ) 
//    break;
    
  ui2RetStatus = PerformCommitOperation();

  }while(CTL_FALSE);

  
  if(CTL_SUCCESS == ui2RetStatus) 
  {
    LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------Update File Operation executed successfully--------------\n")
  }
  else
  {
    LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n------------Update File Operation is failed--------------\n")

    /*Returns this error in case of any failure from Cipurse Terminal Library*/
    ui2RetStatus = CIPURSE_OPERATION_ERROR;
  }

  LOG_MSG(g_psLoggerHandle,(uint8_t *)"\n---------------------------------------------------------------\n")
  

  /* Return the status value.*/
  return ui2RetStatus;
     
}
