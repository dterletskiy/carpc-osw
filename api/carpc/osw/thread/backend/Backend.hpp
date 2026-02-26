#pragma once

#if defined( CARPC_BUILD_POLICY_STD )
   #include "carpc/osw/thread/backend/std/Thread.hpp"
#else
   #if defined( CARPC_BUILD_OS_LINUX )
      #include "carpc/osw/thread/backend/linux/Thread.hpp"
   #elif defined( CARPC_BUILD_OS_QNX )
      #include "carpc/osw/thread/backend/qnx/Thread.hpp"
   #elif defined( CARPC_BUILD_OS_RTOS )
      #include "carpc/osw/thread/backend/rtos/Thread.hpp"
   #else
      #error Unsupported operating system
   #endif
#endif



namespace carpc::osw::thread::backend {

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

} // namespace carpc::osw::thread::backend
