cmake_minimum_required(VERSION 3.10)

find_package(PythonInterp 3 REQUIRED)
find_package(Boost COMPONENTS python3 numpy3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

add_library(polyfit_curved_lane SHARED polyfit_curved_lane.cpp)
target_link_libraries(polyfit_curved_lane ${Boost_LIBRARIES} ${PYTHON_LIBRARY} boost_numpy)
set_target_properties(polyfit_curved_lane PROPERTIES PREFIX "")
