cmake_minimum_required(VERSION 3.2.0)

project(qaib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB QAIB_SOURCE source/**/*.cpp source/**/**/*.cpp source/**/**/**/*.cpp source/**/*.hpp source/**/**/*.hpp source/**/**/**/*.hpp)


macro(GroupSources curdir)

    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
 ${PROJECT_SOURCE_DIR}/${curdir}/*)

    foreach(child ${children})

           if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})

                   GroupSources(${curdir}/${child})

           else()

                  string(REPLACE "/" "\\" groupname ${curdir})

                    string(REPLACE "src" "Common" groupname ${groupname})

             source_group(${groupname} FILES
 ${PROJECT_SOURCE_DIR}/${curdir}/${child})

           endif()

    endforeach()

endmacro()

GroupSources(source/qaib)

include_directories(source)


# LIBRARIES

# SFML
find_package(SFML 2 COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${SFML_LIBRARIES})

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
