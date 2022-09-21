#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE  (32 * 1024) // 32 kb
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void resetHandler (void);
void nonMaskableInterruptHandler (void)           __attribute__ ((weak, alias ("defaultHandler")));
void hardFaultHandler (void)                      __attribute__ ((weak, alias ("defaultHandler")));
void memoryManagementHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void busFaultHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void usageFaultHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));

void svCallHandler (void)                         __attribute__ ((weak, alias ("defaultHandler")));
void debugMonitorHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));

void pendSvHandler (void)                         __attribute__ ((weak, alias ("defaultHandler")));
void sysTickHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));

void gpioPortAIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void gpioPortBIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void gpioPortCIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void gpioPortDIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void gpioPortEIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void uart0IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void uart1IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void ssi0IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void i2c0IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void pwm0FaultIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void pwm0Generator0IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void pwm0Generator1IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void pwm0Generator2IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void qei0IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void Adc0Sequence0IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void Adc0Sequence1IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void Adc0Sequence2IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void Adc0Sequence3IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void watchdogTimers0And1IrqHandler (void)         __attribute__ ((weak, alias ("defaultHandler")));
void timer0AIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer0BIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer1AIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer1BIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer2AIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer2BIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void analogComparator0IrqHandler (void)           __attribute__ ((weak, alias ("defaultHandler")));
void analogComparator1IrqHandler (void)           __attribute__ ((weak, alias ("defaultHandler")));

void systemControlIrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void flashMemoryAndEepromControlIrqHandler (void) __attribute__ ((weak, alias ("defaultHandler")));
void gpioPortFIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));

void uart2IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void ssi1IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void timer3AIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer3BIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void i2c1IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void qei1IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void can0IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void can1IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));

void hibernationModuleIrqHandler (void)           __attribute__ ((weak, alias ("defaultHandler")));
void usbIrqHandler (void)                         __attribute__ ((weak, alias ("defaultHandler")));
void pwmGenerator3IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void uDmaSoftwareIrqHandler (void)                __attribute__ ((weak, alias ("defaultHandler")));
void uDmaErrorIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));
void Adc1Sequence0IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void Adc1Sequence1IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void Adc1Sequence2IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));
void Adc1Sequence3IrqHandler (void)               __attribute__ ((weak, alias ("defaultHandler")));

void ssi2IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void ssi3IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void uart3IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void uart4IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void uart5IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void uart6IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));
void uart7IrqHandler (void)                       __attribute__ ((weak, alias ("defaultHandler")));

void i2c2IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void i2c3IrqHandler (void)                        __attribute__ ((weak, alias ("defaultHandler")));
void timer4AIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer4BIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer5AIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void timer5BIrqHandler (void)                     __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer0AIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer0BIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer1AIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer1BIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer2AIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer2BIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer3AIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer3BIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer4AIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer4BIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer5AIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void wideTimer5BIrqHandler (void)                 __attribute__ ((weak, alias ("defaultHandler")));
void systemExceptionImpreciseIrqHandler (void)    __attribute__ ((weak, alias ("defaultHandler")));

void pwm1Generator0IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void pwm1Generator1IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void pwm1Generator2IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void pwm1Generator3IrqHandler (void)              __attribute__ ((weak, alias ("defaultHandler")));
void pwm1FaultIrqHandler (void)                   __attribute__ ((weak, alias ("defaultHandler")));

uint32_t vectors[] __attribute__ ((section (".isr_vector"))) = {
  STACK_START,
  (uint32_t) &resetHandler,
  (uint32_t) &nonMaskableInterruptHandler,
  (uint32_t) &hardFaultHandler,
  (uint32_t) &memoryManagementHandler,
  (uint32_t) &busFaultHandler,
  (uint32_t) &usageFaultHandler,
  0,
  0,
  0,
  0,
  (uint32_t) &svCallHandler,
  (uint32_t) &debugMonitorHandler,
  0,
  (uint32_t) &pendSvHandler,
  (uint32_t) &sysTickHandler,
  (uint32_t) &gpioPortAIrqHandler,
  (uint32_t) &gpioPortBIrqHandler,
  (uint32_t) &gpioPortCIrqHandler,
  (uint32_t) &gpioPortDIrqHandler,
  (uint32_t) &gpioPortEIrqHandler,
  (uint32_t) &uart0IrqHandler,
  (uint32_t) &uart1IrqHandler,
  (uint32_t) &ssi0IrqHandler,
  (uint32_t) &i2c0IrqHandler,
  (uint32_t) &pwm0FaultIrqHandler,
  (uint32_t) &pwm0Generator0IrqHandler,
  (uint32_t) &pwm0Generator1IrqHandler,
  (uint32_t) &pwm0Generator2IrqHandler,
  (uint32_t) &qei0IrqHandler,
  (uint32_t) &Adc0Sequence0IrqHandler,
  (uint32_t) &Adc0Sequence1IrqHandler,
  (uint32_t) &Adc0Sequence2IrqHandler,
  (uint32_t) &Adc0Sequence3IrqHandler,
  (uint32_t) &watchdogTimers0And1IrqHandler,
  (uint32_t) &timer0AIrqHandler,
  (uint32_t) &timer0BIrqHandler,
  (uint32_t) &timer1AIrqHandler,
  (uint32_t) &timer1BIrqHandler,
  (uint32_t) &timer2AIrqHandler,
  (uint32_t) &timer2BIrqHandler,
  (uint32_t) &analogComparator0IrqHandler,
  (uint32_t) &analogComparator1IrqHandler,
  0,
  (uint32_t) &systemControlIrqHandler,
  (uint32_t) &flashMemoryAndEepromControlIrqHandler,
  (uint32_t) &gpioPortFIrqHandler,
  0,
  0,
  (uint32_t) &uart2IrqHandler,
  (uint32_t) &ssi1IrqHandler,
  (uint32_t) &timer3AIrqHandler,
  (uint32_t) &timer3BIrqHandler,
  (uint32_t) &i2c1IrqHandler,
  (uint32_t) &qei1IrqHandler,
  (uint32_t) &can0IrqHandler,
  (uint32_t) &can1IrqHandler,
  0,
  0,
  (uint32_t) &hibernationModuleIrqHandler,
  (uint32_t) &usbIrqHandler,
  (uint32_t) &pwmGenerator3IrqHandler,
  (uint32_t) &uDmaSoftwareIrqHandler,
  (uint32_t) &uDmaErrorIrqHandler,
  (uint32_t) &Adc1Sequence0IrqHandler,
  (uint32_t) &Adc1Sequence1IrqHandler,
  (uint32_t) &Adc1Sequence2IrqHandler,
  (uint32_t) &Adc1Sequence3IrqHandler,
  0,
  0,
  0,
  0,
  0,
  (uint32_t) &ssi2IrqHandler,
  (uint32_t) &ssi3IrqHandler,
  (uint32_t) &uart3IrqHandler,
  (uint32_t) &uart4IrqHandler,
  (uint32_t) &uart5IrqHandler,
  (uint32_t) &uart6IrqHandler,
  (uint32_t) &uart7IrqHandler,
  0,
  0,
  0,
  0,
  (uint32_t) &i2c2IrqHandler,
  (uint32_t) &i2c3IrqHandler,
  (uint32_t) &timer4AIrqHandler,
  (uint32_t) &timer4BIrqHandler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (uint32_t) &timer5AIrqHandler,
  (uint32_t) &timer5BIrqHandler,
  (uint32_t) &wideTimer0AIrqHandler,
  (uint32_t) &wideTimer0BIrqHandler,
  (uint32_t) &wideTimer1AIrqHandler,
  (uint32_t) &wideTimer1BIrqHandler,
  (uint32_t) &wideTimer2AIrqHandler,
  (uint32_t) &wideTimer2BIrqHandler,
  (uint32_t) &wideTimer3AIrqHandler,
  (uint32_t) &wideTimer3BIrqHandler,
  (uint32_t) &wideTimer4AIrqHandler,
  (uint32_t) &wideTimer4BIrqHandler,
  (uint32_t) &wideTimer5AIrqHandler,
  (uint32_t) &wideTimer5BIrqHandler,
  (uint32_t) &systemExceptionImpreciseIrqHandler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (uint32_t) &pwm1Generator0IrqHandler,
  (uint32_t) &pwm1Generator1IrqHandler,
  (uint32_t) &pwm1Generator2IrqHandler,
  (uint32_t) &pwm1Generator3IrqHandler,
  (uint32_t) &pwm1FaultIrqHandler
};

void resetHandler (void) {
  // Copy .data section to SRAM
  uint32_t size = ((uint32_t) &_edata) - ((uint32_t) &_sdata);
  uint8_t *pSram = (uint8_t *) &_sdata;
  uint8_t *pFlash = (uint8_t *) &_etext;

  for (uint32_t i = 0; i < size; i++) {
    *pSram++ = *pFlash++;
  }

  // Init the .bss section to zero in SRAM
  size = ((uint32_t) &_ebss) - ((uint32_t) &_sbss);
  pSram = (uint8_t *) &_sbss;

  for (uint32_t i = 0; i < size; i++) {
    *pSram++ = 0;
  }

  // call init function of std lib

  // call main()
  main();
}

void defaultHandler (void) {
  while (1);
}