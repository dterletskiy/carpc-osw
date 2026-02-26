#pragma once



namespace carpc::osw::thread::policy::debug::inactive {

   class Simple
   {
      public:
         Simple( ) noexcept = default;
         ~Simple( ) noexcept = default;

      protected:
         void before_start( ) noexcept { }
         void after_start( ) noexcept { }
         void before_join( ) noexcept { }
         void after_join( ) noexcept { }
   };

} // namespace carpc::osw::thread::policy::debug::active
