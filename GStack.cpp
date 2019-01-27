#include "Game.h"

Status InitStack(SqStack &S){//构造一个空栈S 
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base){
		exit(OVERFLOW);	
	}
	else{
		S.top = S.base;
		S.stacksize = STACK_INIT_SIZE;	
	}
	return OK;
}

Status Push(SqStack &S,SElemType e){//插入元素e为新的栈顶元素
	if(S.top - S.base >= S.stacksize){
		S.base = (SElemType *)realloc(S.base,(S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if(!S.base){
			exit(OVERFLOW);
		}
		else{
			S.top = S.base + S.stacksize;
			S.stacksize += STACKINCREMENT;	
		}
	}
	*S.top++ = e;
	return OK;
}

Status GetTop(SqStack &S,SElemType &e){//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE 
	if(S.top == S.base){
		return ERROR;
	}
	else{
		e = *(S.top-1);	
		return OK;
	}
}

Status Pop(SqStack &S,SElemType &e){//若栈不为空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR 
	if(S.top == S.base){
		return ERROR;
	}
	else{
		e = *--S.top;
		return OK;
	}
}

Status StackLength(SqStack S){
	if(S.top == S.base){
		return 0;
	}
	else{
		return (S.top - S.base);
	}
}

Status DestroyStack(SqStack &S){
	if(S.top == NULL || S.base == NULL){
		return FALSE;
	}
	else{
		if(S.top == S.base){
			S.top == NULL;
			S.base == NULL;
			return TRUE;
		}
		else{
			while(S.top == S.base){
				free(S.top--);
			}
			S.top = NULL;
			S.base = NULL;
			return TRUE;
		}
	}
	/*if(S){
		free(S);
		return TRUE;
	}
	else{
		return FALSE;
	}*/
}


Status StackEmpty(SqStack S){
	if(S.top == S.base){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

Status ClearStack(SqStack &S){
	if(S.top != S.base){
		while(S.top != S.base){
			S.top--;
		}
		return TRUE;
	}
	else{
		return FALSE;
	}

	return TRUE;
} 

Status StartTraverse(SqStack S,Status(*Visit)(SElemType e)){
	if(S.top == S.base){
		return FALSE;
	}
	else{
		while(S.top != S.base){
			Visit(*S.base);
			S.base++;
		}
		return TRUE;
	}
	/*if(S.top == S.base){
		return FALSE;
	}
	else{
		while(S.top != S.base){
			if((Visit(S.base)) == TRUE){
				S.base++;
			}
			else{
				return FALSE;
			}
		}
		return TRUE;
	}*/
	/*for(int i = 0;i <= S.top - S.base;i++){
		if(S.top != S.base && Visit(S) == TRUE){
			S.base++; 
			return TRUE;
		}
		else{
			return FALSE;
		}*/
	//}
}

Status Visit(SElemType base){
	printf(" %d",base);
} 

/*Status Visit(int base){
	if(base == NULL){
	//if(printf(" %d",base)){
		printf(" %d",base);
		return TRUE;
	}
	else{
		return FALSE;
	}
}*/
