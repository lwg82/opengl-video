#include "demo.h"

using namespace demo;

class chap203 : public demo_app
{
	public:

		struct Vertex
		{
			GLfloat x,y,z;
		};

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
			//glOrtho(0, width, height, 0, -100, 100);

			// 透视投影
			gluPerspective(
				60,    // 角度
				double(width)/double(height),
				0.1,
				10000);

			// 颜色
			glColor3f(1, 1, 1);

				
			struct Vertex triangles[] =
			{
				{0.5f, 0,     -10.0f},
				{0.2f, 0.3,   -10.0f},
				{0.8f, 0.3,   -10.0f}
			};


			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,              // 维度
					GL_FLOAT, 
					sizeof(struct Vertex),              // 偏移量  sizeof(float3)
					triangles);

			glDrawArrays(GL_TRIANGLES, 0, 3);  
	
		}
};


DECLARE_MAIN(chap203);
