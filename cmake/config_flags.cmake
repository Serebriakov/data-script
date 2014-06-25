# ##################################################
# Compiler flags
# ##################################################

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

include (TestBigEndian)

test_big_endian (ONYX_HAS_BIGENDIAN)

if (${ONYX_HAS_BIGENDIAN})
  message (STATUS "BigEndian platform detected")
else ()
  message (STATUS "LittleEndian platform detected")
endif ()


# --------------------------------------------------
# GCC flags
# --------------------------------------------------

if (UNIX OR MINGW)
  set (LFS_FLAGS "-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE")
else ()
endif ()

if (${ONYX_HAS_BIGENDIAN})
  set (ONYX_ENDIANITY_FLAG "-DONYX_BIG_ENDIAN")
endif ()

if (BUILD_64BIT) 
   set (ONYX_BITNESS_FLAG "-DONYX_BUILD_64BIT")				
endif ()

set (ONYX_DEFINITIONS "${ONYX_BITNESS_FLAG} ${ONYX_ENDIANITY_FLAG}")

# --------------------------------------------------
# GCC flags
# --------------------------------------------------

# warning
set (GCC_COMMON_WARNINGS "-Wall -Wunknown-pragmas -Wformat-security -Wpacked  -Wparentheses  -Wpointer-arith -Wwrite-strings -Wundef -Wextra -Wconversion -Wno-long-long -Wno-variadic-macros")

set (GCC_WARNINGS "${GCC_COMMON_WARNINGS} -Wmissing-prototypes")
set (GPP_WARNINGS "${GCC_COMMON_WARNINGS} -Wnon-virtual-dtor") 

set (GCC_NO_WARNINGS "-w")
set (GPP_NO_WARNINGS "${GCC_NO_WARNINGS}") 

#compiler flags
set (GCC_COMMON_FLAGS "${GCC_64_FLAG} -pipe -fstrict-aliasing -pedantic -fvisibility=hidden -ffunction-sections -fdata-sections ${LFS_FLAGS} ${ONYX_ENDIANITY_FLAG}")
set (GCC_FLAGS "${GCC_COMMON_FLAGS}")
set (GPP_FLAGS "${GCC_COMMON_FLAGS} -fvisibility-inlines-hidden")

set (GCC_FLAGS_DEBUG "${GCC_FLAGS} -g")
set (GCC_FLAGS_RELEASE "${GCC_FLAGS} -O2")
set (GPP_FLAGS_DEBUG "${GPP_FLAGS} -g")
set (GPP_FLAGS_RELEASE "${GPP_FLAGS} -O2")

set (GCC_DEFINES_DEBUG "-D_DEBUG=1 -DONYX_DEBUG")
set (GCC_DEFINES_RELEASE "-DNDEBUG")

#set (GCC_LINKER_FLAGS_DEBUG "-Wl,--gc-sections,--print-gc-sections")

# --------------------------------------------------
# INTEL flags
# --------------------------------------------------

# warning
set (ICC_COMMON_WARNINGS "-Wall -Wpointer-arith -Wwrite-strings -Wcheck -Wp64  -Wconversion")

set (ICC_WARNINGS "${ICC_COMMON_WARNINGS} -Wmissing-prototypes")
set (ICC_NO_WARNINGS "-w")

set (IPP_WARNINGS "${ICC_COMMON_WARNINGS} -Wnon-virtual-dtor ") 
set (IPP_NO_WARNINGS "-w")

#compiler flags
set (ICC_COMMON_FLAGS "${ICC_64_FLAG} -pipe -fno-strict-aliasing -fvisibility=hidden ${LFS_FLAGS}")
set (ICC_FLAGS "${ICC_COMMON_FLAGS}")
set (IPP_FLAGS "${ICC_COMMON_FLAGS} -fvisibility-inlines-hidden")

set (ICC_FLAGS_DEBUG "${ICC_FLAGS} -g")
set (ICC_FLAGS_RELEASE "${ICC_FLAGS} -O2")
set (IPP_FLAGS_DEBUG "${IPP_FLAGS} -g")
set (IPP_FLAGS_RELEASE "${IPP_FLAGS} -O2")

set (ICC_DEFINES_DEBUG "-D_DEBUG=1 -DONYX_DEBUG")
set (ICC_DEFINES_RELEASE "-DNDEBUG")

# --------------------------------------------------
# MSVC flags
# --------------------------------------------------

# warning
set (MSVC_CC_COMMON_WARNINGS "/W3")

set (MSVC_CC_WARNINGS "${MSVC_CC_COMMON_WARNINGS}")
set (MSVC_CXX_WARNINGS "${MSVC_CC_COMMON_WARNINGS} ") 

set (MSVC_CC_NO_WARNINGS "/W0")
set (MSVC_CXX_NO_WARNINGS "${MSVC_CC_NO_WARNINGS} ") 

#compiler flags
set (MSVC_CC_COMMON_FLAGS "${MSVC_CC_64_FLAG} /nologo /EHsc /GR /Zc:wchar_t")
set (MSVC_CC_FLAGS "${MSVC_CC_COMMON_FLAGS}")
set (MSVC_CXX_FLAGS "${MSVC_CC_COMMON_FLAGS}")

set (MSVC_CC_FLAGS_DEBUG "${MSVC_CC_FLAGS} /Zi  /GR /Ob0 /Od /MDd")
set (MSVC_CC_FLAGS_RELEASE "${MSVC_CC_FLAGS} /O2 /MD")

set (MSVC_CXX_FLAGS_DEBUG "${MSVC_CXX_FLAGS} /Zi  /GR /Ob0 /Od /MDd")
set (MSVC_CXX_FLAGS_RELEASE "${MSVC_CXX_FLAGS} /O2 /MD")

set (MSVC_COMMON_DEFINES 
  "/DNOMINMAX ${MSVC_64_FLAG} /D_WINDOWS /D_CONSOLE /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECAT")

set (MSVC_CC_DEFINES_DEBUG "${MSVC_COMMON_DEFINES} /D_DEBUG=1 /DONYX_DEBUG")
set (MSVC_CC_DEFINES_RELEASE "${MSVC_COMMON_DEFINES} /DNDEBUG")

set (MSVC_CC_LINKER_FLAGS_DEBUG "/DEBUG")

# --------------------------------------------------
# SunCC flags
# --------------------------------------------------

set (SUN_CC_COMMON_WARNINGS "-errtags=yes")

set (SUN_CC_WARNINGS "${SUN_CC_COMMON_WARNINGS} ")
set (SUN_CXX_WARNINGS "${SUN_CC_COMMON_WARNINGS} +w2 ")

set (SUN_CC_COMMON_FLAGS "-features=extensions -mt ${SUNCC_64_FLAG} ${LFS_FLAGS}")

if (BUILD_64BIT)
  set (SUN_CC_COMMON_FLAGS "${SUN_CC_COMMON_FLAGS} -m64")
endif ()

set (SUN_CXX_FLAGS_DEBUG "${SUN_CC_COMMON_FLAGS} -g ")
set (SUN_CXX_FLAGS_RELEASE "${SUN_CC_COMMON_FLAGS} -xtarget=native -fast  ")

set (SUN_CC_FLAGS_DEBUG "${SUN_CC_COMMON_FLAGS} -g ")
set (SUN_CC_FLAGS_RELEASE "${SUN_CC_COMMON_FLAGS} -xtarget=native -fast  ")


if (BUILD_64BIT)
  set (SUN_CXX_FLAGS_RELEASE "${SUN_CXX_FLAGS_RELEASE} -xarch=amd64  ")
  set (SUN_CC_FLAGS_RELEASE "${SUN_CXX_FLAGS_RELEASE}  -xarch=amd64 ")
endif ()

set (SUN_CC_DEFINES_DEBUG "-D_DEBUG=1 -DONYX_DEBUG ")
set (SUN_CC_DEFINES_RELEASE "-DNDEBUG  ")

set (SUN_CC_LINKER_FLAGS_DEBUG "-g  -lpthread")
set (SUN_CC_LINKER_FLAGS_RELEASE "-g  -lpthread")

# --------------------------------------------------
# CLang flags
# --------------------------------------------------

set (CLANG_CC_COMMON_WARNINGS "-Weverything -pedantic -Wno-padded -Wno-exit-time-destructors")

set (CLANG_CC_WARNINGS "${CLANG_CC_COMMON_WARNINGS} ")
set (CLANG_CXX_WARNINGS "${CLANG_CC_COMMON_WARNINGS} ")

#set (CLANG_CC_COMMON_FLAGS "-features=extensions -mt ${SUNCC_64_FLAG} ${LFS_FLAGS}")

set (CLANG_CXX_FLAGS_DEBUG "  -g ")
set (CLANG_CXX_FLAGS_RELEASE "-O2  ")

set (CLANG_CC_FLAGS_DEBUG "  -g ")
set (CLANG_CC_FLAGS_RELEASE " -O2 ")

set (CLANG_CC_DEFINES_DEBUG " -D_DEBUG=1 -DONYX_DEBUG ")
set (CLANG_CC_DEFINES_RELEASE " -DNDEBUG  ")

set (CLANG_CC_LINKER_FLAGS_DEBUG " -lpthread")
set (CLANG_CC_LINKER_FLAGS_RELEASE "  -lpthread")

# ======================================================================
macro (config_compile_and_linker_flags_name CXX_NAME CC_NAME)
  if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set (cxx_flags "${${CXX_NAME}_WARNINGS} ${${CXX_NAME}_FLAGS_DEBUG} ${${CC_NAME}_DEFINES_DEBUG}")
    set (cc_flags  "${${CC_NAME}_WARNINGS} ${${CC_NAME}_FLAGS_DEBUG} ${${CC_NAME}_DEFINES_DEBUG}")
	
    set (cxx_no_warn_flags "${${CXX_NAME}_NO_WARNINGS} ${${CXX_NAME}_FLAGS_DEBUG} ${${CC_NAME}_DEFINES_DEBUG}")
    set (cc_no_warn_flags  "${${CC_NAME}_NO_WARNINGS} ${${CC_NAME}_FLAGS_DEBUG} ${${CC_NAME}_DEFINES_DEBUG}")

    set (linker_flags  "${${CC_NAME}_LINKER_FLAGS_DEBUG}")
  else ()
    set (cxx_flags "${${CXX_NAME}_WARNINGS} ${${CXX_NAME}_FLAGS_RELEASE} ${${CC_NAME}_DEFINES_RELEASE}")
    set (cc_flags  "${${CC_NAME}_WARNINGS} ${${CC_NAME}_FLAGS_RELEASE} ${${CC_NAME}_DEFINES_RELEASE}")

    set (cxx_no_warn_flags "${${CXX_NAME}_NO_WARNINGS} ${${CXX_NAME}_FLAGS_RELEASE} ${${CC_NAME}_DEFINES_RELEASE}")
    set (cc_no_warn_flags  "${${CC_NAME}_NO_WARNINGS} ${${CC_NAME}_FLAGS_RELEASE} ${${CC_NAME}_DEFINES_RELEASE}")

    set (linker_flags  "${${CC_NAME}_LINKER_FLAGS_RELEASE}")
  endif ()

  set (cc_flags "${cc_flags} ${MULTI_THREADED_COMPILE_FLAGS} ${ONYX_COMMON_CC_FLAGS} ${ONYX_DEFINITIONS}")
  set (cxx_flags "${cxx_flags} ${MULTI_THREADED_COMPILE_FLAGS} ${ONYX_COMMON_CXX_FLAGS} ${ONYX_DEFINITIONS}")
endmacro ()
# ======================================================================
if (ONYX_TOOLSET STREQUAL "intel")
  config_compile_and_linker_flags_name (IPP ICC)
elseif (ONYX_TOOLSET STREQUAL "gcc44" OR ONYX_TOOLSET STREQUAL "gcc45" OR ONYX_TOOLSET STREQUAL "gcc46" OR ONYX_TOOLSET STREQUAL "gcc47" OR ONYX_TOOLSET STREQUAL "gcc48")
  config_compile_and_linker_flags_name (GPP GCC)
elseif (ONYX_TOOLSET STREQUAL "vc80" OR ONYX_TOOLSET STREQUAL "vc90" OR ONYX_TOOLSET STREQUAL "vc11" OR ONYX_TOOLSET STREQUAL "vc10" OR ONYX_TOOLSET STREQUAL "vc12")
  config_compile_and_linker_flags_name (MSVC_CXX MSVC_CC)
elseif (ONYX_TOOLSET STREQUAL "SunCC")
  config_compile_and_linker_flags_name (SUN_CXX SUN_CC)
elseif (ONYX_TOOLSET STREQUAL "clang")
  config_compile_and_linker_flags_name (CLANG_CXX CLANG_CC)
else ()
  message (FATAL_ERROR "Unknown compiler ${ONYX_TOOLSET}")
endif ()

set (cc_flags "${cc_flags} -DSOURCES_ROOT=${CMAKE_SOURCE_DIR}")
set (cxx_flags "${cxx_flags} -DSOURCES_ROOT=${CMAKE_SOURCE_DIR}")


if (OPENMP_FOUND)
set (cc_flags "${cc_flags} ")
set (cxx_flags "${cxx_flags} ")
endif ()

message ("------------------------------------------")
message ("CC  flags: ${cc_flags}")
message ("C++ flags: ${cxx_flags}")
message ("------------------------------------------")

