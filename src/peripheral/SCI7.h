/*
 * SCI7.h
 *
 *  Created on: 2024/02/01
 *      Author: sata
 */

#ifndef SCI7_H_
#define SCI7_H_

#include "../common.h"


extern void uart_create(uint8 baud);
extern void uart_start();
extern void INT_Excep_SCI7_TXI7(void);


extern void Excep_TEI7(void);
extern void Excep_ERI7(void);

extern void SCI7_Serial_Send(uint8 *const tx_buf, uint16 tx_num);


#endif /* SCI7_H_ */
