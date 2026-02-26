#pragma once



namespace carpc::osw::mutex::policy::debug::inactive {

   class Simple
   {
      public:
         void before_lock( ) noexcept { }
         void after_lock( ) noexcept { }
         void before_unlock( ) noexcept { }
         void after_unlock( ) noexcept { }
   };

} // namespace carpc::osw::mutex::policy::debug::active
