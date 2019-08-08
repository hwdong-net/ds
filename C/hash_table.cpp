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

#include <stdio.h>
#include <malloc.h>
typedef int KeyT;
typedef double ValueT;
typedef struct hash_node {
	KeyT key;
	ValueT value;
	struct hash_node *next;
}HashNode;

HashNode* newHashNode(KeyT key, ValueT value) {
	HashNode* p = (HashNode*)malloc(sizeof(HashNode));
	if (!p) return 0;
	p->key = key;
	p->value = value;
	p->next = 0;
	return p;
}

typedef struct  {
	HashNode * *table;
	int size;
}HashTable;

int InitHashTable(HashTable *hashT,int size) {
	hashT->table = (HashNode* *)malloc(size * sizeof(HashNode*));
	if (!hashT->table) return 0;

	hashT->size = size;	
	for (int i = 0; i < hashT->size; i++)
		hashT->table[i] = 0;
	return 1;
}

int  Hash(KeyT key,const int size){ return key%size; }

int InsertHashTable(HashTable *hashT, KeyT key, ValueT value) {
	HashNode* p = newHashNode(key, value);
	if (!p) return 0;	
	int hash_address = Hash(key,hashT->size);
	//新结点插入在hashT.table[hash_address]所指示的链表的最前面
	p->next = hashT->table[hash_address];
	hashT->table[hash_address] = p;
	return 1;
}

int FindHashTable(HashTable hashT,KeyT key,ValueT& value){
	int hash_address = Hash(key, hashT.size);
	HashNode* p = hashT.table[hash_address];
	while (p) {
		if (p->key == key) {
			value = p->value; return 1;
		}
		p = p->next;
	}
	return 0;
}

int DeleteHashTable(HashTable *hashT, KeyT key) {
	int hash_address = Hash(key, hashT->size);
	HashNode* p = hashT->table[hash_address];
	HashNode* pre = 0;
	if (!p) return 0;
	while (p) {
		if (p->key == key) {
			if (!pre) //p指向的是链表的首结点
				hashT->table[hash_address] = p->next;
			else 
				pre->next = p->next;			
			free(p);	return 1;
		}
		pre = p;
		p = p->next;
	}
	return 0;
}

void DisplayHashTable(HashTable *hashT) {
	for (int i = 0; i < hashT->size; i++) {
		printf("hash address %d:", i);
		HashNode* p = hashT->table[i];
		while (p) {
			printf("->(%d,%lf)", p->key, p->value);
			p = p->next;
		}
		printf("\n");
	}
	printf("\n");
}

void HashTable_test() {
	HashTable hT; 
	KeyT key;
	ValueT e; 
	InitHashTable(&hT,7);
	key = 2134;  e = 10.5;  InsertHashTable(&hT, key, e);
	key = 34;  e = 20.5;    InsertHashTable(&hT, key, e);
	key = 25;  e = 30.5;    InsertHashTable(&hT, key, e);
	
	DisplayHashTable(&hT);

	key = 20;
	if (FindHashTable(hT, key, e))      
		printf("the value of key %d is %lf\n",key, e);    
	else printf("can't find the key %d\n", key);
	key = 25;
	if (FindHashTable(hT, key, e))   
		printf("the value of key %d is %lf\n",key, e);
	else printf("can't find the key %d\n", key);

	DeleteHashTable(&hT,25);
	DisplayHashTable(&hT);
}


int main() {
	HashTable_test();
	return 0;
}





