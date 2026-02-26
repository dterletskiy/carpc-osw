class SpinMutex
{
public:
   void lock() noexcept;
   bool try_lock() noexcept;
   void unlock() noexcept;
};
