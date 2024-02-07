/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  main                                   */
/*      FILE         :  main.c                                 */
/*      DESCRIPTION  :  Main Program                           */
/*                                                             */
/*      This file was generated by e2 studio.                  */
/*                                                             */
/***************************************************************/

/**
 * @file main.c
 * @author sata
 * @brief main routine
 * @version 0.1
 * @date 2024-02-07
 * @details あああああああ
 * @copyright Copyright (c) 2024
 */


#include "common.h"
#include "tool.h"
#include "./peripheral/GPIO.h"
#include "./peripheral/SCI7.h"
#include "./peripheral/CMT.h"


#ifdef CPPAPP
//Initialize global constructors
extern void __main()
{
  static int initialized;
  if (! initialized)
	{
	  typedef void (*pfunc) ();
	  extern pfunc __ctors[];
	  extern pfunc __ctors_end[];
	  pfunc *p;

	  initialized = 1;
	  for (p = __ctors_end; p > __ctors; )
	(*--p) ();

	}
}
#endif

/**
 * @brief main function
 * @return int 0
 * @details UART send
 */
int main(void) {

	volatile uint16 num = 8;
	volatile uint32 i = 0;
	uint8 *buf1 = "GR-KAEDE boot...\r\n";
	uint8 *buf2 = "hello!\r\n";
	uint8 tmp = 0;

	uart_create(UART_9600);
	uart_start();
	SCI7_Serial_Send(buf1, 18);
	while (0 == get_sci7_send_end_flag());
	uart_stop();

	uart_create(UART_9600);
	uart_start();
	SCI7_Serial_Send(buf2, 8);
	while (0 == get_sci7_send_end_flag());
	uart_stop();


	while(1) {
		ms_wait(500);
		led_on(LED1);
		ms_wait(500);
		led_on(LED2);
		ms_wait(500);
		led_on(LED3);
		ms_wait(500);
		led_on(LED4);
		ms_wait(500);
		led_stop();
	}

return 0;
}


