#pragma once

#include <cstdint>



namespace carpc::osw::detail::os_linux
{

   uint32_t process_id( );
   uint32_t thread_id( );

   uint64_t monotonic_time_ns( );
   uint64_t wall_time_ns( );

   void sleep_for_ns( uint64_t duration_ns );
   void sleep_until_ns( uint64_t deadline_ns );

}
