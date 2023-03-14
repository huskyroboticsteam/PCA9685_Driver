#include "project.h"
#include "PCA9685.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    pca_init();
    UART_Start();

    for(;;)
    {
        UART_UartPutString("BRUH");
        //sets individual on and off time
        setPWMFromBytes(PIN0, 0x00, 0x00, 0xE0, 0x02);
        //CyDelay(1000);
        
        for(int i =0; i<100; i++){
            //sets pwm signal based on duty cycle (0-100)
            setPWMFromDutyCycle(PIN0, i);
            CyDelay(1);
        }
        for(int i =99; i>=0; i--){
            setPWMFromDutyCycle(PIN0, i);
            CyDelay(1);
        }
        
    }
}
