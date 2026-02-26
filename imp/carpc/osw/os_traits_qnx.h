#pragma once

#if !defined( CARPC_BUILD_OS_QNX )
   #error This file is for QNX builds only
#endif

#include "os_qnx.h"



namespace carpc::osw::detail
{
   namespace os_detail = os_qnx;

   template< >
   struct os_traits< qnx_tag >
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

