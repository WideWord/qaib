cmake_minimum_required(VERSION 3.2.0)

project(qaib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -rpath .")

file(GLOB QAIB_SOURCE
		source/**/*.cpp
		source/**/**/*.cpp
		source/**/**/**/*.cpp
		source/**/*.hpp
		source/**/**/*.hpp
		source/**/**/**/*.hpp
		source/**/*.h
		source/**/**/*.h
		source/**/**/**/*.h
		data/*.cpp)


include_directories(source)
include_directories(source/third-party)
include_directories(/usr/include)
include_directories(/usr/local/include)


# LIBRARIES

# SFML
find_package(SFML 2 COMPONENTS system window graphics network)
include_directories(${SFML_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${SFML_LIBRARIES})

# GLM
find_package(GLM)
include_directories(${GLM_INCLUDE_DIRS})


# Box2D
find_package(Box2D)
include_directories(${BOX2D_INCLUDE_DIR})
set(QAIB_LIBS ${QAIB_LIBS} ${BOX2D_LIBRARIES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(QAIB_LIBS ${QAIB_LIBS} Threads::Threads)

add_executable(qaib ${QAIB_SOURCE})
target_compile_features(qaib PRIVATE cxx_range_for)

if(QAIB_LIBS)
	target_link_libraries(qaib ${QAIB_LIBS})
endif()

install(TARGETS qaib RUNTIME DESTINATION bin)

