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

