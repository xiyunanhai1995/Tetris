#include"bin.h"

/*---------------------
* �����������캯��
* ��  �ܣ���ʼ�����ڴ�С��������ռ�ͳ�ʼ��
* ����ֵ����
----------------------*/
CBin::CBin(unsigned int width,unsigned int height)
{
	this->width = width;	//��ʼ�����ڿ��
	this->height = height;	//��ʼ�����ڸ߶�

	image = new unsigned char * [height];	//����߶��ڴ�
	for(unsigned int i=0;i < height;i++)	
	{
		image[i] = new unsigned char [width];	//���η������ڴ�
		for(unsigned int j=0;j < width;j++)		//����ʼֵ0
			image[i][j] = 0;
	}
}
/*---------------------
* ����������������
* ��  �ܣ�ɾ���ڹ��캯����Ϊimage����Ŀռ�
* ����ֵ����
---------------------*/
CBin::~CBin(void)
{
	for(unsigned int i=0;i < this->height;i++)
		delete image[i];
	delete image;
}

/*---------------------
* ��������void CBin::GetImage(unsigned char **destImage)
* ��  �ܣ����������ݸ��Ƹ�destImage
* ����ֵ����
---------------------*/
void CBin::GetImage(unsigned char **destImage)
{
	for(unsigned int i=0;i < this->height;i++)
		for(unsigned int j=0;j < this->width;j++)
			destImage[i][j] = image[i][j];
}

/*---------------------
* ��������void CBin::SetImage(unsigned char **srcImage)
* ��  �ܣ����ô������ݣ���srcImage���Ƹ����ڣ�
* ����ֵ����
---------------------*/
void CBin::SetImage(unsigned char **srcImage)
{
	for(unsigned int i=0;i < this->height;i++)
		for(unsigned int j=0;j < this->width;j++)
			image[i][j] = srcImage[i][j];
}
/*---------------------
* ��������unsigned int CBin::RemoveFullLines(void)
* ��  �ܣ�ɾ��������
* ����ֵ��ɾ��������
---------------------*/
unsigned int CBin::RemoveFullLines(void)
{
	unsigned int EmptyLine=0;
	bool flag;
	
	for(int i=0;i < height;i++)
	{
		flag = 1;	//��ʼ����־λΪ������������

		for(int j=0;j < width;j++)
			if(image[i][j] == 0)	//������ڡ��ա�
			{
				flag = 0;	//����λΪ������û������waaaa
				break;
			} 
				
		if(flag)	//�������Ϊ��������
		{
			for(int m=i;m > 0;m--)	//����i-1��������������ƽ��һ��
				for(int j=0;j < width;j++)
					image[m][j] = image[m-1][j];	
			for(int j=0;j < width;j++)	//���õ�0��Ϊ���ա�
				image[0][j] = 0;

			EmptyLine++;	//��¼ɾ��������
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
        //һ����ȫ������
		if(flag==0)  
		{
			//ɾ������
			for(m=i; m>0; m--)
           		for (j=0; j<width; j++) 
				   image[m][j]=image[m-1][j];
	        for (j=0; j<width; j++) 
				   image[0][j]=0;
		    EmptyLine++;  //��¼ɾ��������
		}
	}
     return EmptyLine;   
}
*/




