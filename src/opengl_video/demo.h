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


#define UNUSED_PARAMETER(param) (void)param
#define OUT_PUT_FUNTION_POSITON  printf("%s %d \n", __FUNCTION__, __LINE__);

namespace demo
{

	struct float3
	{
		GLfloat x,y,z;
	};

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
			  void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
			  static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
			  {
				app->OnKey(window, key, scancode, action, mods);
			  }
				
		
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

			void draw_cube(GLfloat x=0.0f, GLfloat y=0.0f, GLfloat z=-10.0f);

			// 移动相机 gluLookAt
			

			struct float3 _eye;
			struct float3 _lookAt;
			
			
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
