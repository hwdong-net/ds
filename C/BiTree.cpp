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
			printf("�ڴ治��!\n"); return 0;
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

//------------��������ǵݹ��㷨-----------
void InOrderTraverse(BiNode* root,void(*visit)(BiNode* )) {
	SqStack S; init(S, 10);
	BiNode *p = root;
	do {
		while (p) {  //�����ߵ�ͷ
			push(S, p); p = p->lchild;
		}
		top(S, p); pop(S); //ջ����������������
		visit(p); //ջ����ջ������֮

		p = p->rchild; //��������

	} while (!empty(S) || p);
}

bool InOrderTraverse_(BiNode* T, void(*visit)(BiNode*)) {
	SqStack S; init(S, 10);            //�½�һ����ջ
	BiNode* p = T;                       //��������ʼ
	while (p || !empty(S)) {  //����δ���ʵ�
		if (p) {                   //һֱ�����ߵ���
			push(S, p);
			p = p->lchild;
		}
		else {              //pΪNULL��˵���ߵ��˵�
			top(S, p); pop(S);  //����һ����û���ʵĽ��
			visit(p);   //����֮

			p = p->rchild;       //��������
		}
	}
	return true;
}

void pre_dfs(BiNode* root, void(*visit)(BiNode*)) {
	BiNode* p;
	SqStack S; init(S, 10);            //�½�һ����ջ
	push(S, root);  //�������ջS
	while (!empty(S)) {  //ֻҪջS����
		top(S, p); pop(S);  //��ջһ�����
		visit(p);    //������
		//�Һ��ӡ�������ջ
		if (p->rchild) push(S, p->rchild);
		if (p->lchild) push(S, p->lchild);
	}
}

void post_dfs(BiNode* root, void(*visit)(BiNode*)) {
	BiNode* p;
	SqStack S; init(S, 10);            //�½�һ����ջ
	SqStack R; init(R, 10);            //�½�һ����ջ
	push(S, root);  //�������ջS
	while (!empty(S)) {  //ֻҪջS����
		top(S, p); pop(S);  //��ջһ�����
		//visit(p);    //������
		push(R, p);
		//�Һ��ӡ�������ջ		
		if (p->lchild) push(S, p->lchild);
		if (p->rchild) push(S, p->rchild);
	}
	while (!empty(R)) {
		top(R, p); pop(R);  //��ջһ�����
		visit(p);    //������
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
	IOT(T, print);  /*��������������*/
	printf("\n");
	PreOT(T, print);  /*��������������*/
	printf("\n");
	PostOT(T, leafs);  /*��������������*/
	printf("Ҷ�ӽ�������:%d\n", num);

	LevelOrderTraverse(T, print);
	num = 0;
	LevelOrderTraverse(T, leafs);
	printf("Ҷ�ӽ�������:%d\n", num);

	BiNode *t2 = clone(T);
	IOT(t2, print);  /*��������������*/
	printf("\n");
	PreOT(t2, print);  /*��������������*/
	printf("\n");
	LevelOrderTraverse(t2, print);

	if(is_same(t2,T))
		printf("t2��T�����������\n");

	BiNode *t3 = newNode();    t3->data = 'A';
	t3->lchild = newNode();   t3->lchild->data = 'B';
	t3->rchild = newNode();   t3->rchild->data = 'C';
	if (is_same(t2,t3))
		printf("t2��t3�����������\n");
	else 
		printf("t2��t3�ǲ���ȵ�2��������\n");
#if 0
	BiNode* t4 = PreOrderCreatBiTree();
	PreOT(t4, print);  /*��������������*/
	printf("\n");
#endif
	InOrderTraverse_(t2, print);
	printf("\n");

	pre_dfs(t2, print);
	printf("\n");

	PostOT(t2, print);  /*��������������*/
	printf("\n");
	post_dfs(t2, print);
	printf("\n");
}
#endif 
