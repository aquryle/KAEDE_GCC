/*
 * SCI7.c
 *
 *  Created on: 2024/02/01
 *      Author: sata
 */

#include "SCI7.h"
#include "interrupt_handlers.h"

static volatile uint8 *sci7_tx_address;	/* SCI7 transmit buffer address */
static volatile uint16 sci7_tx_count;		/* SCI7 transmit data number */
static volatile uint8 *sci7_rx_address;	/* SCI7 receive buffer address */
static volatile uint16 sci7_rx_count;		/* SCI7 receive data number */
static volatile uint16 sci7_rx_length;		/* SCI7 receive data length */

uint8 sci7_send_end_flag = 1;

void uart_create(UART_BAUD baud) {


	IPR(SCI7,RXI7) = _IPR_LEVEL10;
	IPR(SCI7,TXI7) = _IPR_LEVEL10;

	SCI7.SCR.BYTE = 0x00u;	/* Clear the control register */
	SCI7.SCR.BYTE = 0x00u;	/* Set clock enable */

	/* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
	SCI7.SIMR1.BIT.IICM = 0u;
	SCI7.SPMR.BYTE = 0x00u;

	switch (baud)
	{
	case UART_9600:
		/* Set control registers */
		SCI7.SMR.BYTE = 0x00u;
		SCI7.SMR.BIT.CKS = 2u;	// pclk / 16
		SCI7.SCMR.BYTE = 0xF2u;
		SCI7.SEMR.BYTE = 0x00u;

		/* Set bit rate */
		SCI7.BRR = 11u;	// 9600 bps
		break;
	default:
		/* Set control registers */
		SCI7.SMR.BYTE = 0x00u;
		SCI7.SMR.BIT.CKS = 2u;	// pclk / 16
		SCI7.SCMR.BYTE = 0xF2u;
		SCI7.SEMR.BYTE = 0x00u;

		/* Set bit rate */
		SCI7.BRR = 11u;	// 9600 bps
		break;

	}
}



void uart_start(void) {
	sci7_send_end_flag = 0;

	IR(SCI7,TXI7) = 0u;
	IR(SCI7,RXI7) = 0u;

	IEN(SCI7,TXI7) = 1u;
	ICU.GENBL0.BIT.EN14 = 1u;	// TEI7 (Transmit Error Interrupt)
	IEN(SCI7,RXI7) = 1u;
	ICU.GENBL0.BIT.EN15 = 1u;	// ERI7 (Error Recieve Interrupt)

}


void uart_stop(void) {

	/* Set TXD7 pin */
	PORT9.PMR.BYTE &= 0xFEU;

	/* Disable serial transmit */
	SCI7.SCR.BIT.TE = 0U;

	/* Disable serial receive */
	SCI7.SCR.BIT.RE = 0U;

	/* Disable SCI interrupt */
	SCI7.SCR.BIT.TIE = 0U;
	SCI7.SCR.BIT.RIE = 0U;
	IEN(SCI7,TXI7) = 0U;
	ICU.GENBL0.BIT.EN14 = 0U;
	IR(SCI7,TXI7) = 0U;
	IEN(SCI7,RXI7) = 0U;
	ICU.GENBL0.BIT.EN15 = 0U;
	IR(SCI7,RXI7) = 0U;
}


void SCI7_Serial_Send(uint8 *const tx_buf, uint16 tx_num)
{

	if (1U > tx_num) {
		// status = MD_ARGERROR;
	}
	else if (0U == IEN(SCI7, TXI7)) {
		// status = MD_ERROR;
	}
	else {
		sci7_tx_address = tx_buf;
		sci7_tx_count = tx_num;
		IEN(SCI7, TXI7) = 0U;
		SCI7.SCR.BYTE |= 0xA0U;

		/* Set TXD7 pin */
		PORT9.PMR.BYTE |= 0x01U;
		IEN(SCI7, TXI7) = 1U;
	}

	return;
}


void INT_Excep_SCI7_TXI7(void){
	if (0U < sci7_tx_count) {
		SCI7.TDR = *sci7_tx_address;
		sci7_tx_address++;
		sci7_tx_count--;
	}
	else {
		SCI7.SCR.BIT.TIE = 0U;
		SCI7.SCR.BIT.TEIE = 1U;
	}

}

void Excep_TEI7(void) {
	PORT9.PMR.BYTE &= 0xFEU;

	SCI7.SCR.BIT.TIE = 0U;
	SCI7.SCR.BIT.TE = 0U;
	SCI7.SCR.BIT.TEIE = 0U;

	sci7_send_end_flag = 1;
}

void INT_Excep_ICU_GROUPBL0(void){
	// if (ICU.GRPBL0.BIT.IS0);
	// if (ICU.GRPBL0.BIT.IS1);
	// if (ICU.GRPBL0.BIT.IS2);
	// if (ICU.GRPBL0.BIT.IS3);
	// if (ICU.GRPBL0.BIT.IS4);
	// if (ICU.GRPBL0.BIT.IS5);
	// if (ICU.GRPBL0.BIT.IS6);
	// if (ICU.GRPBL0.BIT.IS7);
	// if (ICU.GRPBL0.BIT.IS8);
	// if (ICU.GRPBL0.BIT.IS9);
	// if (ICU.GRPBL0.BIT.IS10);
	// if (ICU.GRPBL0.BIT.IS11);
	// if (ICU.GRPBL0.BIT.IS12);
	// if (ICU.GRPBL0.BIT.IS13);
	if (ICU.GRPBL0.BIT.IS14)	Excep_TEI7();	// SCI7送信完了
	// if (ICU.GRPBL0.BIT.IS15)	Excep_ERI7();	// SCI7受信エラー
	// if (ICU.GRPBL0.BIT.IS16);
	// if (ICU.GRPBL0.BIT.IS17);
	// if (ICU.GRPBL0.BIT.IS18);
	// if (ICU.GRPBL0.BIT.IS19);
	// if (ICU.GRPBL0.BIT.IS20);
	// if (ICU.GRPBL0.BIT.IS21);
	// if (ICU.GRPBL0.BIT.IS22);	// received
	// if (ICU.GRPBL0.BIT.IS23);	// received
	// if (ICU.GRPBL0.BIT.IS24);
	// if (ICU.GRPBL0.BIT.IS25);	// received
	// if (ICU.GRPBL0.BIT.IS26);
	// if (ICU.GRPBL0.BIT.IS27);
	// if (ICU.GRPBL0.BIT.IS28);
	// if (ICU.GRPBL0.BIT.IS29);
	// if (ICU.GRPBL0.BIT.IS30);
	// if (ICU.GRPBL0.BIT.IS31);
}


void INT_Excep_SCI7_RXI7(void){ }
