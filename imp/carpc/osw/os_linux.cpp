#include "os_linux.h"

#if !defined( CARPC_BUILD_OS_LINUX )
   #error This file is for Linux builds only
#endif

#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>



namespace carpc::osw::detail::os_linux
{
   uint32_t process_id( )
   {
      return static_cast< uint32_t >( getpid( ) );
   }

   uint32_t thread_id( )
   {
      static thread_local uint32_t t
         = static_cast< uint32_t >( syscall( SYS_gettid ) );
      return t;
   }

   uint64_t monotonic_time_ns( )
   {
      timespec ts;
      clock_gettime( CLOCK_MONOTONIC_RAW, &ts );

      return static_cast< uint64_t >( ts.tv_sec ) * 1000000000ULL +
             static_cast< uint64_t >( ts.tv_nsec );
   }

   uint64_t wall_time_ns( )
   {
      timespec ts;
      clock_gettime( CLOCK_REALTIME, &ts );

      return static_cast< uint64_t >( ts.tv_sec ) * 1000000000ULL +
             static_cast< uint64_t >( ts.tv_nsec );
   }

   void sleep_for_ns( uint64_t duration_ns )
   {
      timespec ts;
      ts.tv_sec  = duration_ns / 1000000000ULL;
      ts.tv_nsec = duration_ns % 1000000000ULL;

      nanosleep( &ts, nullptr );
   }

   void sleep_until_ns( uint64_t deadline_ns )
   {
      const uint64_t now = monotonic_time_ns( );

      if( deadline_ns <= now )
      {
         return;
      }

      sleep_for_ns( deadline_ns - now );
   }
}
