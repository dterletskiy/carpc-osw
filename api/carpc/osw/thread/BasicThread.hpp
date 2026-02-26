#pragma once

#include <string>
#include <utility>

#include "carpc/base/types/ID.hpp"
#include "carpc/base/callable/CallableStorage.hpp"



namespace carpc::osw::thread {

   template< typename BackendPolicy, typename DebugPolicy >
   class BasicThread
      : private BackendPolicy
      , private DebugPolicy
   {
      public:
         using tThread = BasicThread< BackendPolicy, DebugPolicy >;
         using ID = TID< tThread >;

      public:
         template< typename Fn, typename... Args >
         explicit BasicThread( Fn&& fn, Args&&... args );

         BasicThread( const BasicThread& ) = delete;

         ~BasicThread( );

         BasicThread& operator=( const BasicThread& ) = delete;

      public:
         bool run( const std::string& name = "NoName" );

         bool join( );

         void detach( );

         bool joinable( ) const noexcept;

         const ID& id( ) const;

         const std::string& name( ) const;

      private:
         static void* entry_point( void* arg );

      private:
         callable::CallableStorage< >  m_callable;
         ID                            m_id = ID::generate( );
         std::string                   m_name = "NoName";
         bool                          m_created = false;
   };



   template< typename BackendPolicy, typename DebugPolicy >
   template< typename Fn, typename... Args >
   BasicThread< BackendPolicy, DebugPolicy >::BasicThread( Fn&& fn, Args&&... args )
   {
      m_callable.set(
            [ func = std::forward< Fn >( fn ),
              ... as = std::forward< Args >( args ) ]( ) mutable
            {
               std::invoke(
                  std::move( func ),
                  std::move( as )...
               );
            }
         );
   }

   template< typename BackendPolicy, typename DebugPolicy >
   BasicThread< BackendPolicy, DebugPolicy >::~BasicThread( )
   {
      if( m_created )
         std::terminate( );
   }

   template< typename BackendPolicy, typename DebugPolicy >
   bool BasicThread< BackendPolicy, DebugPolicy >::run( const std::string& name )
   {
      DebugPolicy::before_start( );

      if( m_created || !m_callable.valid( ) )
         return false;

      if( !BackendPolicy::create( &tThread::entry_point, this ) )
         return false;

      m_created = true;
      m_name = name;

      BackendPolicy::set_name( m_name );

      DebugPolicy::after_start( );
      return true;
   }

   template< typename BackendPolicy, typename DebugPolicy >
   bool BasicThread< BackendPolicy, DebugPolicy >::join( )
   {
      DebugPolicy::before_join( );

      if( !m_created )
         return false;

      if( !BackendPolicy::join( ) )
         return false;

      m_created = false;

      DebugPolicy::after_join( );
      return true;
   }

   template< typename BackendPolicy, typename DebugPolicy >
   void BasicThread< BackendPolicy, DebugPolicy >::detach( )
   {
      BackendPolicy::detach( );
   }

   template< typename BackendPolicy, typename DebugPolicy >
   bool BasicThread< BackendPolicy, DebugPolicy >::joinable( ) const noexcept
   {
      return BackendPolicy::joinable( );
   }

   template< typename BackendPolicy, typename DebugPolicy >
   const BasicThread< BackendPolicy, DebugPolicy >::ID& BasicThread< BackendPolicy, DebugPolicy >::id( ) const
   {
      return m_id;
   }

   template< typename BackendPolicy, typename DebugPolicy >
   const std::string& BasicThread< BackendPolicy, DebugPolicy >::name( ) const
   {
      return m_name;
   }

   template< typename BackendPolicy, typename DebugPolicy >
   void* BasicThread< BackendPolicy, DebugPolicy >::entry_point( void* arg )
   {
      tThread* self = static_cast< tThread* >( arg );

      try
      {
         self->m_callable( );
      }
      catch( ... )
      {
         std::terminate( );
      }

      return nullptr;
   }

} // namespace carpc::osw::thread
