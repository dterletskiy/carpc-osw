#pragma once

#include <mutex>



namespace carpc::osw::mutex::backend::os_std {

   class RecursiveMutex
   {
      public:
         RecursiveMutex( ) noexcept = default;
         ~RecursiveMutex( ) noexcept = default;

         RecursiveMutex( const RecursiveMutex& ) = delete;
         RecursiveMutex& operator=( const RecursiveMutex& ) = delete;

      public:
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
         std::recursive_mutex m_mutex;
   };

} // namespace carpc::osw::mutex::backend::os_std
