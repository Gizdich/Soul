/*

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

*/
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <stack.h>
#include <stdint.h>

#define MAXIMUM_NUMBER_OF_PROCESSES 1u
#define MAXIMUM_NUMBER_OF_THREADS   10u

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

  Initialize the kernel

**/
void
osInit (
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
osAddForegroundThread (
  IN  void      (*Thread)(void),
  IN  uint32_t  StackSize,
  IN  uint32_t  Priority
  );

#endif // _KERNEL_H_
