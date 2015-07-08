
#include <stdio.h>
#include <string.h>
#include <stm32f4xx_hal.h>
static void Error_Handler(void);

uint32_t RCC_GET_PLL_OSCSOURCE() 
{
	return ((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC));
}
static void uart_init(void);
static void gpio_init(void);

static GPIO_InitTypeDef GPIO_InitStruct;
UART_HandleTypeDef UartHandle;

static void SystemClock_Config(void);

void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}


void Led_Display(int i)
{

#define GPIOB1       0x40020400 // port B
#define GPIOB_CRH   (GPIOB1 + 0x04) // port configuration register high
#define GPIOB_PUPDR (GPIOB1 + 0x0c) // port PULL-UP／PULL-DOWN register
#define GPIOB_ODR1   (GPIOB1 + 0x14) // port output data register
#define RCC_BASE1    0x40023800
volatile uint32_t *RCC_AHB1ENRP = (void *)(RCC_BASE1 + 0x30);
volatile uint32_t *GPIOBP = (void *)(GPIOB1);
volatile uint32_t *GPIOB_ODRP = (void *)(GPIOB_ODR1);
volatile uint32_t *GPIOB_PUPDRP = (void *)(GPIOB_PUPDR);
    
     *RCC_AHB1ENRP = 1<<1;
     *GPIOBP = 1<<24|0x280;
     *GPIOB_PUPDRP = 1<<25;
     *GPIOB_ODRP = i;
}

int main(void)
{


	//HAL_Init();
	//SystemClock_Config();
    uart_init();
    gpio_init();

    unsigned int iter = 0;
	int  a = 0;

    while (1)
    {
        iter++;
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);     
        HAL_Delay(200);
        printf("[%5d] \r\n", iter);

		a = fgetc(stdin);
		if (a != -1)
			printf("%c",a);	
    }

}
static void uart_init(void)
{
    UartHandle.Instance        = USART2;
    UartHandle.Init.BaudRate   = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

    if(HAL_UART_Init(&UartHandle) != HAL_OK) {
        Error_Handler(); 
    }
}

static void gpio_init(void) 
{
    __GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 
}

static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    __PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Using HSI @ 100 MHz
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 0x10;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
       Error_Handler();
    } 
}
static void Error_Handler(void)
{
    while(1) {

    }
}

