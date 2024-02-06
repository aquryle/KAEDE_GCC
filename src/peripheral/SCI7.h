/*
 * SCI7.h
 *
 *  Created on: 2024/02/01
 *      Author: sata
 */

#ifndef SCI7_H_
#define SCI7_H_

#include "../common.h"

typedef enum {
	UART_9600,
	UART_18200,
} UART_BAUD;



#define ERR_SCI7_BASE		(ERR_SCI_BASE + 0x0700)
#define ERR_SCI7_SEND_TOUT	(ERR_SCI7_BASE + 0x01)



extern uint8 get_sci7_send_end_flag(void);
extern void uart_create(UART_BAUD baud);
extern void uart_start(void);
extern void uart_stop(void);
extern void INT_Excep_SCI7_TXI7(void);


extern void Excep_TEI7(void);
extern void Excep_ERI7(void);

extern void SCI7_Serial_Send(uint8 *const tx_buf, uint16 tx_num);





#endif /* SCI7_H_ */
