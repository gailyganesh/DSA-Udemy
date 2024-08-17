cmake_minimum_required(VERSION 3.22.6 FATAL_ERROR)

# Set C++ standard on global level
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(DSA_Course)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin CACHE PATH "Install path" FORCE)

add_subdirectory(LinkedList)
add_subdirectory(DoublyLinkedList)
add_subdirectory(Stack)
add_subdirectory(Queue)
add_subdirectory(Nodes)
