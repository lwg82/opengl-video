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


class camera
{
public:
    float3  _eye;
    float3  _lookat;
    //! 定义了摄像机的y轴
    float3  _up;
    float3  _right;
    float   _speed;
  
    camera(void)
    {
        _eye    =   float3(0,0,10);
        _lookat =   float3(0,0,0);
        _up     =   float3(0,1,0);
        _right  =   float3(1,0,0);
        _speed  =   0.2f;
    }

	void    moveLeft()
    {
        _eye    -=  normalize(_right) * _speed;
        _lookat -=  normalize(_right) * _speed;
    }
    void    moveRight()
    {
        _eye    +=  normalize(_right) * _speed;
        _lookat +=  normalize(_right) * _speed;
    }

    void    moveFront()
    {
        float3  dir =   normalize(_lookat - _eye);
        _eye    +=  dir * _speed;
        _lookat +=  dir * _speed;

    }
    void    moveBack()
    {
        float3  dir =   normalize(_lookat - _eye);
        _eye    -=  dir * _speed;
        _lookat -=  dir * _speed;
    }

    void    update()
    {
        gluLookAt(_eye.x,_eye.y,_eye.z,_lookat.x, _lookat.y,_lookat.z,_up.x,_up.y,_up.z);
	printf("%.2f,%.2f,%.2f %.2f,%.2f,%.2f \n", _eye.x, _eye.y, _eye.z,_lookat.x, _lookat.y,_lookat.z);
    }
};


};
