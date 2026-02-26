namespace carpc::os::sync
{

   class RecursiveMutex
   {
      public:
         RecursiveMutex() noexcept;
         ~RecursiveMutex() noexcept;

         RecursiveMutex( const RecursiveMutex& ) = delete;
         RecursiveMutex& operator=( const RecursiveMutex& ) = delete;

      public:
         void lock() noexcept;
         bool try_lock() noexcept;
         void unlock() noexcept;
   };

}
