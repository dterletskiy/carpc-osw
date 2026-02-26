#pragma once

#include <thread>
#include <cassert>



namespace carpc::osw::thread::policy::debug::active {

   struct Simple
   {
      public:
         Simple( ) noexcept = default;
         ~Simple( ) noexcept = default;

      protected:
         void before_start( ) noexcept
         {
            assert( !m_started );
         }

         void after_start( ) noexcept
         {
            m_started = true;
         }

         void before_join( ) noexcept
         {
            assert( m_started );
         }

         void after_join( ) noexcept
         {
            m_started = false;
         }

      private:
         bool m_started = false;
   };

} // namespace carpc::osw::thread::policy::debug::active
