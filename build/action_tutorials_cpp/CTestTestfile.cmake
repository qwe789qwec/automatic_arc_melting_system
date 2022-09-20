# CMake generated Testfile for 
# Source directory: /home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp
# Build directory: /home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(copyright "/home/wilson/anaconda3/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/copyright.xunit.xml" "--package-name" "action_tutorials_cpp" "--output-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/ament_copyright/copyright.txt" "--command" "/opt/ros/foxy/bin/ament_copyright" "--xunit-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/copyright.xunit.xml")
set_tests_properties(copyright PROPERTIES  LABELS "copyright;linter" TIMEOUT "60" WORKING_DIRECTORY "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_copyright/cmake/ament_copyright.cmake;41;ament_add_test;/opt/ros/foxy/share/ament_cmake_copyright/cmake/ament_cmake_copyright_lint_hook.cmake;18;ament_copyright;/opt/ros/foxy/share/ament_cmake_copyright/cmake/ament_cmake_copyright_lint_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;74;ament_package;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;0;")
add_test(cppcheck "/home/wilson/anaconda3/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/cppcheck.xunit.xml" "--package-name" "action_tutorials_cpp" "--output-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/ament_cppcheck/cppcheck.txt" "--command" "/opt/ros/foxy/bin/ament_cppcheck" "--xunit-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/cppcheck.xunit.xml" "--include_dirs" "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/include")
set_tests_properties(cppcheck PROPERTIES  LABELS "cppcheck;linter" TIMEOUT "300" WORKING_DIRECTORY "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_cppcheck/cmake/ament_cppcheck.cmake;61;ament_add_test;/opt/ros/foxy/share/ament_cmake_cppcheck/cmake/ament_cmake_cppcheck_lint_hook.cmake;83;ament_cppcheck;/opt/ros/foxy/share/ament_cmake_cppcheck/cmake/ament_cmake_cppcheck_lint_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;74;ament_package;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;0;")
add_test(cpplint "/home/wilson/anaconda3/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/cpplint.xunit.xml" "--package-name" "action_tutorials_cpp" "--output-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/ament_cpplint/cpplint.txt" "--command" "/opt/ros/foxy/bin/ament_cpplint" "--xunit-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/cpplint.xunit.xml")
set_tests_properties(cpplint PROPERTIES  LABELS "cpplint;linter" TIMEOUT "120" WORKING_DIRECTORY "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_cpplint/cmake/ament_cpplint.cmake;68;ament_add_test;/opt/ros/foxy/share/ament_cmake_cpplint/cmake/ament_cmake_cpplint_lint_hook.cmake;35;ament_cpplint;/opt/ros/foxy/share/ament_cmake_cpplint/cmake/ament_cmake_cpplint_lint_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;74;ament_package;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;0;")
add_test(lint_cmake "/home/wilson/anaconda3/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/lint_cmake.xunit.xml" "--package-name" "action_tutorials_cpp" "--output-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/ament_lint_cmake/lint_cmake.txt" "--command" "/opt/ros/foxy/bin/ament_lint_cmake" "--xunit-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/lint_cmake.xunit.xml")
set_tests_properties(lint_cmake PROPERTIES  LABELS "lint_cmake;linter" TIMEOUT "60" WORKING_DIRECTORY "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_lint_cmake/cmake/ament_lint_cmake.cmake;41;ament_add_test;/opt/ros/foxy/share/ament_cmake_lint_cmake/cmake/ament_cmake_lint_cmake_lint_hook.cmake;21;ament_lint_cmake;/opt/ros/foxy/share/ament_cmake_lint_cmake/cmake/ament_cmake_lint_cmake_lint_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;74;ament_package;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;0;")
add_test(uncrustify "/home/wilson/anaconda3/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/uncrustify.xunit.xml" "--package-name" "action_tutorials_cpp" "--output-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/ament_uncrustify/uncrustify.txt" "--command" "/opt/ros/foxy/bin/ament_uncrustify" "--xunit-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/uncrustify.xunit.xml")
set_tests_properties(uncrustify PROPERTIES  LABELS "uncrustify;linter" TIMEOUT "60" WORKING_DIRECTORY "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_uncrustify/cmake/ament_uncrustify.cmake;65;ament_add_test;/opt/ros/foxy/share/ament_cmake_uncrustify/cmake/ament_cmake_uncrustify_lint_hook.cmake;34;ament_uncrustify;/opt/ros/foxy/share/ament_cmake_uncrustify/cmake/ament_cmake_uncrustify_lint_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;74;ament_package;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;0;")
add_test(xmllint "/home/wilson/anaconda3/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/xmllint.xunit.xml" "--package-name" "action_tutorials_cpp" "--output-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/ament_xmllint/xmllint.txt" "--command" "/opt/ros/foxy/bin/ament_xmllint" "--xunit-file" "/home/arc/Documents/automatic_arc_melting_system/build/action_tutorials_cpp/test_results/action_tutorials_cpp/xmllint.xunit.xml")
set_tests_properties(xmllint PROPERTIES  LABELS "xmllint;linter" TIMEOUT "60" WORKING_DIRECTORY "/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_xmllint/cmake/ament_xmllint.cmake;50;ament_add_test;/opt/ros/foxy/share/ament_cmake_xmllint/cmake/ament_cmake_xmllint_lint_hook.cmake;18;ament_xmllint;/opt/ros/foxy/share/ament_cmake_xmllint/cmake/ament_cmake_xmllint_lint_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/opt/ros/foxy/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/opt/ros/foxy/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;74;ament_package;/home/arc/Documents/automatic_arc_melting_system/src/action_tutorials_cpp/CMakeLists.txt;0;")
