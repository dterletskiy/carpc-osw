#pragma once

#include <string>
#include <list>
#include <functional>
#include <memory>

#include "carpc/oswrappers/linux/kernel.hpp"
#include "carpc/oswrappers/linux/socket.hpp"
#include "carpc/base/common/ID.hpp"
#include "carpc/base/common/RawBuffer.hpp"



namespace carpc::os {

   class Socket
   {
      public:
         enum class eResult { OK, ERROR, DISCONNECTED };
         const char* c_str( const eResult );

         using ID = carpc::TID< Socket >;
         using tList = std::list< Socket >;
         using tSptr = std::shared_ptr< Socket >;
         using tWptr = std::weak_ptr< Socket >;
         using tSptrList = std::list< tSptr >;
         using tSptrSet = std::set< tSptr >;
         using tRecvCallback = std::function< void( void*, const size_t, const eResult ) >;

      public:
         ~Socket( );
      protected:
         Socket( const os_linux::socket::configuration&, const size_t );
         Socket( const os_linux::socket::tSocket, const size_t );
         Socket( const Socket& ) = delete;
         Socket( Socket&& );
      public:
         static tSptr create_shared( const os_linux::socket::configuration&, const size_t );
         static tSptr create_shared( const os_linux::socket::tSocket, const size_t );

      public:
         const bool operator<( const Socket& ) const;
      protected:
         Socket& operator=( const Socket& ) = delete;
         Socket& operator=( Socket&& );

      public:
         eResult create( );
         eResult bind( );
         eResult listen( );
         tSptr accept( );
         eResult connect( );
         eResult send( const void* p_buffer, const size_t size, const int flags = 0 );
         eResult recv( const int flags = 0 );
         eResult recv( tRecvCallback, const int flags = 0 );
         void close( );
         void info( const std::string& message ) const;

      public:
         void block( ) const;
         void unblock( ) const;

      public:
         os_linux::socket::tSocket socket( ) const;
         bool is_valid( ) const;
      protected:
         os_linux::socket::tSocket     m_socket = os_linux::socket::InvalidSocket;

      public:
         ID id( ) const;
      private:
         ID                            m_id = ID::generate( );

      public:
         const os_linux::socket::configuration& configuration( ) const;
      protected:
         os_linux::socket::configuration  m_configuration = { };

      public:
         const void* const buffer( size_t& ) const;
         RawBuffer buffer( ) const;
      protected:
         void fill_buffer( const char symbol = 0 );
      protected:
         void*                         mp_buffer = nullptr;
         size_t                        m_buffer_capacity = 0;
         size_t                        m_buffer_size = 0;
         size_t                        m_total_recv_size = 0;
         size_t                        m_total_send_size = 0;
   };



   inline
   os_linux::socket::tSocket Socket::socket( ) const
   {
      return m_socket;
   }

   inline
   bool Socket::is_valid( ) const
   {
      return os_linux::socket::InvalidSocket != m_socket;
   }

   inline
   Socket::ID Socket::id( ) const
   {
      return m_id;
   }

   inline
   void Socket::block( ) const
   {
   }

   inline
   void Socket::unblock( ) const
   {
      os_linux::set_nonblock( m_socket );
   }

   inline
   const os_linux::socket::configuration& Socket::configuration( ) const
   {
      return m_configuration;
   }

}



namespace carpc::os {

   class SocketClient: public Socket
   {
      public:
         using tSptr = std::shared_ptr< SocketClient >;

      public:
         ~SocketClient( );
      private:
         SocketClient( const os_linux::socket::configuration&, const size_t );
      public:
         static tSptr create_shared( const os_linux::socket::configuration&, const size_t );
   };

}



namespace carpc::os {

   class SocketServer: public Socket
   {
      public:
         using tSptr = std::shared_ptr< SocketServer >;

         struct IConsumer
         {
            virtual ~IConsumer( ) = default;
            virtual void connected( Socket::tSptr ) = 0;
            virtual void disconnected( Socket::tSptr ) = 0;
            virtual void read_slave( Socket::tSptr ) = 0;
         };

      public:
         ~SocketServer( );
      private:
         SocketServer( const os_linux::socket::configuration&, const size_t, IConsumer& );
      public:
         static tSptr create_shared( const os_linux::socket::configuration&, const size_t, IConsumer& );

      public:
         bool select( );

      private:
         void fd_reset( );
         void fd_init( );

      public:
         os_linux::socket::tSocket max_socket( ) const;
      private:
         void calc_max( );
         os_linux::socket::tSocket     m_max_socket = -1;

      private:
         tSptrList                     m_slave_sockets;
         os_linux::socket::fds         m_fd;
         IConsumer&                    m_consumer;
   };



   inline
   os_linux::socket::tSocket SocketServer::max_socket( ) const
   {
      return m_max_socket;
   }

}
