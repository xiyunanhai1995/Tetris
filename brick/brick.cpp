#include"brick.h"

//左移
bool CBrick::ShiftLeft(CBin *bin)
{
	int posX;

	posX = GetPosX();
	SetPosX(posX-1);
	if(CheckCollision(bin) == 0)
	{
		SetPosX(posX);
		return 0;
	}

	return 1;
}
//右移
bool CBrick::ShiftRight(CBin *bin)
{
	int posX;

	posX = GetPosX();
	SetPosX(posX+1);
	if(CheckCollision(bin) == 0)
	{
		SetPosX(posX);
		return 0;
	}

	return 1;
}
//下落
bool CBrick::ShiftDown(CBin *bin)
{	
	int posY;

	posY = GetPosY();

	SetPosY(posY+1);
	if(CheckCollision(bin) == 0)
	{
		SetPosY(posY);
		return 0;
	}

	return 1;
}
//下落到底部
bool CBrick::ShiftLow(CBin *bin)
{	
	int posY;

	posY = GetPosY();

	while(CheckCollision(bin) != 0)
	{
		posY++;
		SetPosY(posY);
	}
	SetPosY(posY-1);

	return 1;
}
//旋转
bool CBrick::RotateClockwise(CBin *bin)
{
	unsigned int oldOrientation,Orientation;
	
	oldOrientation = Orientation = GetOrientation();

	switch(Orientation)
	{
		case angle0:
			Orientation = angle90;
			break;
		case angle90:
			Orientation = angle180;
			break;
		case angle180:
			Orientation = angle270;
			break;
		case angle270:
			Orientation = angle0;
			break;
		default: break;
	}
	SetOrientation(Orientation);
	if(CheckCollision(bin) == 0)	//如果冲突 
	{
		SetOrientation(oldOrientation);
		return 0;
	}	

	return 1;
}
//=========================================================	派生类CIBrick
//冲突检查
bool CIBrick::CheckCollision(CBin *bin)
{
	int width,height,posX,posY;
	unsigned int orientation;
	unsigned char **image=NULL;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	switch(orientation)	//按照砖块对应状态进行界面冲突检查
	{
		case angle0:	// 状态 1 
			//砖块碰到边界【位置检查】 
			if((posX-2 < 0)||
			   (posX+1 > width-1)||
			   (posY < 0)||
			   (posY > height-1))	
				return 0;
			//砖块碰到其他固定砖块
			if((image[posY][posX-2] != 0)||
			   (image[posY][posX-1] != 0)||
			   (image[posY][posX] !=0)||
			   (image[posY][posX+1] != 0))
				return 0;
			break;
		case angle90:	// 状态 2 
			if((posX < 0)||
			   (posX > width-1)||
			   (posY-2 < 0)||
			   (posY+1 > height-1))	
				return 0;
			if((image[posY-2][posX] != 0)||
			   (image[posY-1][posX] != 0)||
			   (image[posY][posX] !=0)||
			   (image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle180:	// 状态 3
			if((posX-1 < 0)||
			   (posX+2 > width-1)||
			   (posY < 0)||
			   (posY > height-1))	//位置检查
				return 0;
			if((image[posY][posX-1] != 0)||
			   (image[posY][posX] != 0)||
			   (image[posY][posX+1] !=0)||
			   (image[posY][posX+2] != 0))	//形状检查
				return 0;
			break;
		case angle270:	// 状态 4 
			//砖块碰到边界
			if((posX < 0)||			
			   (posX > width-1)||
			   (posY-1 < 0)||
			   (posY+2 > height-1))	
				return 0;
			//砖块碰到其他固定砖块	
			if((image[posY-1][posX] != 0)||
			   (image[posY][posX] != 0)||
			   (image[posY+1][posX] !=0)||
			   (image[posY+2][posX] != 0))	//形状检查
				return 0;
			break;
		default: break;
	}
	return 1;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-2] = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			break;
		case angle90:
			binImage[posY-2][posX] = color;
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY][posX+2] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			binImage[posY+2][posX] = color;
			break;
		default: break;
	}
}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:   SetPosY(0); break;	
		case angle90:  SetPosY(2); break;	
		case angle180: SetPosY(0); break;
		case angle270: SetPosY(1); break; 
		default :break;
	}
}

//=========================================================	派生类CIIBrick
//冲突检查
bool CIIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	if((posX < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//位置检查
			return false;
	if((image[posY][posX] != 0)||(image[posY][posX+1] != 0)||(image[posY+1][posX] !=0)||(image[posY+1][posX+1] != 0))	//形状检查
			return false;

	return true;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CIIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	binImage[posY][posX]	 = color;
	binImage[posY][posX+1]	 = color;
	binImage[posY+1][posX]   = color;
	binImage[posY+1][posX+1] = color;

}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CIIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
			
	SetPosY(0);	//置顶
}


//=========================================================	派生类CIIIBrick
//冲突检查
bool CIIIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	switch(orientation)	//按照砖块对应状态进行界面冲突检查
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY][posX] != 0)||(image[posY][posX+1] != 0)||(image[posY+1][posX-1] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//位置检查
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY][posX+2] != 0))	//形状检查
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX+1] != 0))	//形状检查
				return 0;
			break;
		default: break;
	}
	return 1;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CIIIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX]	 = color;
			binImage[posY][posX+1]	 = color;
			binImage[posY+1][posX-1] = color;
			binImage[posY+1][posX]	 = color;
			break;
		case angle90:
			binImage[posY-1][posX-1]   = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX]     = color;
			binImage[posY+1][posX]   = color;
			break;
		case angle180:
			binImage[posY-1][posX] = color;
			binImage[posY-1][posX+1]   = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY+1][posX+1] = color;
			break;
		default: break;
	}
}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CIIIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//置顶
			break;
		case angle90:
			SetPosY(1);	//置顶
			break;
		case angle180:
			SetPosY(1); //置顶
			break;
		case angle270:
			SetPosY(1); //置顶
			break;
		default :break;
	}
}

//=========================================================	派生类CIVBrick
//冲突检查
bool CIVBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	switch(orientation)	//按照砖块对应状态进行界面冲突检查
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY+1][posX] !=0)||(image[posY+1][posX+1] != 0))	//形状检查
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY-1][posX-1] != 0))	//形状检查
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY-1][posX] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//形状检查
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX+1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY-1][posX] != 0))	//形状检查
				return 0;
			break;
		default: break;
	}
	return 1;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CIVBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY+1][posX]   = color;
			binImage[posY+1][posX+1] = color;
			break;
		case angle90:
			binImage[posY-1][posX] = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX-1] = color;
			break;
		case angle180:
			binImage[posY-1][posX-1] = color;
			binImage[posY-1][posX]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX+1] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY+1][posX] = color;
			break;
		default: break;
	}
}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CIVBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	
			break;
		case angle90:
			SetPosY(1);	
			break;
		case angle180:
			SetPosY(1); 
			break;
		case angle270:
			SetPosY(1); 
			break;
		default :break;
	}
}

//=========================================================	派生类CVBrick
//冲突检查
bool CVBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	switch(orientation)	//按照砖块对应状态进行界面冲突检查
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX+1] != 0))	//形状检查
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY+1][posX-1] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//形状检查
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY-1][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		default: break;
	}
	return 1;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CVBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1]   = color;
			binImage[posY+1][posX+1] = color;
			break;
		case angle90:
			binImage[posY-1][posX] = color;
			binImage[posY][posX] = color;
			binImage[posY+1][posX-1]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY-1][posX-1] = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY-1][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY+1][posX] = color;
			break;
		default: break;
	}
}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CVBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//置顶
			break;
		case angle90:
			SetPosY(1);	//置顶
			break;
		case angle180:
			SetPosY(1); //置顶
			break;
		case angle270:
			SetPosY(1); //置顶
			break;
		default :break;
	}
}


//=========================================================	派生类CVIBrick
//冲突检查
bool CVIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	switch(orientation)	//按照砖块对应状态进行界面冲突检查
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX-1] != 0))	//形状检查
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY-1][posX] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX+1] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//形状检查
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY+1][posX] !=0)||(image[posY+1][posX+1] != 0))	//形状检查
				return 0;
			break;
		default: break;
	}
	return 1;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CVIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1]   = color;
			binImage[posY+1][posX-1] = color;
			break;
		case angle90:
			binImage[posY-1][posX-1] = color;
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY-1][posX+1] = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			binImage[posY+1][posX+1] = color;
			break;
		default: break;
	}
}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CVIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//置顶
			break;
		case angle90:
			SetPosY(1);	//置顶
			break;
		case angle180:
			SetPosY(1); //置顶
			break;
		case angle270:
			SetPosY(1); //置顶
			break;
		default :break;
	}
}

//=========================================================	派生类CVIIBrick
//冲突检查
bool CVIIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//得到界面宽
	height = bin->GetHeight();	//得到界面高
	image = new unsigned char * [height];	//创建界面
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//获取界面数据
	orientation = GetOrientation();	//获取砖块状态
	posX = GetPosX();	//获取特征点坐标
	posY = GetPosY();

	switch(orientation)	//按照砖块对应状态进行界面冲突检查
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//形状检查
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//位置检查
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX] != 0))	//形状检查
				return 0;
			break;
		default: break;
	}
	return 1;
}
//根据砖块的状态，在界面中设置其特征点，颜色
void CVIIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle90:
			binImage[posY-1][posX] = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY-1][posX] = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY+1][posX] = color;
			break;
		default: break;
	}
}
//根据新的特征点X坐标和状态，设置特征点Y，并且将砖块放在顶部
void CVIIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//置顶
			break;
		case angle90:
			SetPosY(1);	//置顶
			break;
		case angle180:
			SetPosY(1); //置顶
			break;
		case angle270:
			SetPosY(1); //置顶
			break;
		default :break;
	}
}


