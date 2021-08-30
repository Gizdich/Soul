/*
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
*/
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <stdint.h>

#define MAXIMUM_NUMBER_OF_PROCESSES 1u
#define MAXIMUM_NUMBER_OF_THREADS   10u

//
// During a context switch, the contents of the registers are pushed
// into the stack in this order.
//
#define STACK_SIZE              256u
#define STACK_LOCATION_PSR      (STACK_SIZE - 1u)
#define STACK_LOCATION_PC       (STACK_SIZE - 2u)
#define STACK_LOCATION_LR       (STACK_SIZE - 3u)
#define STACK_LOCATION_R12      (STACK_SIZE - 4u)
#define STACK_LOCATION_R3       (STACK_SIZE - 5u)
#define STACK_LOCATION_R2       (STACK_SIZE - 6u)
#define STACK_LOCATION_R1       (STACK_SIZE - 7u)
#define STACK_LOCATION_R0       (STACK_SIZE - 8u)
#define STACK_LOCATION_R11      (STACK_SIZE - 9u)
#define STACK_LOCATION_R10      (STACK_SIZE - 10u)
#define STACK_LOCATION_R9       (STACK_SIZE - 11u)
#define STACK_LOCATION_R8       (STACK_SIZE - 12u)
#define STACK_LOCATION_R7       (STACK_SIZE - 13u)
#define STACK_LOCATION_R6       (STACK_SIZE - 14u)
#define STACK_LOCATION_R5       (STACK_SIZE - 15u)
#define STACK_LOCATION_R4       (STACK_SIZE - 16u)
#define INITIAL_STACK_POINTER   STACK_LOCATION_R4
#define END_OF_STACK            0

#define IN
#define OUT

typedef enum {
  OsSuccess,
  OsFailure,
  OsOutOfResource
} OS_STATUS;

typedef enum {
  Ready,
  Running,
  Waiting
} STATE;

struct ThreadControlBlock {
  uint32_t                    *StackPointer;
  uint32_t                    StackMem[STACK_SIZE];
  struct ThreadControlBlock   *Next;
  struct ThreadControlBlock   *Previous;
  uint32_t                    ThreadId;
  STATE                       Status;
  uint32_t                    Priority;
  uint32_t                    BlockedState;
};

typedef struct ThreadControlBlock THREAD_CONTROL_BLOCK;

typedef struct {
  void                  *CodeSection;
  void                  *DataSection;
  uint32_t              ProcessId;
  STATE                 Status;
  uint32_t              NumberOfThreads;
  uint32_t              Priority;
  THREAD_CONTROL_BLOCK  Tcbs[MAXIMUM_NUMBER_OF_THREADS];
} PROCESS_CONTROL_BLOCK;

/**

  Disable interrupts in the system

  @param N/A

  @retval N/A

**/
void
DisableInterrupts (
  void
  );

/**

  Enable interrupts in the system

  @param N/A

  @retval N/A

**/
void
EnableInterrupts (
  void
  );

/**

  Initialize the kernel

  @param N/A

  @retval N/A

**/
void
OsInit (
  void
  );

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
  );

#endif // _KERNEL_H_
