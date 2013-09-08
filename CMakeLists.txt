project(GrayScaleCpp)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package( OpenCV REQUIRED )
find_package( FreeImage REQUIRED)
find_package( OpenCL REQUIRED )

include_directories( $${OpenCV_INCLUDE_DIRS} )
include_directories( ${FREEIMAGE_INCLUDE_DIRS} )
include_directories( ${OPENCL_INCLUDE_DIRS} )

if( OPENCL_HAS_CPP_BINDINGS )
        message( "OpenCL has CPP bindings. Full include is: " ${OPENCL_INCLUDE_DIRS} )
else( OPENCL_HAS_CPP_BINDINGS )
        message( "No OpenCL CPP bindings found" )
endif( OPENCL_HAS_CPP_BINDINGS )

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST} reference.cpp)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBRARIES} ${OPENCL_LIBRARIES} )

