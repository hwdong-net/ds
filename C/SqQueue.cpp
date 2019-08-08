/*==================C语言版本数据结构（源代码）=============
  source code for the course "data starcture in C"
--------请在https ://hwdong.net 上的链接购买腾讯课堂上的数据结构课程-----

教学博客：https ://hwdong.net
youtube频道： hwdong
twitter： hwdong
B站和微博：hw - dong
qq群：101132160
微信公众号：hwdong编程

版权所有 侵权必究
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
		return 0;//扩大内存
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
		printf("队列满了\n ");
	if(!EnQueue(&queue, 'C'))
		printf("队列满了\n");
	if(!EnQueue(&queue, 'D'))
		printf("队列满了\n ");
	T e;
	while (!empty(&queue)) {
		front(queue, &e);
		DeQueue(&queue);
		printf("%c ", e);
	}
	printf("\n");

	return 0;
}