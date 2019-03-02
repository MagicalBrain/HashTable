/*
* 描述：这是基于无头结点的单链表的实现
* 创建日期：20190302
* 修改日期：20190302
* 作者：HRL
*/
#pragma once
#include <iostream>

using namespace std;

//常用变量的预定义：
#define TRUE 1
#define FALSE 0

#define OK 1
#define ERROR 0

#define NUM         13
#define NULLKEY    -1
#define SUCCESS     1
#define UNSUCCESS   0
#define DUPLICATE  -1

//结构体定义
typedef int Status;


#define RcdType char
////关键字类型
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

////元素类型
typedef char HKeyType;

////链表结点定义
typedef struct HNode {
	HKeyType  data;
	struct HNode*  next;
}*HLink,HNode;

////哈希表定义
typedef struct {
	HLink  *rcd;   // 指针存储基址，动态分配数组
	int    count;  // 当前表中含有的记录个数
	int    size;  // 哈希表的当前容量
}ChainHashTab;    // 链地址哈希表

// 哈希函数
int Hash(ChainHashTab H, HKeyType k) { 
	
	return k % H.size;
}

//处理冲突函数
Status Collision(ChainHashTab H, HLink &p) {
	// 求得下一个探查地址p 
	if (p && (p->next == NULL) ) {
		p = p->next;
		return SUCCESS;
	}
	else return UNSUCCESS;
}


//初始化函数
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
/* 直接调用下列函数                             */
/* 哈希函数：                                   */
/*    int Hash(ChainHashTab H, HKeyType k);     */
/* 冲突处理函数：                               */
/*    int Collision(ChainHashTab H, HLink &p);  */
//H:建立的哈希表
//m：哈希表的元素个数
//es：输入元素数组
{
	int i, num, flag = 0;
	HLink  *rcd;
	HLink p, q;
	HKeyType temp;

	//基址动态数组分配空间
	H.rcd = (HLink*)malloc(m * sizeof(HLink));
	//H.rcd = rcd;
	H.size = NUM;
	H.count = 0;

	//初始化指针基址数组
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