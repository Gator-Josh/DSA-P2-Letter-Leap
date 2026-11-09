# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\letter_leap_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\letter_leap_autogen.dir\\ParseCache.txt"
  "letter_leap_autogen"
  )
endif()
