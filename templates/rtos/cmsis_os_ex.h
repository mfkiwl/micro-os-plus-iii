/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
 * Copyright (c) 2013 ARM LIMITED
 *
 * µOS++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * µOS++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This file is part of the CMSIS++ proposal, intended as a CMSIS
 * replacement for C++ applications.
 *
 * The code extends the ARM CMSIS cmsis_os.h file, v1.02,
 * with several new calls, similar to those available in the
 * C++ version.
 */

#ifndef CMSIS_OS_EX_H_
#define CMSIS_OS_EX_H_

#include <cmsis_os.h>

#include <cstddef>

// ----------------------------------------------------------------------------

#ifdef  __cplusplus
extern "C"
{
#endif

  // --------------------------------------------------------------------------

  // ===== Thread Management =====

  osThreadId
  osThreadCreateEx (osThread* addr, const char* name, void* stack,
                    size_t stack_size_bytes, osPriority prio,
                    os_pthread function, const void* args);

  // --------------------------------------------------------------------------

  // ===== Generic Wait Functions =====

  osStatus
  osWaitEx (uint32_t millisec);

  // --------------------------------------------------------------------------

  // ===== Timer Management Functions =====

  osTimerId
  osTimerCreateEx (osTimer* addr, const char* name, os_ptimer function,
                   os_timer_type type, void* args);

  // --------------------------------------------------------------------------

  // ===== Signal Management =====

  osStatus
  osSignalWaitEx (int32_t signals, uint32_t millisec);

  // --------------------------------------------------------------------------

  // ===== Mutex Management =====

  osMutexId
  osMutexCreateEx (osMutex* addr, const char* name);

// ===== Semaphore Management Functions =====

#if (defined (osFeature_Semaphore)  &&  (osFeature_Semaphore != 0))

  osSemaphoreId
  osSemaphoreCreateEx (osSemaphoreId addr, const char* name,
                       int32_t initial_count, uint32_t max_count);

#endif /* osFeature_Semaphore */

  // --------------------------------------------------------------------------

  // ===== Memory Pool Management Functions =====

#if (defined (osFeature_Pool)  &&  (osFeature_Pool != 0))

  osPoolId
  osPoolCreateEx (osPool* addr, const char* name, size_t items,
                  uint32_t item_size, void* mem);

  void
  osPoolDeleteEx (osPoolId pool_id);

#endif /* osFeature_Pool */

  // --------------------------------------------------------------------------

  // ===== Message Queue Management Functions =====

#if (defined (osFeature_MessageQ)  &&  (osFeature_MessageQ != 0))

  osMessageQId
  osMessageCreateEx (osMessageQ* addr, const char* name, size_t items,
                     void* mem, osThreadId thread_id);

  osStatus
  osMessageGetEx (osMessageQId queue_id, uint32_t millisec);

  void
  osMessageDeleteEx (osMessageQId queue_id);

#endif /* osFeature_MessageQ */

  // --------------------------------------------------------------------------

  // ===== Mail Queue Management Functions =====

#if (defined (osFeature_MailQ)  &&  (osFeature_MailQ != 0))

  osMailQId
  osMailCreateEx (osMailQ* addr, const char* name, size_t messages,
                  size_t message_size, void* mem, osThreadId thread_id);

  osStatus
  osMailGetEx (osMailQId queue_id, uint32_t millisec);

  void
  osMailDeleteEx (osMailQId queue_id);

#endif /* osFeature_MailQ */

// ============================================================================

// ----- Scheduler critical sections. -----

  typedef uint32_t scheduler_status_t;

  scheduler_status_t
  osSchedulerLock (void);

  void
  osSchedulerUnlock (scheduler_status_t);

  // ----- Interrupt critical sections. -----

  typedef uint32_t interrupts_status_t;

  interrupts_status_t
  osCriticalEnter (void);

  void
  osCriticalExit (interrupts_status_t);

  // ----- Memory allocation. -----

  void*
  osMalloc (size_t);

  void
  osFree (void*);

// --------------------------------------------------------------------------
// Calls from Interrupt Service Routines
//
// The following CMSIS-RTOS functions can be called from threads and Interrupt Service Routines (ISR):
//
// - osCriticalEnter, osCriticalExit (although with little effect)

#ifdef  __cplusplus
}
#endif

#endif /* CMSIS_OS_EX_H_ */