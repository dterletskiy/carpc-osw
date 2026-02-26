#pragma once

#if !defined( CARPC_BUILD_OS_LINUX )
   #error This file is for Linux builds only
#endif

#include <pthread.h>



namespace carpc::osw::mutex::backend::os_linux {

   class RecursiveMutex
   {
      public:
         RecursiveMutex( ) noexcept
         {
            pthread_mutexattr_init( &m_attr );
            pthread_mutexattr_settype( &m_attr, PTHREAD_MUTEX_RECURSIVE );
            pthread_mutex_init( &m_mutex, &m_attr );
         }

         ~RecursiveMutex( ) noexcept
         {
            pthread_mutex_destroy( &m_mutex );
            pthread_mutexattr_destroy( &m_attr );
         }

         RecursiveMutex( const RecursiveMutex& ) = delete;
         RecursiveMutex& operator=( const RecursiveMutex& ) = delete;

      public:
         void lock( ) noexcept
         {
            pthread_mutex_lock( &m_mutex );
         }

         bool try_lock( ) noexcept
         {
            return pthread_mutex_trylock( &m_mutex ) == 0;
         }

         void unlock( ) noexcept
         {
            pthread_mutex_unlock( &m_mutex );
         }

      private:
         pthread_mutex_t     m_mutex;
         pthread_mutexattr_t m_attr;
   };

} // namespace carpc::osw::mutex::backend::os_linux
