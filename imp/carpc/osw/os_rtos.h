#pragma once

#include <cstdint>



extern "C"
{
   uint32_t rtos_thread_id( );
   uint64_t rtos_time_ns( );
}

namespace carpc::osw::detail::os_rtos
{
   uint32_t process_id( );
   uint32_t thread_id( );

   uint64_t monotonic_time_ns( );
}
