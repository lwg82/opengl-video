cmake_minimum_required (VERSION 3.0)

project (lua-workspace)


if(UNIX)
	
	include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/include")
	link_directories("${CMAKE_SOURCE_DIR}/lib")
	

	set(COMMON_LIBS glut X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL GLU rt dl m pthread liblua.a)
else()
	
	include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/include")
	link_directories("${CMAKE_SOURCE_DIR}/lib")

	set(COMMON_LIBS ${COMMON_LIBS} freeglut_static)
endif()




set(COMPILE_EXAMPLE
			${COMPILE_EXAMPLE}
			#chap01
			chap02
			chap03
			chap04
		)



set(EXAMPLES
	${COMPILE_EXAMPLE}
)


message(STATUS "comment libs:${COMMON_LIBS}\n")

foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE}  
		       ${COMPILE_EXAMPLE_EXTR}
		       ${EXAMPLE}.cpp)
	set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
  	target_link_libraries(${EXAMPLE} ${COMMON_LIBS})
endforeach()














