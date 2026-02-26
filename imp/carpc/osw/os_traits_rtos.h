#pragma once

#if !defined( CARPC_BUILD_OS_RTOS )
   #error This file is for RTOS builds only
#endif

#include "os_rtos.h"



namespace carpc::osw::detail
{
   namespace os_detail = os_rtos;

   template< >
   struct os_traits< rtos_tag >
   {
      static uint32_t process_id( )
      {
         return os_detail::process_id( );
      }

      static uint32_t thread_id( )
      {
         return os_detail::thread_id( );
      }

      static uint64_t monotonic_time_ns( )
      {
         return os_detail::monotonic_time_ns( );
      }
   };
}
