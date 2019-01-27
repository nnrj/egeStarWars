#include "Game.h" 

Status InitList(LinkList &L){
	L = (LinkList)malloc(sizeof(LNode));
	if(!L){
		exit(OVERFLOW);
	}
	else{
		L->data.ID = NULL;
		L->next = NULL;
		return TRUE;
	}
}

Status InsAfter(LinkList &L,ElemType e){
	LinkList p,q;
	p = (LinkList)malloc(sizeof(LNode));
	q = (LinkList)malloc(sizeof(LNode));
	if(!p || !q){
		exit(OVERFLOW);
	}
	else{
		p = L;
		q->data = e;
		q->next = NULL;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = q;
		return TRUE;	
	}
}

Status DelElem(LinkList &L,ElemType e){
	LinkList p,q;
	p = L;
	while(p->next != NULL){
		q = p->next;
		if(q->data.ID == e.ID){
			p->next = q->next;
			free(q);
			break;
		}
		p = p->next;
	}
} 


