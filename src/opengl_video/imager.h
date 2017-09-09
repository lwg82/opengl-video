#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "FreeImage/FreeImage.h"



unsigned    CreateTexture(int w,int h,const void* data)
{
	glEnable(GL_TEXTURE_2D);

	unsigned    texId;
	glGenTextures(1,&texId);
	glBindTexture(GL_TEXTURE_2D,texId);

	// 纹理过滤
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	#if   0
		// 纹理包装
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	#endif

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

	return  texId;
}


bool CreateTextureFromImage(const char *fileName, GLuint &textureId)
{
	//1 获取图片格式
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(fileName, 0);

	if(FIF_UNKNOWN == fif)
		return false;

	//2 加载图片
	FIBITMAP *dib = FreeImage_Load(fif, fileName, 0);

	FREE_IMAGE_COLOR_TYPE type    =   FreeImage_GetColorType(dib);

 	//! 获取数据指针
        FIBITMAP*   temp    =   dib;
        dib =   FreeImage_ConvertTo32Bits(dib);
                FreeImage_Unload(temp);

        BYTE*   pixels =   (BYTE*)FreeImage_GetBits(dib);
        int     width   =   FreeImage_GetWidth(dib);
        int     height  =   FreeImage_GetHeight(dib);

        for (int i = 0 ;i < width * height * 4 ; i+=4 )
        {
            BYTE temp       =   pixels[i];
            pixels[i]       =   pixels[i + 2];
            pixels[i + 2]   =   temp;
        }

        textureId =   CreateTexture(width,height,pixels);

        FreeImage_Unload(dib);
       
	return true;
}
