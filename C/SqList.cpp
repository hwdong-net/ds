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

typedef int T;
typedef struct {
	T *data;
	int capacity, n;
}SqList;

#include <malloc.h>
int init(SqList &L,int cap) {
	L.data = (T*)malloc(cap * sizeof(T));
	if (!L.data) return 0;
	L.capacity = cap; 
	L.n = 0;
}

int push_back(SqList &L,T e) {
	if (L.n == L.capacity) {
		T *p = (T*)realloc(L.data, 2*L.capacity * sizeof(T));
		if (!p) return 0;
		L.capacity *= 2;
		//free(L.data); 
		L.data = p;
	}
	L.data[L.n] = e;
	L.n++;
}
int get(SqList &L, int i, T &e) {
	if (i<1 || i>L.n) return 0;
	e = L.data[i - 1];
	return 1;
}
int set(SqList &L, int i, T e) {
	if (i<1 || i>L.n) return 0;
	L.data[i - 1]  = e;
	return 1;
}
int size(SqList L) {
	return L.n;
}

int insert(SqList &L, int i, T e) {
	if (i<1 || i> L.n + 1) return 0;
	if (L.n == L.capacity) {
		T *p = (T*)realloc(L.data, 2 * L.capacity * sizeof(T));
		if (!p) return 0;
		L.capacity *= 2;		
		L.data = p;
	}
#if 0
	for (int j = L.n; j >= i; j--)
		L.data[j ] = L.data[j - 1];
#else
	T *q = L.data + i - 1; //&(L.data[i-1])
	for (T *p = L.data + L.n - 1; p >= q; p--)
		*(p + 1) = *p;
#endif

	L.data[i - 1] = e;
	L.n++; return 1;
}

int remove(SqList &L, int i) {
	if (i<1 || i>L.n) return 0;
	T *p = &(L.data[i]);
	T *q = L.data + L.n - 1;
	while (p <= q) {
		*(p - 1) = *p;
		p++;
	}
	L.n--; 
	return 1;
}

int pop_back(SqList &L) {
	if (L.n == 0) return 0;
	L.n--; return 1;
}
int insert_front(SqList &L,T e) {
	return insert(L, 1, e);
}

int remove_front(SqList &L) {
	return remove(L, 1);
}

#include <stdio.h>
void traverse(SqList L,void (*fp)(T &e)) {
	for (int i = 1; i <= L.n; i++)
		fp(L.data[i-1]);	
}

void print_ch(char &e) {
	printf("%c ",e);
}
void print_int(int &e) {
	printf("%d ", e);
}

void square(int &e) {
	e *= e;
}

int s=0;
void sum(int &e) {
	s += e;
}

int find(SqList L, int (*fp)(T e)) {
	for (int i = 1; i <= L.n; i++)
		if(fp(L.data[i - 1])==1) return i;
	return 0;
}

int equal16(int e) {
	return e==16;
}
int main() {
	SqList list;
	init(list,3);
	push_back(list, 3);
	push_back(list, 4);
	push_back(list, 5);
	push_back(list, 6);
	push_back(list, 7);
	traverse(list, print_int); printf("\n");
	traverse(list, square);
	traverse(list, print_int); printf("\n");
	traverse(list, sum);
	printf("%d \n",s);
	int ret = find(list, equal16);
	if (ret >= 1)
		printf("等于16的元素序号是:%d\n", ret);
	pop_back(list);
	traverse(list, print_int); printf("\n");
	insert_front(list, 120);
	insert_front(list, 118);
	traverse(list, print_int); printf("\n");
	remove_front(list);
	traverse(list, print_int); printf("\n");
#if 0
	push_back(list, 'a');
	push_back(list, 'b');
	push_back(list, 'c');
	push_back(list, 'd');
	push_back(list, 'e');

	set(list, 3, 'S');
	traverse(list, print); printf("\n");

	insert(list, 2, 'Q');
	insert(list, 2, 'P');

	traverse(list, print); printf("\n");

	remove(list, 3);
	traverse(list, print); printf("\n");
#endif

	return 0;
}