/*
 * Copyright (c) 2015, Martin Jaros <xjaros32@stud.feec.vutbr.cz>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
 
 /*
 * Copyright (c) 2017, Piyush Itankar <pitankar@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __REG_NAMES__
#define __REG_NAMES__

typedef struct _GPIO {
  volatile unsigned long GPIODATA;
  volatile unsigned long PADDING_1[255];
  volatile unsigned long GPIODIR;
  volatile unsigned long GPIOIS;
  volatile unsigned long GPIOIBE;
  volatile unsigned long GPIOIEV;
  volatile unsigned long GPIOIM;
  volatile unsigned long GPIORIS;
  volatile unsigned long GPIOMIS;
  volatile unsigned long GPIOICR;
  volatile unsigned long GPIOAFSEL;
  volatile unsigned long PADDING_2[55];
  volatile unsigned long GPIODR2R;
  volatile unsigned long GPIODR4R;
  volatile unsigned long GPIODR8R;
  volatile unsigned long GPIOODR;
  volatile unsigned long GPIOPUR;
  volatile unsigned long GPIOPDR;
  volatile unsigned long GPIOSLR;
  volatile unsigned long GPIODEN;
  volatile unsigned long GPIOLOCK;
  volatile unsigned long GPIOCR;
  volatile unsigned long GPIOAMSEL;
  volatile unsigned long GPIOPCTL;
  volatile unsigned long GPIOADCCTL;
  volatile unsigned long GPIODMACTL;
  volatile unsigned long PADDING_3[678];
  volatile unsigned long GPIOPeriphlID4;
  volatile unsigned long GPIOPeriphlID5;
  volatile unsigned long GPIOPeriphlID6;
  volatile unsigned long GPIOPeriphlID7;
  volatile unsigned long GPIOPeriphlID0;
  volatile unsigned long GPIOPeriphlID1;
  volatile unsigned long GPIOPeriphlID2;
  volatile unsigned long GPIOPeriphlID3;
  volatile unsigned long GPIOPCellID0;
  volatile unsigned long GPIOPCellID1;
  volatile unsigned long GPIOPCellID2;
  volatile unsigned long GPIOPCellID3;
} GPIO;

// Register Map of the ADC
typedef struct _ADC{
  volatile unsigned long ADCACTSS;
  volatile unsigned long ADCRIS;
  volatile unsigned long ADCIM;
  volatile unsigned long ADCISC;
  volatile unsigned long ADCOSTAT;
  volatile unsigned long ADCEMUX;
  volatile unsigned long ADCUSTAT;
  volatile unsigned long ADCTSSEL;
  volatile unsigned long ADCSSPRI;
  volatile unsigned long ADCSPC;
  volatile unsigned long ADCPSSI;
  volatile unsigned long ADCSAC;
  volatile unsigned long ADCDCISC;
  volatile unsigned long ADCCTL;
  volatile unsigned long ADCSSMUX0;
  volatile unsigned long ADCSSCTL0;
  volatile unsigned long ADCSSFIFO0;
  volatile unsigned long ADCSSFSTAT0;
  volatile unsigned long ADCSSOP0;
  volatile unsigned long ADCSSDC0;
  volatile unsigned long ADCSSMUX1;
  volatile unsigned long ADCSSCTL1;
  volatile unsigned long ADCSSFIFO1;
  volatile unsigned long ADCSSFSTAT1;
  volatile unsigned long ADCSSOP1;
  volatile unsigned long ADCSSDC1;
  volatile unsigned long PADDING_1[2];
  volatile unsigned long ADCSSMUX2;
  volatile unsigned long ADCSSCTL2;
  volatile unsigned long ADCSSFIFO2;
  volatile unsigned long ADCSSFSTAT2;
  volatile unsigned long ADCSSOP2;
  volatile unsigned long ADCSSDC2;
  volatile unsigned long PADDING_2[2];
  volatile unsigned long ADCSSMUX3;
  volatile unsigned long ADCSSCTL3;
  volatile unsigned long ADCSSFIFO3;
  volatile unsigned long ADCSSFSTAT3;
  volatile unsigned long ADCSSOP3;
  volatile unsigned long ADCSSDC3;
  volatile unsigned long PADDING_3[787];
  volatile unsigned long ADCDCRIC;
  volatile unsigned long PADDING_4[64];
  volatile unsigned long ADCDCCTL0;
  volatile unsigned long ADCDCCTL1;
  volatile unsigned long ADCDCCTL2;
  volatile unsigned long ADCDCCTL3;
  volatile unsigned long ADCDCCTL4;
  volatile unsigned long ADCDCCTL5;
  volatile unsigned long ADCDCCTL6;
  volatile unsigned long ADCDCCTL7;
  volatile unsigned long PADDING_5[9];
  volatile unsigned long ADCDCCMP0;
  volatile unsigned long ADCDCCMP1;
  volatile unsigned long ADCDCCMP2;
  volatile unsigned long ADCDCCMP3;
  volatile unsigned long ADCDCCMP4;
  volatile unsigned long ADCDCCMP5;
  volatile unsigned long ADCDCCMP6;
  volatile unsigned long ADCDCCMP7;
  volatile unsigned long PADDING_6[91];
  volatile unsigned long ADCPP;
  volatile unsigned long ADCPC;
  volatile unsigned long ADCCC;
} ADC;

#endif
