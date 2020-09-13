#ifndef __BRICK_H
#define __BRICK_H
#include<iostream>
#include<windows.h>
#include"../bin/bin.h"

#define	angle0		1	//无旋转
#define	angle90		2	//旋转90度
#define	angle180	3	//二次旋转90度
#define	angle270	4	//三次旋转90度

//定义所有砖块的基类（抽象类） 
class CBrick
{
protected:
	int posX;				//特定点X坐标
	int posY;				//特定点Y坐标
	unsigned int BrickType;	//砖块类型
	unsigned int orientation;//状态
	unsigned int color; 	//砖块颜色
	
public:
	int oldposX;
	
	unsigned int GetOrientation(void) { return orientation; }
	int GetPosX(void) { return posX; }
	int GetPosY(void) { return posY; }
	unsigned int GetColor(void) { return color; }
	unsigned int GetBrickType(void) { return BrickType; }
	void SetOrientation(unsigned int orientation) { this->orientation = orientation; }
	void SetPosX(int posX) { this->posX = posX; }
	void SetPosY(int posY) { this->posY = posY; }
	void SetColor(unsigned int color) { this->color = color; }
	void SetBrickType(unsigned int BrickType) { this->BrickType = BrickType; }

	bool ShiftLeft(CBin *bin);	//左移
	bool ShiftRight(CBin *bin);	//右移
	bool ShiftDown(CBin *bin);	//下落
	bool ShiftLow(CBin *bin);	//下落到底部
	bool RotateClockwise(CBin *bin);	//旋转
	
protected:
	virtual bool CheckCollision(CBin *bin)=0;	//冲突检查 [纯虚函数]
	virtual void operator>>(unsigned char **binImage)=0;//设置游戏面板
	virtual void PutAtTop(unsigned int orientation,int posX)=0;	//置顶
};

class CIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶
};

class CIIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶
};

class CIIIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶	
};

class CIVBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶
};

class CVBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶
};

class CVIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶
};

class CVIIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//冲突检查
	void operator>>(unsigned char **binImage);	//设置游戏面板
	void PutAtTop(unsigned int orientation,int posX);	//置顶
};


#endif



