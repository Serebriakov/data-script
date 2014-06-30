set (scanner_generated ${CMAKE_CURRENT_BINARY_DIR}/scanner.re2c.c)
set (scanner_input ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.re2c)

set (scanner_src 
  scanner/lexer.cpp
  scanner/lexeme.cpp
  scanner/tokens_storage.cpp
  ${scanner_generated}
  )

set (scanner_hdr 
  scanner/tokens.h 
  scanner/tokens_storage.h
  scanner/lexeme.hpp
  scanner/lexer.hpp)
# -------------------------------------------------
set (libscanner_src
  scanner/libscanner/libscanner.c
  scanner/libscanner/reader.c
)
set (libscanner_hdr
  scanner/libscanner/libscanner.h
  scanner/libscanner/reader.h
)
# -------------------------------------------------
set (parser_src
  ${CMAKE_CURRENT_BINARY_DIR}/dsparser.c
  parser/parser.cpp
  parser/parser_procs.cpp
)
# -------------------------------------------------
set (parser_hdr
  ${CMAKE_CURRENT_BINARY_DIR}/dsparser.h
  parser/parser.hpp
  parser/parserfwd.h
  parser/parser_procs.h
)
# -------------------------------------------------
set (generic_src
  ast_builder.cpp
  syntax_tree.cpp
)

set (generic_hdr
	compiler.h
	datascript_api.h
	ast_builder.hpp
	syntax_tree.hpp
)

# ========================
# housekeeping
# ========================

set (modules 
	generic
	scanner
	libscanner
	parser
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


if (WINDOWS)
	set (RE2C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/re2c-bin.exe)
	set (LEMON ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lemon-bin.exe)
else ()
	set (RE2C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/re2c-bin)
	set (LEMON ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lemon-bin)
endif ()

ADD_CUSTOM_COMMAND(
   OUTPUT ${scanner_generated}
   COMMAND ${RE2C} -cbs -o ${scanner_generated} ${scanner_input}
   DEPENDS re2c-bin ${scanner_input}
   )

ADD_CUSTOM_COMMAND (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dsparser.c ${CMAKE_CURRENT_BINARY_DIR}/dsparser.h
  COMMAND ${LEMON} -q ${CMAKE_CURRENT_SOURCE_DIR}/parser/dsparser.y -T${CMAKE_SOURCE_DIR}/src/tools/lemon/lempar.c
  COMMAND cmake -E rename ${CMAKE_CURRENT_SOURCE_DIR}/parser/dsparser.c ${CMAKE_CURRENT_BINARY_DIR}/dsparser.c
  COMMAND cmake -E rename ${CMAKE_CURRENT_SOURCE_DIR}/parser/dsparser.h ${CMAKE_CURRENT_BINARY_DIR}/dsparser.h
  DEPENDS lemon-bin ${CMAKE_SOURCE_DIR}/src/tools/lemon/lempar.c ${CMAKE_CURRENT_SOURCE_DIR}/parser/dsparser.y
)

include_directories (${CMAKE_CURRENT_BINARY_DIR})   

onyx_shared_lib (datascript src hdr)

#ADD_CUSTOM_TARGET(scanner ALL DEPENDS ${scanner_generated})

