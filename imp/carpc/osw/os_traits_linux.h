#pragma once

#if !defined( CARPC_OS_LINUX )
   #error This file is for Linux builds only
#endif

#include "os_linux.h"



namespace carpc::osw::detail
{
   namespace os_detail = os_linux;

   template< >
   struct os_traits< linux_tag >
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

      static uint64_t wall_time_ns( )
      {
         return os_detail::wall_time_ns( );
      }

      static void sleep_for_ns( uint64_t duration_ns )
      {
         os_detail::sleep_for_ns( duration_ns );
      }

      static void sleep_until_ns( uint64_t duration_ns )
      {
         os_detail::sleep_until_ns( duration_ns );
      }
   };
}
