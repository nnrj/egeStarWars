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

Status InitList_Sq(SqList &L);//����ձ� 
Status Creat_Sq(SqList &L); //�������Ա� 
Status Show_Sq(SqList L); //��ʾ�������� 
Status Add_Sq(SqList &L,ElemType e);//�������� 
Status Inverse_Sq(SqList &L,int i,ElemType e);//�������� 
Status Del_Sq(SqList &L,int i,ElemType &e );//ɾ������ 
Status Find_Sq(SqList L,int i,ElemType &e);//�������� 
Status Change(SqList L,int i,ElemType e);//�޸����� 
Status line(int n);
Status cls();
Status end();

Status InitList_Sq(SqList &L){
	L.elem = (ElemType *)malloc(LIST_INT_SIZE *sizeof(ElemType));
	if(!L.elem){
		printf("ϵͳ��ʼ��ʧ�ܣ�\n");
		exit(OVERFLOW);
	}
	L.length = 0; 
	L.listsize = LIST_INT_SIZE;
	return OK;
}

Status Creat_Sq(SqList &L) {
	for(int i = 0;i < N;i++){
		if(L.listsize!=0){
			printf("�������%d�����ݵ�ֵ��",i+1);
			scanf("%d",&L.elem[L.length]);
			line(M);
			L.length++;
		}
		else{
			printf("�ռ䲻�㣡\n");
			line(M);
			return ERROR; 
		}
	}
	return OK;
}

Status Show_Sq(SqList L){
	for(int i = 0;i < L.length;i++){
		printf("����%d:%d\n",i+1,L.elem[i]);
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
		printf("�ռ䲻�㣡\n");
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
	printf("ϵͳ���˳���\n");
	line(M);
	exit(OK);
	return OK;
}

int main(){
	int ch = 0,i = 0;
	ElemType e;
	SqList L;
	printf("���ڳ�ʼ��ϵͳ...\n");
	InitList_Sq(L);
	Sleep(1000);
	cls();
	printf("ϵͳ��ʼ����ϡ�\n");
	//Sleep(1000);
	line(M);
	printf("��ʼ��������...\n");	
	//Sleep(1000);
	line(M);
	Creat_Sq(L);
	//Sleep(1000);
	//line(M);
	cls();
	printf("���Ա�����ϡ�\n");
	line(M);
	while(1){
		printf("��ѡ��Ҫ���еĲ�����\n");
		printf("<1>��������\n");
		printf("<2>��������\n");
		printf("<3>ɾ������\n");
		printf("<4>��������\n");
		printf("<5>�޸�����\n");
		printf("<6>��������\n");
		printf("<7>�˳�ϵͳ\n");
		scanf("%d",&ch);
		getchar();
		switch(ch){
			case 1:{
				cls();
				printf("������Ҫ���ӵ����ݣ�");
				scanf("%d",&e);
				if (Add_Sq(L,e) == TRUE){
					cls();
					printf("�ɹ���������%d��%d��\n",L.length,L.elem[L.length-1]);
				}
				else{
					cls();
					printf("��������%dʧ�ܣ�\n",e);
				}
				line(M);
				break;
			}
			case 2:{
				cls();
				printf("������Ҫ��������ݵ�ǰ����ţ�");
				scanf("%d",&i);
				printf("������Ҫ��������ݣ�");
				scanf("%d",&e);
				if(Inverse_Sq(L,i,e) == TRUE){
					cls();
					printf("�ɹ��ڵ�%d������ǰ��������%d��\n",i,e);
				}
				else{
					cls();
					printf("��������ʧ�ܣ�\n");
				}	
				line(M);
				break;
			}
			case 3:{
				printf("������Ҫɾ��������λ�ã�");
				scanf("%d",&i);
				if(Del_Sq(L,i,e) == TRUE){
					cls();
					printf("�ѳɹ�ɾ����%d�����ݣ�%d��\n",i,e);
				}
				else{
					cls();
					printf("ɾ����%d������ʧ�ܣ�\n",i);
				}
				line(M);
				break;
			}
			case 4:{
				printf("������Ҫ���ҵ����ݵ�λ�ã�");
				scanf("%d",&i);
				if(Find_Sq(L,i,e) == TRUE){
					cls();
					printf("���ҳɹ�����%d�����ݵ�ֵ��%d��\n",i,e);
				}
				else{
					cls();
					printf("���ҵ�%d�����ݵ�ֵʧ�ܣ�"); 
				}
				line(M);
				break;
			}
			case 5:{
				cls();
				printf("��������Ҫ�޸ĵ����ݵ�λ�ã�");
				scanf("%d",&i);
				printf("�������µ����ݣ�");
				scanf("%d",&e);
				if(Change_Sq(L,i,e) == TRUE){
					printf("��%d�������ѳɹ��޸�Ϊ%d��\n",i,e);
				}
				else{
					printf("�޸ĵ�%d�����ݵ�ֵʧ�ܣ�\n");
				}
				line(M);
				break;
			}

			case 6:{
				cls();
				printf("�������ݣ�\n");
				if(Show_Sq(L) == TRUE){
					line(M);	
				}
				else{
					printf("��ʾ�������ݵ�ֵʧ�ܣ�\n");
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
				printf("��Ч�Ĳ�����\n");
				line(M);	
			}
		}
	}
	return OK;
}
