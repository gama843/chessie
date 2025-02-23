# CMake generated Testfile for 
# Source directory: /home/danielkuchta/kuchtad/project
# Build directory: /home/danielkuchta/kuchtad/project/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_tests "/home/danielkuchta/kuchtad/project/build/tests" "--gtest_filter=unit_tests.*")
set_tests_properties(unit_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/danielkuchta/kuchtad/project/CMakeLists.txt;38;add_test;/home/danielkuchta/kuchtad/project/CMakeLists.txt;0;")
add_test(functional_tests "/home/danielkuchta/kuchtad/project/build/tests" "--gtest_filter=functional_tests.*")
set_tests_properties(functional_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/danielkuchta/kuchtad/project/CMakeLists.txt;39;add_test;/home/danielkuchta/kuchtad/project/CMakeLists.txt;0;")
add_test(performance_tests "/home/danielkuchta/kuchtad/project/build/tests" "--gtest_filter=performance_tests.*")
set_tests_properties(performance_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/danielkuchta/kuchtad/project/CMakeLists.txt;40;add_test;/home/danielkuchta/kuchtad/project/CMakeLists.txt;0;")
subdirs("external/googletest")
