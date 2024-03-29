macro (ONYX_INSTALL_PROGRAM oname)
INSTALL (TARGETS ${oname}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib 
	)
endmacro ()
# -----------------------------------------------------------------------
macro (onyx_apply_flags base_name defs)
  

  include_directories (${ONYX_INCLUDE})
  link_directories (${ONYX_LIBS_PATH})
  add_definitions (${defs})

  string (TOUPPER ${base_name} defname)

  

  if (MSVC_IDE)
  	set (CMAKE_CC_FLAGS "${cc_flags}")
  	set (CMAKE_CXX_FLAGS "${cxx_flags}")
  	if (linker_flags)
      	    set (CMAKE_EXE_LINKER_FLAGS "${linker_flags}")
      	    set (CMAKE_SHARED_LINKER_FLAGS "${linker_flags}")
      	    set (CMAKE_MODULE_LINKER_FLAGS "${linker_flags}")
        endif ()
  	
  	
 else ()
  get_target_property (INC_DIRS ${base_name} INCLUDE_DIRECTORIES)
  if (INC_DIRS STREQUAL "INC_DIRS-NOTFOUND")
    set (INC_DIRS)
  endif ()
  foreach (inc_dir ${ONYX_INCLUDE})
    list (APPEND INC_DIRS ${inc_dir})
  endforeach ()

  get_target_property (TGT_SRC ${base_name} SOURCES)
  if (TGT_SRC STREQUAL "TGT_SRC-NOTFOUND")
    message (FATAL_ERROR "No sources for ${base_name}")
  endif ()
  #message (STATUS "**************** TGT ${TGT_SRC}")  
  foreach (src ${TGT_SRC})
    string (REGEX MATCH ".cpp$" ext ${src})
    if (ext STREQUAL ".cpp")
      set (cxx_f "${cxx_flags} ${defs}")
      #message (STATUS "${base_name} **************** ${cxx_f}")
      set_source_files_properties (${src} PROPERTIES COMPILE_FLAGS ${cxx_f})
    endif ()
    string (REGEX MATCH ".c$" ext ${src})
    if (ext STREQUAL ".c")
      set (cc_f "${cc_flags} ${defs}")  
      #message (STATUS "${base_name} **************** ${cc_f}")
      set_source_files_properties (${src} PROPERTIES COMPILE_FLAGS "${cc_f}" )
    endif ()
    #if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    #    set_source_files_properties (${src} PROPERTIES COMPILE_DEFINITIONS_DEBUG ${defs})
    #else ()
    #    set_source_files_properties (${src} PROPERTIES COMPILE_DEFINITIONS_DEBUG ${defs})
    #endif ()
  endforeach ()
  include_directories (${INC_DIRS})
  set_target_properties (${base_name} PROPERTIES LINK_DIRECTORIES "${ONYX_LIBS_PATH}")
 endif ()
endmacro ()
# -----------------------------------------------------------------------
macro (onyx_shared_lib base_name sources headers)
  set (outname "${base_name}")
  string (TOUPPER ${base_name} defname)
  add_library (${outname} SHARED ${${sources}} ${${headers}})
  onyx_install_program (${outname})
  target_link_libraries (${outname} ${ARGN} ${ONYX_CORE_LIBS})
  set (defs  "-D${defname}_CREATE_SHARED_LIBRARY -DONYX_MODULE_NAME=${base_name}")
  onyx_apply_flags (${outname} ${defs})
endmacro ()
# -------------------------------------------------------------------
macro (onyx_static_lib base_name sources headers)
  set (outname "${base_name}")
  string (TOUPPER ${base_name} defname)
  set (defs "-DONYX_MODULE_NAME=${base_name} -D${defname}_AS_STATIC_LIBRARY")
  add_library (${outname} STATIC ${${sources}} ${${headers}})
  onyx_apply_flags (${outname} ${defs})
endmacro ()
# -------------------------------------------------------------------
macro (onyx_exec base_name sources headers)
  set (outname ${base_name})
  
  add_executable (${outname} ${${sources}} ${${headers}})
  set_target_properties (${outname} PROPERTIES LINK_FLAGS "${linker_flags}")
  target_link_libraries (${outname} ${ARGN} ${SDL_MAIN} ${ONYX_CORE_LIBS})
  
  onyx_install_program (${outname})
  set (defs "-DONYX_MODULE_NAME=${base_name}")
  onyx_apply_flags (${outname} ${defs})
endmacro ()
# ------------------------------------------------------------------
function(cxx_test name sources)
  set (outname ${name}_test)
  set (defs "-DONYX_MODULE_NAME=${outname}")
  if (NOT MSVC_IDE)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)
  endif ()
  add_executable (${outname} ${sources})
  
  target_link_libraries (${outname} ${ARGN} ${ONYX_CORE_LIBS})
  get_target_property (test_path ${outname} LOCATION)
  if (MSVC_IDE)
    STRING(REGEX REPLACE "\\$\\(.*\\)" "\${CTEST_CONFIGURATION_TYPE}" test_path "${test_path}") 

  endif ()

  onyx_apply_flags (${outname} ${defs})
  add_test ("${outname}" ${test_path} "-t" "*")
endfunction()
