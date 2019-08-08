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
#include <stdio.h>
#include <malloc.h>

typedef struct  {
	int parent,rank;
}disjoint_set_node;
typedef disjoint_set_node ds_node;

typedef struct {
	disjoint_set_node *forest;
	int n;
}disjoint_set;

int init_disjoint_set(disjoint_set *ds,const int n) {
	ds->forest =(ds_node*)malloc(n * sizeof(ds_node));
	if (!ds->forest) return 0;
	ds->n = n;
	for (int i = 0; i != n; i++) {
		ds->forest[i].parent = i;     // MAKE_SET(i)
		ds->forest[i].rank = 0;
	}
	return 1;
}

int find(disjoint_set ds,int x) {
	if (x == ds.forest[x].parent) return x;
	int p = ds.forest[x].parent;
	while (p != ds.forest[p].parent) {
		p = ds.forest[p].parent;
	}	
	return p;
}

int merge(disjoint_set *ds,int x, int  y) {
	x = find(*ds,x);
	y = find(*ds,y);

	if (ds->forest[x].rank > ds->forest[y].rank) {
		ds->forest[y].parent = x; return x;
	}
	else if (ds->forest[x].rank < ds->forest[y].rank) {
		ds->forest[x].parent = y; return y;
	}
	else { // x��rank==y��rank
		ds->forest[x].parent = y;
		++(ds->forest[y].rank);	  return y;
	}
}

typedef char ElemT;
int value_to_index(ElemT x) {
	return x - 'a';
}
int find(disjoint_set ds, ElemT x) {
	return find(ds,value_to_index(x));
}
int merge(disjoint_set *ds, ElemT x, ElemT  y) {
	return merge(ds, value_to_index(x), value_to_index(y));
}
void test_disjoint_set() {
	disjoint_set ds;
	init_disjoint_set(&ds, 5);
	merge(&ds, 'a', 'b');
	merge(&ds, 'c', 'b');
	merge(&ds, 'd', 'c');
	printf("%d\n", find(ds, 'a'));
	printf("%d\n", find(ds, 'b'));
	printf("%d\n", find(ds, 'c'));
	printf("%d\n", find(ds, 'd'));
	printf("%d\n", find(ds, 'e'));
}

void test_disjoint_set_2() {
/*
	You are given number of nodes, N, and number of edges, 
	M, of a undirected connected graph. After adding each edge, 
	print the size of all the connected components (in increasing order).

Input:
First line contains two integers, N and M, number of nodes and number of edges.
Next M lines contains two integers each, X and Y, 
denoting that there is an edge between X and Y.

Output:
For each edge, print the size of all the connected components 
(in increasing order) after adding that edge.

����
5 4
1 2
3 4
4 5
1 3

�����
1 1 1 2
1 2 2
2 3
5
	*/

	int N, M;
	scanf("%d %d",&N,&M);
	disjoint_set ds;
	init_disjoint_set(&ds, N);
	int *nums = (int *)malloc(N * sizeof(int));

	for (int i = 0; i < M; i++) {
		int u, v;
		printf("������һ����:\n");
		scanf("%d %d", &u, &v);
		u--; v--;   //�����1��ŵģ����Լ�ȥ1
		int root = merge(&ds, u, v); 

		for (int i = 0; i < N; i++) nums[i] = 0;
		for (int i = 0; i < N; i++) {
			int root = find(ds, i);
			nums[root]++;			
		}	
		for (int i = 0; i < N; i++) {			
			if (find(ds, i)==i)printf("%d ", nums[i]);
		}
				
		printf("\n");
	}
}

int main() {
	//test_disjoint_set();
	test_disjoint_set_2();
}