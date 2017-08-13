cmake_minimum_required (VERSION 3.0)

project (opengl-video)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

option(USE_GLEW        "Use glew library" OFF)
option(COMPILE_CHAP02  "Compile chap02"   ON)


# c++11
include(CheckCXXCompilerFlag)  
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)  
if(COMPILER_SUPPORTS_CXX11)  
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  
elseif(COMPILER_SUPPORTS_CXX0X)  
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
else()  
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
endif()  

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

if(USE_GLEW)
	set(GLEW_INCLUDE /usr/include)
	set(GLEW_LIBRARY /usr/lib64)

	message(STATUS "glew:\n${GLEW_INCLUDE} \n${GLEW_LIBRARY}")


	include_directories(GLEW_INCLUDE)
	link_directories(GLEW_INCLUDE)

	set(COMMON_LIBS ${COMMON_LIBS}
		GLEW.a
	)
endif()

set(COMPILE_EXAMPLE
)	

if(COMPILE_CHAP02)
	set(COMPILE_EXAMPLE
	${COMPILE_EXAMPLE}
	draw_point
	chap201
	chap202
	chap203
	chap204
	chap205
	chap206
	chap207
	chap208
	chap209)
endif()

set(EXAMPLES
	${COMPILE_EXAMPLE}
)


foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} WIN32 
			src/demo.h
			src/demo.cpp
			src/${EXAMPLE}.cpp)
	set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
  	target_link_libraries(${EXAMPLE} ${COMMON_LIBS})
endforeach()















