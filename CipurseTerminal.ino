#include <Wire.h>
#include <SPI.h>

#include "CipurseExamples.h"


unsigned char  response_data_buf[100];
//unsigned char data1[]="pushkar:1234567890:pushkard999@gmail.com";
unsigned char data;
unsigned int i=0;

//unsigned char acc[10]="0987654321";


  
void setup(void) {
  
  #ifndef ESP8266
    while (!Serial); 
  #endif
  Serial.begin(9600);
}



void loop(void) {

	STATUS ui2RetStatus;
  
 // unsigned char res; 	
	Serial.println("Enter u : To perform update file operations");
	Serial.println("Enter r : To perform read file operations");
	//Serial.println("Enter h : To perform hash value read operations");
	
	//delay(1000);
	int size_total=sizeof(data);
 
	Serial.print("\n Enter your option : ");

  
	//Wait till char entered
	while(!(Serial.available() > 0));

	char c = Serial.read();
  

/*  while(Serial.available())
  {
    char d=Serial.read();
    Serial.println("Data......");
    Serial.print(d);
  }*/
	Serial.print(c);
	
	if(c == 'u' || c == 'U')
	{
 
  Serial.println("\n Enter your name : ");
  
  while(!(Serial.available() > 0));
   //char x = Serial.read();


   int i=0;
   while( Serial.available() )
    {
      char c=Serial.read(); 
      data=c;
      
      //Serial.print(char(data));
      delay(500);
    }
         
 

 
  //for(int i=0;i<20;i++)
  Serial.print(char(data));
  
  
		ui2RetStatus = UpdateFileOperations(data,1);	
    //for(int i =0; i<size_total-1; i++)
    //{
      Serial.print(char(data));
    //}
    

    //ui2RetStatus = UpdateFileOperations(acc,10,2);
    //for(int i =0; i<10; i++)
    //{
    //  Serial.print(char(acc[i]));
    //}

    
  
      	
	}
	else if(c == 'r' ||c == 'R') 
	{
		ui2RetStatus = ReadFileOperations(response_data_buf);
      Serial.print(char(response_data_buf));  

    
	}

 	Serial.read();
	
	delay(3000);
	  
}
