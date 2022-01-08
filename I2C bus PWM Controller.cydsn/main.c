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
#define TRANSFER_CMPLT      (0x00u)
#define TRANSFER_ERROR      (0xFFu)

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
#define RD_BUFFER_SIZE      (3u)


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    int errorFlag;

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Start();
    I2C_Enable();
    
    /*Prototype*/
    void ToggleLed(uint32_t PCA9685addy, int Ledn, int dutyCycle);
    uint8 DetermineOnTime(int dutyCycle);
    uint32 writeBuffer(uint8* buffer,uint32_t PCA9685Address, uint32_t mode);
    
   // I2C_I2CMasterWriteBuf();

    for(;;)
    {
        /* Place your application code here. */
    }
}

uint8 TurnOnTime(int dutyCycle){
           dutyCycle = (4095*dutyCycle)/100;
        return dutyCycle;
}

uint32 writeBuffer(uint8* buffer, uint32_t PCA9685Address, uint32_t mode){
     uint32 status = TRANSFER_ERROR;
    
    (void) I2C_I2CMasterClearStatus();
         if( I2C_I2C_MSTR_NO_ERROR ==  I2C_I2CMasterWriteBuf(PCA9685Address, buffer,
                                                            bufferSize, mode)){
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

void ToggleLed(uint32_t PCA9685Address, int ledN, int dutyCycle){
     uint32 status = TRANSFER_ERROR;

    uint8 buffer[bufferSize] = {0,0};
    switch (ledN){
    case LED0: 
       buffer[0] = (0x06);
       buffer[1] = TurnOnTime(dutyCycle);
       writeBuffer(buffer, PCA9685Address, I2C_I2C_MODE_NO_STOP);
       buffer[1] = TurnOnTime(dutyCycle);
       //buffer[1] = TurnOffTime(dutyCyle);
   
    }
       
}

;


/* [] END OF FILE */
