namespace carpc::os::sync
{

   class SharedMutex
   {
      public:
         SharedMutex() noexcept;
         ~SharedMutex() noexcept;

         SharedMutex( const SharedMutex& ) = delete;
         SharedMutex& operator=( const SharedMutex& ) = delete;

      public:
         // Exclusive
         void lock() noexcept;
         bool try_lock() noexcept;
         void unlock() noexcept;

         // Shared
         void lock_shared() noexcept;
         bool try_lock_shared() noexcept;
         void unlock_shared() noexcept;
   };

}
