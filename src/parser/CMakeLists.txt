set (src 
  tokens.cpp 
  main.cpp
  io.cpp
  scanner_iface.c
  scanner.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/scanner.re2c.c)

set (hdr 
  tokens.h 
  io.hpp 
  scanner_iface.h 
  scanner.hpp)

if (WINDOWS)
	set (RE2C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/re2c-bin.exe)
else ()
	set (RE2C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/re2c-bin)
endif ()

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/scanner.re2c.c
   COMMAND ${RE2C} -cbs -o ${CMAKE_CURRENT_BINARY_DIR}/scanner.re2c.c ${CMAKE_CURRENT_SOURCE_DIR}/scanner.re2c
   DEPENDS re2c-bin ${CMAKE_CURRENT_SOURCE_DIR}/scanner.re2c
   )


onyx_exec (parser src hdr)

ADD_CUSTOM_TARGET(scanner ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/scanner.re2c.c)

