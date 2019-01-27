#include "Game.h"

Status InitTree(BiTree &T){//------------------------------------断点 
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if(!T){
		exit(OVERFLOW);
	}
	else{
		//T->flag = 0;
		//T->lchild->data = 0;
		//T->rchild->data = 0;
		//T->data->ID = -1;
		return TRUE;
		//T->data->ID = -1;
		//T->lchild = NULL;
		//T->rchild = NULL;
	}
}

Status InsBiTree(BiTree &T){ //------------------------结点的创建问题
	if(!T){
		return FALSE;
	}
	else{
		if(!T->lchild && !T->rchild){
			InitTree(T->lchild);
			InitTree(T->rchild);
			T->lchild->data = T->data;
			T->lchild->data->R = (T->data->R)/2;
			T->rchild->data = T->lchild->data;
			return TRUE;
		}
		else{
			InsBiTree(T);
		}
		//if(T->lchild->flag == 0){
			
		//}
	}
	/*if(!T){
		InitTree(T);
	}
	else{
		T->data = e;
		if(T->flag == 1){
			InsBiTree(T->lchild);
			InsBiTree(T->rchild);
			T->flag = 0;
		}
	}*/
	/*if(!T){
		InitTree(T);
	}
	else{
		if(T->flag != 0){
			if(T->lchild->flag != 0){
				if(T->rchild->flag != 0){
					InsBiTree(T->rchild,e);
				}
				else{
					T->rchild->data = e;
					//InsBiTree(T->lchild,e);
				}
			}
			else{
					
			}
		}
	}*/

	/*if(!T){
		//T=(BiTNode*)malloc(sizeof(BiTNode));
		InitTree(T);
		//T->data
	}
	if(T->flag == 0){
		T->data = e;
		T->flag = 1;
	}
	if(T)
	else if(T->lchild->flag == 0){
		InsBiTree(T->lchild,e);
	}
	/*if(!T){
		return ERROR;
	}
	else{
		if(T->data->ID != -1){
			if(T->lchild->data->ID != -1){
				if(T->rchild->data->ID != -1){
					InsBiTree(T->rchild,e);
				}
				else{
					T->rchild->data = e;
				}
			}
			else{
				T->lchild->data = e;
			}
		}
		else{
			T->data = e;
		}
	}*/


	/*if(!T){
		return ERROR;
	}
	else{
		if(T->data->ID = -1){
			T->data = e;
			return TRUE;
		}
		else{
			if(T->lchild->data){
				InsBiTree
			}
		}
	}*/

	/*if(T->lchild){
		if(T->rchild){
			
		}
	}*/
	/*if(!T){
		T = (BiTNode*)malloc(sizeof(BiTNode));
		T->data = e;
		return OK;
	}
	else{
		if(T->lchild){
			InsBiTree(T->lchild,e);
		}
		else{
			if(T->rchild){
				InsBiTree(T->rchild,e);
			}
		}
	}*/
	
	/*if(!T){
		exit(OVERFLOW);
	} 
	else{
		T->lchild = (BiTNode*)malloc(sizeof(BiTNode));
		T->rchild = (BiTNode*)malloc(sizeof(BiTNode));
		if(!T->lchild || !T->rchild){
			exit(OVERFLOW);
		}
		else{
			T->rchild
		}
	}*/
	/*if(T->lchild){
		InsBiTree(T->lchild,e);
	}
	else{
		if(T->rchild){
			InsBiTree(T->rchild,e);
		}
		else{
			T = (BiTNode*)malloc(sizeof(BiTNode));
			T->data = e;
			return TRUE;
		}
	}*/
	/*if(!T->lchild){
		if(!T->rchild){
			T = (BiTNode*)malloc(sizeof(BiTNode));
			T->data = e;
			return TRUE;
		}
		else{
			InsBiTree(T->rchild,e);
		}
	}
	else{
		InsBiTree(T->lchild,e);
	}*/
	//T = (BiTNode*)malloc(sizeof(BiTNode));
	/*if(!T){
		T = (BiTNode*)malloc(sizeof(BiTNode));
		T->data = e;
		return TRUE;
	}
	else{
		if(T->rchild)
		InsBiTree(T->lchild,e);
		InsBiTree(T->rchild,e);
	}*/
	/*if(!T){
		T = (BiTNode*)malloc(sizeof(BiTNode));
		T->data = e;
		return TRUE;
	}
	else{
		if(!T->lchild){
			InsBiTree(T->lchild,e);
		}
		else{
			if(T->rchild){
				InsBiTree(T->rchild,e);
			}	
		}	
	}*/
	/*if(!T){
		T = (BiTNode*)malloc(sizeof(BiTNode));
		T->data = e;
		return TRUE;
	}
	else{
		if(!T->rchild){
			InsBiTree(T->lchild,e);
			return TRUE;
		}
		else{
			InsBiTree(T->rchild,e);
			return TRUE;
		}	
	}*/		
} 

Status PreOrderTraverse(BiTree T,int(*Visit)(TElemType e)){
	/*Status PreintElement(TElemType e){
		printf("%d",e);
	}*/
	
	if(T){
		if(Visit(T->data)){
			if(PreOrderTraverse(T->lchild,Visit)){
				if(PreOrderTraverse(T->rchild,Visit)){
					return OK;
				}
			}
		}
		else{
			return ERROR;
		}
	}
	else{
		return OK;
	}
	
	/*if(!T){
		exit(OVERFLOW);
	}
	else{
		if(Visit(T->data)){
			if(PreOrderTraverse(T->lchild,Visit)){
				if(PreOrderTraverse(T->rchild,Visit)){
					return TRUE;
				}
			}
		}
	}*/

	/*if(T){
		if(Visit(T->data)){
			if(PreOrderTraverse(T->lchild,Visit)){
				if(PreOrderTraverse(T->rchild,Visit)){
					return OK;
				}
			}
		}
		return ERROR;
	}
	else{
		return OK;
	}*/
}

/*void visitPlayer(Point player){
	gameControl(&player);
	//gameRefresh(&player,food_L);//food_L怎么传过来--------------------------断点 
}*/
