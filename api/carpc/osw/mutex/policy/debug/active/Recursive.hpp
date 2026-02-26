#pragma once

#include <thread>
#include <cassert>



namespace carpc::osw::mutex::policy::debug::active {

   class Recursive
   {
      public:
         Recursive( ) noexcept = default;
         ~Recursive( ) noexcept = default;

      protected:
         void before_lock( ) noexcept
         {
            const auto current = std::this_thread::get_id( );

            if( m_owner == current )
            {
               ++m_depth;
               return;
            }
         }

         void after_lock( ) noexcept
         {
            const auto current = std::this_thread::get_id( );

            if( m_depth == 0 )
               m_owner = current;

            ++m_depth;
         }

         void before_unlock( ) noexcept
         {
            const auto current = std::this_thread::get_id( );

            assert( m_owner == current );
            assert( m_depth > 0 );

            --m_depth;
         }

         void after_unlock( ) noexcept
         {
            if( m_depth == 0 )
               m_owner = std::thread::id{ };
         }

      private:
         std::thread::id   m_owner{ };
         std::size_t       m_depth = 0;
   };

} // namespace carpc::osw::mutex::policy::debug::active
