cmake_minimum_required(VERSION 3.10)

project(chessie)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/chessengine.cpp
    src/moveexecutor.cpp
    src/movegenerator.cpp
    src/movevalidator.cpp
    src/utils.cpp
)

set(MAIN_SOURCE
    src/main.cpp
)

include_directories(src)

add_executable(chessie ${SOURCES} ${MAIN_SOURCE})

enable_testing()

add_subdirectory(external/googletest)
include_directories(external/googletest/googletest/include)

set(TEST_SOURCES
    test/unit_tests.cpp
    test/functional_tests.cpp
    test/performance_tests.cpp
)

add_executable(tests ${TEST_SOURCES} ${SOURCES})
target_link_libraries(tests gtest gtest_main)

add_test(NAME unit_tests COMMAND tests --gtest_filter=unit_tests.*)
add_test(NAME functional_tests COMMAND tests --gtest_filter=functional_tests.*)
add_test(NAME performance_tests COMMAND tests --gtest_filter=performance_tests.*)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc_doxygen ALL
                      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      COMMENT "Generating API documentation with Doxygen"
                      VERBATIM)
else()
    message("Doxygen needs to be installed to generate the documentation")
endif()