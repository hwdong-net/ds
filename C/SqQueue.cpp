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

#include <malloc.h>
#include <stdio.h>
typedef char T;
typedef struct {
	T *data;
	int capacity, front, rear;
}SqQueue;

int initQueue(SqQueue *Q, int cap) {
	Q->data = (T *)malloc(cap * sizeof(T));
	Q->capacity = cap;
	Q->front = Q->rear = 0;
	return 1;
}

int EnQueue(SqQueue *Q, T e) {
	if ((Q->rear + 1) % Q->capacity == Q->front)
		return 0;//�����ڴ�
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % Q->capacity;
	return 1;

}

int DeQueue(SqQueue *Q) {
	if (Q->rear == Q->front) return 0;
	Q->front = (Q->front + 1) % Q->capacity;
	return 1;
}
int front(SqQueue Q, T *pe) {
	if (Q.rear == Q.front) return 0;
	*pe = Q.data[Q.front];
	return 1;
}
int empty(SqQueue *Q) {
	if (Q->rear == Q->front) return 1;
	return 0;
}
void clear(SqQueue *Q) {
	Q->rear = Q->front = 0;
}

int main() {
	SqQueue queue;
	initQueue(&queue, 3);
	EnQueue(&queue, 'A');
	if(!EnQueue(&queue, 'B'))
		printf("��������\n ");
	if(!EnQueue(&queue, 'C'))
		printf("��������\n");
	if(!EnQueue(&queue, 'D'))
		printf("��������\n ");
	T e;
	while (!empty(&queue)) {
		front(queue, &e);
		DeQueue(&queue);
		printf("%c ", e);
	}
	printf("\n");

	return 0;
}