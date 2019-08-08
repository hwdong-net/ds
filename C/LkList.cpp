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

typedef char T;
typedef struct lnode {
	T data;
	struct lnode* next;
}LNode;

#include <malloc.h>
LNode *initLkList(LNode *&L) {
	L = (LNode *)malloc(sizeof(LNode));
	if (!L) return 0;
	L->next = 0; return L;
}
LNode * insert_front(LNode *&L,T e) {
	LNode *p = (LNode *)malloc(sizeof(LNode));
	if (!p) return 0;
	p->data = e; p->next = 0;
	p->next = L->next;
	L->next = p;
	return p;
}
void traverse(LNode *L, void(*fp)(T &e)) {
	LNode *p = L->next;
	while (p) {
		fp(p->data); 
		p = p->next;
	}
}

LNode * front(LNode *&L) {
	return L->next;
}
int pop_front(LNode* L) {
	LNode *p = L->next;
	if (!p) return 0;
	L->next = p->next;
	free(p);
	return 1;
}

int get(LNode* L, int i, T &e) {
	if (i < 1) return 0;
	LNode *p = L; int j = 0;
	while (p&&j < i) {
		p = p->next;
		j++;
	}
	if (!p) return 0;
	e = p->data;
	return 1;
}

int insert(LNode* L, int i, T e) {
	if (i < 1) return 0;
	LNode *p = L; int j = 0;
	while (p&&j < i-1) {
		p = p->next;
		j++;
	}
	if (!p) return 0;

	LNode *s = (LNode *)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}
int remove(LNode* L, int i) {
	if (i < 1) return 0;
	LNode *p = L; int j = 0;
	while (p&&j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p) return 0;

	LNode *q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

#include <stdio.h>
int remove_front(LNode* L) {
	LNode *q = L->next;
	if (!q) { printf("空表"); return 0; }
	L->next = q->next;
	free(q);
	return 1;
}


void print(T &e) {
	printf("%c ", e);
}

void converse(LNode *head) {
	LNode *p = head->next;
	head->next = 0;
	while (p) { //前插法到头结点后面
		LNode *q = p->next; //保存下一个结点地址
		p->next = head->next; //指向新链表首结点
		head->next = p;
		p = q;
	}

}

int main() {
	LNode *head;
	initLkList(head);
	insert_front(head, 'a');
	insert_front(head, 'b');
	insert_front(head, 'c');
	traverse(head, print); printf("\n");
	LNode *p = front(head);
	if (p) print(p->data); printf("\n");

	pop_front(head);
	traverse(head, print); printf("\n");

	T ele;
	if (get(head, 2, ele) > 0) {
		print(ele); printf("\n");
	}

	insert(head, 3, 'H');
	traverse(head, print); printf("\n");
	insert(head, 3, 'R');
	traverse(head, print); printf("\n");
	insert(head, 1, 'X');
	traverse(head, print); printf("\n");

#if 0
	remove(head, 2);
	traverse(head, print); printf("\n");
	remove(head, 1);
	traverse(head, print); printf("\n");
	remove_front(head);	
	traverse(head, print); printf("\n");
	remove_front(head);
	traverse(head, print); printf("\n");
	remove_front(head);
	traverse(head, print); printf("\n");
	remove_front(head);
	traverse(head, print); printf("\n");
#endif

	converse(head);
	traverse(head, print); printf("\n");
	return 0;
}