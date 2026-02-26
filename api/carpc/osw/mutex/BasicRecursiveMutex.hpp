#pragma once



namespace carpc::osw::mutex {

   template< typename BackendPolicy, typename DebugPolicy >
   class BasicRecursiveMutex
      : private BackendPolicy
      , private DebugPolicy
   {
      public:
         BasicRecursiveMutex( ) noexcept = default;
         ~BasicRecursiveMutex( ) noexcept = default;

         BasicRecursiveMutex( const BasicRecursiveMutex& ) = delete;
         BasicRecursiveMutex& operator=( const BasicRecursiveMutex& ) = delete;

         BasicRecursiveMutex( BasicRecursiveMutex&& ) = delete;
         BasicRecursiveMutex& operator=( BasicRecursiveMutex&& ) = delete;

      public:
         void lock( ) noexcept
         {
            DebugPolicy::before_lock( );
            BackendPolicy::lock( );
            DebugPolicy::after_lock( );
         }

         bool try_lock( ) noexcept
         {
            DebugPolicy::before_lock( );
            if( !BackendPolicy::try_lock( ) )
               return false;
            DebugPolicy::after_lock( );
            return true;
         }

         void unlock( ) noexcept
         {
            DebugPolicy::before_unlock( );
            BackendPolicy::unlock( );
            DebugPolicy::after_unlock( );
         }
   };

} // namespace carpc::osw::mutex
