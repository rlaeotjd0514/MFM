# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BackTester\\BackTester_autogen"
  "BackTester\\CMakeFiles\\BackTester_autogen.dir\\AutogenUsed.txt"
  "BackTester\\CMakeFiles\\BackTester_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\MMM_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MMM_autogen.dir\\ParseCache.txt"
  "MMM_autogen"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineApp_autogen.dir\\AutogenUsed.txt"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineApp_autogen.dir\\ParseCache.txt"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineLib_autogen.dir\\AutogenUsed.txt"
  "NetworkEngineLib\\CMakeFiles\\NetworkEngineLib_autogen.dir\\ParseCache.txt"
  "NetworkEngineLib\\NetworkEngineApp_autogen"
  "NetworkEngineLib\\NetworkEngineLib_autogen"
  "TradeCenterConnector\\CMakeFiles\\TradeCenterConnector_autogen.dir\\AutogenUsed.txt"
  "TradeCenterConnector\\CMakeFiles\\TradeCenterConnector_autogen.dir\\ParseCache.txt"
  "TradeCenterConnector\\TradeCenterConnector_autogen"
  "Util\\CMakeFiles\\Utils_autogen.dir\\AutogenUsed.txt"
  "Util\\CMakeFiles\\Utils_autogen.dir\\ParseCache.txt"
  "Util\\Utils_autogen"
  )
endif()
