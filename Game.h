#ifndef _ONCE_  
#define _ONCE_

#include <stdio.h>
//#include <stdlib.h>
#include "malloc.h"
#include <windows.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
//#define OVERFLOW -2
#define OK 1
#define POINT_SIZE sizeof(struct Point)
#define LNODE_SIZE sizeof(struct LNode)

#define LIST_INT_SIZE 100
#define LISTINCREMENT 10

#define MAX_TREE_SIZE 100

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct Coor{ //���� 
	int X;
	int Y;
}Coor;

typedef struct Color{ //��ɫ 
	int LINE_R;
	int LINE_G;
	int LINE_B;
	int FILL_R;
	int FILL_G;
	int FILL_B;
}Color;

typedef struct Point{ //СԲ�� 
	float R;
	Coor coor;
	Color color;
	int ID;
	int live;
	float step;
}Point;

typedef struct Brick{ //ש�� 
	int lift;
	int right;
	int top;
	int bottom;
	int width;
	int height;
	int depth;
	Color color;
	int br_r;
	int X;
	int Y;
	//int 
}Brick; 

typedef struct Bullet{ //�ӵ� 
	Point bullet;
	//int X;
	//int Y;
	//int R;
	//int live;
	int dir;
	int belong;
}Bullet;

typedef int Status;
typedef Point ElemType;//���Ա�����Ԫ������ 
typedef Point* TElemType;
typedef int SElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];


typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef struct BiTNode{
	TElemType data;
	int flag;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

typedef struct Game{
	int foodNum;
	//LinkList G	
}Game;

Status InitList(LinkList &L);//����һ���յ�����L 
Status InsAfter(LinkList &L,ElemType e);//�ں��������
Status DelElem(LinkList &L,ElemType e);//ɾ��e��� 

Status InitTree(BiTree &T);
//Status CreateBiTree(BiTree &T);
//Status InsBiTree(BiTree &T,TElemType e);
Status InsBiTree(BiTree &T);
Status PreOrderTraverse(BiTree T,int(*Visit)(TElemType e));//�������������

Status InitStack(SqStack &S); //����һ����ջS
Status Push(SqStack &S,SElemType e); //����Ԫ��eΪ�µ�ջ��Ԫ��
Status DestroyStack(SqStack &S); //����ջS��S���ٴ��� 
Status ClearStack(SqStack &S); //��S��Ϊ��ջ
Status StackEmpty(SqStack S); //��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
int StackLength(SqStack S); //����S��Ԫ�ظ�������ջ�ĳ���
Status GetTop(SqStack &S,SElemType &e); //��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE 
Status Pop(SqStack &S,SElemType &e); //��ջ��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR 
Status StartTraverse(SqStack S,Status(*Visit)(SElemType e));//��ջ�׵�ջ�����ζ�ջ�е�ÿ��Ԫ�ص���Visit()��һ������ʧ�ܣ������ʧ�� 
Status Visit(int base); 

/*typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;


Status InitList_Sq(SqList &L);//����ձ� */

#endif 
