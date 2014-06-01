if (MSVC)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
endif ()
add_executable (lemon-bin lemon.c)