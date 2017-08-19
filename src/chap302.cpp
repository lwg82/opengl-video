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

				
			struct Vertex cube[] =
			{
				// left
				{-1.0f, -1.0f,  -1.0f},
				{-1.0f, -1.0f,   1.0f},
				{-1.0f,  1.0f,   1.0f},
				{-1.0f,  1.0f,  -1.0f},

				// top
				{-1.0f, 1.0f,   1.0f},
				{-1.0f, 1.0f,  -1.0f},
				{1.0f,  1.0f,   1.0f},
				{1.0f,  1.0f,  -1.0f},

				// back
				{-1.0f, -1.0f,  -1.0f},
				{-1.0f,  1.0f,  -1.0f},
				{ 1.0f,  1.0f,  -1.0f},
				{ 1.0f, -1.0f,  -1.0f},

				// right
				{1.0f, -1.0f,  -1.0f},
				{1.0f, -1.0f,   1.0f},
				{1.0f,  1.0f,   1.0f},
				{1.0f,  1.0f,  -1.0f},

				// bottom
				{-1.0f, -1.0f,   1.0f},
				{-1.0f, -1.0f,  -1.0f},
				{1.0f,  -1.0f,   1.0f},
				{1.0f,  -1.0f,  -1.0f},

				// front
				{-1.0f, -1.0f,  1.0f},
				{-1.0f,  1.0f,  1.0f},
				{ 1.0f,  1.0f,  1.0f},
				{ 1.0f, -1.0f,  1.0f}

			};

			for(int i=0; i< sizeof(cube)/sizeof(cube[0]); ++i)
			{
				cube[i].z -= 5;
			}


			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,              // 维度
					GL_FLOAT, 
					sizeof(struct Vertex),              // 偏移量  sizeof(float3)
					cube);

			glDrawArrays(GL_QUADS, 0, 24);  
	
		}
};


DECLARE_MAIN(chap203);
