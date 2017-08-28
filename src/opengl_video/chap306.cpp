#include "demo.h"

using namespace demo;

class chap203 : public demo_app
{
	public:
		GLfloat _angle;
		struct Vertex
		{
			unsigned char r,g,b,a;
			float x,y,z;
		};

		virtual void init()
		{
			_angle=0;
		}

		virtual void render()
		{
		
			// 清空颜色缓存
		    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			// 视口
			glViewport(0, 0, width, height);

			// 指定一下操作针对投影矩阵
			glMatrixMode(GL_PROJECTION);

			// 将投影矩阵清空为单位矩阵
			glLoadIdentity();

			// 产生投影矩阵
			//glOrtho(0, width, height, 0, -100, 100);

			// 透视投影
			gluPerspective(
				60,    // 角度
				double(width)/double(height),
				0.1,
				10000);

			// 颜色
			//glColor3f(1, 1, 1);

				
			struct Vertex cube[] =
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

			// 平移
			glTranslatef(0,3,-10.0f);

			
			_angle += 1.0f;
			glRotatef(_angle, 0, 0, 1);

			glTranslatef(4,0,0);

			// 启用深度测试
			glEnable(GL_DEPTH_TEST);

		
			glInterleavedArrays(GL_C4UB_V3F, 0, cube);


			glDrawArrays(GL_QUADS, 0, 24);  

		}
};


DECLARE_MAIN(chap203);
