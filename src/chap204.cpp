#include "demo.h"

using namespace demo;

class chap203 : public demo_app
{
	public:

		struct float3
		{
			GLfloat x,y,z;
		};

		float3 _circle[360 * 3]; // 一个三角形有3个顶点

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
			GLfloat cz = 0;
			GLfloat r  = 80.0f;

		
			for(int i=0; i<360; ++i)
			{
				_circle[i * 3 + 0].x = cx;
				_circle[i * 3 + 0].y = cy;
				_circle[i * 3 + 0].z = cz;


				_circle[i * 3 + 1].x = cosf((double)i * M_PI/180) * r + cx;
				_circle[i * 3 + 1].y = sinf((double)i * M_PI/180) * r + cy;
				_circle[i * 3 + 1].z = cz;

				_circle[i * 3 + 2].x = cosf((double)(i+1) * M_PI/180) * r + cx;
				_circle[i * 3 + 2].y = sinf((double)(i+1) * M_PI/180) * r + cy;	
				_circle[i * 3 + 2].z = cz;
				
			}
			
			// 起用顶点模式
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,              // 维度
					GL_FLOAT, 
					0,              // 偏移量  sizeof(float3)
					_circle);

			glDrawArrays(GL_TRIANGLES, 0, 360 *3);
	
		}
};


DECLARE_MAIN(chap203);
