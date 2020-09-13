#include"bin.h"

/*---------------------
* 函数名：构造函数
* 功  能：初始化窗口大小，并分配空间和初始化
* 返回值：无
----------------------*/
CBin::CBin(unsigned int width,unsigned int height)
{
	this->width = width;	//初始化窗口宽度
	this->height = height;	//初始化窗口高度

	image = new unsigned char * [height];	//分配高度内存
	for(unsigned int i=0;i < height;i++)	
	{
		image[i] = new unsigned char [width];	//依次分配宽度内存
		for(unsigned int j=0;j < width;j++)		//赋初始值0
			image[i][j] = 0;
	}
}
/*---------------------
* 函数名：析构函数
* 功  能：删除在构造函数中为image分配的空间
* 返回值：无
---------------------*/
CBin::~CBin(void)
{
	for(unsigned int i=0;i < this->height;i++)
		delete image[i];
	delete image;
}

/*---------------------
* 函数名：void CBin::GetImage(unsigned char **destImage)
* 功  能：将窗口数据复制给destImage
* 返回值：无
---------------------*/
void CBin::GetImage(unsigned char **destImage)
{
	for(unsigned int i=0;i < this->height;i++)
		for(unsigned int j=0;j < this->width;j++)
			destImage[i][j] = image[i][j];
}

/*---------------------
* 函数名：void CBin::SetImage(unsigned char **srcImage)
* 功  能：设置窗口数据（将srcImage复制给窗口）
* 返回值：无
---------------------*/
void CBin::SetImage(unsigned char **srcImage)
{
	for(unsigned int i=0;i < this->height;i++)
		for(unsigned int j=0;j < this->width;j++)
			image[i][j] = srcImage[i][j];
}
/*---------------------
* 函数名：unsigned int CBin::RemoveFullLines(void)
* 功  能：删除填满行
* 返回值：删除的行数
---------------------*/
unsigned int CBin::RemoveFullLines(void)
{
	unsigned int EmptyLine=0;
	bool flag;
	
	for(int i=0;i < height;i++)
	{
		flag = 1;	//初始化标志位为‘整行填满’

		for(int j=0;j < width;j++)
			if(image[i][j] == 0)	//如果存在‘空’
			{
				flag = 0;	//则制位为‘整行没填满’waaaa
				break;
			} 
				
		if(flag)	//如果整行为‘填满’
		{
			for(int m=i;m > 0;m--)	//将第i-1行以上整体向下平移一行
				for(int j=0;j < width;j++)
					image[m][j] = image[m-1][j];	
			for(int j=0;j < width;j++)	//设置第0行为‘空’
				image[0][j] = 0;

			EmptyLine++;	//记录删除的行数
		}
	}
	return EmptyLine;
}
/*
unsigned int CBin::RemoveFullLines(void)
{
	unsigned int flag,EmptyLine=0;
    unsigned int i,j,m;
	for (i=0; i<height; i++) 
	{
		flag=0;
		for (j=0; j<width; j++) 
		{
			if (image[i][j]==0 )
			{
				flag=1;
				break; 
			} 
				
		}
        //一行完全被填满
		if(flag==0)  
		{
			//删除整行
			for(m=i; m>0; m--)
           		for (j=0; j<width; j++) 
				   image[m][j]=image[m-1][j];
	        for (j=0; j<width; j++) 
				   image[0][j]=0;
		    EmptyLine++;  //记录删除的行数
		}
	}
     return EmptyLine;   
}
*/




