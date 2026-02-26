#pragma once

#if !defined( CARPC_BUILD_OS_LINUX )
   #error This file is for Linux builds only
#endif

#include <pthread.h>
#include <string>



namespace carpc::osw::thread::backend::os_linux {

   class Thread
   {
      public:
         using NativeID     = pthread_t;
         using NativeHandle = pthread_t;
         using EntryFn = void* ( * )( void* );

      public:
         Thread( ) noexcept = default;
         Thread( const Thread& other ) = delete;
         Thread( Thread&& other ) noexcept;
         ~Thread( );

         Thread& operator=( const Thread& other ) = delete;
         Thread& operator=( Thread&& other ) noexcept;

      public:
         bool create( EntryFn entry, void* arg );
         bool join( );
         bool detach( );
         bool joinable( ) const noexcept;
         void set_name( const std::string& name );

      private:
         NativeHandle   m_handle{ };
         bool           m_joinable = false;
   };



   Thread::Thread( Thread&& other ) noexcept
   {
      m_handle    = other.m_handle;
      m_joinable  = other.m_joinable;
      other.m_joinable = false;
   }

   Thread::~Thread( )
   {
      if( m_joinable )
         pthread_detach( m_handle );
   }

   Thread& Thread::operator=( Thread&& other ) noexcept
   {
      if( this != &other )
      {
         m_handle   = other.m_handle;
         m_joinable = other.m_joinable;
         other.m_joinable = false;
      }
      return *this;
   }

   bool Thread::create( EntryFn entry, void* arg )
   {
      pthread_attr_t attr;
      pthread_attr_init( &attr );
      pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
      pthread_attr_setscope( &attr, PTHREAD_SCOPE_PROCESS );

      const int result =
         pthread_create( &m_handle, &attr, entry, arg );

      m_joinable = true;

      pthread_attr_destroy( &attr );

      return result == 0;
   }

   bool Thread::join( )
   {
      if( not m_joinable )
         return false;

      m_joinable = false;
      return pthread_join( m_handle, nullptr ) == 0;
   }

   bool Thread::detach( )
   {
      if( not m_joinable )
         return false;

      pthread_detach( m_handle );
      m_joinable = false;
      return true;
   }

   bool Thread::joinable( ) const noexcept
   {
      return m_joinable;
   }

   void Thread::set_name( const std::string& name )
   {
      pthread_setname_np( m_handle, name.c_str( ) );
   }

} // namespace carpc::osw::thread::backend::os_linux
