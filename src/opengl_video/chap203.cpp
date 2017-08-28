#include "demo.h"

using namespace demo;

class chap203 : public demo_app
{
	public:

		virtual void init()
		{
			
		}

		virtual void render()
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

			// 画圆
			GLfloat cx = 100.0f;
			GLfloat cy = 100.0f;
			GLfloat r  = 80.0f;

			// 划线

	
			glBegin(GL_TRIANGLES);

			for(int i=0; i<360; ++i)
			{
				
				GLfloat x1 = cosf((double)i * M_PI/180) * r + cx;
				GLfloat y1 = sinf((double)i * M_PI/180) * r + cy;

				GLfloat x2 = cosf((double)(i+1) * M_PI/180) * r + cx;
				GLfloat y2 = sinf((double)(i+1) * M_PI/180) * r + cy;	

				glVertex3f(cx, cy, 0);
				glVertex3f(x1, y1, 0);
				glVertex3f(x2, y2, 0);
				
				
			}

			glEnd();
	
		}
};


DECLARE_MAIN(chap203);
