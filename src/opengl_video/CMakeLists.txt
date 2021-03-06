﻿cmake_minimum_required (VERSION 3.0)

project (opengl-video)

option(COMPILE_CHAP02        "Compile chap02")
option(COMPILE_CHAP04        "Compile chap04 -- texture")
option(COMPILE_CHAP06        "Compile chap06" TRUE)

#GLFW
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

# 添加 freeimage
if(UNIX)
	include_directories(${CMAKE_SOURCE_DIR}/include)
	link_directories(${CMAKE_SOURCE_DIR}/lib)

	message(STATUS "lib:\n${CMAKE_SOURCE_DIR}/lib")

	set(COMMON_LIBS ${COMMON_LIBS}  freeimage) # 静态库
endif()


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
			chap209
			chap301
			chap302
			chap303
			chap3032
			chap304
			chap305
			chap306
		)

endif(COMPILE_CHAP02)

if(COMPILE_CHAP04)
	
set(COMPILE_EXAMPLE
			${COMPILE_EXAMPLE}
			texture01
			texture02
			texture03
			texture04
			texture05
			texture06
)

endif(COMPILE_CHAP04)


if(COMPILE_CHAP06)
set(COMPILE_EXAMPLE
			${COMPILE_EXAMPLE}
			chap0601
			chap0602
			chap0603
			chap0604
			chap0605
			chap0606
			chap0607
)

endif(COMPILE_CHAP06)

set(EXAMPLES
	${COMPILE_EXAMPLE}
)

set(COMPILE_EXAMPLE_EXTR
		demo.h
		demo.cpp
		camera.h
		imager.h
		camera3rd.h)

message(STATUS "comment libs:${COMMON_LIBS}\n")

foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE}  
		       ${COMPILE_EXAMPLE_EXTR}
		       ${EXAMPLE}.cpp)
	set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
  	target_link_libraries(${EXAMPLE} ${COMMON_LIBS})
endforeach()














