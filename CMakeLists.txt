cmake_minimum_required (VERSION 3.9)
project (helloworld)

set (helloworld_VERSION_MAJOR 0)
set (helloworld_VERSION_MINOR 1)

add_executable(helloworld main.cpp world/src/World.cpp)


# SOurce files adding
# test files mit gtest integrieren
# lint
# code analyzer
# coverage
# clang tidy  clang format

#---------------------------------------------------------------------------------------------------
# gtest
#---------------------------------------------------------------------------------------------------
#set(ENABLE_GTEST "" CACHE STRING "")

#if (ENABLE_GTEST)
  #find_program(GTEST_BIN gtest)

  #if (GTEST_BIN STREQUAL "GTEST_BIN-NOTFOUND")
    #message(FATAL_ERROR "unable to locate gtest")
  #endif()

  #list(APPEND GTEST_BIN_ARGS
    ##-style=file
    ##-i
  #)

  ##add_custom_target(
    ##format
    ##COMMAND ${CLANG_FORMAT_BIN} ${CLANG_FORMAT_BIN_ARGS} ${PROJECT_SOURCE_DIR}/world/*.hpp --
    ##COMMENT "running clang-format"
  ##)
#endif()

#---------------------------------------------------------------------------------------------------
# build tests
#---------------------------------------------------------------------------------------------------

# Locate GTest
set (GTEST_LIBRARY "/home/sassa/programs/googletest/build/lib/libgtest.a")
set (GTEST_MAIN_LIBRARY "/home/sassa/programs/googletest/build/lib/libgtest_main.a")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests world/test/World.cpp world/src/World.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${GTEST_MAIN_LIBRARY})

  #add_custom_target(
    #test
    #COMMAND clang++ ${CLANG_TIDY_BIN_ARGS} ${PROJECT_SOURCE_DIR}/world/*.hpp -- -std=c++17 ...
    #COMMENT "running clang-tidy"
  #)
#---------------------------------------------------------------------------------------------------
# Clang Tidy
#---------------------------------------------------------------------------------------------------
if (ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_BIN clang-tidy)

  if (CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(FATAL_ERROR "unable to locate clang-tidy")
  endif()

  list(APPEND CLANG_TIDY_BIN_ARGS
    -header-filter=${PROJECT_SOURCE_DIR}/*.hpp
    -checks=performance-*,clang-analyzer-*,cppcoreguidelines-*,modernize-*,readability-*
  )

  add_custom_target(
    tidy
    COMMAND ${CLANG_TIDY_BIN} ${CLANG_TIDY_BIN_ARGS} ${PROJECT_SOURCE_DIR}/world/*.hpp -- -std=c++17 ...
    COMMENT "running clang-tidy"
  )
endif()

#---------------------------------------------------------------------------------------------------
# Clang Format
#---------------------------------------------------------------------------------------------------
if (ENABLE_CLANG_FORMAT)
  find_program(CLANG_FORMAT_BIN clang-format)

  if (CLANG_FORMAT_BIN STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(FATAL_ERROR "unable to locate clang-format")
  endif()

  list(APPEND CLANG_FORMAT_BIN_ARGS
    -style=file
    -i
  )

  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT_BIN} ${CLANG_FORMAT_BIN_ARGS} ${PROJECT_SOURCE_DIR}/world/*.hpp --
    COMMENT "running clang-format"
  )
endif()

#---------------------------------------------------------------------------------------------------
# CppCheck
#---------------------------------------------------------------------------------------------------
if (ENABLE_CPP_CHECK)
  find_program(CPP_CHECK_BIN cppcheck)
  if (CPP_CHECK_BIN STREQUAL "CPP_CHECK_BIN-NOTFOUND")
    message(FATAL_ERROR "unable to locate cppcheck")
  endif()

  list(APPEND CPP_CHECK_BIN_ARGS
    --error-exitcode=1
    --enable=all
    --report-progress
    --platform=unix64
    --std=c++11 
    -I ${PROJECT_SOURCE_DIR}/include/
    -q
  )

  add_custom_target(
    cppcheck
    COMMAND ${CPP_CHECK_BIN} ${CPP_CHECK_BIN_ARGS} ${PROJECT_SOURCE_DIR}/world/*.hpp 
    COMMENT "running cppcheck"
  )
endif()

#---------------------------------------------------------------------------------------------------
# Coverage
#---------------------------------------------------------------------------------------------------
if (ENABLE_COVERAGE)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
  set (CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} ${COVERAGE_FLAGS}")
  set (CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} ${COVERAGE_FLAGS}")
  include(CodeCoverage)
  setup_target_for_coverage(${PROJECT_NAME}_coverage test-algorithm lcov)
endif()

#---------------------------------------------------------------------------------------------------
# Address Sanitizer
#---------------------------------------------------------------------------------------------------
if (ENABLE_ASAN)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILER_ASAN_FLAGS}")
  set (CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} ${CXX_COMPILER_ASAN_FLAGS}")
  set (CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} ${CXX_COMPILER_ASAN_FLAGS}")
  set (CMAKE_LINKER "clang++")
endif()

#---------------------------------------------------------------------------------------------------
# Memory Sanitizer
#---------------------------------------------------------------------------------------------------
if (ENABLE_MSAN)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILER_MSAN_FLAGS}")
  set (CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} ${CXX_COMPILER_MSAN_FLAGS}")
  set (CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} ${CXX_COMPILER_MSAN_FLAGS}")
  set (CMAKE_LINKER "clang++")
endif()

