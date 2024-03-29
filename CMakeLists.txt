cmake_minimum_required( VERSION 3.16 FATAL_ERROR )

fenix_project( TARGET osw PROJECT OSW )



###########################################################################################
#                                                                                         #
#                             Compilation include directories                             #
#                                                                                         #
###########################################################################################
include_directories( ${PROJECT_SOURCE_DIR}/api )
include_directories( ${TRACING_SOURCE_DIR}/api )
include_directories( ${BASE_SOURCE_DIR}/api )



###########################################################################################
#                                                                                         #
#                                Linkage include directories                              #
#                                                                                         #
###########################################################################################
link_directories( ${TRACING_BINARY_DIR} )
link_directories( ${BASE_BINARY_DIR} )



###########################################################################################
#                                                                                         #
#                                   Compile definitions                                   #
#                                                                                         #
###########################################################################################



###########################################################################################
#                                                                                         #
#                                      Code generation                                    #
#                                                                                         #
###########################################################################################
find_files_by_ext( RECURSE FILES PLANTUML_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_PLANTUML} )
generate_plantumls( PLANTUML_FILES ${PLANTUML_FILES} GENERATED_FILES PROJECT_GEN_PLANTUML_FILES )



###########################################################################################
#                                                                                         #
#                                   Build source file list                                #
#                                                                                         #
###########################################################################################
find_files_by_ext( RECURSE FILES PROJECT_SOURCE_FILES LOCATION ${PROJECT_SOURCE_DIR} EXTENTIONS ${EXTENTIONS_CPP_SRC} )
if( ${OS_TARGET} EQUAL ${OS_ANDROID} )
   list( REMOVE_ITEM PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/imp/carpc/oswrappers/Spinlock.cpp )
   list( REMOVE_ITEM PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/imp/carpc/oswrappers/linux/backtrace.cpp )
endif( )



###########################################################################################
#                                                                                         #
#                                      Debug messages                                     #
#                                                                                         #
###########################################################################################
print_variables( )


add_library(
      ${PROJECT_TARGET_NAME} SHARED
      ${PROJECT_SOURCE_FILES}
   )

target_link_libraries( ${PROJECT_TARGET_NAME} ${BASE_TARGET_NAME} )
if( ${OS_TARGET} EQUAL ${OS_LINUX} )
   target_link_libraries( ${PROJECT_TARGET_NAME} pthread )
endif( )

add_custom_target( "${PROJECT_TARGET_NAME}_documentation" ALL
      COMMENT "cmake ${PROJECT_TARGET_NAME}_documentation"
      DEPENDS ${PROJECT_GEN_PLANTUML_FILES}
   )

add_dependencies( ${PROJECT_TARGET_NAME} "${PROJECT_TARGET_NAME}_documentation" )

install( TARGETS ${PROJECT_TARGET_NAME} DESTINATION lib )
install( DIRECTORY ${PROJECT_SOURCE_DIR}/api/ DESTINATION include )
