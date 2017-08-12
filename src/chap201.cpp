
#include <GLFW/glfw3.h>

static int width = 800;
static int height = 600;

void render()
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

	// 划线
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 100, 0);
	glEnd();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, 200, 200);	

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
       render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
