


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


static int xpos = 200;
static int ypos = 200;

static int width = 400;
static int height= 300;

static GLfloat _anglex = 0.0f;
static GLfloat _angley = 0.0f;
static GLfloat _anglez = 0.0f;

static GLfloat _angle = 0.0f;


void get_information(GLenum e)
{
	const GLubyte *strVendor = glGetString(e);
	printf("%s \n", strVendor);
}

GLenum check_error()
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


void reshape(int w, int h)
{
	printf("resize width=%d, height=%d \n", w, h);

	if (0 == h)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 透视投影
	gluPerspective(
		60,    // 角度
		GLdouble(width) / GLdouble(height),
		0.1,
		100);

	// 起用模型
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	width = w;
	height = h;
}


void init()
{
	get_information(GL_VENDOR);
	get_information(GL_RENDERER);
	//get_information(GL_VERSION);
	//get_information(GL_EXTENSIONS);

	glClearColor(0.0,0.0,0.0,0.0);      //指定屏幕背景为黑色

	// 获取定点大小
	GLfloat point_size = 0.0f;
	glGetFloatv(GL_POINT_SIZE, &point_size);
	printf("point size:%f \n", point_size);

	// 开启顶点抗锯齿
	if (!glIsEnabled(GL_POINT_SMOOTH))
		glEnable(GL_POINT_SMOOTH);

	// 获取顶点尺寸范围
	GLfloat sizes[2];
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);

	// 顶点的颗粒度
	GLfloat granularity;
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &granularity);


	// 启用深度测试
	glEnable(GL_DEPTH_TEST);
}




void render(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           //清理屏幕颜色为我们指定的颜色
	
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -5.0f);
	glRotatef(_angle, 1.0f, 0.0f, 0.0f);
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glRotatef(_angle, 0.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(40.0f);

	glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	
	//glFlush();                       //强制以上绘图操作执行

	glutSwapBuffers();
}

void SpinIdle()
{
   _angle += 0.1f;
   
	if(_angle >= 360.0f)
		_angle = 0.0f;

   //glutPostRedisplay();
}

void render_timer_fun(int id)
{
	if (1 == id)
	{
		_angle += 0.1f;

		//if (_angle >= 360.0f)
		//	_angle = 0.0f;

		glutPostRedisplay();

		glutTimerFunc(1, render_timer_fun, 1);
	}
}

//Main program

int main(int argc, char **argv) {

    glutInit(&argc, argv);

    /*Setting up  The Display
    /    -RGB color model + Alpha Channel = GLUT_RGBA
    */
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH); // 单缓存，

    //Configure Window Postion
    glutInitWindowPosition(xpos, ypos);

    //Configure Window Size
    glutInitWindowSize(width,height);

    //Create Window
    glutCreateWindow("Hello OpenGL");

    init();

    //Call to the drawing function
    glutDisplayFunc(render);

    glutReshapeFunc(reshape);   // 注册窗口大小改变时的响应函数

	glutTimerFunc(100, render_timer_fun, 1); // glutTimerFunc(毫秒数, 回调函数指针, 区别值);
   // glutIdleFunc(SpinIdle);
    // Loop require by OpenGL
    glutMainLoop();

    return 0;
}
