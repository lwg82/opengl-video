#include "demo.h"

using namespace demo;

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

			gluLookAt (_eye.x, _eye.y, _eye.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
			

			glColor3f(0.7f, 1.0f, 0.3f);
			
			glBegin(GL_TRIANGLES);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f( 1.0f, -1.0f, -1.0f);
				glVertex3f( 0.0f,  1.0f, -1.0f);
			glEnd();
			

			draw_cube();
		}


	
};


DECLARE_MAIN(chap203);
