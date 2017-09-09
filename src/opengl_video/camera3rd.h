#pragma once

//GLEW  
#define GLEW_STATIC  
#include <GL/glew.h>  


// glu
//#include <GL/glu.h>

// GLFW
#include <GLFW/glfw3.h>

#include "CELLMath.hpp"

using namespace CELL;

namespace demo
{

	class camera3rd
	{
		public:
			camera3rd()
			{
				 _eye    =   float3(0,10,10);
				 _lookat =   float3(0,0,0);

				 _radius =   10;
       				 updateLookat(_lookat);

			        _up     =   float3(0,1,0);
				_right  =   float3(1,0,0);
				_speed  =   0.2f;
			}
		
			void perspective(float fovy, float aspect, float zNear, float zFar)
			{
				_matProj = CELL::perspective(fovy, aspect, zNear, zFar);
			}
			
			void update2()
			{
				_matView = lookAt(_eye, _lookat, _up);
			}

			matrix4 getMVP()
			{
				return _matProj * _matView;
			}
			
			 void    updateLookat(float3 pos)
			 {
				float3  dir =   normalize(_lookat - _eye);
				_lookat =   pos;
				_eye    =   _lookat - _radius * dir;

				//sprintf("pos(%f,%f,%f), eye(%f,%f,%f), lookat(%f,%f,%f) \n",pos.x,pos.y,pos.z, _eye.x,_eye.y,_eye.z,_lookat.x, _lookat.y,_lookat.z);
			 }

			 void rotateY(float angle)
			    {
				float3 dir = normalize(_lookat - _eye);

				float3  dir1 = CELL::rotateY(dir, angle);

				//_lookat = _eye + dir1*len;

				_eye = _lookat - dir1 * _radius;

				_right  = normalize(cross(dir1, _up)); // 求叉积
			    }

			 void    update()
			 {
				gluLookAt(_eye.x,_eye.y,_eye.z,_lookat.x, _lookat.y,_lookat.z,_up.x,_up.y,_up.z);
			 }

			float get_radius() const {return _radius;}

			void set_radius(float r){_radius = r;}

			void    setView(int x,int y)
			{
				_viewSize.x =   x;
				_viewSize.y =   y;
			}


  /**
    *   窗口坐标转化为世界坐标
    */
    bool    unProject( const float4& screen, float4& world )
    {
        float4 v;
        v.x =   screen.x;
        v.y =   screen.y;
        v.z =   screen.z;
        v.w =   1.0;

        // map from viewport to 0 - 1
        v.x =   (v.x) /_viewSize.x;
        v.y =   (_viewSize.y - v.y) /_viewSize.y;
        //v.y = (v.y - _viewPort.Y) / _viewPort.Height;

        // map to range -1 to 1
        v.x =   v.x * 2.0f - 1.0f;
        v.y =   v.y * 2.0f - 1.0f;
        v.z =   v.z * 2.0f - 1.0f;

        CELL::matrix4  inverse = (_matProj * _matView ).inverse();

        v   =   v * inverse;
        if (v.w == 0.0f)
        {
            return false;
        }
        world   =   v / v.w;
        return true;
    }

   // 根据鼠标坐标创建射线
    Ray createRayFromScreen(int x,int y)
    {
        float4  minWorld;
        float4  maxWorld;

        float4  screen(float(x),float(y),0,1);   // 视锥体近点
        float4  screen1(float(x),float(y),1,1);  // 视锥体远点

        unProject(screen,minWorld);
        unProject(screen1,maxWorld);
        Ray     ray;
        ray.setOrigin(float3(minWorld.x,minWorld.y,minWorld.z));

        float3  dir(maxWorld.x - minWorld.x,maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
        ray.setDirection(normalize(dir));
        return  ray;
    }

		private:
			float3     _eye;
			float3     _lookat;

			    float3  _up;
			    float3  _right;
			    float   _speed;
			    float   _radius;

			matrix4 _matView;
			matrix4 _matProj;  // 投影矩阵
		        float2  _viewSize; // 记录窗口宽高
	};


}// namespace
