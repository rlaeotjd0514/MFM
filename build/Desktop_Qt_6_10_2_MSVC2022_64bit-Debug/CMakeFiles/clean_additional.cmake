# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MMM_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MMM_autogen.dir\\ParseCache.txt"
  "MMM_autogen"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineApp_autogen.dir\\AutogenUsed.txt"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineApp_autogen.dir\\ParseCache.txt"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineLib_autogen.dir\\AutogenUsed.txt"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineLib_autogen.dir\\ParseCache.txt"
  "NetworkEngineLib\\NetworkEngineApp_autogen"
  "NetworkEngineLib\\NetworkEngineLib_autogen"
  )
endif()
