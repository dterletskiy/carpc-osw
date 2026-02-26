#pragma once

#include "carpc/osw/thread/BasicThread.hpp"

#include "carpc/osw/thread/backend/Backend.hpp"
#include "carpc/osw/thread/policy/debug/Debug.hpp"



namespace carpc::osw {

   using Thread = thread::BasicThread<
         thread::backend::nsBackendPolicy::Thread,
         thread::policy::debug::nsDebugPolicy::Simple
      >;

} // namespace carpc::osw
