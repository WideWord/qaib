cmake_minimum_required(VERSION 3.2.0)

project(qaib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB QAIB_SOURCE source/**/*.cpp source/**/**/*.cpp source/**/*.hpp source/**/**/*.hpp)
include_directories(source)


# LIBRARIES

# SFML
find_package(SFML 2 COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${SFML_LIBRARIES})



add_executable(qaib ${QAIB_SOURCE})

if(QAIB_LIBS)
	target_link_libraries(qaib ${QAIB_LIBS})
endif()
