#include "carpc/trace/trace.h"



#include "carpc/osw/osw.h"
#include "carpc/osw/mutex.h"
#include "carpc/osw/thread.h"

namespace test::osw {

   void run_all( )
   {
      CARPC_TRACE_LOG_TRACE( "process_id: %lu",
            carpc::osw::process_id( )
         );
      CARPC_TRACE_LOG_TRACE( "thread_id: %lu",
            carpc::osw::thread_id( )
         );
      CARPC_TRACE_LOG_TRACE( "monotonic_time_ns: %llu",
            carpc::osw::monotonic_time_ns( )
         );
      CARPC_TRACE_LOG_TRACE( "wall_time_ns: %llu",
            carpc::osw::wall_time_ns( )
         );

      carpc::osw::Mutex mutex;
      mutex.try_lock( );
      mutex.unlock( );

      auto ep = [ ]( )
      {
         for( size_t i = 0; i < 1000; ++i )
            CARPC_TRACE_LOG_TRACE( "%zu", i );
      };
      carpc::osw::Thread thread( ep );
      thread.run( );
      thread.join( );

      CARPC_TRACE_LOG_TRACE( "[TName] All tests passed." );
   }

}



int main( )
{
   carpc::trace::StdoutSink sink;
   carpc::trace::Runtime::start( &sink );

   test::osw::run_all( );

   carpc::trace::Runtime::stop( );

   return 0;
}
