/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

#define PCA9685ADDY (0x40)

/* Transfer statuses */
#define TRANSFER_CMPLT (0x00u)
#define TRANSFER_ERROR      (0xFFu)

#define DELAYTIME 1

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7
#define LED8 8
#define LED9 9
#define LED10 10
#define LED11 11
#define LED12 12
#define LED13 13
#define LED14 14
#define LED15 15
#define bufferSize 2
//#define RD_BUFFER_SIZE      (3u)

 /*Prototype*/
    void ToggleLed(int Ledn, int dutyCycle);
    uint8 TurnOnTimeL();
    uint8 TurnOnTimeH();
    uint8 TurnOffTimeH(int dutyCycle);
    uint8 TurnOffTimeL(int dutyCycle);
    uint32 writeBuffer(uint8 buff[],uint32_t PCA9685Address);

void writeByte(unsigned char chip_register, unsigned char value){
     uint8 buf[2] = {chip_register, value};
     writeBuffer(buf, PCA9685ADDY);
}
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   // int errorFlag; 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Start();
    I2C_Enable();
    //uint8 mode_buf[2] = {0,0b10000000};
    //writeBuffer(mode_buf, PCA9685ADDY);
    for(;;)
    {
        //writeByte(0x06,0);
        //writeByte(0x07,0);
        //writeByte(0x08,0xFE);
        //writeByte(0x09,0x07);
        //ToggleLed(LED0,90);
        for(int i =0; i<100; i++){
            ToggleLed(LED0, i);
            CyDelay(1);
        }
        for(int i =99; i>=0; i--){
            ToggleLed(LED0, i);
            CyDelay(1);
        }
    }
}




/*Casting delayTime as uint8_t gets rid of the four left most significant bits*/
uint8 TurnOnTimeL(){
           int delayTime = DELAYTIME; /*This ammounts to 41 ticks before turn on*/
           //dutyCycle = (4095*dutyCycle)/100;
            delayTime = (4095*delayTime)/100 - 1;
        return delayTime;
}

/*Shifting to the right keeps the four most signifcant bits but gets rid of 8 least significant digits */
uint8 TurnOnTimeH(){
    int delayTime = DELAYTIME;
    delayTime = (4095*delayTime)/100 - 1;
    delayTime = delayTime >> 8;
        return delayTime;
}

uint8 TurnOffTimeL(int dutyCycle){
    int delayTime = DELAYTIME;
    int offTime=0;
    if(delayTime+dutyCycle<=100){
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle;
    } else {
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle - 4096;
    offTime = offTime;
    }
       return offTime;}

uint8 TurnOffTimeH(int dutyCycle){
    int delayTime = DELAYTIME;
    int offTime = 0; //initialized because program giving a warning
    if(delayTime+dutyCycle<=100){
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle;
    } else {
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle - offTime;
    }
       return offTime >> 8;}

uint32 writeBuffer(uint8 *buff, uint32_t PCA9685Address){
     uint32 status = TRANSFER_ERROR;
    
    (void) I2C_I2CMasterClearStatus();
         if( I2C_I2C_MSTR_NO_ERROR ==  I2C_I2CMasterWriteBuf(PCA9685Address, buff,
                                                            bufferSize, I2C_I2C_MODE_COMPLETE_XFER)){
     /* If I2C write started without errors, 
         * wait until I2C Master completes write transfer */
        while (0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT))
        {
        }
        
        /* Report transfer status */
        if (0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_ERR_XFER))
        {
            /* Check if all bytes were written */
            if (I2C_I2CMasterGetWriteBufSize() == bufferSize)
            {
                status = TRANSFER_CMPLT;
            }
        }
    }
    
    return status;}

void ToggleLed(int ledN, int dutyCycle){
    //uint32 status = TRANSFER_ERROR;
    uint8 registerNum = 0;
    
    
    switch (ledN){
    case LED0: 
       registerNum = 0x06;
        break;
    case LED1:
       registerNum = 0x0A;  
        break;
    case LED2:
       registerNum = (0x0E);
        break;
    case LED3:
       registerNum = (0x12);   
        break;
    case LED4:
       registerNum = (0x16);    
       break;
    case LED5:
       registerNum = (0x1A);
       break;
    case LED6:
       registerNum = (0x1E);
       break;
    case LED7:
       registerNum = (0x22);
       break;
    case LED8:
       registerNum = (0x26);
       break;
    case LED9:
       registerNum = (0x2A);
       break;
    case LED10:
       registerNum = (0x2E);
       break;
    case LED11:
       registerNum = (0x32);
       break;
    case LED12:
       registerNum = (0x3C);
       break;
    case LED13:
       registerNum = (0x36);
       break;
    case LED14:
       registerNum = (0x3E);
       break;
    case LED15:
       registerNum = (0x42);
       break;
    default:
      registerNum = 0x06;
    }
       
    writeByte(registerNum, TurnOnTimeL());
    writeByte(registerNum+1, TurnOnTimeH());
    writeByte(registerNum+2, TurnOffTimeL(dutyCycle));
    writeByte(registerNum+3, TurnOffTimeH(dutyCycle));
    
     
}

