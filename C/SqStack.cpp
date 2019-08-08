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
	T *data,*top;
	int capacity;
}SqStack;

int init(SqStack &S, int cap) {
	S.data = (T*)malloc(cap * sizeof(T));
	if (!S.data) return 0;
	S.top = S.data;
	S.capacity = cap;
	return 1;
}

int push(SqStack &S, T e) {
	if (S.top - S.data == S.capacity) {
		T *p = (T*)realloc(S.data, 2*S.capacity * sizeof(T));
		if (!p) return 0;
		S.data = p;
		S.top = S.data + S.capacity;
		S.capacity *= 2;
	}
	*(S.top) = e;
	S.top++;
	return 1;
}
int top(SqStack &S, T &e) {
	if (S.top == S.data) return 0;
	e = *(S.top - 1); return 1;
}
int pop(SqStack &S) {
	if (S.top == S.data) return 0;
	S.top--; return 1;
}
int empty(SqStack S) {
	if (S.top == S.data) return 1;
	return 0;
}
void clear(SqStack &S) {
	S.top = S.data;
}


int main() {
	SqStack stack;
	init(stack, 3);
	push(stack, 'A');
	push(stack, 'B');
	push(stack, 'C');
	push(stack, 'E');
	T e;
	if (top(stack, e)) {
		printf("%c\n", e);
	}
	while (!empty(stack) ) {
		top(stack, e); pop(stack);
		printf("%c\n", e);
	}
	clear(stack);
	if (top(stack, e)) {
		printf("%c\n", e);
	}
	else printf("空栈\n");
	return 0;
}