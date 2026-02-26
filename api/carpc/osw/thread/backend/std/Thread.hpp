#pragma once

#include <thread>
#include <string>



namespace carpc::osw::thread::backend::os_std {

   class Thread
   {
      public:
         using NativeID     = std::thread::id;
         using NativeHandle = std::thread::native_handle_type;
         using EntryFn      = void* ( * )( void* );

      public:
         Thread( ) noexcept = default;
         Thread( const Thread& ) = delete;
         Thread( Thread&& other ) noexcept;
         ~Thread( );

         Thread& operator=( const Thread& ) = delete;
         Thread& operator=( Thread&& other ) noexcept;

      public:
         bool create( EntryFn entry, void* arg );
         bool join( );
         bool detach( );
         bool joinable( ) const noexcept;
         void set_name( const std::string& name );

      private:
         std::thread  m_thread;
         bool         m_joinable = false;
   };



   Thread::Thread( Thread&& other ) noexcept
      : m_thread( std::move( other.m_thread ) )
      , m_joinable( other.m_joinable )
   {
      other.m_joinable = false;
   }

   Thread::~Thread( )
   {
      if( m_joinable )
         m_thread.detach( );
   }

   Thread& Thread::operator=( Thread&& other ) noexcept
   {
      if( this != &other )
      {
         if( m_joinable )
            m_thread.detach( );

         m_thread   = std::move( other.m_thread );
         m_joinable = other.m_joinable;
         other.m_joinable = false;
      }

      return *this;
   }

   bool Thread::create( EntryFn entry, void* arg )
   {
      if( m_joinable )
         return false;

      try
      {
         m_thread = std::thread(
               [ entry, arg ]( )
               {
                  entry( arg );
               }
            );

         m_joinable = true;
      }
      catch( ... )
      {
         return false;
      }

      return true;
   }

   bool Thread::join( )
   {
      if( not m_joinable )
         return false;

      m_thread.join();
      m_joinable = false;
      return true;
   }

   bool Thread::detach( )
   {
      if( not m_joinable )
         return false;

      m_thread.detach();
      m_joinable = false;
      return true;
   }

   bool Thread::joinable( ) const noexcept
   {
      return m_joinable && m_thread.joinable();
   }

   void Thread::set_name( const std::string& )
   {
      // std::thread has no portable API for naming threads.
      // Intentionally left empty.
   }

} // namespace carpc::osw::thread::backend::os_std
