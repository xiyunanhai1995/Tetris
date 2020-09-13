#ifndef __BIN_H
#define __BIN_H
#include<iostream>

using namespace std;

//定义界面类
class CBin
{
private:
	unsigned int width;	//界面宽度
	unsigned int height;	//界面高度
	unsigned char **image;	//界面映像
public:
	CBin(unsigned int width,unsigned int height);
	~CBin(void);
	unsigned int GetWidth(void) { return width; }	//设置界面宽度
	unsigned int GetHeight(void) { return height; }	//设置界面高度
	void GetImage(unsigned char **destImage);		//得到映像数据

	void SetImage(unsigned char **srcImage);	//设置映像数据
	unsigned int RemoveFullLines(void);				//输出整行
};


#endif



