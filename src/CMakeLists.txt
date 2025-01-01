# CMakeList.txt : CMake project for ThreadSafeQueue, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ThreadSafeQueue "testing.cpp" "../include/ThreadSafeQueue.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThreadSafeQueue PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
