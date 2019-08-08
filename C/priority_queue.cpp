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

#define _CRT_SECURE_NO_WARNINGS
#if 0
#include <math.h>
typedef int T;
void down_adjust(T data[], int s, int n) {
	if (2 * s + 1 >= n) return;
	T t = data[s];   int m = n - 1;
	for (int j = 2 * s + 1; j < n; ) {
		if (j < m && data[j] < data[j + 1])
			j++;  //j指向较大的孩子
		if (!(t < data[j]))  break;
		data[s] = data[j];
		s = j; j = 2 * j + 1;
	}
	data[s] = t;
}

void make_heap(T data[], int n) {
	for (int s = floor((n - 1 - 1.) / 2); s >= 0; s--)
		down_adjust(data, s, n);
}

void swap(T &a, T &b) {
	T t = a; a = b; b = t;
}

void pop_heap(T data[], int &n) {
	swap(data[0], data[n - 1]);
	n--;
	down_adjust(data, 0, n);
}

void push_heap(T data[], const T e, int &n) {
	data[n] = e; n++;
	int s = n - 1;
	T t = data[s];
	for (int j = floor((s - 1.) / 2); j >= 0;) {
		if (t < data[j])  break;
		data[s] = data[j];
		s = j; j = floor((s - 1.) / 2);
	}
	data[s] = t;
}


#include <stdio.h>

void print(int a[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}
int main() {
#if 0
	//        0 1 2 3 4 5 6 7  
	T a[] = { 7,9,6,8,1,4,2,3 };  int n = 8;
	down_adjust(a, 0, 8);
	print(a, n);
#endif

#if 0
	T a[] = { 7,9,2,8,1,4,6,3 }; int n = 8;
	make_heap(a, n);
	print(a, n);
#endif

#if 1
	T a[9] = { 7,19,2,8,1,4,6,3 }; int n = 8;
	make_heap(a, n);
	print(a, n);

	printf("将11加入到堆:\n");
	push_heap(a, 11, n);
	print(a, n);

	printf("堆顶出堆:\n");
	pop_heap(a, n);
	print(a, n);

	printf("堆顶出堆:\n");
	pop_heap(a, n);
	print(a, n);

	printf("堆顶出堆:\n");
	pop_heap(a, n);
	print(a, n);
#endif
}

#endif

#if 1
#include <malloc.h>
#include <stdio.h>
#include <math.h>
typedef int T;
typedef struct {
	T *data;
	int capacity, n;
}heap;

int init_heap(heap *h, const int cap) {
	h->data = (T *)malloc(cap * sizeof(T));
	if (!h->data) return 0;
	h->capacity = cap;
	h->n = 0;
	return 1;
}

void down_adjust(heap *h, int s) {
	const int n = h->n;
	T *data = h->data;
	if (2 * s + 1 >= n) return;
	T t = data[s];   int m = n - 1;
	for (int j = 2 * s + 1; j < n; ) {
//		if (j < m && data[j] < data[j + 1])
		if (j < m && data[j] > data[j + 1])
			j++;  //j指向较大的孩子
//		if (!(t < data[j]))  break;
		if (!(t > data[j]))  break;
		data[s] = data[j];
		s = j; j = 2 * j + 1;
	}
	data[s] = t;
}

//int floor(double e) { return (int)(e); }
int make_heap(heap *h, T *data, const int n) {
	if (!init_heap(h, n)) return 0;
	for (int i = 0; i < n; i++)
		h->data[i] = data[i];
	h->n = n;
	for (int i = floor((n - 1 - 1) / 2); i >= 0; i--)
		down_adjust(h, i);
	return 1;
}
int top_heap(heap h, T *ep) {
	if (h.n == 0) return 0;
	*ep = h.data[0];
	return 1;
}

int empty_heap(heap h) {
	if (h.n == 0) return 1;
	return 0;
}

void clear_heap(heap *h) {
	h->n = 0;
}

void swap(T &a, T &b) {
	T t = a; a = b; b = t;
}
void pop_heap(heap *h) {
	swap(h->data[0], h->data[h->n - 1]);
	h->n--;
	down_adjust(h, 0);
}
int push_heap(heap *h, T e) {
	if (h->n == h->capacity) {
		T *p = (T*)realloc(h->data, 2 * h->capacity * sizeof(T));
		if (!p) return 0;
		h->capacity *= 2;
		h->data = p;
	}
	h->data[h->n] = e; h->n++;

	T * data = h->data;
	int s = h->n - 1;
	T t = data[s];
	for (int j = floor((s - 1.) / 2); j >= 0;) {
	//	if (t < data[j])  break;
		if (t > data[j])  break;
		data[s] = data[j];
		s = j; j = floor((s - 1.) / 2);
	}
	data[s] = t;
}

void print(int a[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main_() {
	heap hp;
	T a[] = { 7,19,2,8,1,4,6,3 }; int n = 8;
	printf("原来的序列\n");
	print(a, n);
	printf("建堆的结果\n");
	make_heap(&hp, a, n);
	print(hp.data, hp.n);

	printf("将11加入到堆:\n");
	push_heap(&hp, 11);
	print(hp.data, hp.n);

	printf("将31加入到堆:\n");
	push_heap(&hp, 31);
	print(hp.data, hp.n);

	printf("将13加入到堆:\n");
	push_heap(&hp, 13);
	print(hp.data, hp.n);

	printf("堆顶出堆:\n");
	pop_heap(&hp);
	print(hp.data, hp.n);

	printf("堆顶出堆:\n");
	pop_heap(&hp);
	print(hp.data, hp.n);
	return 0;
}

typedef heap priority_queue;

int init_queue(priority_queue *q,int cap) {
	return init_heap(q,cap);
}
int push(priority_queue *q, T e) {
	return push_heap(q, e);
}
void pop(priority_queue *q) {
	pop_heap(q);
}
int top(priority_queue q, T *ep) {
	return top_heap(q, ep);
}
void clear(priority_queue *q) {
	clear_heap(q);
}

int empty(priority_queue q) {
	return empty_heap(q);
}

int main_2() {
	priority_queue queue;
	T e;
	init_queue(&queue,2);

	push(&queue, 11);
	print(queue.data, queue.n);

	push(&queue, 31);
	print(queue.data, queue.n);

	push(&queue, 13);
	print(queue.data, queue.n);

	push_heap(&queue, 9);
	print(queue.data, queue.n);


	while (!empty(queue)) {
		top(queue, &e);
		pop(&queue);
		printf("%d ", e);
	}
	printf("\n");
	return  0;
}



/*
一位老木匠需要将一根长的木棒切成N段。每段的长度分别为L1,L2,......,LN（1 <= L1,L2,…,LN <= 1000，
且均为整数）个长度单位。我们认为切割时仅在整数点处切且没有木材损失。
木匠发现，每一次切割花费的体力与该木棒的长度成正比，不妨设切割长度为1的木棒花费1单位体力。
例如：若N=3，L1 = 3,L2 = 4,L3 = 5，则木棒原长为12，木匠可以有多种切法，如：
先将12切成3+9.，花费12体力，再将9切成4+5，花费9体力，一共花费21体力；
还可以先将12切成4+8，花费12体力，再将8切成3+5，花费8体力，一共花费20体力。显
然，后者比前者更省体力。
那么，木匠至少要花费多少体力才能完成切割任务呢？

输入
4

7
4
3
5
输出：
38
*/


int main() {
	int sum = 0;
	int n,Li;
	priority_queue q;
	init_queue(&q, 2);
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {		
		scanf("%d", &Li);;
		push(&q,Li);
	}

	while (!empty(q)) {
		int a, b;
		top(q, &a); pop(&q);
		if (!top(q, &b)) break;
		pop(&q);	
		
		push(&q,a + b); //一次切割
		sum += (a + b);
		printf("切割：%d %d，当前和： %d\n", a, b, sum);
		
		n--;
	}
	printf("%d\n",  sum);	

	
	return 0;

}


#endif

