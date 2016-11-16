//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

#include <stdio.h>

#include <si32_device.h>

//------------------------------------------------------------------------------
// ARM RealView - MicroLIB runtime support

#pragma import(__use_no_semihosting_swi)

volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;

struct __FILE 
{ 
  int handle; 
  /* Add whatever you need here */ 
};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) 
{
  ITM_SendChar(ch);
  return ch;
}

int fgetc(FILE *f) 
{
  int c;
  do 
  {
    c = ITM_ReceiveChar();
  } while (c == -1);
  return c;
}

int ferror(FILE *f) 
{
  /* Your implementation of ferror */
  return EOF;
}

int __backspace(FILE *f) 
{
  return (0);
}

void _ttywrch(int ch) 
{
  ITM_SendChar(ch);
}

void _sys_exit(int return_code) 
{
label:  goto label;  /* endless loop */
}

//-eof--------------------------------------------------------------------------
