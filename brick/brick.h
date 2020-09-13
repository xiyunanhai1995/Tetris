#ifndef __BRICK_H
#define __BRICK_H
#include<iostream>
#include<windows.h>
#include"../bin/bin.h"

#define	angle0		1	//����ת
#define	angle90		2	//��ת90��
#define	angle180	3	//������ת90��
#define	angle270	4	//������ת90��

//��������ש��Ļ��ࣨ�����ࣩ 
class CBrick
{
protected:
	int posX;				//�ض���X����
	int posY;				//�ض���Y����
	unsigned int BrickType;	//ש������
	unsigned int orientation;//״̬
	unsigned int color; 	//ש����ɫ
	
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

	bool ShiftLeft(CBin *bin);	//����
	bool ShiftRight(CBin *bin);	//����
	bool ShiftDown(CBin *bin);	//����
	bool ShiftLow(CBin *bin);	//���䵽�ײ�
	bool RotateClockwise(CBin *bin);	//��ת
	
protected:
	virtual bool CheckCollision(CBin *bin)=0;	//��ͻ��� [���麯��]
	virtual void operator>>(unsigned char **binImage)=0;//������Ϸ���
	virtual void PutAtTop(unsigned int orientation,int posX)=0;	//�ö�
};

class CIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�
};

class CIIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�
};

class CIIIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�	
};

class CIVBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�
};

class CVBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�
};

class CVIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�
};

class CVIIBrick : public CBrick
{
public:
	bool CheckCollision(CBin *bin);	//��ͻ���
	void operator>>(unsigned char **binImage);	//������Ϸ���
	void PutAtTop(unsigned int orientation,int posX);	//�ö�
};


#endif



