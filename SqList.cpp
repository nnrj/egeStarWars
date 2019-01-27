#include "stdio.h"
//#include <iostream>
#include <windows.h>
#define LIST_INT_SIZE 100
#define LISTINCREMENT 10

#define OVERFLOW -2
#define OK 1
#define ERROR 0 
#define N 10 
#define M 30

typedef int ElemType; 
typedef int Status;
//using namespace std;

typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList &L);//构造空表 
Status Creat_Sq(SqList &L); //创建线性表 
Status Show_Sq(SqList L); //显示所有数据 
Status Add_Sq(SqList &L,ElemType e);//增加数据 
Status Inverse_Sq(SqList &L,int i,ElemType e);//插入数据 
Status Del_Sq(SqList &L,int i,ElemType &e );//删除数据 
Status Find_Sq(SqList L,int i,ElemType &e);//查找数据 
Status Change(SqList L,int i,ElemType e);//修改数据 
Status line(int n);
Status cls();
Status end();

Status InitList_Sq(SqList &L){
	L.elem = (ElemType *)malloc(LIST_INT_SIZE *sizeof(ElemType));
	if(!L.elem){
		printf("系统初始化失败！\n");
		exit(OVERFLOW);
	}
	L.length = 0; 
	L.listsize = LIST_INT_SIZE;
	return OK;
}

Status Creat_Sq(SqList &L) {
	for(int i = 0;i < N;i++){
		if(L.listsize!=0){
			printf("请输入第%d个数据的值：",i+1);
			scanf("%d",&L.elem[L.length]);
			line(M);
			L.length++;
		}
		else{
			printf("空间不足！\n");
			line(M);
			return ERROR; 
		}
	}
	return OK;
}

Status Show_Sq(SqList L){
	for(int i = 0;i < L.length;i++){
		printf("数据%d:%d\n",i+1,L.elem[i]);
	}
	printf("\n");
	return TRUE;
}

Status Add_Sq(SqList &L,ElemType e){
	if(L.listsize != 0){
		L.elem[L.length] = e; 
		L.length++;
		return TRUE;
	}
	else{
		printf("空间不足！\n");
		exit(OVERFLOW);
	}
	return FALSE;
}

Status Inverse_Sq(SqList &L,int i,ElemType e){
	if(i > 0 && i <= L.length){
		if(L.listsize!=0){
			for(int j = L.length;j>i;j--){
				L.elem[j+1] = L.elem[j];
			}
			L.elem[i] = e;
			L.length++;
			return TRUE;
		}
		else{
			return FALSE;
		}	
	}
	else{
		return FALSE;
	}
	return FALSE;
}

Status Del_Sq(SqList &L,int i,ElemType &e){
	if(i > 0 && i <= L.length){
		e = L.elem[i-1];
		for(;i < L.length;i++){
			L.elem[i-1] = L.elem[i]; 
		}
		L.length--;
		return TRUE;
	}
	else{
		return FALSE;
	}
	return FALSE;
}

Status Find_Sq(SqList L,int i,ElemType &e){
	if(i > 0 && i <= L.length){
		e = L.elem[i-1];
		return TRUE;
	}
	else{
		return FALSE;
	}
	return FALSE;
}

Status Change_Sq(SqList &L,int i,ElemType e){
	if(i > 0 && i < L.length){
		L.elem[i-1] = e;
		return TRUE; 
	}
	else{
		return FALSE;
	}
	return FALSE;
}

Status line(int n){
	for(int i = n;i > 0;i--){
		printf("-");
	}
	printf("\n");
	return OK;
}

Status cls(){
	system("cls");
	return OK;
}

Status end(){
	cls();
	printf("系统已退出。\n");
	line(M);
	exit(OK);
	return OK;
}

int main(){
	int ch = 0,i = 0;
	ElemType e;
	SqList L;
	printf("正在初始化系统...\n");
	InitList_Sq(L);
	Sleep(1000);
	cls();
	printf("系统初始化完毕。\n");
	//Sleep(1000);
	line(M);
	printf("开始建立数据...\n");	
	//Sleep(1000);
	line(M);
	Creat_Sq(L);
	//Sleep(1000);
	//line(M);
	cls();
	printf("线性表建立完毕。\n");
	line(M);
	while(1){
		printf("请选择要进行的操作。\n");
		printf("<1>增加数据\n");
		printf("<2>插入数据\n");
		printf("<3>删除数据\n");
		printf("<4>查找数据\n");
		printf("<5>修改数据\n");
		printf("<6>所有数据\n");
		printf("<7>退出系统\n");
		scanf("%d",&ch);
		getchar();
		switch(ch){
			case 1:{
				cls();
				printf("请输入要增加的数据：");
				scanf("%d",&e);
				if (Add_Sq(L,e) == TRUE){
					cls();
					printf("成功增加数据%d：%d。\n",L.length,L.elem[L.length-1]);
				}
				else{
					cls();
					printf("增加数据%d失败！\n",e);
				}
				line(M);
				break;
			}
			case 2:{
				cls();
				printf("请输入要插入的数据的前驱编号：");
				scanf("%d",&i);
				printf("请输入要插入的数据：");
				scanf("%d",&e);
				if(Inverse_Sq(L,i,e) == TRUE){
					cls();
					printf("成功在第%d个数据前插入数据%d。\n",i,e);
				}
				else{
					cls();
					printf("插入数据失败！\n");
				}	
				line(M);
				break;
			}
			case 3:{
				printf("请输入要删除的数据位置：");
				scanf("%d",&i);
				if(Del_Sq(L,i,e) == TRUE){
					cls();
					printf("已成功删除第%d个数据：%d。\n",i,e);
				}
				else{
					cls();
					printf("删除第%d个数据失败！\n",i);
				}
				line(M);
				break;
			}
			case 4:{
				printf("请输入要查找的数据的位置：");
				scanf("%d",&i);
				if(Find_Sq(L,i,e) == TRUE){
					cls();
					printf("查找成功，第%d个数据的值：%d。\n",i,e);
				}
				else{
					cls();
					printf("查找第%d个数据的值失败！"); 
				}
				line(M);
				break;
			}
			case 5:{
				cls();
				printf("请输入您要修改的数据的位置：");
				scanf("%d",&i);
				printf("请输入新的数据：");
				scanf("%d",&e);
				if(Change_Sq(L,i,e) == TRUE){
					printf("第%d个数据已成功修改为%d。\n",i,e);
				}
				else{
					printf("修改第%d个数据的值失败！\n");
				}
				line(M);
				break;
			}

			case 6:{
				cls();
				printf("所有数据：\n");
				if(Show_Sq(L) == TRUE){
					line(M);	
				}
				else{
					printf("显示所有数据的值失败！\n");
				}
				line(M);
				break;
			}
			case 7:{
				cls();
				end();
				break;
			}
			default:{
				cls();
				printf("无效的操作！\n");
				line(M);	
			}
		}
	}
	return OK;
}
