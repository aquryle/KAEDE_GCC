/*
 * CMT.c
 *
 *  Created on: 2024/02/05
 *      Author: sata
 */


#include "CMT.h"


/**
 * @fn
 * 1msのウェイト
 * @brief コンペアマッチタイマ ch.0を使って1msをカウントする。
 * @param cnt カウントする時間（ミリ秒）
 * @details あとで1874の計算式を書く
*/
void ms_wait(uint32 cnt)
{
	volatile uint32 i, tmp;

	CMT.CMSTR0.BIT.STR0 = 1;		// CMT0 start
	for( i = 0; i < cnt; i++ ) {
		CMT0.CMCNT = 0;
		while( CMT0.CMCNT < 1874 ); // 1msをカウント
	}
	CMT.CMSTR0.BIT.STR0 = 0;		// CMT0 stop
}


void cmt0_create() {
	CMT0.CMCR.WORD = 0x0081;			// PCLKB/32 = 1875000 Hz
}
