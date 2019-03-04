/*******************************************************************************
	*
	* FILE NAME
	*						MCU_Config.c
	* 
*******************************************************************************/
#include "MCU_Config.h" 


/* Gloable Parameters */
_Uint8	HseStatus;


/**
	* FunctionName		MCU_Config
	*/
void MCU_Config(void)
{
	CLK_Init();
	WDT_Init();
	GPIO_Init();
	UART_Init();
	TIM_Init();
	#if AL96 | AL95
	PWM_Init();
	#endif
}

/**
	* FunctionName		CLK_Init
	*/
static void CLK_Init(void)
{
	/*---------------------------------------------------------------------------------------------------------*/
	/* Init System Clock                                                                                       */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Unlock protected registers */
	SYS_UnlockReg();
	
	/* Set P5 multi-function pins for crystal output/input */
	SYS->P5_MFP &= ~(SYS_MFP_P50_Msk | SYS_MFP_P51_Msk);
	SYS->P5_MFP |= (SYS_MFP_P50_XT1_IN | SYS_MFP_P51_XT1_OUT);

	/* Enable HXT clock (external XTAL 12MHz) */
	CLK_EnableXtalRC(CLK_PWRCTL_XTLEN_HXT);

	/* Wait for HXT clock ready */
	HseStatus = (_Uint8)CLK_WaitClockReady(CLK_STATUS_XTLSTB_Msk);
	
	if (HseStatus == 0) // Change the HCLK to HIRC if HXT clock doesn't work
	{
		/* Enable HIRC clock (Internal RC 22.1184MHz) */
		CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
		/* Wait for HIRC clock ready */
		CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
		/* Select HCLK clock source as HIRC and and HCLK source divider as 1 */
		CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV_HCLK(1));
	}
	
	/* Set core clock as PLL_CLOCK from PLL */
	CLK_SetCoreClock(PLL_CLOCK);
	
	#if 1
	// Enable LIRC for WDT
	CLK->PWRCTL = CLK_PWRCTL_LIRCEN_Msk;
	// Wait for LIRC
	CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);
	// Enable WDT IP clock
	CLK->APBCLK = CLK_APBCLK_WDTCKEN_Msk;
	CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_WDTSEL_Msk) | CLK_CLKSEL1_WDTSEL_IRC10K;
	#endif
	
	
	/* Reset UART clock */
  CLK->APBCLK &= ~CLK_APBCLK_UART0CKEN_Msk;
	CLK->APBCLK |= CLK_APBCLK_UART0CKEN_Msk;
	/* Select UART clock source from external crystal*/
	CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UARTSEL_Msk) | CLK_CLKSEL1_UARTSEL_XTAL;
	/* Set P1 multi-function pins for UART1 RXD and TXD  */
	SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
	SYS->P1_MFP |= (SYS_MFP_P12_UART0_RXD | SYS_MFP_P13_UART0_TXD);
	
	
	
	
	/* Enable Timer 0 clock */
  CLK->APBCLK |= CLK_APBCLK_TMR0CKEN_Msk;
	/* Select TIMER0 clock source from external crystal*/
	CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_TMR0SEL_Msk) | CLK_CLKSEL1_TMR0SEL_XTAL;
	
	
	
	/* Enable Timer 1 clock */
  CLK->APBCLK |= CLK_APBCLK_TMR1CKEN_Msk;
	/* Select TIMER0 clock source from LIRC*/
	CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_TMR1SEL_Msk) | CLK_CLKSEL1_TMR1SEL_XTAL;
	
	
	
	#if AL96 | AL95  /* PWM module selected */
	/* Enable IP clock */
	CLK->APBCLK |= CLK_APBCLK_PWMCH01CKEN_Msk;
	CLK->APBCLK |= CLK_APBCLK_PWMCH45CKEN_Msk;
	/* Select PWM clock source from external crystal*/
	CLK_SetModuleClock(PWMCH01_MODULE, CLK_CLKSEL1_PWMCH01SEL_HCLK, NULL);
	CLK_SetModuleClock(PWMCH45_MODULE, CLK_CLKSEL2_PWMCH45SEL_HCLK, NULL);
	/* Set P0 multi-function pin for PWM Channel 0  */
	SYS->P0_MFP |= (SYS_MFP_P04_PWM0_CH5 | SYS_MFP_P05_PWM0_CH4 | SYS_MFP_P06_PWM0_CH1 | SYS_MFP_P07_PWM0_CH0);
	#endif
	
	
	
	
	/* Update System Core Clock */
	/* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CycylesPerUs automatically. */
	SystemCoreClockUpdate();
	
	/* Lock protected registers */
  SYS_LockReg();
}


/**
	* FunctionName		WDT_Init
	*/
static void WDT_Init(void)
{
	SYS_UnlockReg();
	
	WDT->CTL = 0x00000300;		// 2^10 = 1024 = 102.4ms
	WDT->CTL |= WDT_CTL_RSTEN_Msk;
	WDT->ALTCTL = 0x00000001;	// Reset after 130 * WDT_CLK = 13ms
	WDT->CTL |= WDT_CTL_WDTEN_Msk;		//Enable
	
	SYS_LockReg();
}




/**
	* Function Name		TIM_Init
	*/
static void TIM_Init(void)
{
	// Set timer 0 working 50Hz in periodic mode
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 50);
	TIMER_Start(TIMER0);
	
	// Timer1 for count down hour
	TIMER1->CTL = TIMER_PERIODIC_MODE | 0xff;		//12M/256
  TIMER1->CMP = 46875;
	TIMER_Start(TIMER1);
}

/**
  * Function Name: GPIO_Init
	*/
static void GPIO_Init(void)
{
//	// Set the Tx & Rx as output port, and reset them
//	GPIO_SetMode(P1, GP_PIN_PIN2_Msk | GP_PIN_PIN3_Msk, GPIO_MODE_OUTPUT);
//	PORT_TX = RESET;
//	PORT_RX = RESET;
	
	
	
	#if AL91 | AL92 | AL_CURTAIN
	// PIO11_T-P14	VCC CE-P06	COMM-P24
	GPIO_SetMode(P1, GP_PIN_PIN4_Msk, GPIO_MODE_QUASI);
	GPIO_SetMode(P0, GP_PIN_PIN6_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P2, GP_PIN_PIN4_Msk, GPIO_MODE_OUTPUT);
	PORT_COMM 	= RESET;
	
	
	
	
	#elif AL94
	// PIO11_T-P07,VCC_CE-P06,COMM-P24,KEY-P15
	GPIO_SetMode(P0, GP_PIN_PIN7_Msk, GPIO_MODE_QUASI);
	GPIO_SetMode(P1, GP_PIN_PIN5_Msk, GPIO_MODE_QUASI);
	GPIO_SetMode(P0, GP_PIN_PIN6_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P2, GP_PIN_PIN4_Msk, GPIO_MODE_OUTPUT);
	PORT_COMM 	= RESET;
	
	
	
	
	
	
	#elif AL95
	//PIO11_T-P14,VDD_CE-P15,RED-P05,GREEN-P06,BLUE-P07,COMM-P24
	GPIO_SetMode(P1, GP_PIN_PIN4_Msk, GPIO_MODE_QUASI);
	GPIO_SetMode(P1, GP_PIN_PIN5_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P0, GP_PIN_PIN5_Msk | GP_PIN_PIN6_Msk | GP_PIN_PIN7_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P2, GP_PIN_PIN4_Msk, GPIO_MODE_OUTPUT);
	PORT_COMM 	= RESET;
	
	
	
	
	
	#elif AL96
	//VDD_CE-P14,RED-P04,GREEN-P05,BLUE-P06,WHITE-P07,PIO11_T-P25,KEY-P15
	GPIO_SetMode(P1, GP_PIN_PIN4_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P0, GP_PIN_PIN4_Msk | GP_PIN_PIN5_Msk | GP_PIN_PIN6_Msk | GP_PIN_PIN7_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P2, GP_PIN_PIN5_Msk, GPIO_MODE_QUASI);
	
	GPIO_SetMode(P1, BIT5, GPIO_MODE_INPUT);
	GPIO_EnableInt(P1, 5, GPIO_INT_FALLING);
	NVIC_EnableIRQ(GPIO01_IRQn);
	
	
	
	
	
	
	#elif AL99
	//KEY-P15,PIO11_T-P34,VDD_CE-P35,A1-P04,A2-P05,A3-P06,A4-P07,A5-P25,A6-P24,A7-P14
	GPIO_SetMode(P1, GP_PIN_PIN5_Msk, GPIO_MODE_QUASI);
	GPIO_SetMode(P3, GP_PIN_PIN4_Msk, GPIO_MODE_QUASI);
	GPIO_SetMode(P3, GP_PIN_PIN5_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P0, GP_PIN_PIN4_Msk | GP_PIN_PIN5_Msk | GP_PIN_PIN6_Msk | GP_PIN_PIN7_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P2, GP_PIN_PIN4_Msk | GP_PIN_PIN5_Msk, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P1, GP_PIN_PIN4_Msk, GPIO_MODE_OUTPUT);
	PORT_COMM_1 = RESET;
	PORT_COMM_2 = RESET;
	PORT_COMM_3 = RESET;
	PORT_COMM_4 = RESET;
	PORT_COMM_5 = RESET;
	PORT_COMM_6 = RESET;
	PORT_COMM_7 = RESET;
	#endif
	
  #if AL91 | AL_CURTAIN | AL92
  PORT_BT_CE = RESET;
  #else
  PORT_BT_CE = SET;
  #endif
}


/**
 	* FunctionName: UART_Init
 	*/
static void UART_Init(void)
{ 
/* Enable Interrupt and install the call back function */
	UART_SetTimeoutCnt(UART0, 20);
	UART_ENABLE_INT(UART0, UART_INTEN_RXTOIEN_Msk);
  NVIC_EnableIRQ(UART0_IRQn);
	UART_Open(UART0, 9600);
}



/**
 	* FunctionName: PWM_Init
 	*/
#if AL95 | AL96
static void PWM_Init(void)
{
	PWM->CLKPSC 	= 0x003B003B;				// HCLK = 48M  		Fclk = 48 / (59 + 1) = 4/5 M
	PWM->CLKDIV 	= 0x00330033;				// Fpwm = Fclk / 16 = 1 / 20M = 20us
	PWM->CTL			|= (BIT23 | BIT19 | BIT7 | BIT3);				// Auto Reload
	//PWM->CTL			|= (BIT22 | BIT18 | BIT6 | BIT2);				// Rerverse
	PWM->PERIOD0 	= 255;				// 256 * 20us = 5.12ms
	PWM->PERIOD1 	= 255;				// 256 * 20us = 5.12ms
	PWM->PERIOD4 	= 255;				// 256 * 20us = 5.12ms
	PWM->PERIOD5 	= 255;				// 256 * 20us = 5.12ms
	PWM->CMPDAT0 	= 0;
	PWM->CMPDAT1 	= 0;
	PWM->CMPDAT4 	= 0;
	PWM->CMPDAT5 	= 0;
	PWM->POEN 		|= (BIT0 | BIT1 | BIT4 | BIT5);				// Enable the channel 0,1,4,5
	PWM->CTL			|= (BIT20 | BIT16 | BIT4 | BIT0);			// Start
}
#endif



