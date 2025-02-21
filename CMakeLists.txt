cmake_minimum_required(VERSION 3.5)

project(BT)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/ros/humble")
find_package(behaviortree_cpp_v3 REQUIRED)

add_executable(${PROJECT_NAME} "bt.cpp")
target_link_libraries(${PROJECT_NAME} BT::behaviortree_cpp_v3)
