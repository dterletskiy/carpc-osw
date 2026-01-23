#pragma once

#include <cstdint>



namespace carpc::osw::detail::os_qnx
{
   uint32_t process_id( );
   uint32_t thread_id( );

   uint64_t monotonic_time_ns( );
}
