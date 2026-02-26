#pragma once



namespace carpc::osw::detail
{
   struct linux_tag { };
   struct qnx_tag   { };
   struct rtos_tag  { };

#if defined( CARPC_BUILD_OS_LINUX )
   using current_os = linux_tag;
#elif defined( CARPC_BUILD_OS_QNX )
   using current_os = qnx_tag;
#elif defined( CARPC_BUILD_OS_RTOS )
   using current_os = rtos_tag;
#else
   #error Unsupported operating system
#endif
}
