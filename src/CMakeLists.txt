cmake_minimum_required (VERSION 3.0)

project (opengl-demo)

option(USE_GLEW        "Use glew library"    TRUE)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)


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
	
	set(COMMON_LIBS	${OPENGL_LIBRARIES})
endif(NOT OPENGL_FOUND)


# GLEW
if(USE_GLEW)
	if(UNIX)
		set(GLEW_INCLUDE /usr/include)
		set(GLEW_LIBRARY /usr/lib64)

		message(STATUS "glew:\n${GLEW_INCLUDE} \n${GLEW_LIBRARY}")


		include_directories(GLEW_INCLUDE)
		link_directories(GLEW_LIBRARY)

		set(COMMON_LIBS ${COMMON_LIBS}
			GLEW.a
		)
	else()
		include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/include")
		link_directories("${CMAKE_SOURCE_DIR}/lib")

		set(COMMON_LIBS ${COMMON_LIBS} glew32)
	endif()
endif()


#add_subdirectory(opengl_game)
add_subdirectory(opengl_video)











