#include "demo.h"

#include <cstring>

using namespace demo;


demo_app *demo_app::app=nullptr;

demo_app::demo_app():pWindow(nullptr),width(800), height(600),_rotate_angle(0.0f)
{
	_eye.x = 0.0f; _eye.y = 0.0f; _eye.z = 0.0f;
	_lookAt.x = 0.0f; _lookAt.y = 0.0f; _lookAt.z = 0.0f;
}


demo_app::~demo_app()
{
	
}

void demo_app::glfwErrorCallback(int error, const char *description)

{
	printf("%s %d: %d:%s \n", __FUNCTION__, __LINE__, error, description);
} 


void demo_app::run(demo_app *a)
{
	app = a;

	if (!glfwInit())
	{
	    fprintf(stderr, "Failed to initialize GLFW\n");
	    glfwSetErrorCallback(glfwErrorCallback); 
	    exit(EXIT_FAILURE);
	}


	int Major, Minor, Rev;
	glfwGetVersion(&Major, &Minor, &Rev);
	printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);


	// opengl core profile 4.0
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Major = 4
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
 
	
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);   //不可改变大小  
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);   //没有边框和标题栏  

	pWindow = glfwCreateWindow(width, height, "Simple example",  /*glfwGetPrimaryMonitor()*/ NULL, NULL);
	if (!pWindow)
	{
		fprintf(stderr, "Failed to open window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowPos(pWindow, 200, 200);
	
	// 回调窗口宽高
	//glfwSetWindowSizeCallback(window, glfw_onResize); 

	/* Make the window's context current */
	glfwMakeContextCurrent(pWindow);
/*
	//glew设置为true  让glew知道使用现在的方法去恢复指针和扩展  
   	 glewExperimental = GL_TRUE;  
    	//初始化glew 去设置opengl功能指针  
     	 GLenum err = glewInit();     
   	 if( err != GLEW_OK ) {    
       	 	fprintf( stderr, "glew init error: %s\n", glewGetErrorString(err));    
       		exit(EXIT_FAILURE);
    	}    
*/

	GLint major, minor;  
        glGetIntegerv(GL_MAJOR_VERSION, &major);  
        glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL version(d):%d,%d\n", major,minor);    

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	fprintf(stderr, "VENDOR: %s\n", glGetString(GL_VENDOR));
	fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
	fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));


	glfwSetKeyCallback(pWindow, glfw_onKey);
	init();

	while (!glfwWindowShouldClose(pWindow))
	{
		render();

	 	glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	release();

	glfwDestroyWindow(pWindow);

	glfwTerminate();
}

void demo_app::render()
{
	 // 清空颜色缓存
    	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	// 视口
	glViewport(0, 0, width, height);

	// 指定一下操作针对投影矩阵
	glMatrixMode(GL_PROJECTION);

	// 将投影矩阵清空为单位矩阵
	glLoadIdentity();
	
	// 产生投影矩阵
	glOrtho(0, width, height, 0, -100, 100);

	// 颜色
	glColor3f(1, 1, 1);
	// 划线
	glBegin(GL_TRIANGLES);
		glVertex3f(width*0.5f, 0, 0);
		glVertex3f(width, height, 0);
		glVertex3f(0, height, 0);
	glEnd();
}

void demo_app::init()
{

}


void demo_app::release()
{

}	


void demo_app::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("key: %d \n", key);
	switch(key)
	{
		case GLFW_KEY_UP:
			_camera.moveFront();
		break;

		case GLFW_KEY_DOWN:
			_camera.moveBack();
		break;

		case GLFW_KEY_LEFT:
			_camera.moveLeft();
		break;

		case GLFW_KEY_RIGHT:
			_camera.moveRight();
		break;
	}
	

}

void demo_app::draw_cube(GLfloat x, GLfloat y, GLfloat z)
{
		struct vertex_color cube[] =
			{
				
				// front
				{255,0,0,1,-1.0f, -1.0f,  1.0f},
				{255,0,0,1,-1.0f,  1.0f,  1.0f},
				{255,0,0,1, 1.0f,  1.0f,  1.0f},
				{255,0,0,1, 1.0f, -1.0f,  1.0f},

				// right
				{255,255,0, 1, 1.0f, -1.0f,  -1.0f},
				{255,255,0, 1, 1.0f, -1.0f,   1.0f},
				{255,255,0, 1, 1.0f,  1.0f,   1.0f},
				{255,255,0, 1, 1.0f,  1.0f,  -1.0f},

				// bottom
				{ 0,0,255,1, -1.0f,  -1.0f,   1.0f},
				{ 0,0,255,1, -1.0f,  -1.0f,  -1.0f},
				{ 0,0,255,1,  1.0f,  -1.0f,  -1.0f},
				{ 0,0,255,1,  1.0f,  -1.0f,   1.0f},

				

				// left
				{0,255,0,1, -1.0f, -1.0f,  -1.0f},
				{0,255,0,1, -1.0f, -1.0f,   1.0f},
				{0,255,0,1, -1.0f,  1.0f,   1.0f},
				{0,255,0,1, -1.0f,  1.0f,  -1.0f},

				// top
				{0,255,255,1, -1.0f, 1.0f,   1.0f},
				{0,255,255,1, -1.0f, 1.0f,  -1.0f},
				{0,255,255,1,  1.0f,  1.0f,  -1.0f},
				{0,255,255,1,  1.0f,  1.0f,   1.0f},

				// back
				{255,0,255,1, -1.0f, -1.0f,  -1.0f},
				{255,0,255,1, -1.0f,  1.0f,  -1.0f},
				{255,0,255,1,  1.0f,  1.0f,  -1.0f},
				{255,0,255,1,  1.0f, -1.0f,  -1.0f}

			};

			// 颜色
			glColor3f(0, 1, 0);

			glTranslatef(x, y, z);
			// 旋转
			_rotate_angle += 1.0f;
			glRotatef(_rotate_angle, 1, 1, 1);

			glInterleavedArrays(GL_C4UB_V3F, 0, cube);
			glDrawArrays(GL_QUADS, 0, 24);  

}


GLenum  demo_app::check_error()
{
	GLenum code;
	
	const GLubyte *error_string = NULL;

	code = glGetError();
	
	if(GL_NO_ERROR != code)
	{
		error_string = gluErrorString(code);
		fprintf(stderr, "OpenGL error: %d,%s \n", code, error_string);
	}

	return code;
}
