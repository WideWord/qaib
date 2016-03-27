cmake_minimum_required(VERSION 3.2.0)

project(qaib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB QAIB_SOURCE source/**/*.cpp source/**/**/*.cpp source/**/**/**/*.cpp source/**/*.hpp source/**/**/*.hpp source/**/**/**/*.hpp)


include_directories(source)


# LIBRARIES

# SFML
find_package(SFML 2 COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${SFML_LIBRARIES})

# SFGUI
find_package(SFGUI)
include_directories(${SFGUI_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${SFGUI_LIBRARY})

# GLM
find_package(GLM)
include_directories(${GLM_INCLUDE_DIRS})


# Box2D
find_package(Box2D)
include_directories(${BOX2D_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${BOX2D_LIBRARIES})

# YamlCpp
find_package(YamlCpp)
include_directories(${YAMLCPP_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${YAMLCPP_LIBRARY})

# Boost
find_package(Boost COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
set(QAIB_LIBS ${QAIB_LIBS} ${Boost_LIBRARIES})

add_executable(qaib ${QAIB_SOURCE})
target_compile_features(qaib PRIVATE cxx_range_for)

if(QAIB_LIBS)
	target_link_libraries(qaib ${QAIB_LIBS})
endif()
