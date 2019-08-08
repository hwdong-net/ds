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
#include <malloc.h>
#include <stdio.h>

//typedef int T;
typedef char T;
typedef struct lnode {
	T data;
	struct lnode *next;
}LNode;

int initLkStack(LNode * &S) {
	S = (LNode*)malloc(sizeof(LNode));
	if (!S) return 0;
	S->next = 0; return 1;
}
int push(LNode * &S,T e) {
	LNode *p = (LNode*)malloc(sizeof(LNode));
	if (!p) return 0;
	p->data = e;
	p->next = S->next;
	S->next = p; return 1;
}
int pop(LNode * &S) {
	LNode *p = S->next;
	if (!p) return 0;
	S->next = p->next;
	free(p);
	return 1;
}
int top(LNode * &S, T &e) {
	LNode *p = S->next;
	if (!p) return 0;
	e = p->data; return 1;
}
int empty(LNode * S) {
	LNode *p = S->next;
	if (!p) return 1;
	return 0;
}
int clear(LNode * S) {
	LNode *p = S->next;
	while (p) {
		S->next = p->next;
		free(p);
		p = S->next;
	}
	return 1;
}
#if 0
int main() {
	LNode * stack;
	initLkStack(stack);
	push(stack, 'A');
	push(stack, 'B');
	while (!empty(stack)) {
		T e;
		top(stack, e);	pop(stack);
		printf("%c\n", e);
	}
	push(stack, 'C');
	push(stack, 'D');
	clear(stack);
	while (!empty(stack)) {
		T e;
		top(stack, e);	pop(stack);
		printf("%c\n", e);
	}
	return 0;
}
#endif

#if 0
void conversion(const int d) {
	/*输入非负十进制整数，输出对应的八进制数*/
	LNode * S; // 构造空栈
	initLkStack(S);
	int N;
	scanf("%d", &N);
	while (N) {
		push(S, N % d);   N = N / d;
	}
	while (!empty(S)) {
		T e;
		top(S, e);     pop(S);
		printf("%d", e);
	}
	printf("\n");
}
#endif
int is_left_kuohao(char ch) {
	if (ch == '(' || ch == '[' || ch == '{')
		return 1;
	return 0;
}
int is_right_kuohao(char ch) {
	if (ch == ')' || ch == ']' || ch == '}')
		return 1;
	return 0;
}

int is_match(char lc, char rc) {
	if (lc == '('&&rc == ')'
		|| lc == '['&&rc == ']'
		|| lc == '{'&&rc == '}') return 1;
	return 0;
}
int is_matching(char *str){
	LNode *S;
	initLkStack(S);
	char *p = str;
	while(*p!='\0' ){
		if (is_left_kuohao(*p))
			push(S, *p);
		else if (is_right_kuohao(*p)) {
			if (empty(S)) return 0;
			char ch;
			top(S, ch);
			if (!is_match(ch, *p))
				return 0;
			pop(S); 
		}
		p++;
	}
	if ( !empty(S)) return 0;
	return 1;
}
int main() {
//	conversion(8);
//	conversion(2);
//	char s[] = "{(}a[]4)";
	char s[] = "{}[(3[d][]ad)]";
	if (is_matching(s))
		printf("%s 匹配\n",s);
	else
		printf("%s 不匹配\n", s);
	return 0;
}
