#pragma once

//GLEW  
#define GLEW_STATIC  
#include <GL/glew.h> 


#include <GL/freeglut.h>



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
	class demo_app
	{
		public:
			demo_app();
			virtual ~demo_app();

			virtual void init(int &argc, char **argv);
			virtual void release();	
			virtual void render();

	
			virtual void run(demo_app *app);

			
		
		protected:
			
			int         width;
			int         height;
			
	};
}




#define DECLARE_MAIN(app)	                       \
int main(int argc, char *argv[])                   \
{                                                  \
	app *obj = new app;                            \
	obj->run(obj);                                   \
	delete obj;                                    \
	exit(EXIT_SUCCESS);                            \
}                                                  \



