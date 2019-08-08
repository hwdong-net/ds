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
typedef int T;
typedef struct binode {
	T data;
	struct binode *lchild, *rchild;	
}BiNode;

BiNode* newTNode(T e) {
	BiNode* p = (BiNode*)malloc(sizeof(BiNode));
	if (!p) return 0;
	p->data = e;
	p->lchild = p->rchild = 0;	
	return p;
}

BiNode* SearchBST(BiNode* root, T key) {
	if (!root) return 0; //递归出口

	if (root->data == key) return root;    //处理根
	if (key < root->data)                 //左子树        
		return SearchBST(root->lchild, key);
	else                             //右子树
		return SearchBST(root->rchild, key);
}

BiNode* SearchBST_(BiNode* root, T key) {
	BiNode* p = root;

	while (p&&p->data != key)
		if (key < p->data)                 //左子树        
			p = p->lchild;
		else                             //右子树
			p = p->rchild;
	if (!p) return 0;
	return p;
}

BiNode* InsertBST(BiNode* root, T e) {
	if (root == 0) {
		return newTNode(e);
	}
	if (e < root->data)          //左子树
		root->lchild = InsertBST(root->lchild, e);
	else if (e > root->data)     //右子树
		root->rchild = InsertBST(root->rchild, e);
	return root;
}

BiNode* InsertBST_(BiNode* root, T e) {
	BiNode* p = root, *parent = 0;
	while (p&&p->data != e) {
		parent = p;
		if (e < p->data) p = p->lchild;               //左子树        
		else          p = p->rchild;               //右子树
	}
	if (p)   return 0;
	if (!parent) return newTNode(e);
	else if (e < parent->data) {
		parent->lchild = newTNode(e); return parent->lchild;
	}
	else { parent->rchild = newTNode(e); return parent->rchild; }
}

BiNode* deleteBST(BiNode*root, T e) {
	if (!root)       return 0;
	if (e < root->data)
		root->lchild = deleteBST(root->lchild, e);
	else if (e > root->data)
		root->rchild = deleteBST(root->rchild, e);
	else {
		if (!root->lchild && !root->rchild) {
			free(root); return 0;
		}
		else if (!root->rchild) {  //1个孩子
			BiNode *ret = root->lchild;
			free(root); return ret;
		}
		else if (!root->lchild) {  //1个孩子
			BiNode *ret = root->rchild;
			free(root); return ret;
		}
		else { //2个孩子
			BiNode *tmp = root->rchild;
			while (tmp->lchild)
				tmp = tmp->lchild;

			root->data = tmp->data;
			root->rchild =
				deleteBST(root->rchild, root->data);
			return root;
		}
	}
}
	



void PreOT(BiNode* p) {
	if (!p) return;
	printf("%d ", p->data);
	PreOT(p->lchild);
	PreOT(p->rchild);
}
void IOT(BiNode* p) {
	if (!p) return;
	IOT(p->lchild);
	printf("%d ", p->data);	
	IOT(p->rchild);
}
void PostOT(BiNode* p) {
	if (!p) return;	
	PostOT(p->lchild);
	PostOT(p->rchild);
	printf("%d ", p->data);
}
int main() {
#if 0
	/*                 30
					  /  \
					 20   40
					/  \
				   17  25
	*/
	BiNode *root = newTNode(30); 
	root->lchild = newTNode(20);  
	root->rchild = newTNode(40);  
	BiNode *p = root->lchild;
	p->lchild = newTNode(17);  
	p->rchild = newTNode(25);

	PreOT(root); printf("\n");
	IOT(root); printf("\n");


	if (SearchBST_(root, 17))
		printf("查找到了17\n");
	else printf("未找到17\n");

	if (SearchBST_(root, 23))
		printf("查找到了23\n");
	else printf("未找到23\n");
#endif
	BiNode* t = 0;
	t = InsertBST_(t, 30);
	InsertBST_(t, 20);
	InsertBST_(t, 38);
	InsertBST_(t, 19);

	PreOT(t); printf("\n");
	IOT(t); printf("\n");

	if (SearchBST_(t, 30))
		printf("查找到了30\n");
	else printf("未找到30\n");

	deleteBST(t, 20);
	PreOT(t); printf("\n");
	IOT(t); printf("\n");

	deleteBST(t, 30);
	PreOT(t); printf("\n");
	IOT(t); printf("\n");

}
