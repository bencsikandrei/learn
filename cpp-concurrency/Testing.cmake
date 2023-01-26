## Add a google test
macro(add_gtest )
	set(options)
	set(oneValueArgs TCNAME)
	set(multiValueArgs SOURCE_FILES LIBS)
    cmake_parse_arguments(add_gtest "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )
	## Add the test executable
	add_executable(${add_gtest_TCNAME} ${add_gtest_SOURCE_FILES})
	## If extra argument given
	message("-- Additional link libraries: ${add_gtest_LIBS}")
	target_link_libraries(${add_gtest_TCNAME} ${add_gtest_LIBS})
	message("-- Added gtest: ${add_gtest_TCNAME}")
endmacro()


