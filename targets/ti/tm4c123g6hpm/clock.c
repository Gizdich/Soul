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

/******************************************************************************
 * Global variables                                                           *
 ******************************************************************************/
uint32_t volatile     *RunModeClockConfigurationRegister  = (uint32_t volatile *) 0x400FE060;
uint32_t volatile     *RunModeClockConfiguration2Register = (uint32_t volatile *) 0x400FE070;
uint32_t volatile     *RawInterruptStatusRegister         = (uint32_t volatile *) 0x400FE050;

/**

  Set the system's clock to 80 MHz

**/
void
setSystemClock (
  void
  )
{
  // Run the raw clock source first before initializing PLL
  *RunModeClockConfigurationRegister &= ~0x1;           // Main oscillator is enabled
  *RunModeClockConfigurationRegister |= (1 << 11);      // Set bypass by setting to 1
  *RunModeClockConfigurationRegister &= ~(1 << 22);     // Do not use SYSDIV

  *RunModeClockConfigurationRegister |= (0x15 << 6);    // Crystal Value: 16 MHz
  *RunModeClockConfigurationRegister &= ~(0x3 << 4);    // MOSC
  *RunModeClockConfigurationRegister &= ~(1 << 13);     // PLL Normal Operation
  *RunModeClockConfigurationRegister |= (1 << 23);      // SYSDIV
  *RunModeClockConfigurationRegister |= (1 << 22);      // Use SYSDIV

  *RunModeClockConfiguration2Register |= (1 << 31);     // RCC2 is used
  *RunModeClockConfiguration2Register |= (1 << 11);     // Set bypass2 by setting to 1
  *RunModeClockConfiguration2Register &= ~(0x7 << 4);   // MOSC
  *RunModeClockConfiguration2Register &= ~(1 << 13);    // PLL Normal Operation
  *RunModeClockConfiguration2Register |= (1 << 30);     // Append SYSDIV2LSB to SYSDIV2 (DIV400)
  *RunModeClockConfiguration2Register &= ~(1 << 22);    // SYSDIV2LSB
  *RunModeClockConfiguration2Register &= ~(0x3F << 23); // Clear SYSDIV2
  *RunModeClockConfiguration2Register |= (0x2 << 23);   // Set SYSDIV2

  // Wait until PLL is ready
  while ((((*RawInterruptStatusRegister) >> 6) & 0x1) == 0);

  // PLL Normal Operation
  *RunModeClockConfigurationRegister &= ~(1 << 11);
  *RunModeClockConfiguration2Register &= ~(1 << 11);
}