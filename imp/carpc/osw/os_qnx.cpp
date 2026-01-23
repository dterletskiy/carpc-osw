#include "os_qnx.h"

#if !defined( CARPC_OS_QNX )
   #error This file is for QNX builds only
#endif

#include <unistd.h>
#include <pthread.h>
#include <time.h>



namespace carpc::osw::detail::os_qnx
{
   uint32_t process_id( )
   {
      return static_cast< uint32_t >( getpid( ) );
   }

   uint32_t thread_id( )
   {
      return static_cast< uint32_t >(
         reinterpret_cast< uintptr_t >( pthread_self( ) )
      );
   }

   uint64_t monotonic_time_ns( )
   {
      timespec ts;
      clock_gettime( CLOCK_MONOTONIC, &ts );

      return static_cast< uint64_t >( ts.tv_sec ) * 1000000000ULL +
             static_cast< uint64_t >( ts.tv_nsec );
   }
}
