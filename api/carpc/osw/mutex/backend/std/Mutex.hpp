#pragma once

#include <mutex>



namespace carpc::osw::mutex::backend::os_std {

   class Mutex
   {
      public:
         Mutex( ) noexcept = default;
         ~Mutex( ) noexcept = default;

         Mutex( const Mutex& ) = delete;
         Mutex& operator=( const Mutex& ) = delete;

         void lock( ) noexcept
         {
            m_mutex.lock( );
         }

         bool try_lock( ) noexcept
         {
            return m_mutex.try_lock( );
         }

         void unlock( ) noexcept
         {
            m_mutex.unlock( );
         }

      private:
         std::mutex m_mutex;
   };

} // namespace carpc::osw::mutex::backend::os_std
