#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include <stm32f4xx_hal.h>

extern UART_HandleTypeDef UartHandle;

int _write(int file, char *ptr, int len) 
{ 
  HAL_UART_Transmit(&UartHandle, (uint8_t*) ptr, len, 0xffff); 
  return len; 
}


int fgetc(FILE *f)
{
	unsigned int c = -1;

  	HAL_UART_Receive(&UartHandle, &c, 1, 0x1);
	return c;
}

/*
int _read(int file, char *ptr, int len) 
{ 

    int num = 0;
    int n;
	int count = 0xffff;

    switch (file) {
    case STDIN_FILENO:
        for (n = 0; n < len; n++) {
			unsigned char c = -1;
  			//HAL_UART_Receive(&UartHandle, &c, 1, 0xffff);
			while (count--)
				{
			        if (USART2->SR & USART_FLAG_RXNE)
			        {
            			c = (unsigned char) (USART2->DR & (uint16_t) 0x01FF);
						break;
        			}
				}
			if (count == 0)
			{
					*ptr++ = -1;
					return -1;
			}
			count = 0xffff;
            num++;
			*ptr++ = c;
        }
        break;
    default:
        return -1;
    }
    return num;
}
*/
