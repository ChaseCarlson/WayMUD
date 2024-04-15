# CMakeList.txt : CMake project for WayMUD, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB_RECURSE SOURCE_FILES 
     "*.cpp"
     "*.h")

# Define the executable
add_executable(WayMUD ${SOURCE_FILES})
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WayMUD PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
