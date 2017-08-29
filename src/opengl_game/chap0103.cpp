


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

static GLfloat red_light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat red_light_pos[] = { 5.0, 0.0, 0.0, 1.0 };
static GLfloat red_light_dir[] = { -1.0, 0.0, 0.0 };

static GLUquadric *sphere;

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
		90,    // 角度
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

	
	
	// 启用深度测试
	glEnable(GL_DEPTH_TEST);

	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING); // 开启灯光

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, red_light_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, red_light_color);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0f);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, red_light_dir);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
	//glDisable(GL_LIGHT0);


	sphere = gluNewQuadric();
}




void render(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           //清理屏幕颜色为我们指定的颜色
	
	glLoadIdentity();
	
	gluLookAt(0.0, 0.0, 10.0,
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0);
		
	// position the red light
	glLightfv(GL_LIGHT0, GL_POSITION, red_light_pos);

	// draw the red light
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(red_light_pos[0], red_light_pos[1], red_light_pos[2]);
		glColor3fv(red_light_color);
		gluSphere(sphere, 0.2f, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		//glTranslatef(0.0, 0.0, -5.0f);
		glRotatef(_angle, 1.0f, 0.0f, 0.0f);
		glRotatef(_angle, 0.0f, 1.0f, 0.0f);
		glRotatef(_angle, 0.0f, 0.0f, 1.0f);
		glutSolidCube(1.0f);
	glPopMatrix();
	//glFlush();                       //强制以上绘图操作执行

	glutSwapBuffers();
}

void SpinIdle()
{
	/*
   _angle += 0.1f;
   
	if(_angle >= 360.0f)
		_angle = 0.0f;

   glutPostRedisplay();
   */
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
