#pragma once

#include <thread>
#include <cassert>



namespace carpc::osw::mutex::policy::debug::active {

   struct Simple
   {
      public:
         Simple( ) noexcept = default;
         ~Simple( ) noexcept = default;

      protected:
         void before_lock( ) noexcept
         {
            // Detect recursive lock (if not recursive mutex)
            assert(
                  m_owner != std::this_thread::get_id( ) &&
                  "Mutex recursive lock detected"
               );
         }

         void after_lock( ) noexcept
         {
            m_owner = std::this_thread::get_id( );
            m_locked = true;
         }

         void before_unlock( ) noexcept
         {
            // Detect unlock from wrong thread
            assert(
                  m_owner == std::this_thread::get_id( ) &&
                  "Mutex unlock from non-owner thread"
               );
         }

         void after_unlock( ) noexcept
         {
            m_locked = false;
            m_owner = std::thread::id{ };
         }

      private:
         std::thread::id   m_owner{ };
         bool              m_locked{ false };
   };

} // namespace carpc::osw::mutex::policy::debug::active
