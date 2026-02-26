#pragma once

#if defined( CARPC_BUILD_POLICY_STD )
   #include "carpc/osw/mutex/backend/std/Mutex.hpp"
   #include "carpc/osw/mutex/backend/std/RecursiveMutex.hpp"
#else
   #if defined( CARPC_BUILD_OS_LINUX )
      #include "carpc/osw/mutex/backend/linux/Mutex.hpp"
      #include "carpc/osw/mutex/backend/linux/RecursiveMutex.hpp"
   #elif defined( CARPC_BUILD_OS_QNX )
      #include "carpc/osw/mutex/backend/qnx/Mutex.hpp"
      #include "carpc/osw/mutex/backend/qnx/RecursiveMutex.hpp"
   #elif defined( CARPC_BUILD_OS_RTOS )
      #include "carpc/osw/mutex/backend/rtos/Mutex.hpp"
      #include "carpc/osw/mutex/backend/rtos/RecursiveMutex.hpp"
   #else
      #error Unsupported operating system
   #endif
#endif



namespace carpc::osw::mutex::backend {

   #if defined( CARPC_BUILD_POLICY_STD )
      namespace nsBackendPolicy = os_std;
   #else
      #if defined( CARPC_BUILD_OS_LINUX )
         namespace nsBackendPolicy = os_linux;
      #elif defined( CARPC_BUILD_OS_QNX )
         namespace nsBackendPolicy = os_qnx;
      #elif defined( CARPC_BUILD_OS_RTOS )
         namespace nsBackendPolicy = os_rtos;
      #else
         #error Unsupported operating system
      #endif
   #endif

} // namespace carpc::osw::mutex::backend
