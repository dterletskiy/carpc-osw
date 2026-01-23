#include "os_rtos.h"

#if !defined( CARPC_OS_RTOS )
   #error This file is for RTOS builds only
#endif



namespace carpc::osw::detail::os_rtos
{
   uint32_t process_id( )
   {
      return 0U;
   }

   uint32_t thread_id( )
   {
      return rtos_thread_id( );
   }

   uint64_t monotonic_time_ns( )
   {
      return rtos_time_ns( );
   }
}
