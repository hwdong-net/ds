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
typedef char T;
typedef struct binode {
	T data;
	struct binode *lchild, *rchild;
}BiNode;

BiNode* newNode() {
	BiNode* p = (BiNode*)malloc(sizeof(BiNode));
	if (!p) return 0;
	p->lchild = p->rchild = 0;
	return p;
}

void IOT(BiNode *t,void(*visit)(BiNode *p)) {
	if (!t) return;
	IOT(t->lchild,visit);
	visit(t);
	IOT(t->rchild, visit);
}
void PreOT(BiNode *t, void(*visit)(BiNode *p)) {
	if (!t) { printf("#"); return; }
	visit(t);
	PreOT(t->lchild,visit);	
	PreOT(t->rchild, visit);
}

void PostOT(BiNode *t, void(*visit)(BiNode *p)) {
	if (!t) return;	
	PostOT(t->lchild, visit);
	PostOT(t->rchild, visit);
	visit(t);
}

void print(BiNode *p) {
	printf("%c", p->data);
}

int num = 0;

void leafs(BiNode *p) {
	if (p->lchild ==0 && p->rchild == 0)
		num++;
}

BiNode* PreOrderCreatBiTree() {
	char ch;  BiNode* T;
	scanf("%c", &ch);
	if (ch == '#') return 0;
	else {
		if (!(T = (BiNode*)malloc(sizeof(BiNode)))) {
			printf("内存不够!\n"); return 0;
		}
		T->data = ch;
		T->lchild = PreOrderCreatBiTree();
		T->rchild = PreOrderCreatBiTree();
		return T;
	}
}

typedef struct lnode {
	BiNode* data;
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
int push(LkQueue *Qp, BiNode* e) {
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (!p) return 0;
	p->data = e; p->next = 0;
	Qp->rear->next = p;
	Qp->rear = p;
	return 1;
}
int pop(LkQueue *Qp) {
	LNode* p = Qp->front->next;
	if (!p) return 0;
	Qp->front->next = p->next;
	if (Qp->rear == p) Qp->rear = Qp->front;
	free(p);
	return 1;
}

int front(LkQueue *Qp, BiNode* &e) {
	if (Qp->front == Qp->rear) return 0;
	e = Qp->front->next->data;
	return 1;
}

int empty(LkQueue Q) {
	if (Q.front == Q.rear) return 1;
	return 0;
}



int LevelOrderTraverse(BiNode* T,void(*visit)(BiNode *)) {
	LkQueue Q;  initQueue(&Q);
	BiNode *p;
	push(&Q, T);
	while (!empty(Q)) {
		front(&Q, p); pop(&Q);
		visit(p);
		if (p->lchild)
			push(&Q, p->lchild);
		if (p->rchild)
			push(&Q, p->rchild);
	}
	return 0;
}


BiNode * clone(BiNode *p) {
	if (!p) return 0;
	BiNode *t = newNode();
	t->data = p->data;
	t->lchild = clone(p->lchild);
	t->rchild = clone(p->rchild);
	return t;
}

int is_same(BiNode *t1, BiNode *t2) {
	if (!t1&&t2 || t1&&!t2) return 0;
	if (!t1&&!t2) return 1;
	if (t1->data != t2->data) return 0;

	if (!is_same(t1->lchild, t2->lchild)) return 0;
	return is_same(t1->rchild, t2->rchild);
}


typedef BiNode* BP;
typedef struct {
	BP *data, *top;
	int capacity;
}SqStack;

int init(SqStack &S, int cap) {
	S.data = (BP*)malloc(cap * sizeof(BP));
	if (!S.data) return 0;
	S.top = S.data;
	S.capacity = cap;
	return 1;
}

int push(SqStack &S, BP e) {
	if (S.top - S.data == S.capacity) {
		BP *p = (BP*)realloc(S.data, 2 * S.capacity * sizeof(BP));
		if (!p) return 0;
		S.data = p;
		S.top = S.data + S.capacity;
		S.capacity *= 2;
	}
	*(S.top) = e;
	S.top++;
	return 1;
}
int top(SqStack &S, BP &e) {
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

//------------中序遍历非递归算法-----------
void InOrderTraverse(BiNode* root,void(*visit)(BiNode* )) {
	SqStack S; init(S, 10);
	BiNode *p = root;
	do {
		while (p) {  //向左走到头
			push(S, p); p = p->lchild;
		}
		top(S, p); pop(S); //栈顶的左子树访问完
		visit(p); //栈顶出栈并访问之

		p = p->rchild; //再向右走

	} while (!empty(S) || p);
}

bool InOrderTraverse_(BiNode* T, void(*visit)(BiNode*)) {
	SqStack S; init(S, 10);            //新建一个堆栈
	BiNode* p = T;                       //从树根开始
	while (p || !empty(S)) {  //还有未访问的
		if (p) {                   //一直向左走到底
			push(S, p);
			p = p->lchild;
		}
		else {              //p为NULL，说明走到了底
			top(S, p); pop(S);  //弹出一个还没访问的结点
			visit(p);   //访问之

			p = p->rchild;       //再向右走
		}
	}
	return true;
}

void pre_dfs(BiNode* root, void(*visit)(BiNode*)) {
	BiNode* p;
	SqStack S; init(S, 10);            //新建一个堆栈
	push(S, root);  //根结点入栈S
	while (!empty(S)) {  //只要栈S不空
		top(S, p); pop(S);  //出栈一个结点
		visit(p);    //访问它
		//右孩子、左孩子入栈
		if (p->rchild) push(S, p->rchild);
		if (p->lchild) push(S, p->lchild);
	}
}

void post_dfs(BiNode* root, void(*visit)(BiNode*)) {
	BiNode* p;
	SqStack S; init(S, 10);            //新建一个堆栈
	SqStack R; init(R, 10);            //新建一个堆栈
	push(S, root);  //根结点入栈S
	while (!empty(S)) {  //只要栈S不空
		top(S, p); pop(S);  //出栈一个结点
		//visit(p);    //访问它
		push(R, p);
		//右孩子、左孩子入栈		
		if (p->lchild) push(S, p->lchild);
		if (p->rchild) push(S, p->rchild);
	}
	while (!empty(R)) {
		top(R, p); pop(R);  //出栈一个结点
		visit(p);    //访问它
	}
}

#if 0
int main() {
	/*                 A
	                  / \
					 B   C
					/ \
				   D   E
	*/
	BiNode *T = newNode();    T->data = 'A';
	T->lchild = newNode();   T->lchild->data = 'B';
	T->rchild = newNode();   T->rchild->data = 'C';
	BiNode *p = T->lchild;
	p->lchild = newNode();   p->lchild->data = 'D';
	p->rchild = newNode();   p->rchild->data = 'E';
	IOT(T, print);  /*输出中序遍历序列*/
	printf("\n");
	PreOT(T, print);  /*输出先序遍历序列*/
	printf("\n");
	PostOT(T, leafs);  /*输出后序遍历序列*/
	printf("叶子结点个数是:%d\n", num);

	LevelOrderTraverse(T, print);
	num = 0;
	LevelOrderTraverse(T, leafs);
	printf("叶子结点个数是:%d\n", num);

	BiNode *t2 = clone(T);
	IOT(t2, print);  /*输出中序遍历序列*/
	printf("\n");
	PreOT(t2, print);  /*输出先序遍历序列*/
	printf("\n");
	LevelOrderTraverse(t2, print);

	if(is_same(t2,T))
		printf("t2和T是两个相等树\n");

	BiNode *t3 = newNode();    t3->data = 'A';
	t3->lchild = newNode();   t3->lchild->data = 'B';
	t3->rchild = newNode();   t3->rchild->data = 'C';
	if (is_same(t2,t3))
		printf("t2和t3是两个相等树\n");
	else 
		printf("t2和t3是不相等的2个二叉树\n");
#if 0
	BiNode* t4 = PreOrderCreatBiTree();
	PreOT(t4, print);  /*输出先序遍历序列*/
	printf("\n");
#endif
	InOrderTraverse_(t2, print);
	printf("\n");

	pre_dfs(t2, print);
	printf("\n");

	PostOT(t2, print);  /*输出后序遍历序列*/
	printf("\n");
	post_dfs(t2, print);
	printf("\n");
}
#endif 
