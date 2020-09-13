#ifndef __BIN_H
#define __BIN_H
#include<iostream>

using namespace std;

//���������
class CBin
{
private:
	unsigned int width;	//������
	unsigned int height;	//����߶�
	unsigned char **image;	//����ӳ��
public:
	CBin(unsigned int width,unsigned int height);
	~CBin(void);
	unsigned int GetWidth(void) { return width; }	//���ý�����
	unsigned int GetHeight(void) { return height; }	//���ý���߶�
	void GetImage(unsigned char **destImage);		//�õ�ӳ������

	void SetImage(unsigned char **srcImage);	//����ӳ������
	unsigned int RemoveFullLines(void);				//�������
};


#endif



