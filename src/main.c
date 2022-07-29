/*
 ============================================================================
 Name        : main.c
 Author      : Usman
 Version     :
 Copyright   : Usman Zain - 2022 -  All rights reserved
 Description : Hello RISC-V World in C
 ============================================================================
 */

#include "gpio.h"

int
main(void)
{
	gpio_direct_write_enable(12);
	gpio_direct_write(12, 0x0142);
  int a, b, total;
  a = 15;
  b = 15;
  total = a + b;
  return 0;
}
