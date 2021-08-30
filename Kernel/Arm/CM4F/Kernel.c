/**

  Copyright (c) 2021 John G. Gizdich III

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
#include <stdlib.h>
#include <stdint.h>
#include "Kernel.h"

/******************************************************************************
 * Function Prototypes                                                        *
 ******************************************************************************/

static
void
SetSystemClock (
  void
  );

static
void
PcbAndTcbInit (
  void
  );

static
void
StackInitForTcb (
  uint8_t Pid,
  uint8_t Tid
  );

/******************************************************************************
 * Global variables                                                           *
 ******************************************************************************/
uint32_t volatile     *RunModeClockConfigurationRegister  = (uint32_t volatile *) 0x400FE060;
uint32_t volatile     *RunModeClockConfiguration2Register = (uint32_t volatile *) 0x400FE070;
PROCESS_CONTROL_BLOCK Pcbs[MAXIMUM_NUMBER_OF_PROCESSES]   = {0};

/******************************************************************************
 * Code                                                                       *
 ******************************************************************************/

/**

  Set the system's clock to 80 MHz

**/
static
void
SetSystemClock (
  void
  )
{

}

/**

  Initialize all Process Control Blocks (PCBs) and their Thread Control Blocks
  (TCBs).

**/
static
void
PcbAndTcbInit (
  void
  )
{
  uint8_t               Pid;
  uint8_t               Tid;
  THREAD_CONTROL_BLOCK  *Tcbs;

  // By default, PCBs and TCBs are in Ready state since the global PCBs array
  // are initialized to zero. The Ready state is equivalent to zero.
  for (Pid = 0; Pid < MAXIMUM_NUMBER_OF_PROCESSES; Pid++) {
    Pcbs[Pid].ProcessId = Pid;
    Tcbs = (Pcbs[Pid].Tcbs);

    for (Tid = 0; Tid < MAXIMUM_NUMBER_OF_THREADS; Tid++) {
      Tcbs[Tid].ThreadId = Tid;
    }
  }
}

/**

  Initialize the stack for a given Process Control Block (PCB) and Thread
  Control Block (TCB).

  @param[in] Pcb - Initialize the stack for the given PCB
  @param[in] Tcb - Initialize the stack for the given TCB

**/
static
void
StackInitForTcb (
  IN  uint8_t Pid,
  IN  uint8_t Tid
  )
{
  THREAD_CONTROL_BLOCK *Tcb;

  // Save the address of a given TCB within a given PCB to a local variable for
  // better code readability
  Tcb = &(Pcbs[Pid].Tcbs[Tid]);

  // The start of the stack pointer due to the last 16 elements in the stack
  // are used to save core registers' values
  Tcb->StackPointer = &(Tcb->StackMem[INITIAL_STACK_POINTER]);

  // Program Status Register (PSR): Thumb bit is set
  Tcb->StackMem[STACK_LOCATION_PSR] = 0x01000000;

  // Include a dummy value at the last stack entry to signify a flag for
  // stack overflow
  Tcb->StackMem[END_OF_STACK] = 0x12345678;
}

/**

  Initialize the kernel

**/
void
OsInit (
  void
  )
{
  DisableInterrupts ();
  SetSystemClock ();
  PcbAndTcbInit ();
}

/**

  Adds foreground thread to the scheduler

  @param[in]  (*Thread)(void) - Contains the address of a function to act as a thread
  @param[in]  StackSize       - Size of the stack that will be allocated for the new thread
  @param[in]  Priority        - Priority number that gets assigned for the new thread

  @retval OsSuccess
  @retval OsOutOfResource

**/
OS_STATUS
OsAddForegroundThread (
  IN  void      (*Thread)(void),
  IN  uint32_t  StackSize,
  IN  uint32_t  Priority
  )
{
  OS_STATUS             Status;
  THREAD_CONTROL_BLOCK  *Tcb;
  uint8_t               Pid;
  uint8_t               Tid;

  DisableInterrupts ();

  Status  = OsOutOfResource;
  Pid     = 0;

  if (Pcbs[Pid].NumberOfThreads == MAXIMUM_NUMBER_OF_THREADS) {
    EnableInterrupts ();
    return Status;
  }

  for (Tid = 0; Tid < MAXIMUM_NUMBER_OF_THREADS; Tid++) {
    if (Pcbs[Pid].Tcbs[Tid].Status == Ready) {
      Tcb         = &(Pcbs[Pid].Tcbs[Tid]);
      Tcb->Status = Running;

      StackInitForTcb (Pid, Tid);

      Tcb->StackMem[STACK_LOCATION_PC] = (uint32_t) (Thread);

      if (Pcbs[Pid].DataSection != NULL) {
        Tcb->StackMem[STACK_LOCATION_R9] = (uint32_t) Pcbs[Pid].DataSection;
      }

      Tcb->Priority = Priority;

      Status = OsSuccess;

      break;
    }
  }

  EnableInterrupts ();

  return Status;
}
