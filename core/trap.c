#include "trap.h"

#include "plic.h"
#include "timer.h"

unsigned int extract_ie_code(unsigned int num) {
  unsigned int exception_code;
  exception_code = (num & 0X7FFFFFFF);
  return exception_code;
}
void default_handler(__attribute__((unused)) uintptr_t mcause,
                     __attribute__((unused)) uintptr_t epc) {
  while (1)
    ;
}

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc) {
  unsigned int ie_entry = 0;
  uint32_t shift_length = 0;

  shift_length = 32 - 1;

  /* checking for type of trap */
  if (mcause & (1 << (shift_length))) {
    ie_entry = extract_ie_code(mcause);
    if (ie_entry == 11)
      mach_plic_handler(mcause, epc);
    else if (ie_entry == 7)
      mach_timer_handler(mcause, epc);
  }
  return epc;
}
