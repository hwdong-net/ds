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

#define _CRT_SECURE_NO_WARNINGS
#if 0
#include <math.h>
typedef int T;
void down_adjust(T data[], int s, int n) {
	if (2 * s + 1 >= n) return;
	T t = data[s];   int m = n - 1;
	for (int j = 2 * s + 1; j < n; ) {
		if (j < m && data[j] < data[j + 1])
			j++;  //jָ��ϴ�ĺ���
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

	printf("��11���뵽��:\n");
	push_heap(a, 11, n);
	print(a, n);

	printf("�Ѷ�����:\n");
	pop_heap(a, n);
	print(a, n);

	printf("�Ѷ�����:\n");
	pop_heap(a, n);
	print(a, n);

	printf("�Ѷ�����:\n");
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
			j++;  //jָ��ϴ�ĺ���
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
	printf("ԭ��������\n");
	print(a, n);
	printf("���ѵĽ��\n");
	make_heap(&hp, a, n);
	print(hp.data, hp.n);

	printf("��11���뵽��:\n");
	push_heap(&hp, 11);
	print(hp.data, hp.n);

	printf("��31���뵽��:\n");
	push_heap(&hp, 31);
	print(hp.data, hp.n);

	printf("��13���뵽��:\n");
	push_heap(&hp, 13);
	print(hp.data, hp.n);

	printf("�Ѷ�����:\n");
	pop_heap(&hp);
	print(hp.data, hp.n);

	printf("�Ѷ�����:\n");
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
һλ��ľ����Ҫ��һ������ľ���г�N�Ρ�ÿ�εĳ��ȷֱ�ΪL1,L2,......,LN��1 <= L1,L2,��,LN <= 1000��
�Ҿ�Ϊ�����������ȵ�λ��������Ϊ�и�ʱ���������㴦����û��ľ����ʧ��
ľ�����֣�ÿһ���и�ѵ��������ľ���ĳ��ȳ����ȣ��������и��Ϊ1��ľ������1��λ������
���磺��N=3��L1 = 3,L2 = 4,L3 = 5����ľ��ԭ��Ϊ12��ľ�������ж����з����磺
�Ƚ�12�г�3+9.������12�������ٽ�9�г�4+5������9������һ������21������
�������Ƚ�12�г�4+8������12�������ٽ�8�г�3+5������8������һ������20��������
Ȼ�����߱�ǰ�߸�ʡ������
��ô��ľ������Ҫ���Ѷ���������������и������أ�

����
4

7
4
3
5
�����
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
		
		push(&q,a + b); //һ���и�
		sum += (a + b);
		printf("�и%d %d����ǰ�ͣ� %d\n", a, b, sum);
		
		n--;
	}
	printf("%d\n",  sum);	

	
	return 0;

}


#endif

