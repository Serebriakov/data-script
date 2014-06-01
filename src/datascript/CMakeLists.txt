set (scanner_generated ${CMAKE_CURRENT_BINARY_DIR}/scanner/scanner.re2c.c)
set (scanner_input ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.re2c)

set (scanner_src 
  scanner/tokens.cpp 
  scanner/io.cpp
  scanner/scanner_iface.c
  scanner/scanner.cpp
  ${scanner_generated}
  )

set (scanner_hdr 
  scanner/tokens.h 
  scanner/io.hpp 
  scanner/scanner_iface.h 
  scanner/scanner.hpp)

set (generic_src)
set (generic_hdr
	compiler.h
	datascript_api.h
)

# ========================
# housekeeping
# ========================

set (modules 
	generic
	scanner
)

if (WIN32)
	list (APPEND modules win_reg)
endif ()


set (src )
set (hdr )

foreach (m ${modules})
  set (mdl_src ${${m}_src})
  set (mdl_hdr ${${m}_hdr})
  
  foreach (s ${mdl_src})
    list (APPEND src ${s})
  endforeach ()

  foreach (h ${mdl_hdr})
    list (APPEND hdr ${h})
  endforeach ()
  if (m MATCHES "generic")
    source_group ("sources" FILES ${mdl_src})
    source_group ("headers" FILES ${mdl_hdr})
  else ()
    source_group ("${m}\\sources" FILES ${mdl_src})
    source_group ("${m}\\headers" FILES ${mdl_hdr})
  endif ()
endforeach ()


   
onyx_shared_lib (datascript src hdr)

if (WINDOWS)
	set (RE2C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/re2c-bin.exe)
else ()
	set (RE2C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/re2c-bin)
endif ()

ADD_CUSTOM_COMMAND(
   OUTPUT ${scanner_generated}
   COMMAND ${RE2C} -cbs -o ${scanner_generated} ${scanner_input}
   DEPENDS re2c-bin {scanner_input}
   )
ADD_CUSTOM_TARGET(scanner ALL DEPENDS ${scanner_generated})

