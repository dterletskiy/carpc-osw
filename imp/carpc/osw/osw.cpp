#include "carpc/osw/osw.h"
#include "os_traits.h"



namespace carpc::osw
{
   uint32_t process_id( )
   {
      return detail::os_traits< detail::current_os >::process_id( );
   }

   uint32_t thread_id( )
   {
      return detail::os_traits< detail::current_os >::thread_id( );
   }

   uint64_t monotonic_time_ns( )
   {
      return detail::os_traits< detail::current_os >::monotonic_time_ns( );
   }

   uint64_t wall_time_ns( )
   {
      return detail::os_traits< detail::current_os >::wall_time_ns( );
   }

   void sleep_for_ns( uint64_t duration_ns )
   {
      detail::os_traits< detail::current_os >::sleep_for_ns( duration_ns );
   }

   void sleep_until_ns( uint64_t duration_ns )
   {
      detail::os_traits< detail::current_os >::sleep_until_ns( duration_ns );
   }
}
