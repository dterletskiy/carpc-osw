#pragma once

#include "carpc/osw/thread/policy/debug/active/Simple.hpp"

#include "carpc/osw/thread/policy/debug/inactive/Simple.hpp"



namespace carpc::osw::thread::policy::debug {

   #if defined( CARPC_BUILD_DEBUG )
      namespace nsDebugPolicy = active;
   #else
      namespace nsDebugPolicy = inactive;
   #endif

} // namespace carpc::osw::thread::policy::debug
