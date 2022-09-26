/**

  Copyright (c) 2022 John G. Gizdich III

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

**/
#include <stdint.h>

#define FIFO_SIZE 1024

/******************************************************************************
 * Registers                                                                  *
 ******************************************************************************/
volatile uint32_t *runModeClockGatingControlRegister      = (volatile uint32_t *) 0x400FE608;
volatile uint32_t *runModeClockGatingControlUartRegister  = (volatile uint32_t *) 0x400FE618;

volatile uint32_t *uartDataRegister                       = (volatile uint32_t *) 0x4000C000;
volatile uint32_t *uartFlagRegister                       = (volatile uint32_t *) 0x4000C018;
volatile uint32_t *uartIntegerBaudRateDivisorRegister     = (volatile uint32_t *) 0x4000C024;
volatile uint32_t *uartFractionalBaudRateDivisorRegister  = (volatile uint32_t *) 0x4000C028;
volatile uint32_t *uartLineControlRegister                = (volatile uint32_t *) 0x4000C02C;
volatile uint32_t *uartControlRegister                    = (volatile uint32_t *) 0x4000C030;
volatile uint32_t *uartInterruptFifoLevelSelectRegister   = (volatile uint32_t *) 0x4000C034;
volatile uint32_t *uartInterruptMaskRegister              = (volatile uint32_t *) 0x4000C038;
volatile uint32_t *uartInterruptClearRegister             = (volatile uint32_t *) 0x4000C044;
volatile uint32_t *uartClockConfigurationRegister         = (volatile uint32_t *) 0x4000CFC8;

volatile uint32_t *gpioAlternateFunctionSelectRegisterA   = (volatile uint32_t *) 0x40004420;
volatile uint32_t *gpioDigitalEnableRegisterA             = (volatile uint32_t *) 0x4000451C;
volatile uint32_t *gpioPortControlRegisterA               = (volatile uint32_t *) 0x4000452C;

volatile uint32_t *nvicEn0Register                        = (volatile uint32_t *) 0xE000E100;
volatile uint32_t *nvicPri1Register                       = (volatile uint32_t *) 0xE000E404;

/******************************************************************************
 * Global Variables                                                           *
 ******************************************************************************/
static uint8_t  rxPutIndex,
                rxGetIndex,
                txPutIndex,
                txGetIndex,
                rxFifo[FIFO_SIZE],
                txFifo[FIFO_SIZE];

/******************************************************************************
 * Code                                                                       *
 ******************************************************************************/

/**

  Initialize UART0 for serial communication between host and target

**/
void
initializeUart (
  void
  )
{
  // The software FIFOs are needed due to the hardware FIFO's limited capacity for UART. Initialize the indices that
  // point to the first entries of the software RX and TX FIFOs.
  rxPutIndex = 0;
  rxGetIndex = 0;
  txPutIndex = 0;
  txGetIndex = 0;

  // Activate UART0 and Port A
  *runModeClockGatingControlUartRegister  |= 0x1;
  *runModeClockGatingControlRegister      |= 0x1;

  // Wait until the clock is stable.
  while (((*runModeClockGatingControlUartRegister & 0x1) == 0) || ((*runModeClockGatingControlRegister & 0x1) == 0));

  // Pins 0 and 1 are used for UART transmission from port A.
  *gpioAlternateFunctionSelectRegisterA   |= 0x3;
  *gpioDigitalEnableRegisterA             |= 0x3;
  *gpioPortControlRegisterA               |= 0x3;

  // Disable UART0 before programming the configurations
  *uartControlRegister                    &= ~0x1;

  // BRD = UARTSysClk / (ClkDiv * Baud Rate) = 80,000,000 / (16 * 115,200) = 80,000,000 / 1,843,200 = 43.402778
  *uartIntegerBaudRateDivisorRegister     = 43; // integer(43.402778) = 43
  *uartFractionalBaudRateDivisorRegister  = 26; // integer (0.402778 * 64 + 0.5) = integer (26.277792)

  // Set data length to 8 bits and enable hardware FIFO
  *uartLineControlRegister                |= 0x70;

  // Uses system's clock
  *uartClockConfigurationRegister         = 0;

  // Initialize interrupts for UART0
  // RX FIFO >= 1⁄8 full
  // TX FIFO <= 1/8 empty
  *uartInterruptFifoLevelSelectRegister   &= ~0x3F;
  *uartInterruptFifoLevelSelectRegister   |= 0x4;
  *uartInterruptMaskRegister              |= 0x70;

  // Set interrupt priority to 3
  *nvicPri1Register                       &= ~0xE000;
  *nvicPri1Register                       |= 0x6000;
  *nvicEn0Register                        |= 0x20;

  // Enable RX, TX, and UART0 after configuration is completed
  *uartControlRegister |= 0x301;
}

void uart0IrqHandler (void) {
  *uartInterruptClearRegister |= 0x70;
}
