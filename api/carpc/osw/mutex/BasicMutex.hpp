#pragma once



namespace carpc::osw::mutex {

   template< typename BackendPolicy, typename DebugPolicy >
   class BasicMutex
      : private BackendPolicy
      , private DebugPolicy
   {
      public:
         BasicMutex( ) noexcept = default;
         ~BasicMutex( ) noexcept = default;

         BasicMutex( const BasicMutex& ) = delete;
         BasicMutex& operator=( const BasicMutex& ) = delete;

         BasicMutex( BasicMutex&& ) = delete;
         BasicMutex& operator=( BasicMutex&& ) = delete;

      public:
         void lock( ) noexcept;
         bool try_lock( ) noexcept;
         void unlock( ) noexcept;
   };



   template< typename BackendPolicy, typename DebugPolicy >
   void BasicMutex< BackendPolicy, DebugPolicy >::lock( ) noexcept
   {
      DebugPolicy::before_lock( );
      BackendPolicy::lock( );
      DebugPolicy::after_lock( );
   }

   template< typename BackendPolicy, typename DebugPolicy >
   bool BasicMutex< BackendPolicy, DebugPolicy >::try_lock( ) noexcept
   {
      DebugPolicy::before_lock( );
      if( !BackendPolicy::try_lock( ) )
         return false;
      DebugPolicy::after_lock( );
      return true;
   }

   template< typename BackendPolicy, typename DebugPolicy >
   void BasicMutex< BackendPolicy, DebugPolicy >::unlock( ) noexcept
   {
      DebugPolicy::before_unlock( );
      BackendPolicy::unlock( );
      DebugPolicy::after_unlock( );
   }

} // namespace carpc::osw::mutex
