#include "demo.h"

using namespace demo;

/*
	第一人称摄像机
*/

class chap203 : public demo_app
{
	public:
		virtual void init()
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			// 启用深度测试
			glEnable(GL_DEPTH_TEST);

			//glShadeModel(GL_FLAT);
			glShadeModel(GL_SMOOTH);
		}

		virtual void render()
		{
			// 清空颜色缓存
		       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// 视口
			glViewport(0, 0, width, height);
			// 指定一下操作针对投影矩阵
			glMatrixMode(GL_PROJECTION);

			// 将投影矩阵清空为单位矩阵
			glLoadIdentity();

			// 透视投影
			gluPerspective(
				60,    // 角度
				GLdouble(width)/GLdouble(height),
				0.1,
				100);

			// 起用模型
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			_camera.update();
			

			glColor3f(0.7f, 1.0f, 0.3f);
			
			glBegin(GL_TRIANGLES);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f( 1.0f, -1.0f, -1.0f);
				glVertex3f( 0.0f,  1.0f, -1.0f);
			glEnd();
			

			draw_cube();
		}

		
virtual void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//printf("key: %d \n", key);
	printf("%s,%d, key:%d, scancode:%d, action:%d, mods:%d \n", __FUNCTION__, __LINE__, key, scancode, action, mods);
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


virtual void OnCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	printf("x=%f,y=%f \n",xpos, ypos);
	
	if(left_button_pressed)
	{
		int2 mouse_cursor = int2(xpos, ypos);
		float offsetx = _mouse_pos.x - mouse_cursor.x;
		_mouse_pos = mouse_cursor;

		_camera.rotateY(offsetx * 0.5f);
	}

}

private:
		demo::camera  _camera;
};


DECLARE_MAIN(chap203);
