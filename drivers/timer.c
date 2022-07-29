#include "timer.h"

#include <stdbool.h>
#include <stdint.h>

#include "utils.h"

void mach_timer_handler(__attribute__((unused)) uintptr_t int_id,
                        __attribute__((unused)) uintptr_t epc) {
  __asm__ __volatile__(
      "li s0 , 0x40000000;"
      "li x6 , 0xffffffff;"
      "li x7 , 0x1;"

      "sw x6 , 0x10C(s0);"
      "sw x6 , 0x110(s0);"
      "sw x0 , 0x104(s0);"
      "sw x0 , 0x108(s0);"
      "sw x11, 0x100(s0);"
      "sw x0 , 0x114(s0);"
      "sw x7 , 0x118(s0);"
      "sw x0 , 0x0(s0);");
}

void delay(int a) {
  mem_write32(TIMER_BASE_ADDRESS, TIMER_CMP_OFFSET, (a * 4));
  // timer compare upper
  mem_write32(TIMER_BASE_ADDRESS, TIMER_CMP_UPPER_OFFSET, 0);

  __asm__ __volatile__(
      "li x5 , 0x80;"
      "li x6 , 8;"

      "csrrs x0 , 0x300, x6;"
      "csrrs x0 , 0x304, x5;");
  // configuration for hart 0
  int prescale = 1 << 16 | 4000;
  mem_write32(TIMER_BASE_ADDRESS, TIMER_CONFIG_HART0_OFFSET, prescale);
  // interrupt enable
  mem_write32(TIMER_BASE_ADDRESS, TIMER_INTERRUPT_ENABLE_OFFSET, 1);
  // control register
  mem_write32(TIMER_BASE_ADDRESS, TIMER_CNTRL_REGISTER_OFFSET, 1);

  __asm__ __volatile__("wfi;");
}
