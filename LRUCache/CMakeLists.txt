# CMakeList.txt : CMake project for LRUCache, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LRUCache "main.cpp" "LRUCache.hpp" "src/lru.hpp" "src/intrusive_list.hpp" "src/hashtable.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LRUCache PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
# Add the include directories for the headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Create test executable and link with Google Test
enable_testing()
add_executable(runTests "tests/test_lru.cpp" "tests/test_intrusive_list.cpp" "tests/test_hashtable.cpp")
target_link_libraries(runTests gtest_main)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Set the runtime library to be consistent (Static Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")

# Ensure this is applied only for Debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# If you want consistency for Release builds (optional)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

# Include GoogleTest's discovery feature
include(GoogleTest)
gtest_discover_tests(runTests)