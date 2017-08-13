#pragma once


//GLEW  
//#define GLEW_STATIC  
//#include <GL/glew.h>  

#include <GLFW/glfw3.h>


#include <cstdio>
#include <cstdlib>


#define UNUSED_PARAMETER(param) (void)param
#define OUT_PUT_FUNTION_POSITON  printf("%s %d \n", __FUNCTION__, __LINE__);

namespace demo
{
	class demo_app
	{
		public:
			demo_app();
			virtual ~demo_app();

			virtual void init();
			virtual void release();	
			virtual void render();

	
			virtual void run(demo_app *app);

			static void glfwErrorCallback(int error, const char *description);
		
		protected:
			GLFWwindow *pWindow;
			int         width;
			int         height;
			
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
