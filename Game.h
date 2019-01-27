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

typedef struct Coor{ //坐标 
	int X;
	int Y;
}Coor;

typedef struct Color{ //颜色 
	int LINE_R;
	int LINE_G;
	int LINE_B;
	int FILL_R;
	int FILL_G;
	int FILL_B;
}Color;

typedef struct Point{ //小圆点 
	float R;
	Coor coor;
	Color color;
	int ID;
	int live;
	float step;
}Point;

typedef struct Brick{ //砖块 
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

typedef struct Bullet{ //子弹 
	Point bullet;
	//int X;
	//int Y;
	//int R;
	//int live;
	int dir;
	int belong;
}Bullet;

typedef int Status;
typedef Point ElemType;//线性表数据元素类型 
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

Status InitList(LinkList &L);//构造一个空的链表L 
Status InsAfter(LinkList &L,ElemType e);//在后面插入结点
Status DelElem(LinkList &L,ElemType e);//删除e结点 

Status InitTree(BiTree &T);
//Status CreateBiTree(BiTree &T);
//Status InsBiTree(BiTree &T,TElemType e);
Status InsBiTree(BiTree &T);
Status PreOrderTraverse(BiTree T,int(*Visit)(TElemType e));//先序遍历二叉树

Status InitStack(SqStack &S); //构造一个空栈S
Status Push(SqStack &S,SElemType e); //插入元素e为新的栈顶元素
Status DestroyStack(SqStack &S); //销毁栈S，S不再存在 
Status ClearStack(SqStack &S); //把S置为空栈
Status StackEmpty(SqStack S); //若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(SqStack S); //返回S的元素个数，即栈的长度
Status GetTop(SqStack &S,SElemType &e); //若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE 
Status Pop(SqStack &S,SElemType &e); //若栈不为空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR 
Status StartTraverse(SqStack S,Status(*Visit)(SElemType e));//从栈底到栈顶依次对栈中的每个元素调用Visit()。一旦访问失败，则操作失败 
Status Visit(int base); 

/*typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;


Status InitList_Sq(SqList &L);//构造空表 */

#endif 
