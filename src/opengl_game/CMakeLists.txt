cmake_minimum_required (VERSION 3.0)

project (opengl-game)

# freeglut
if(UNIX)
	find_package(GLUT REQUIRED)

	if(NOT GLUT_FOUND)
		message(ERROR "GLUT not find!")
		return()
	endif()


	message(STATUS "glut:\n${GLUT_INCLUDE_DIR} \n${GLUT_LIBRARIES}")

	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARIES})
	#add_definitions(${OpenGL_DEFINITIONS})

	set(COMMON_LIBS glut X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL GLU rt dl m pthread)
else()
	
	include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/include")
	link_directories("${CMAKE_SOURCE_DIR}/lib")

	set(COMMON_LIBS ${COMMON_LIBS} freeglut_staticd)
endif()




set(COMPILE_EXAMPLE
			${COMPILE_EXAMPLE}
			#ogc_chap0401
			ogc_chap0402
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














