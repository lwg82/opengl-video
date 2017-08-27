cmake_minimum_required (VERSION 3.0)

project (opengl-video)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

option(USE_GLEW        "Use glew library" TRUE)
option(USE_GLFW        "Use glfw library")
option(USE_FREEGLUT    "Use freeglut library" TRUE)


#编译内容 glfw
option(COMPILE_CHAP02  "Compile chap02")
option(COMPILE_CHAP03  "Compile chap03")

#编译内容 freeglut
option(COMPILE_OPENGL_GAME_COMPILE "OpenGL game compile" TRUE)

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


# GLFW
if(USE_GLFW)
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

		set(COMMON_LIBS glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL GLU rt dl m pthread)

	
	elseif(WIN32)

		include_directories(include)
		link_directories(${PROJECT_SOURCE_DIR}/lib)
	
		if(MSVC14)
			set(COMMON_LIBS glfw3_2015 ${OPENGL_LIBRARIES})
		else()
			set(COMMON_LIBS glfw3 ${OPENGL_LIBRARIES})
		endif(MSVC14)
	endif()
endif()
	

# GLFW 编译内容
if(USE_GLFW)
	set(COMPILE_EXAMPLE_EXTR
		src/demo.h
		src/demo.cpp)
		 
		


	if(COMPILE_CHAP02)

		message(STATUS "chap02 compile...")

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


	if(COMPILE_CHAP03)

		message(STATUS "chap03 compile...")

		set(COMPILE_EXAMPLE
			${COMPILE_EXAMPLE}
			chap301
			chap302
			chap303
			chap3032
			chap304
			chap305
			chap306)

	endif()
endif()




# freeglut
if(USE_FREEGLUT)
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
		

	endif()
endif()


if(USE_FREEGLUT)

	set(COMPILE_EXAMPLE_EXTR
		src/freeglut_app.h
		src/freeglut_app.cpp)

	# OpenGL游戏编程
	if(COMPILE_OPENGL_GAME_COMPILE)
	
		set(COMPILE_EXAMPLE
			${COMPILE_EXAMPLE}
			#ogc_chap0401
			ogc_chap0402
		)

	endif(COMPILE_OPENGL_GAME_COMPILE)

endif()




set(EXAMPLES
	${COMPILE_EXAMPLE}
)


foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE}  
		       ${COMPILE_EXAMPLE_EXTR}
		       src/${EXAMPLE}.cpp)
	set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
  	target_link_libraries(${EXAMPLE} ${COMMON_LIBS})
endforeach()















