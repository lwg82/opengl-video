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

			// 矩形 上色
			struct Vertex _rect[4] = {
				{10, 10,   0, 1, 0, 0},
				{110, 10,  0, 0, 1, 0},
				{10, 110,  0, 0, 0, 1},
				{110, 110, 0, 1, 1, 0}
			};

	

			
			// 起用顶点模式
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,              // 维度
					GL_FLOAT, 
					sizeof(struct Vertex),              // 偏移量  sizeof(float3)
					_rect);
			// 起用颜色
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3,              // 维度
					GL_FLOAT, 
					sizeof(struct Vertex),              // 偏移量  sizeof(float3)
					&_rect[0].r);   // 第一个顶点的 r 颜色地址

			//glDrawArrays(GL_LINES, 0, 4);     // 线段
			glDrawArrays(GL_LINE_STRIP, 0, 4);  // 线带
			glDrawArrays(GL_LINE_LOOP, 0, 4);   // 首位相连
			
	
		}
};


DECLARE_MAIN(chap203);
