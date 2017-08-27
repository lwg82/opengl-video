


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


static int xpos = 400;
static int ypos = 400;

static int width = 800;
static int height= 600;


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
	// Black background 背景色
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void draw(void) {

    glClear(GL_COLOR_BUFFER_BIT);


    //Draw i
    glFlush();

}

//Main program

int main(int argc, char **argv) {

    glutInit(&argc, argv);

    /*Setting up  The Display
    /    -RGB color model + Alpha Channel = GLUT_RGBA
    */
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE); // 单缓存，

    //Configure Window Postion
    glutInitWindowPosition(xpos, ypos);

    //Configure Window Size
    glutInitWindowSize(width,height);

    //Create Window
    glutCreateWindow("Hello OpenGL");


    //Call to the drawing function
    glutDisplayFunc(draw);

    // Loop require by OpenGL
    glutMainLoop();
    return 0;
}
