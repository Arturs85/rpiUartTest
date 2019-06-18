project(vsmRoomba)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)
aux_source_directory(. SRC_LIST)
list(APPEND SRC_LIST "uartTest.cpp" "roombaController.cpp" "roombaBehaviour.cpp" "localMap.cpp" "main.cpp")
add_executable(${PROJECT_NAME} ${SRC_LIST})

set (CMAKE_CXX_FLAGS "-D_DEFAULT_SOURCE=1")



set (CMAKE_SHARED_LINKER_FLAGS "-lpthread -pthread")
target_link_libraries(${PROJECT_NAME}  pthread)

