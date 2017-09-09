#pragma once


//GLEW  
#define GLEW_STATIC  
#include <GL/glew.h>  


// glu
//#include <GL/glu.h>

// GLFW
#include <GLFW/glfw3.h>



#if _WIN32
	#define _USE_MATH_DEFINES
#endif

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "CELLMath.hpp"

using namespace CELL;

#include "camera.h"
#include "camera3rd.h"

#define UNUSED_PARAMETER(param) (void)param
#define OUT_PUT_FUNTION_POSITON  printf("%s %d \n", __FUNCTION__, __LINE__);

namespace demo
{

	

	class demo_app
	{
		public:
			demo_app();
			virtual ~demo_app();

			GLenum check_error();
			virtual void init();
			virtual void release();	
			virtual void render();

	
			virtual void run(demo_app *app);

			static void glfwErrorCallback(int error, const char *description);

		public:
			// 键盘事件
			  virtual void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
			  static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
			  {
				app->OnKey(window, key, scancode, action, mods);
			  }

			  virtual void OnMouse(GLFWwindow* window, int key, int action, int mods);
			  static void glfw_OnMouse(GLFWwindow* window, int key, int action, int mods)	
			  {
				app->OnMouse(window, key, action, mods);		
			  }
			
                          virtual void OnCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
			  static void glfw_OnCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
			  {
				app->OnCursorPosCallback(window, xpos, ypos);
			  }

			  virtual void OnScroll(GLFWwindow* window, double xoffset, double yoffset);
			  static void glfw_OnScroll(GLFWwindow* window, double xoffset, double yoffset)
			  {
				app->OnScroll(window, xoffset, yoffset);
			  }

			  virtual void OnWindowSize(GLFWwindow *window, int width, int height);
		          static void glfw_OnWindowSize(GLFWwindow *window, int width, int height)
			  {
				app->OnWindowSize(window, width, height);
			  }

		public:
			unsigned   CreateTexture(int w,int h,const void* data);
			bool       CreateTextureFromImage(const char *fileName, GLuint &textureId);
				
		
		protected:
			GLFWwindow *pWindow;
			int         width;
			int         height;

			static      demo_app  *app;

			

		protected:

			// 绘制旋转立方体
			GLfloat _rotate_angle;

			struct vertex_color
			{
				unsigned char r,g,b,a;
				float x,y,z;
			};

			struct vertex_texture
			{
				GLfloat u,v;
				GLfloat x,y,z;
			};

			void draw_cube(GLfloat x=0.0f, GLfloat y=0.0f, GLfloat z=-10.0f);
			
			// 绘制地面
			

			// 移动相机 gluLookAt
			

			float3 _eye;
			float3 _lookAt;
			
			

			bool        left_button_pressed;
			int2        _mouse_pos;


			
	};
}




#define DECLARE_MAIN(app)	                       \
int main(int argc, char *argv[])                   \
{                                                  \
	UNUSED_PARAMETER(argc);UNUSED_PARAMETER(argv); \
	app *obj = new app;                            \
	obj->run(obj);                                   \
	delete obj;                                    \
	exit(EXIT_SUCCESS);                            \
}                                                  \



/*

	http://blog.csdn.net/qq_28637193/article/details/52502828
*/
