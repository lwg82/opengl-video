


//GLEW  
//#define GLEW_STATIC  
//#include <GL/glew.h> 

#include <GL/freeglut.h>



#if _WIN32
	#define _USE_MATH_DEFINES
#endif

#include <cstdio>
#include <cstdlib>
#include <cmath>


#define UNUSED_PARAMETER(param) (void)param
#define OUT_PUT_FUNTION_POSITON  printf("%s %d \n", __FUNCTION__, __LINE__);


static int xpos = 400;
static int ypos = 400;

static int width = 800;
static int height= 600;

static GLfloat _angle = 0.0f;


static GLfloat _diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
static GLfloat _specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
static GLfloat _lightPosition[]   = {0.0f, 0.0f, 10.0f, 1.0f};


static GLfloat _diffuseLightR[] = {1.0f, 0.0f, 0.0f, 1.0f};
static GLfloat _specularLightR[] = {1.0f, 0.0f, 0.0f, 1.0f};
static GLfloat _lightPositionR[]   = {0.0f, 0.0f, 5.0f, 1.0f};

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



void init()
{
	glClearColor(1.0,0.0,0.0,0.0);      //指定屏幕背景为黑色

	

	//glShadeModel(GL_FLAT);              //设置颜色插值为平面模式

	// 启用深度测试
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, _lightPosition);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, _diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, _specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, _lightPositionR);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void reshape (int w, int h)
{
	printf("resize width=%d, height=%d \n", w, h);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 透视投影
	gluPerspective(
		45,    // 角度
		double(width)/double(height),
		0.1,
		10000);

	// 起用模型
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}



void draw(void) 
{
	printf("%s \n", __FUNCTION__);

	//glClearColor(1.0,0.0,0.0,0.0);      //指定屏幕背景为黑色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           //清理屏幕颜色为我们指定的颜色
	
	glPushMatrix();
		glLoadIdentity();
		
		// 平移
		glTranslatef(4,0,-18.0f);

		// 旋转
		glRotatef(_angle, 1, 1, 1);

		glLightfv(GL_LIGHT1, GL_POSITION, _lightPositionR);

		//glTranslatef(_lightPositionR[0], _lightPositionR[1], _lightPositionR[2]);

		glColor3f(0.0, 1.0f, 0.0);

		glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);
				//glutWireCube(1.0);
				//glutSolidCube(1.0);
				glutSolidSphere(1.0, 50, 50);
			glEnable(GL_LIGHTING);
		glPopAttrib();
	glPopMatrix();

	glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0, 0.0f, 1.0f);
		glTranslatef(-4,0,-10.0f);
		glRotatef(_angle, 1, 1, 1);

		glutWireSphere(1.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0, 1.0f, 1.0f);

		glTranslatef(-4.0f, 3.0f, -10.0f);
		glRotatef(_angle, 1, 1, 1);

		glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	//
	
  	
	//glutWireSphere(1.0, 50, 50);
	//glutSolidSphere(1.0, 50, 50);


	glFlush();                       //强制以上绘图操作执行


}

void SpinIdle()
{
   _angle += 0.01f;
   
	if(_angle >= 360.0f)
		_angle = 0.0f;

   glutPostRedisplay();
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
    glutDisplayFunc(draw);

    glutReshapeFunc ( reshape );   // 注册窗口大小改变时的响应函数

    glutIdleFunc(SpinIdle);
    // Loop require by OpenGL
    glutMainLoop();
    return 0;
}
