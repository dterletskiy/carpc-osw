set( SOURCES
      osw.cpp

      $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:
            os_linux.cpp
         >

      $<$<STREQUAL:${CMAKE_SYSTEM_NAME},QNX>:
            os_qnx.cpp
         >

      $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Generic>:
            os_rtos.cpp
         >
   )

target_sources( ${PROJECT_TARGET_NAME}-shared
      PRIVATE
         ${SOURCES}
   )

target_sources( ${PROJECT_TARGET_NAME}-static
      PRIVATE
         ${SOURCES}
   )
