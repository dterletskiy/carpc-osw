#pragma once

#include "carpc/osw/mutex/policy/debug/active/Simple.hpp"
#include "carpc/osw/mutex/policy/debug/active/Recursive.hpp"

#include "carpc/osw/mutex/policy/debug/inactive/Simple.hpp"
#include "carpc/osw/mutex/policy/debug/inactive/Recursive.hpp"



namespace carpc::osw::mutex::policy::debug {

   #if defined( CARPC_BUILD_DEBUG )
      namespace nsDebugPolicy = active;
   #else
      namespace nsDebugPolicy = inactive;
   #endif

} // namespace carpc::osw::mutex::policy::debug
