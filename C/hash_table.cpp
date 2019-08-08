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
	//�½�������hashT.table[hash_address]��ָʾ���������ǰ��
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
			if (!pre) //pָ�����������׽��
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





