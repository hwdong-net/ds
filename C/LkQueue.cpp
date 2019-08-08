/*==================C���԰汾���ݽṹ��Դ���룩=============
  source code for the course "data starcture in C"
--------����https ://hwdong.net �ϵ����ӹ�����Ѷ�����ϵ����ݽṹ�γ�-----

��ѧ���ͣ�https ://hwdong.net
youtubeƵ���� hwdong
twitter�� hwdong
Bվ��΢����hw - dong
qqȺ��101132160
΢�Ź��ںţ�hwdong���

��Ȩ���� ��Ȩ�ؾ�
*/

#include <stdio.h>
#include <malloc.h>
typedef char T;
typedef struct lnode {
	T data;
	struct lnode* next;
}LNode;

typedef struct {
	LNode* front, *rear;
}LkQueue;

int initQueue(LkQueue *Qp) {
	Qp->front = Qp->rear = (LNode*)malloc(sizeof(LNode));
	if (!Qp->front) return 0;
	Qp->front->next = 0;
	return 1;
}
int EnQueue(LkQueue *Qp,T e) {
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (!p) return 0;
	p->data = e; p->next = 0;
	Qp->rear->next = p;
	Qp->rear = p;
	return 1;
}
int DeQueue(LkQueue *Qp) {
	LNode* p = Qp->front->next;
	if (!p) return 0;
	Qp->front->next = p->next;
	if (Qp->rear == p) Qp->rear = Qp->front;
	free(p);
	return 1;
}

int front(LkQueue *Qp, T &e) {
	if (Qp->front == Qp->rear) return 0;
	e = Qp->front->next->data;
	return 1;
}

int empty(LkQueue Q) {
	if (Q.front == Q.rear) return 1;
	return 0;
}
int clear(LkQueue *Qp) {
	//...
}
int destory(LkQueue *Qp) {
	//...
}
int main() {
	LkQueue Q;
	initQueue(&Q);
	EnQueue(&Q, 'A');
	EnQueue(&Q, 'B');
	EnQueue(&Q, 'C');

	T e;
	front(&Q, e);	
	printf("%c ", e);

	while (!empty(Q)) {		
		front(&Q, e);
		DeQueue(&Q);
		printf("%c ", e);
	}
	printf("\n");
	return 0;
}