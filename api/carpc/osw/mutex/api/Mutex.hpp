namespace carpc::os::sync
{

   class Mutex
   {
      public:
         Mutex() noexcept;
         ~Mutex() noexcept;

         Mutex( const Mutex& ) = delete;
         Mutex& operator=( const Mutex& ) = delete;

         Mutex( Mutex&& ) = delete;
         Mutex& operator=( Mutex&& ) = delete;

      public:
         void lock() noexcept;
         bool try_lock() noexcept;
         void unlock() noexcept;

      public:
         // Optional debug hook
         bool is_locked() const noexcept;   // debug only
   };

}
