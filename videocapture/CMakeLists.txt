cmake_minimum_required(VERSION 3.1)

project(vediocapture)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(include)

add_executable(main main.cpp)
add_executable(vedio vedio.cpp)
target_link_libraries(main ${OpenCV_LIBS} )
target_link_libraries(vedio ${OpenCV_LIBS} )