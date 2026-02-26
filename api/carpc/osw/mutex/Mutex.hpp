#pragma once

#include "carpc/osw/mutex/BasicMutex.hpp"
#include "carpc/osw/mutex/BasicRecursiveMutex.hpp"

#include "carpc/osw/mutex/backend/Backend.hpp"
#include "carpc/osw/mutex/policy/debug/Debug.hpp"



namespace carpc::osw {

   using Mutex = mutex::BasicMutex<
         mutex::backend::nsBackendPolicy::Mutex,
         mutex::policy::debug::nsDebugPolicy::Simple
      >;

   using RecursiveMutex = mutex::BasicRecursiveMutex<
         mutex::backend::nsBackendPolicy::RecursiveMutex,
         mutex::policy::debug::nsDebugPolicy::Recursive
      >;

}
