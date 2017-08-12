cmake_minimum_required (VERSION 3.0)

project (opengl-video)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)


# OpenGL
find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
	message(ERROR "OPENGL not find!")
else()
	message(STATUS "opengl:\n${OPENGL_INCLUDE_DIR} \n${OPENGL_LIBRARIES}")

	include_directories(${OpenGL_INCLUDE_DIRS})
	link_directories(${OpenGL_LIBRARY_DIRS})
	add_definitions(${OpenGL_DEFINITIONS})

	#message(STATUS  ${GLUT_INCLUDE_DIRS})
	#message(STATUS  ${GLUT_LIBRARY_DIRS})
	#message(STATUS  ${GLUT_DEFINITIONS})
endif(NOT OPENGL_FOUND)

# GLEW

# GLFW
if(UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GLFW REQUIRED glfw3)

	if(NOT GLFW_FOUND)
		message(ERROR "glfw3 not find!")
		return()
	endif()

	message(STATUS "glfw3:\n${GLFW_INCLUDE_DIRS} \n${GLFW_LIBRARY_DIRS}")

		
	include_directories(${GLFW_INCLUDE_DIRS})
	link_directories(${GLFW_LIBRARY_DIRS})

	set(COMMON_LIBS glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl m pthread)

	
elseif(WIN32)
	if(MSVC14)
		set(COMMON_LIBS glfw3_2015 ${OPENGL_LIBRARIES})
	else()
		set(COMMON_LIBS glfw3 ${OPENGL_LIBRARIES})
	endif(MSVC14)
endif()




set(EXAMPLES
	draw_point
	chap201
	chap202)


foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} WIN32 src/${EXAMPLE}.cpp)
	set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
  	target_link_libraries(${EXAMPLE} ${COMMON_LIBS})
endforeach()















