#include "demo.h"

using namespace demo;

class chap203 : public demo_app
{
	public:

		struct Vertex
		{
			GLfloat x,y,z;
			GLfloat r,g,b;
		};

		Vertex _circle[360 * 2];
		Vertex _circle1[361];
		Vertex _circle2[360];

	
		virtual void init()
		{
			
		}

		virtual void render()
		{
		
			// 清空颜色缓存
		    	glClear(GL_COLOR_BUFFER_BIT);

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			// 视口
			glViewport(0, 0, width, height);

			// 指定一下操作针对投影矩阵
			glMatrixMode(GL_PROJECTION);

			// 将投影矩阵清空为单位矩阵
			glLoadIdentity();

			// 产生投影矩阵
			glOrtho(0, width, height, 0, -100, 100);

			// 全局颜色
			glColor3f(1, 0, 0);

			// 圆心
			GLfloat cx = 100;
			GLfloat cy = 100;
			GLfloat cz = 0;

			GLfloat r = 80;

			for(int i=0; i<360; ++i)
			{
				_circle[i*2].x = cosf((double)i * M_PI / 180) * r + cx;
				_circle[i*2].y = sinf((double)i * M_PI / 180) * r + cy;
				_circle[i*2].z = cz;
				_circle[i*2].r = 1.0f;
				_circle[i*2].g = 0;
				_circle[i*2].b = 0;

				_circle[i*2+1].x = cosf((double)(i+1) * M_PI / 180) * r + cx;
				_circle[i*2+1].y = sinf((double)(i+1) * M_PI / 180) * r + cy;
				_circle[i*2+1].z = cz;
				_circle[i*2+1].r = 1.0f;
				_circle[i*2+1].g = 0;
				_circle[i*2+1].b = 0;
			}

			
			// 起用顶点模式
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,              // 维度
					GL_FLOAT, 
					sizeof(struct Vertex),              // 偏移量  sizeof(float3)
					_circle);
			// 起用颜色
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3,              // 维度
					GL_FLOAT, 
					sizeof(struct Vertex),              // 偏移量  sizeof(float3)
					&_circle[0].r);   // 第一个顶点的 r 颜色地址

			glDrawArrays(GL_LINES, 0, sizeof(_circle)/sizeof(_circle[0]));     // 线段

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
			cx += 100;
			for(int i=0; i<=360; ++i)
			{
				_circle1[i].x = cosf((double)i * M_PI / 180) * r + cx;
				_circle1[i].y = sinf((double)i * M_PI / 180) * r + cy;
				_circle1[i].z = cz;
				_circle1[i].r = 1.0f;
				_circle1[i].g = 0;
				_circle1[i].b = 0;
			}
			glVertexPointer(3,  GL_FLOAT, sizeof(struct Vertex),  _circle1);
			glColorPointer(3,   GL_FLOAT, sizeof(struct Vertex), &_circle1[0].r);   // 第一个顶点的 r 颜色地址
			glDrawArrays(GL_LINE_STRIP, 0, sizeof(_circle1)/sizeof(_circle1[0]));   // 线带

///////////////////////////////////////////////////////////////////////////////////////////////////
			cx += 100;
			for(int i=0; i<360; ++i)
			{
				_circle2[i].x = cosf((double)i * M_PI / 180) * r + cx;
				_circle2[i].y = sinf((double)i * M_PI / 180) * r + cy;
				_circle2[i].z = cz;
				_circle2[i].r = 1.0f;
				_circle2[i].g = 0;
				_circle2[i].b = 0;
			}
			glVertexPointer(3,  GL_FLOAT, sizeof(struct Vertex),  _circle2);
			glColorPointer(3,   GL_FLOAT, sizeof(struct Vertex), &_circle2[0].r);   // 第一个顶点的 r 颜色地址
			glDrawArrays(GL_LINE_LOOP, 0, sizeof(_circle2)/sizeof(_circle2[0]));   // 首位相连
		
			
	
		}
};


DECLARE_MAIN(chap203);
