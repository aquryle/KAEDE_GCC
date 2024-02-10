/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 18/57/2017                                        */
/************************************************************************/

/**
 * @file hwinit.c
 * @author sata
 * @brief HardwareSetup(void) is defined.
 * @version 0.1
 * @date 2024-02-07
 * @details Hardware setup before main().
 * @copyright Copyright (c) 2024
 */

#include "iodefine.h"
#include "common.h"


#ifdef __cplusplus
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif


/**
 * @brief Hardware setup before main().
 * @details clock, port, cmt, module stop, group interrupt
 * @todo Organize code by port
 */
void HardwareSetup(void)
{
#if 1
/****************************************************************/
/*		Clock (main clock: 12MHz)								*/
/*	ICLK:	120 MHz		FCLK:	60 MHz		BCLK:	120MHz		*/
/*	PCLKA:	60 MHz		PCLKB:	60 MHz							*/
/*	PCLKC:	60 MHz		PCLKC:	60 MHz							*/
/****************************************************************/
	PORT3.PDR.BYTE = 0u;			// Clock connected port: input.

	// main clock start
	SYSTEM.PRCR.WORD = 0xA50Bu;		// Protected register write enable.

	SYSTEM.MOSCWTCR.BYTE = 0x0Fu;				// Main clock oscillator wait: max
	SYSTEM.MOSCCR.BYTE = 0x00u;					// Main clock: start
	while (0x00u != SYSTEM.MOSCCR.BYTE);		// Waiting until value set
	while (1u != SYSTEM.OSCOVFSR.BIT.MOOVF);	// Waiting until main clock stable.

	// PLL
	SYSTEM.PLLCR.BIT.STC = 0x13;			// PLL multiple x10
	SYSTEM.PLLCR.BIT.PLLSRCSEL = 0;			// PLL clock source: main clock
	SYSTEM.PLLCR.BIT.PLIDIV = 0;			// PLL divide /1
	SYSTEM.PLLCR2.BIT.PLLEN = 0;			// PLL start
	while (1 != SYSTEM.OSCOVFSR.BIT.PLOVF); // Waiting until PLL stable.

	// peripheral clock division
	SYSTEM.SCKCR.LONG = 0x10001111;
	while (SYSTEM.SCKCR.LONG != 0x10001111);
	SYSTEM.SCKCR2.WORD = 0x0031;	// UCLK: /4
	SYSTEM.BCKCR.BYTE  = 0x01;		// BCLK: /4

	// select clock source
	SYSTEM.SCKCR3.WORD = 0x0400;			// System clock: PLL
	while (SYSTEM.SCKCR3.WORD != 0x0400);
	SYSTEM.LOCOCR.BYTE = 0x01;				// LOCO stop

	SYSTEM.PRCR.WORD = 0xA500;				// Protected register write disable.

/****************************************************************/
/*		Pin Configuration										*/
/****************************************************************/
	// MPC
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P92PFS.BYTE = 0x0AU;	// P92 -> RX7
	MPC.P90PFS.BYTE = 0x0AU;	// P90 -> TX7
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PWPR.BIT.B0WI = 0;

	// PMR
	PORT9.PMR.BYTE |= _B2;				// RX7: 1
	PORTC.PMR.BYTE &= ~(_B0 & _B1);		// LED1-2: 0
	PORT0.PMR.BYTE &= ~(_B2 & _B3);		// LED3-4: 0

	// PODR
	PORT9.PODR.BYTE |= _B0;				// TX7: 1
	PORTC.PODR.BYTE &= ~(_B0 & _B1);	// LED1-2: 0
	PORT0.PODR.BYTE &= ~(_B2 & _B3);	// LED3-4: 0


	// PDR
	PORT9.PDR.BYTE |= _B0;				// TX7: output
	PORTC.PDR.BYTE |= (_B0 & _B1);		// LED1-2: output
	PORT0.PDR.BYTE |= (_B2 & _B3);		// LED3-4: output

/****************************************************************/
/*		Module stop invalidation								*/
/****************************************************************/
	SYSTEM.PRCR.WORD = 0xA50Bu;		// Protected register write enable.
	MSTP(SCI7) = 0;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;		// Protected register write disable.


/****************************************************************/
/*		CMT		// これはcmt.cに書く？							*/
/****************************************************************/
	CMT0.CMCR.WORD = 0x0081;			// PCLKB/32 = 1875000 Hz


/****************************************************************/
/*		Group interrupt										*/
/****************************************************************/
	IEN(ICU,GROUPBL0) = 0;
	IPR(ICU,GROUPBL0) = 10;
	IEN(ICU,GROUPBL0) = 1;

#else
/****************************************************************/
/*		System Clock											*/
/****************************************************************/
	SYSTEM.PRCR.WORD = 0xA50Bu;

	// port
	PORT3.PDR.BYTE = 0u;

	// main clock start
	SYSTEM.MOSCWTCR.BYTE = 0x0Fu;
	SYSTEM.MOSCCR.BYTE = 0x00u;
	while (0x00u != SYSTEM.MOSCCR.BYTE);
	while (1u != SYSTEM.OSCOVFSR.BIT.MOOVF);

	// PLL
	SYSTEM.PLLCR.BIT.STC = 0x13;	// *10
	SYSTEM.PLLCR.BIT.PLLSRCSEL = 0;	// PLL clock source: main clock
	SYSTEM.PLLCR.BIT.PLIDIV = 0;	// /1
	SYSTEM.PLLCR2.BIT.PLLEN = 0;	// PLL start
	while (1 != SYSTEM.OSCOVFSR.BIT.PLOVF);

	// division
	/*	main clock: 12MHz, PLL: *10
		FCLK: 60 MHz	ICLK: 120 MHz	BCLK: 120 MHz
		PCLKA: 60 MHz	PCLKB: 60 MHz
		PCLKC: 60 MHz	PCLKD: 60 MHz */
	SYSTEM.SCKCR.LONG = 0x10001111;
	while (SYSTEM.SCKCR.LONG != 0x10001111);
	SYSTEM.SCKCR2.WORD = 0x0031;	// UCLK: /4
	SYSTEM.BCKCR.BYTE  = 0x01;		// BCLK: /4

	// select clock source
	SYSTEM.SCKCR3.WORD = 0x0400;
	while (SYSTEM.SCKCR3.WORD != 0x0400);

	// LOCO stop
	SYSTEM.LOCOCR.BYTE = 0x01;

	SYSTEM.PRCR.WORD = 0xA500;


/****************************************************************/
/*		UART Pin												*/
/****************************************************************/
	SYSTEM.PRCR.WORD = 0xA50B;

	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;

	/* Set RXD7 pin */
	MPC.P92PFS.BYTE = 0x0AU;
	PORT9.PMR.BYTE |= 0x04U;

	/* Set TXD7 pin */
	PORT9.PODR.BYTE |= 0x01U;
	MPC.P90PFS.BYTE = 0x0AU;
	PORT9.PDR.BYTE |= 0x01U;

	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PWPR.BIT.B0WI = 0;

	MSTP(SCI7) = 0;
	SYSTEM.PRCR.WORD = 0xA500;


/****************************************************************/
/*		LED Pin													*/
/****************************************************************/
	// 標準入出力モードにする
	PORTC.PMR.BIT.B0 = 0;
	PORTC.PMR.BIT.B1 = 0;
	PORT0.PMR.BIT.B2 = 0;
	PORT0.PMR.BIT.B3 = 0;

	// 全部OFF
	PORTC.PODR.BIT.B0 = 0;	// LED1
	PORTC.PODR.BIT.B1 = 0;	// LED2
	PORT0.PODR.BIT.B2 = 0;	// LED3
	PORT0.PODR.BIT.B3 = 0;	// LED4

	// LEDに繋がっているポートを出力にする
	PORTC.PDR.BIT.B0 = 1;	// LED1
	PORTC.PDR.BIT.B1 = 1;	// LED2
	PORT0.PDR.BIT.B2 = 1;	// LED3
	PORT0.PDR.BIT.B3 = 1;	// LED4


/****************************************************************/
/*		CMT 0													*/
/****************************************************************/
	SYSTEM.PRCR.WORD = 0xA503;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	CMT0.CMCR.WORD = 0x0081;			// PCLKB/32 = 1875000 Hz


/****************************************************************/
/*		Group interrupt BL0 enable								*/
/****************************************************************/
	IEN(ICU,GROUPBL0) = 0;
	IPR(ICU,GROUPBL0) = 10;
	IEN(ICU,GROUPBL0) = 1;
#endif
}
