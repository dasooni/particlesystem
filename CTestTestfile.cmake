# CMake generated Testfile for 
# Source directory: C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem
# Build directory: C:/Users/Dasmit/Desktop/TNM094LAB2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[unittest]=] "C:/Users/Dasmit/Desktop/TNM094LAB2/Debug/unittest.exe")
  set_tests_properties([=[unittest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;114;add_test;C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[unittest]=] "C:/Users/Dasmit/Desktop/TNM094LAB2/Release/unittest.exe")
  set_tests_properties([=[unittest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;114;add_test;C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[unittest]=] "C:/Users/Dasmit/Desktop/TNM094LAB2/MinSizeRel/unittest.exe")
  set_tests_properties([=[unittest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;114;add_test;C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[unittest]=] "C:/Users/Dasmit/Desktop/TNM094LAB2/RelWithDebInfo/unittest.exe")
  set_tests_properties([=[unittest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;114;add_test;C:/Users/Dasmit/Desktop/TNM094LAB2/particlesystem/CMakeLists.txt;0;")
else()
  add_test([=[unittest]=] NOT_AVAILABLE)
endif()
