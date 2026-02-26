#pragma once

#include <cstdint>

#include "os_select.h"



namespace carpc::osw::detail
{
   template< typename T >
   struct os_traits;
}



#if defined( CARPC_BUILD_OS_LINUX )

   #include "os_traits_linux.h"

#elif defined( CARPC_BUILD_OS_QNX )

   #include "os_traits_qnx.h"

#elif defined( CARPC_BUILD_OS_RTOS )

   #include "os_traits_rtos.h"

#endif
