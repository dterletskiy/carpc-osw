namespace carpc::os::sync
{

   class TimedMutex
   {
      public:
         TimedMutex() noexcept;
         ~TimedMutex() noexcept;

         TimedMutex( const TimedMutex& ) = delete;
         TimedMutex& operator=( const TimedMutex& ) = delete;

      public:
         void lock() noexcept;
         bool try_lock() noexcept;
         void unlock() noexcept;

         template< typename Rep, typename Period >
         bool try_lock_for(
            const std::chrono::duration< Rep, Period >& timeout
         ) noexcept;

         template< typename Clock, typename Duration >
         bool try_lock_until(
            const std::chrono::time_point< Clock, Duration >& time_point
         ) noexcept;
   };

}
