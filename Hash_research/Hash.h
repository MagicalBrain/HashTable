/*
* ���������ǻ�����ͷ���ĵ������ʵ��
* �������ڣ�20190302
* �޸����ڣ�20190302
* ���ߣ�HRL
*/
#pragma once
#include <iostream>

using namespace std;

//���ñ�����Ԥ���壺
#define TRUE 1
#define FALSE 0

#define OK 1
#define ERROR 0

#define NUM         13
#define NULLKEY    -1
#define SUCCESS     1
#define UNSUCCESS   0
#define DUPLICATE  -1

//�ṹ�嶨��
typedef int Status;


#define RcdType char
////�ؼ�������
#define KeyType int 


typedef struct Node
{
	RcdType r;
	struct Node* next;
}Node;


typedef struct
{
	Node **rcd;
	int size;
	int count;
	int(*hash)(KeyType key, int hashSize);
};

////Ԫ������
typedef char HKeyType;

////�����㶨��
typedef struct HNode {
	HKeyType  data;
	struct HNode*  next;
}*HLink,HNode;

////��ϣ����
typedef struct {
	HLink  *rcd;   // ָ��洢��ַ����̬��������
	int    count;  // ��ǰ���к��еļ�¼����
	int    size;  // ��ϣ��ĵ�ǰ����
}ChainHashTab;    // ����ַ��ϣ��

// ��ϣ����
int Hash(ChainHashTab H, HKeyType k) { 
	
	return k % H.size;
}

//�����ͻ����
Status Collision(ChainHashTab H, HLink &p) {
	// �����һ��̽���ַp 
	if (p && (p->next == NULL) ) {
		p = p->next;
		return SUCCESS;
	}
	else return UNSUCCESS;
}


//��ʼ������
Status InitHashTab(ChainHashTab &H, int m)
//
{
	if (m >= NUM)
	{
		if (H.rcd = (HLink*)malloc(m * sizeof(HLink)))
			return OK;
		else
			return ERROR;

		for (int i = 0; i < m; i++)
		{
			H.rcd[i]->data = NULL;
			H.rcd[i]->next = NULL;
		}

		H.count = 0;
		H.size = NUM;
	}
	return ERROR;
}


int BuildHashTab(ChainHashTab &H, int m, HKeyType es[])
/* ֱ�ӵ������к���                             */
/* ��ϣ������                                   */
/*    int Hash(ChainHashTab H, HKeyType k);     */
/* ��ͻ��������                               */
/*    int Collision(ChainHashTab H, HLink &p);  */
//H:�����Ĺ�ϣ��
//m����ϣ���Ԫ�ظ���
//es������Ԫ������
{
	int i, num, flag = 0;
	HLink  *rcd;
	HLink p, q;
	HKeyType temp;

	//��ַ��̬�������ռ�
	H.rcd = (HLink*)malloc(m * sizeof(HLink));
	//H.rcd = rcd;
	H.size = NUM;
	H.count = 0;

	//��ʼ��ָ���ַ����
	for (i = 0; i< m; ++i)
	{
		H.rcd[i] = (HLink)malloc(sizeof(HNode));
		H.rcd[i]->data = NULL;
		H.rcd[i]->next = NULL;
	}

	for (i = 0; i< m; ++i)
	{
		p = (HLink)malloc(sizeof(HNode));
		num = Hash(H, es[i] - 'A');
		q = H.rcd[num];
		//q->next = H.rcd[num];
		p->data = es[i];


		while (q->data != p->data && Collision(H, q))
		{
			if (q == NULL)
			{
				flag = 0;
				break;
			}
			else if (q->data == p->data)
			{
				flag = 1;
				break;
			}
			q = q->next;
		}

		if (flag)
			flag = 0;
		else
		{
			temp = p->data;
			p->data = H.rcd[num]->data;
			H.rcd[num]->data = temp;

			p->next = H.rcd[num]->next;
			H.rcd[num]->next = p;
			//q->next = H.rcd[num]->next;

			H.count++;
		}

	}
	return SUCCESS;
}