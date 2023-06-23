cmake_minimum_required(VERSION 3.24)
project(03)

set(CMAKE_CXX_STANDARD 14)

add_executable(03 main.cpp Geometry.cpp Geometry.h SimObject.h MovingObject.h Agent.h Knight.cpp Knight.h Peasant.h Peasant.cpp Thug.h Thug.cpp Structure.h Farm.h Farm.cpp Castle.h Castle.cpp Model.h Model.cpp Controller.h Controller.cpp View.cpp View.h)
