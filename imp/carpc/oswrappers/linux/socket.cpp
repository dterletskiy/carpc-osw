#include <string.h>
#include <errno.h>
#include <cstring>

#include "carpc/oswrappers/linux/kernel.hpp"
#include "carpc/oswrappers/linux/socket.hpp"
#include "carpc/base/helpers/functions/format.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "Socket"



namespace carpc::os::os_linux::socket {

   int thread_local error = 0;



   const char* const socket_domain_to_string( const int domain )
   {
      switch( domain )
      {
         case AF_UNIX:        return "AF_UNIX"; // "AF_LOCAL" - Synonym for "AF_UNIX"
         case AF_INET:        return "AF_INET";
         case AF_AX25:        return "AF_AX25";
         case AF_IPX:         return "AF_IPX";
         case AF_APPLETALK:   return "AF_APPLETALK";
         case AF_X25:         return "AF_X25";
         case AF_INET6:       return "AF_INET6";
         case AF_DECnet:      return "AF_DECnet";
         case AF_KEY:         return "AF_KEY";
         case AF_NETLINK:     return "AF_NETLINK";
         case AF_PACKET:      return "AF_PACKET";
         case AF_RDS:         return "AF_RDS";
         case AF_PPPOX:       return "AF_PPPOX";
         case AF_LLC:         return "AF_LLC";
         case AF_CAN:         return "AF_CAN";
         case AF_TIPC:        return "AF_TIPC";
         case AF_BLUETOOTH:   return "AF_BLUETOOTH";
         case AF_ALG:         return "AF_ALG";
         case AF_VSOCK:       return "AF_VSOCK";
         case AF_KCM:         return "AF_KCM";
      #if OS_TARGET == OS_LINUX
         case AF_IB:          return "AF_IB";
         case AF_MPLS:        return "AF_MPLS";
         case AF_XDP:         return "AF_XDP";
      #endif
         default:             return "AF_UNDEFINED";
      }
      return "AF_UNDEFINED";
   }

   int socket_domain_from_string( const char* const domain )
   {
      if     ( 0 == std::strcmp( domain, "AF_UNIX" )        ) return AF_UNIX;
      else if( 0 == std::strcmp( domain, "AF_LOCAL" )       ) return AF_LOCAL;
      else if( 0 == std::strcmp( domain, "AF_INET" )        ) return AF_INET;
      else if( 0 == std::strcmp( domain, "AF_AX25" )        ) return AF_AX25;
      else if( 0 == std::strcmp( domain, "AF_IPX" )         ) return AF_IPX;
      else if( 0 == std::strcmp( domain, "AF_APPLETALK" )   ) return AF_APPLETALK;
      else if( 0 == std::strcmp( domain, "AF_X25" )         ) return AF_X25;
      else if( 0 == std::strcmp( domain, "AF_INET6" )       ) return AF_INET6;
      else if( 0 == std::strcmp( domain, "AF_DECnet" )      ) return AF_DECnet;
      else if( 0 == std::strcmp( domain, "AF_KEY" )         ) return AF_KEY;
      else if( 0 == std::strcmp( domain, "AF_NETLINK" )     ) return AF_NETLINK;
      else if( 0 == std::strcmp( domain, "AF_PACKET" )      ) return AF_PACKET;
      else if( 0 == std::strcmp( domain, "AF_RDS" )         ) return AF_RDS;
      else if( 0 == std::strcmp( domain, "AF_PPPOX" )       ) return AF_PPPOX;
      else if( 0 == std::strcmp( domain, "AF_LLC" )         ) return AF_LLC;
      else if( 0 == std::strcmp( domain, "AF_CAN" )         ) return AF_CAN;
      else if( 0 == std::strcmp( domain, "AF_TIPC" )        ) return AF_TIPC;
      else if( 0 == std::strcmp( domain, "AF_BLUETOOTH" )   ) return AF_BLUETOOTH;
      else if( 0 == std::strcmp( domain, "AF_ALG" )         ) return AF_ALG;
      else if( 0 == std::strcmp( domain, "AF_VSOCK" )       ) return AF_VSOCK;
      else if( 0 == std::strcmp( domain, "AF_KCM" )         ) return AF_KCM;
   #if OS_TARGET == OS_LINUX
      else if( 0 == std::strcmp( domain, "AF_IB" )          ) return AF_IB;
      else if( 0 == std::strcmp( domain, "AF_MPLS" )        ) return AF_MPLS;
      else if( 0 == std::strcmp( domain, "AF_XDP" )         ) return AF_XDP;
   #endif
      else                                                    return -1;

      return -1;
   }

   const char* const socket_type_to_string( const int type )
   {
      switch( type )
      {
         case SOCK_STREAM:    return "SOCK_STREAM";
         case SOCK_DGRAM:     return "SOCK_DGRAM";
         case SOCK_SEQPACKET: return "SOCK_SEQPACKET";
         case SOCK_RAW:       return "SOCK_RAW";
         case SOCK_RDM:       return "SOCK_RDM";
         case SOCK_PACKET:    return "SOCK_PACKET";
         default:             return "SOCK_UNDEFINED";
      }
      return "SOCK_UNDEFINED";
   }

   int socket_type_from_string( const char* const type )
   {
      if     ( 0 == std::strcmp( type, "SOCK_STREAM" )    ) return SOCK_STREAM;
      else if( 0 == std::strcmp( type, "SOCK_DGRAM" )     ) return SOCK_DGRAM;
      else if( 0 == std::strcmp( type, "SOCK_SEQPACKET" ) ) return SOCK_SEQPACKET;
      else if( 0 == std::strcmp( type, "SOCK_RAW" )       ) return SOCK_RAW;
      else if( 0 == std::strcmp( type, "SOCK_RDM" )       ) return SOCK_RDM;
      else if( 0 == std::strcmp( type, "SOCK_PACKET" )    ) return SOCK_PACKET;
      else                                                  return -1;

      return -1;
   }

   const char* const vsock_cid_to_string( const unsigned int cid )
   {
      switch( cid )
      {
         case VMADDR_CID_ANY:          return "VMADDR_CID_ANY";
         case VMADDR_CID_HYPERVISOR:   return "VMADDR_CID_HYPERVISOR";
         case VMADDR_CID_LOCAL:        return "VMADDR_CID_LOCAL";
         case VMADDR_CID_HOST:         return "VMADDR_CID_HOST";
         default:                      return "VMADDR_CID_UNDEFINED";
      }
      return "VMADDR_CID_UNDEFINED";
   }

   unsigned int vsock_cid_from_string( const char* const cid )
   {
      if     ( 0 == std::strcmp( cid, "VMADDR_CID_ANY" )          ) return VMADDR_CID_ANY;
      else if( 0 == std::strcmp( cid, "VMADDR_CID_HYPERVISOR" )   ) return VMADDR_CID_HYPERVISOR;
      else if( 0 == std::strcmp( cid, "VMADDR_CID_LOCAL" )        ) return VMADDR_CID_LOCAL;
      else if( 0 == std::strcmp( cid, "VMADDR_CID_HOST" )         ) return VMADDR_CID_HOST;
      else                                                          return -2u;

      return -2u;
   }



   configuration::configuration( int dm, int tp, int pr, const std::string& a, int p )
      : domain( dm )
      , type( tp )
      , protocole( pr )
      , address( a )
      , port( p )
   {
   }

   configuration::configuration( const tSocket _socket )
   {
      socklen_t addrlen = 0;
      if( false == carpc::os::os_linux::socket::getsockname( _socket, nullptr, &addrlen ) )
         return;

      struct sockaddr* addr = (sockaddr*)malloc( addrlen );
      carpc::os::os_linux::socket::getsockname( _socket, addr , &addrlen );

      domain = addr->sa_family;

      socklen_t type_len = sizeof( type );
      if( false == carpc::os::os_linux::socket::getsockopt( _socket, SOL_SOCKET, SO_TYPE, &type, &type_len ) )
         return;

      protocole = 0;

      switch( domain )
      {
         case AF_UNIX:
         {
            address = ((sockaddr_un*)addr)->sun_path;
            break;
         }
         case AF_INET:
         {
            static thread_local char ip[ INET_ADDRSTRLEN ];
            inet_ntop( AF_INET, &(((sockaddr_in*)addr)->sin_addr), ip, INET_ADDRSTRLEN );

            address = ip;
            port = htons( ((sockaddr_in*)addr)->sin_port );
            break;
         }
         case AF_INET6:
         {
            static thread_local char ip[ INET6_ADDRSTRLEN ];
            inet_ntop( AF_INET6, &(((sockaddr_in6*)addr)->sin6_addr), ip, INET6_ADDRSTRLEN );

            address = ip;
            port = ((sockaddr_in6*)addr)->sin6_port;
            break;
         }
         case AF_VSOCK:
         {
            address = std::to_string( ((sockaddr_vm*)addr)->svm_cid );
            port = htons( ((sockaddr_vm*)addr)->svm_port );
            break;
         }
         default:
         {
            SYS_ERR( "undefined socket family: %d", domain );
            break;
         }
      }

      free( addr );
   }

   configuration::configuration( const configuration& _config )
      : domain( _config.domain )
      , type( _config.type )
      , protocole( _config.protocole )
      , address( _config.address )
      , port( _config.port )
   {
   }

   configuration& configuration::operator=( const configuration& _config )
   {
      if( this == &_config )
         return *this;

      domain = _config.domain;
      type = _config.type;
      protocole = _config.protocole;
      address = _config.address;
      port = _config.port;

      return *this;
   }

   bool configuration::operator==( const configuration& other ) const
   {
      return ( other.domain == domain ) && ( other.type == type ) && ( other.protocole == protocole )
               && ( other.address == address ) && ( other.port == port );
   }

   bool configuration::operator!=( const configuration& other ) const
   {
      return !( *this == other );
   }

   bool configuration::eq( const configuration& other ) const
   {
      return ( other.address == address ) && ( other.port == port );
   }

   const std::string configuration::dbg_name( ) const
   {
      return carpc::format_string( domain, ".", type, ".", protocole, "-", address, ":", port );
   }

   void configuration::print( const std::string& _message ) const
   {
      SYS_INF(
         "%s => domain: %d / type: %d / protocole: %d / address: %s / port: %d",
         _message.c_str( ), domain, type, protocole, address.c_str( ), port
      );
   }



   socket_addr::socket_addr( const int _domain, const char* const _address, const int _port )
   {
      init( _domain, _address, _port );
   }

   socket_addr::socket_addr( const configuration& _config )
   {
      init( _config.domain, _config.address.c_str( ), _config.port );
   }

   socket_addr::socket_addr( const tSocket _socket )
   {
      if( false == carpc::os::os_linux::socket::getsockname( _socket, nullptr, &m_len ) )
         return;

      m_addr = (sockaddr*)malloc( m_len );

      carpc::os::os_linux::socket::getsockname( _socket, m_addr , &m_len );
   }

   socket_addr::~socket_addr( )
   {
      free( m_addr );
   }

   void socket_addr::init( const int _domain, const char* const _address, const int _port )
   {
      switch( _domain )
      {
         case AF_UNIX:
         {
            struct sockaddr_un* addr_un = (sockaddr_un*)malloc( sizeof( sockaddr_un ) );
            memset( addr_un, 0, sizeof( sockaddr_un ) );

            addr_un->sun_family = _domain;
            if( _address )
            {
               strncpy( addr_un->sun_path, _address, sizeof( addr_un->sun_path ) - 1 );
            }

            m_addr = reinterpret_cast< sockaddr* >( addr_un );
            // m_len = sizeof( addr_un->sun_family ) + strlen( addr_un->sun_path );
            m_len = sizeof( sockaddr_un );
            break;
         }
         case AF_INET:
         {
            struct sockaddr_in* addr_in = (sockaddr_in*)malloc( sizeof( sockaddr_in ) );
            memset( addr_in, 0, sizeof( sockaddr_in ) );

            addr_in->sin_family = _domain;
            if( _address )
            {
               addr_in->sin_addr.s_addr = inet_addr( _address );
            }
            addr_in->sin_port = htons( _port );

            m_addr = reinterpret_cast< sockaddr* >( addr_in );
            m_len = sizeof( sockaddr_in );
            break;
         }
         case AF_INET6:
         {
            break;
         }
         case AF_VSOCK:
         {
            struct sockaddr_vm* addr_vm = (sockaddr_vm*)malloc( sizeof( sockaddr_vm ) );
            memset( addr_vm, 0, sizeof( sockaddr_vm ) );

            addr_vm->svm_family = _domain;
            if( _address )
            {
               addr_vm->svm_cid = atoi( _address );
            }
            addr_vm->svm_port = _port;

            m_addr = reinterpret_cast< sockaddr* >( addr_vm );
            m_len = sizeof( addr_vm );
            break;
         }
         default:
         {
            break;
         }
      }
   }

   sockaddr* socket_addr::addr( )
   {
      return m_addr;
   }

   socklen_t& socket_addr::len( )
   {
      return m_len;
   }



   fds::fds( )
   {
      mp_read = new fd_set;
      mp_write = new fd_set;
      mp_except = new fd_set;
   }

   fds::~fds( )
   {
      delete mp_read;
      delete mp_write;
      delete mp_except;
   }

   void fds::reset( )
   {
      FD_ZERO( mp_read );
      FD_ZERO( mp_write );
      FD_ZERO( mp_except );
   }

   void fds::set( const tSocket _socket, const eType type )
   {
      fd_set* p_fd_set = convert( type );
      FD_SET( _socket, p_fd_set );
   }

   void fds::set( const std::set< tSocket > socket_set, const std::set< eType > type_set )
   {
      std::set< fd_set* > p_fd_set = convert( type_set );
      for( const auto& _socket : socket_set )
         set( _socket, p_fd_set );
   }

   void fds::clear( const tSocket _socket, const eType type )
   {
      fd_set* p_fd_set = convert( type );
      FD_CLR( _socket, p_fd_set );
   }

   void fds::clear( const std::set< tSocket > socket_set, const std::set< eType > type_set )
   {
      std::set< fd_set* > p_fd_set = convert( type_set );
      for( const auto& _socket : socket_set )
         clear( _socket, p_fd_set );
   }

   bool fds::is_set( const tSocket _socket, const eType type )
   {
      fd_set* p_fd_set = convert( type );

      return p_fd_set ? FD_ISSET( _socket, p_fd_set ) : false;
   }

   void fds::set( tSocket _socket, std::set< fd_set* > p_fd_set )
   {
      for( const auto& item : p_fd_set )
         FD_SET( _socket, item );
   }

   void fds::clear( tSocket _socket, std::set< fd_set* > p_fd_set )
   {
      for( auto& item : p_fd_set )
         FD_CLR( _socket, item );
   }

   fd_set* fds::convert( const eType type ) const
   {
      switch( type )
      {
         case eType::READ:       return mp_read;
         case eType::WRITE:      return mp_write;
         case eType::EXCEPT:     return mp_except;
         default:                return nullptr;
      }
      return nullptr;
   }

   std::set< fd_set* > fds::convert( const std::set< eType > type_set ) const
   {
      std::set< fd_set* > fds;
      for( auto& type : type_set )
      {
         switch( type )
         {
            case eType::READ:       fds.insert( mp_read );     break;
            case eType::WRITE:      fds.insert( mp_write );    break;
            case eType::EXCEPT:     fds.insert( mp_except );   break;
            default:                                           break;
         }
      }
      return fds;
   }
   
   fd_set* const fds::read( ) const
   {
      return mp_read;
   }
   
   fd_set* const fds::write( ) const
   {
      return mp_write;
   }
   
   fd_set* const fds::except( ) const
   {
      return mp_except;
   }

} // namespace carpc::os::os_linux::socket



namespace carpc::os::os_linux::socket {

   void print( const sockaddr* sa )
   {
      switch( sa->sa_family )
      {
         case AF_UNIX:
         {
            print( (sockaddr_un*)sa );
            break;
         }
         case AF_INET:
         {
            print( (sockaddr_in*)sa );
            break;
         }
         case AF_INET6:
         {
            print( (sockaddr_in6*)sa );
            break;
         }
         case AF_VSOCK:
         {
            print( (sockaddr_vm*)sa );
            break;
         }
         default:
         {
            SYS_ERR( "undefined socket family: %d", sa->sa_family );
            break;
         }
      }
   }

   void print( const sockaddr_un* sa_un )
   {
      SYS_VRB( "sockaddr_un: %p", sa_un );
      if( not sa_un )
         return;
      SYS_VRB( "   sun_family: %d -> %s", sa_un->sun_family, socket_domain_to_string( sa_un->sun_family ) );
      SYS_VRB( "   sun_path: %s", sa_un->sun_path );
   }

   void print( const sockaddr_in* sa_in )
   {
      SYS_VRB( "sockaddr_in: %p", sa_in );
      if( not sa_in )
         return;
      SYS_VRB( "   sin_family: %d -> %s", sa_in->sin_family, socket_domain_to_string( sa_in->sin_family ) );
      SYS_VRB( "   sin_port: %d -> %hu", sa_in->sin_port, ntohs( sa_in->sin_port ) );
      static thread_local char ip[ INET_ADDRSTRLEN ];
      inet_ntop( AF_INET, &(sa_in->sin_addr), ip, INET_ADDRSTRLEN );
      SYS_VRB( "   sin_addr: %u -> %s", sa_in->sin_addr.s_addr, ip );
   }

   void print( const sockaddr_in6* sa_in6 )
   {
      SYS_VRB( "sockaddr_in6: %p", sa_in6 );
      if( not sa_in6 )
         return;
      SYS_VRB( "   sin6_family: %d -> %s", sa_in6->sin6_family, socket_domain_to_string( sa_in6->sin6_family ) );
      SYS_VRB( "   sin6_port: %d -> %hu", sa_in6->sin6_port, ntohs( sa_in6->sin6_port ) );
      static thread_local char ip[ INET6_ADDRSTRLEN ];
      inet_ntop( AF_INET6, &(sa_in6->sin6_addr), ip, INET6_ADDRSTRLEN );
      SYS_VRB( "   sin6_addr: %s -> %s", sa_in6->sin6_addr.s6_addr, ip );
   }

   void print( const sockaddr_vm* sa_vm )
   {
      SYS_VRB( "sockaddr_vm: %p", sa_vm );
      if( not sa_vm )
         return;
   }

   void info( const tSocket _socket, const char* _message )
   {
      socklen_t addrlen = 0;
      if( false == carpc::os::os_linux::socket::getsockname( _socket, nullptr, &addrlen ) )
         return;

      struct sockaddr* addr = (sockaddr*)malloc( addrlen );

      carpc::os::os_linux::socket::getsockname( _socket, addr , &addrlen );
      SYS_INF( "%s (%d):", _message, _socket );
      print( addr );

      free( addr );
   }

   void info( const tSocket _socket, configuration& _config )
   {
      struct sockaddr_in address;
      socklen_t addrlen = sizeof( address );

      carpc::os::os_linux::socket::getsockname( _socket , (struct sockaddr*)&address , (socklen_t*)&addrlen );
      _config.address = inet_ntoa(address.sin_addr);
      _config.port = ntohs(address.sin_port);

   }

   tSocket socket( const int _domain, const int _type, const int _protocole )
   {
      tSocket _socket = ::socket( _domain, _type, _protocole );
      error = errno;
      if( -1 == _socket )
      {
         SYS_ERR( "socket(%d, %d, %d) error: %d", _domain, _type, _protocole, error );
         return _socket;
      }

      SYS_VRB( "socket(%d)", _socket );
      return _socket;
   }

   tSocket socket( const configuration _config )
   {
      return socket( _config.domain, _config.type, _config.protocole );
   }

   bool setsockopt( tSocket _socket, int level, int option_name, const void *option_value, socklen_t option_len )
   {
      int result = ::setsockopt( _socket, level, option_name, option_value, option_len );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "setsockopt(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "setsockopt(%d)", _socket );
      return true;
   }

   int getsockopt( tSocket _socket, int level, int option_name, void* option_value, socklen_t* option_len )
   {
      int result = ::getsockopt( _socket, level, option_name, option_value, option_len );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "getsockopt(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "getsockopt(%d)", _socket );
      return true;
   }

   bool bind( const tSocket _socket, const sockaddr* _address, const socklen_t _address_len )
   {
      if( nullptr == _address )
      {
         SYS_ERR( "bind(%d): address is nullptr", _socket );
         return false;
      }

      int result = ::bind( _socket, _address, _address_len );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "bind(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "bind(%d)", _socket );
      return true;
   }

   bool bind( const tSocket _socket, socket_addr& sa )
   {
      return carpc::os::os_linux::socket::bind( _socket, sa.addr( ), sa.len( ) );
   }

   bool bind( const tSocket _socket, const configuration& _config )
   {
      socket_addr sa( _config );
      return carpc::os::os_linux::socket::bind( _socket, sa );
   }

   bool connect( const tSocket _socket, const sockaddr* _address, const socklen_t _address_len )
   {
      if( nullptr == _address )
      {
         SYS_ERR( "connect(%d): address is nullptr", _socket );
         return false;
      }

      int result = ::connect( _socket, _address, _address_len );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "connect(%d): error %d", _socket, error );
         return false;
      }
      SYS_VRB( "connect(%d)", _socket );
      return true;
   }

   bool connect( const tSocket _socket, socket_addr& sa )
   {
      return carpc::os::os_linux::socket::connect( _socket, sa.addr( ), sa.len( ) );
   }

   bool connect( const tSocket _socket, const configuration& _config )
   {
      socket_addr sa( _config );
      return carpc::os::os_linux::socket::connect( _socket, sa );
   }

   bool listen( const tSocket _socket, const int _backlog )
   {
      int result = ::listen( _socket, _backlog );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "listen(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "listen(%d)", _socket );
      return true;
   }

   ssize_t send( const tSocket _socket, const void* _buffer, const size_t _size, const int _flags )
   {
      if( nullptr == _buffer )
      {
         SYS_ERR( "send(%d): buffer is nullptr", _socket );
         return 0;
      }

      ssize_t size = ::send( _socket, _buffer, _size, _flags );
      error = errno;
      if( size != static_cast< ssize_t >( _size ) )
      {
         SYS_ERR( "send(%d): error %d / bytes %zd", _socket, error, size );
         return size;
      }
      SYS_VRB( "send(%d): %zd bytes", _socket, size );
      return size;
   }

   ssize_t sendto( const tSocket _socket, const void* _buffer, const size_t _size, const int _flags,
                        const sockaddr* const _address, const socklen_t _address_len )
   {
      if( nullptr == _buffer )
      {
         SYS_ERR( "sendto(%d): buffer is nullptr", _socket );
         return 0;
      }

      ssize_t size = ::sendto( _socket, _buffer, _size, _flags, _address, _address_len );
      error = errno;
      if( size != static_cast< ssize_t >( _size ) )
      {
         SYS_ERR( "sendto(%d): error %d / bytes %zd", _socket, error, size );
         return size;
      }
      SYS_VRB( "sendto(%d): %zd bytes", _socket, size );
      return size;
   }

   ssize_t sendmsg( const tSocket _socket, const msghdr* const _message, const int _flags )
   {
      ssize_t size = ::sendmsg( _socket, _message, _flags );
      error = errno;
      SYS_VRB( "sendmsg(%d): %zd bytes", _socket, size );
      return size;
   }

   ssize_t recv( const tSocket _socket, void* const _buffer, const size_t _size, const int _flags )
   {
      if( nullptr == _buffer )
      {
         SYS_ERR( "recv(%d): buffer is nullptr", _socket );
         return 0;
      }

      ssize_t size = ::recv( _socket, _buffer, _size, _flags );
      error = errno;
      if( 0 >= size )
      {
         SYS_ERR( "recv(%d): error %d", _socket, error );
         return size;
      }
      SYS_VRB( "recv(%d): %zd bytes", _socket, size );
      return size;
   }

   ssize_t recvfrom( const tSocket _socket, void* const _buffer, const size_t _size, const int _flags,
                        sockaddr* const _address, socklen_t* const _address_len )
   {
      if( nullptr == _buffer )
      {
         SYS_ERR( "recvfrom(%d): buffer is nullptr", _socket );
         return 0;
      }

      ssize_t size = ::recvfrom( _socket, _buffer, _size, _flags, _address, _address_len );
      error = errno;
      if( 0 >= size )
      {
         SYS_ERR( "recvfrom(%d): error %d", _socket, error );
         return size;
      }
      SYS_VRB( "recvfrom(%d): %zd bytes", _socket, size );
      return size;
   }

   ssize_t recvmsg( const tSocket _socket, msghdr* const _message, const int _flags )
   {
      ssize_t size = ::recvmsg( _socket, _message, _flags );
      error = errno;
      SYS_VRB( "recvmsg(%d): %zd bytes", _socket, size );
      return size;
   }

   tSocket accept( const tSocket _socket, sockaddr* const _address, socklen_t* const _address_len )
   {
      tSocket slave_socket = ::accept( _socket, _address, _address_len );
      error = errno;
      if( -1 == slave_socket )
      {
         SYS_ERR( "accept(%d): error %d", _socket, error );
         return slave_socket;
      }
      SYS_VRB( "accept(%d): %d slave socket", _socket, slave_socket );
      return slave_socket;
   }

   tSocket accept( const tSocket _socket, socket_addr* sa )
   {
      return sa ? os_linux::socket::accept( _socket, sa->addr( ), &sa->len( ) )
         : carpc::os::os_linux::socket::accept( _socket, nullptr, nullptr );
   }

   bool select( const tSocket _max_socket, fd_set* const _fd_set_read, fd_set* const _fd_set_write, fd_set* const _fd_set_except, timeval* const _timeout )
   {
      int result = ::select( _max_socket + 1, _fd_set_read, _fd_set_write, _fd_set_except, _timeout );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "select(%d + 1) error: %d", _max_socket, error );
         return false;
      }
      SYS_VRB( "select(%d + 1)", _max_socket );
      return true;
   }

   bool select( const tSocket _max_socket, fds& _fd, timeval* const _timeout )
   {
      return carpc::os::os_linux::socket::select( _max_socket, _fd.read( ), _fd.write( ), _fd.except( ), _timeout );
   }

   bool shutdown( tSocket _socket, int _how )
   {
      int result = ::shutdown( _socket, _how );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "shutdown(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "shutdown(%d)", _socket );
      return true;
   }

   bool getsockname( tSocket _socket, sockaddr* const _address, socklen_t* const _address_len )
   {
      int result = ::getsockname( _socket, _address, _address_len );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "getsockname(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "getsockname(%d)", _socket );
      return true;
   }

   bool getsockname( const tSocket _socket, socket_addr* sa )
   {
      if( not sa )
      {
         SYS_ERR( "socket_addr null pointer" );
         return false;
      }

      return os_linux::socket::getsockname( _socket, sa->addr( ), &sa->len( ) );
   }

   bool close( tSocket _socket )
   {
      int result = ::close( _socket );
      error = errno;
      if( -1 == result )
      {
         SYS_ERR( "close(%d) error: %d", _socket, error );
         return false;
      }
      SYS_VRB( "close(%d)", _socket );
      return true;
   }

} // namespace carpc::os::os_linux::socket



namespace carpc::os::os_linux {

   bool get_mac( const std::string& connection_name, std::string& connection_mac )
   {
      socket::tSocket fd = socket::socket( AF_UNIX, SOCK_DGRAM, IPPROTO_IP );
      if( -1 == fd )
         return false;

      struct ifreq ifreq_data;
      strcpy( ifreq_data.ifr_name, connection_name.c_str( ) );
      int result = ioctl( fd, SIOCGIFHWADDR, &ifreq_data );
      int errno_ioctl = errno;
      SYS_INF( "ioctl result: %d", result );
      if( 0 != result )
      {
         SYS_ERR( "error: %d", errno_ioctl );
         return false;
      }

      connection_mac.clear( );
      for( size_t i = 0; i < 6; ++i )
      {
         char buffer[3];
         sprintf( buffer, "%02x", ( uint8_t )ifreq_data.ifr_addr.sa_data[i] );
         connection_mac += buffer;
      }
      SYS_INF( "Connection: %s / MAC: %s", connection_name.c_str( ), connection_mac.c_str( ) );

      return true;
   }

} // namespace carpc::os::os_linux

