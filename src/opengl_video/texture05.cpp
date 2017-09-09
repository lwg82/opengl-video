#include "demo.h"

/*
	多立方体，多纹理

*/

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

			// texture
			glEnable(GL_TEXTURE_2D);
			
			CreateTextureFromImage("1.jpg", _texture_id);
			CreateTextureFromImage("2.jpg", _texture_id2);
			
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
			
			

			
			
			
			

			//glColor3f(0.7f, 1.0f, 0.3f);
			
			
			static struct vertex_texture cube_tex[] =
			{
				{0,  0,  -1.0f, -1.0f, 1.0f},
				{0,  1,  -1.0f, 1.0f, 1.0f},
				{1,  1,   1.0f, 1.0f, 1.0f},
				{1,  0,   1.0f,-1.0f, 1.0f},

				// right
				{0,  0, 1.0f, -1.0f,  -1.0f},
				{0,  1, 1.0f, -1.0f,   1.0f},
				{1,  1, 1.0f,  1.0f,   1.0f},
				{1,  0, 1.0f,  1.0f,  -1.0f},

				
				{0,  0, -1.0f,  -1.0f,   1.0f},
				{0,  1, -1.0f,  -1.0f,  -1.0f},
				{1,  1,  1.0f,  -1.0f,  -1.0f},
				{1,  0,  1.0f,  -1.0f,   1.0f},

				
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
			
			//glColor3f(0, 1, 0);

			

			glLoadIdentity();
			_camera.update();
			glBindTexture(GL_TEXTURE_2D, _texture_id2);
#if 0
			glTranslatef(0,0,-10.0f); // 平移
		        glInterleavedArrays( GL_T2F_V3F, sizeof(vertex_texture), cube_tex );
#else
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);


			glVertexPointer(3, GL_FLOAT,   sizeof(vertex_texture), &cube_tex[0].x);
			glTexCoordPointer(2,GL_FLOAT,       sizeof(vertex_texture),     &cube_tex[0].u);

			
// 旋转
			_rotate_angle += 1.0f;
			glRotatef(_rotate_angle, 0, 1, 0);
			
	
#endif
			glDrawArrays(GL_QUADS, 0, 24);


			// 第二个立方体
			glLoadIdentity();
			_camera.update();
			glTranslatef(-5.0f,0,-10.0f); // 平移
			glBindTexture(GL_TEXTURE_2D, _texture_id);
			glDrawArrays(GL_QUADS, 0, 24);

			

		}

			
		GLuint    _texture_id;
		GLuint    _texture_id2;
};


DECLARE_MAIN(chap203);
