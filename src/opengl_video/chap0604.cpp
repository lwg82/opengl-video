#include "demo.h"



using namespace demo;

/*
	第三人称摄像机,  实现鼠标左键点击移动物体
*/

class chap203 : public demo_app
{
	public:

		virtual void OnWindowSize(GLFWwindow *window, int w, int h)
		{
			printf("width:%d, height:%d \n", w, h);

			if(!window)
				return;

			width = w;
			height = h;
			// 视口
			glViewport(0, 0, width, height);

			_camera.setView(w,h);

			_camera.perspective(
			60,    // 角度
			GLdouble(width)/GLdouble(height),
			0.1,
			1000.0f);

			
		}

		virtual void init()
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			_rolePos = float3(0,0,0);
			size_ground = 100.0;

			_rolePos = _moveto;

			// 启用深度测试
			glEnable(GL_DEPTH_TEST);
        		glEnable(GL_TEXTURE_2D);

			//glShadeModel(GL_FLAT);
			glShadeModel(GL_SMOOTH);

			if(!CreateTextureFromImage("bkg.jpg", texture_ground))
				std::terminate();

			if(!CreateTextureFromImage("2.jpg", texture_cube))
					std::terminate();

			_camera.perspective(
			60,    // 角度
			GLdouble(width)/GLdouble(height),
			0.1,
			1000.0f);

			_camera.setView(width,height);

		}

		virtual void render()
		{
			// 清空颜色缓存
		       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			
			// 指定一下操作针对投影矩阵
			//glMatrixMode(GL_PROJECTION);

			// 将投影矩阵清空为单位矩阵
			// glLoadIdentity();

/*
			// 透视投影
			gluPerspective(
				60,    // 角度
				GLdouble(width)/GLdouble(height),
				0.1,
				100);
*/

		
			// 起用模型
			glMatrixMode(GL_MODELVIEW);
			//glLoadIdentity();
			
			
		

			_camera.updateLookat(_rolePos);
			_camera.update2();

			matrix4 matVP = _camera.getMVP();
			glLoadMatrixf(matVP.data());
			
			/*
			glColor3f(0.7f, 1.0f, 0.3f);
			
			glBegin(GL_TRIANGLES);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f( 1.0f, -1.0f, -1.0f);
				glVertex3f( 0.0f,  1.0f, -1.0f);
			glEnd();
			
			*/
			//draw_cube(_rolePos.x, _rolePos.y, _rolePos.z);


			struct vertex_texture ground[4] = {
					{ 0,           0,           -size_ground,  -1.0f,  size_ground},
					{ size_ground, 0,            size_ground,  -1.0f,  size_ground},
					{ size_ground, size_ground,  size_ground,  -1.0f,  -size_ground},
					{ 0,           size_ground, -size_ground,  -1.0f,  -size_ground}
			};


			glBindTexture(GL_TEXTURE_2D,texture_ground);
			//glTranslatef(0,0,-10.0f); // 平移
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(3, GL_FLOAT,        sizeof(vertex_texture),     &ground[0].x);
			glTexCoordPointer(2,GL_FLOAT,       sizeof(vertex_texture),     &ground[0].u);
			glDrawArrays(GL_QUADS, 0, 4);

			//

			// cube
	struct vertex_texture cube_tex[] =
	{
// bottom
		{0,  0, -1.0f,  -1.0f,   1.0f},
		{0,  1, -1.0f,  -1.0f,  -1.0f},
		{1,  1,  1.0f,  -1.0f,  -1.0f},
		{1,  0,  1.0f,  -1.0f,   1.0f},

		{0,  0,  -1.0f, -1.0f, 1.0f},
		{0,  1,  -1.0f, 1.0f, 1.0f},
		{1,  1,   1.0f, 1.0f, 1.0f},
		{1,  0,   1.0f,-1.0f, 1.0f},

		// right
		{0,  0, 1.0f, -1.0f,  -1.0f},
		{0,  1, 1.0f, -1.0f,   1.0f},
		{1,  1, 1.0f,  1.0f,   1.0f},
		{1,  0, 1.0f,  1.0f,  -1.0f},

		

		
		// left
		{0,  0, -1.0f, -1.0f,  -1.0f},
		{0,  1, -1.0f,  1.0f,  -1.0f},
		{1,  1, -1.0f,  1.0f,   1.0f},
		{1,  0, -1.0f, -1.0f,   1.0f},

		
		{0,  0, -1.0f, 1.0f,   1.0f},
		{0,  1, -1.0f, 1.0f,  -1.0f},
		{1,  1,  1.0f,  1.0f,  -1.0f},
		{1,  0,  1.0f,  1.0f,   1.0f},

		
		{0,  0, -1.0f, -1.0f,  -1.0f},
		{0,  1, -1.0f,  1.0f,  -1.0f},
		{1,  1,  1.0f,  1.0f,  -1.0f},
		{1,  0,  1.0f, -1.0f,  -1.0f}
	};

	glLoadMatrixf(matVP.data());
	glBindTexture(GL_TEXTURE_2D,texture_cube);
 	glVertexPointer(3,GL_FLOAT,         sizeof(vertex_texture),     &cube_tex[0].x);
	glTexCoordPointer(2,GL_FLOAT,       sizeof(vertex_texture),     &cube_tex[0].u);

	float3 dir = normalize(_moveto - _rolePos);
	if(length(_moveto - _rolePos) < 1)
	{
		_rolePos = _moveto;
	}
	else
	{
		_rolePos += dir * (10.0f/60.0f);
	}


	glTranslatef(_rolePos.x, _rolePos.y, _rolePos.z); 
	glDrawArrays(GL_QUADS, 0, 24);

}

		
virtual void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//printf("key: %d \n", key);
	//printf("%s,%d, key:%d, scancode:%d, action:%d, mods:%d \n", __FUNCTION__, __LINE__, key, scancode, action, mods);
	switch(key)
	{
		case GLFW_KEY_UP:
			_rolePos.z  -=  1;
		break;

		case GLFW_KEY_DOWN:
			 _rolePos.z  +=  1;
		break;

		case GLFW_KEY_LEFT:
			_rolePos.x  -=  1;
		break;

		case GLFW_KEY_RIGHT:
			_rolePos.x  +=  1;
		break;
	}
}


virtual void OnCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	//printf("x=%f,y=%f \n",xpos, ypos);
	

}

virtual void OnScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	printf("scroll:(%f,%f) \n", xoffset, yoffset);

	if(yoffset > 0)
	{
		_camera.set_radius(_camera.get_radius() * 1.2);
	}
	else
	{
		_camera.set_radius(_camera.get_radius() * 0.8);
	}
}

void OnMouse(GLFWwindow* window, int key, int action, int mods)
{
	printf("%s,%d, key:%d, action:%d, mods:%d \n", __FUNCTION__, __LINE__, key, action, mods);

	double xpos = 0;
	double ypos = 0;
	
	switch(key)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		    if(GLFW_PRESS == action)
			{
				glfwGetCursorPos(window, &xpos, &ypos);
				// 根据鼠标坐标创建射线
				CELL::Ray ray = _camera.createRayFromScreen(xpos, ypos);
				float3    orth = ray.getOrigin();   // 获取射线起点

				// 射线Y轴长度加上离地面的距离1，除以方向的Y长度，得到射线到达地面的时间
				float    tm = fabs((orth.y + 1)/ray.getDirection().y);
				// 得到交点，时间乘以方向
				float3   c  = ray.getOrigin() + tm * ray.getDirection();

				_moveto = c;

			}
		break;

	}


}

private:
		demo::camera3rd  _camera;
		float3  _rolePos;

		GLuint    texture_ground;
		GLfloat   size_ground;

		GLuint    texture_cube;

		float3   _moveto;    // 需要移动的坐标
};


DECLARE_MAIN(chap203);
