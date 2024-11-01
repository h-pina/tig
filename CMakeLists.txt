cmake_minimum_required(VERSION 3.10)
project(tig)
add_subdirectory(src)

SET(TGT "build" CACHE STRING "TARGET OPTION")
if( TGT STREQUAL "build") 
	add_subdirectory(main)
	target_include_directories(tig PUBLIC "${PROJECT_SOURCE_DIR}/src")
elseif( TGT STREQUAL "test") 
	include(CTest)
	add_subdirectory(external)
	add_subdirectory(test)
endif()

