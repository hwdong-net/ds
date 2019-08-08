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
typedef int T;
void print(T a[], const int n) {
	for (int i = 0; i < n; i++)
		printf("%d,", a[i]);
	printf("\n");
}
void print2(T a[], const int l,const int h) {
	for (int i = l; i <=h; i++)
		printf("%d,", a[i]);
	//printf("\n");
}


void insert_sort(T a[], int n) {
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) { //a[i]插入到a[0,...,i-1]
			T t = a[i];  
			a[i] = a[i - 1];
			int j = i - 2;
			for (; j >= 0 && t < a[j];j--) 
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
	//	print(a, n);
	}
}

void binary_insert_sort(T a[], int n) {
	int l, h, m,j;
	for (int i = 1; i < n; i++) {
		T t = a[i];
		if (a[i] < a[i - 1]) {
			l = 0;  h = i - 1;
			while (l <= h) {  //log2i
				m = (l + h) / 2;
				if (t < a[m])
					h = m - 1;
				else
					l = m + 1;
			}
			for (j = i - 1; j >= h + 1; j--)
				a[j + 1] = a[j];
			a[h + 1] = t;
		}
		print(a,n);

	}
}



void shell_pass_sort(T a[], int n,int d) {
	for (int i = d; i < n; i++) {
		if (a[i] < a[i - d]) { //a[i]插入到a[0,...,i-1]
			T t = a[i];
			a[i] = a[i - d];
			int j = i - 2*d;
			for (; j >= 0 && t < a[j]; j-=d)
				a[j + d] = a[j];
			a[j + d] = t;
		}		
	}
}

void shell_sort(T a[], int n) {
	int d[] = { 5,3,1 };
	for (int i = 0; i < 3; i++) {
		shell_pass_sort(a, n, d[i]);
		print(a, n);
	}
}

void Swap(T *a,T *b) {
	T t = *a; *a = *b; *b = t;
}
void swap(T &a, T &b) {
	T t = a; a = b; b = t;
}
void bubble_sort(T a[], int n) {
	for (int i = n - 1; i > 0; i--) {
		int flag = 0;
		for(int j = 0 ;j<i;j++)
			if (a[j + 1] < a[j]) {
			/*	T t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;*/
				//Swap(&a[j + 1], &a[j]);
				swap(a[j + 1], a[j]);
				flag = 1;
		}
		if (flag == 0) break;
		print(a, n);
	}
}

int partition(T a[],int L,int H) {
	T t = a[L];
	while (L < H) {
		while (L < H && !(a[H] < t))
			H--;
		a[L] = a[H];
		while (L < H && a[L] < t)
			L++;
		a[H] = a[L];
	}
	a[L] = t;
	return L;
}

void Qsort(T a[], int L, int H) {
	if (L >= H) return;
	int loc = partition(a, L, H);	
	print2(a, L,H);
	Qsort(a, L, loc - 1);
	Qsort(a, loc+1,H);
}

void quick_sort(T a[], int n) {
	Qsort(a, 0, n - 1);
}
void select_sort(T a[], int n) {
	int ind = 0;
	for (int i = 0; i < n - 1; i++) { //a[i,...n-1]
		ind = i;
		for (int j = i + 1; j < n; j++) 
			if (a[j] < a[ind]) ind = j;
		if (ind != i) 
			swap(a[i], a[ind]);	
		print(a, n);
	}
}

void merge(const T data[],T out[],const int s, const int M, const int N) {
	int i = s,j = M+1,k=s;
	while (i <= M && j <= N) {
		if (data[i] < data[j])
			out[k++] = data[i++];
		else 
			out[k++] = data[j++];
	}
	while(i<=M)out[k++] = data[i++];
	while (j <= N)out[k++] = data[j++];
}

int min(const int a, const int b) {
	return a < b ? a : b;
}

void copy(T A[], T B[], int n) {
	for (int i = 0; i < n; i++)
		B[i] = A[i];
}
void merge_sort_iter(T A[],T B[],int n) {
	for (int width = 1; width < n; width *= 2) {
		for (int i = 0; i < n; i = i + 2 * width)
			merge(A, B, i, i + width - 1, min(i + 2 * width - 1, n - 1));
		copy(B, A, n);	
		print(B, n);
	}
}

void copy2(T A[], T B[], const int s, const int t) {
	for (int i = s; i <=t; i++)
		B[i] = A[i];
}
void merge_sort_recursive(T A[], T B[], const int s, const int t) {
	if (s == t) return;
	merge_sort_recursive(A, B, s, (s + t) / 2);
	merge_sort_recursive(A, B, (s + t) / 2+1 ,t);
	merge(A, B, s, (s + t) / 2, t);
	copy2(B, A, s, t);
	print2(A, s,t);
}

#include <malloc.h>
void bucket_sort(T a[],const int n,const int bucket_num) {
	T minValue = a[0], maxValue = a[0];
	int bucket_n = bucket_num,i,k;
	for (int i = 1; i < n; i++) {
		if (a[i] < minValue) 
			minValue = a[i];
		if (maxValue< a[i]  )
			maxValue = a[i];
	}
	if (bucket_n == 0)
		bucket_n = maxValue - minValue + 1;
	// D= M-m;  D/S+1 = N; S = D/(N-1);
	T  interval = (maxValue - minValue) / (bucket_n-1);
	
	typedef struct {
		T* data; int n,j;
	}Bucket;
	Bucket * buckets = (Bucket *)malloc(bucket_n * sizeof(Bucket));
	for ( i = 0; i < bucket_n; i++) {
		buckets[i].data = 0;
		buckets[i].n = buckets[i].j=  0;
	}
	for ( i = 0; i < n; i++) {
		int b = (a[i] - minValue) / interval;
		buckets[b].n++;
	}
	for (i = 0; i < bucket_n; i++) {
		if(buckets[i].n>0)
		buckets[i].data = (T *)malloc(buckets[i].n * sizeof(T));	
	}
	for (i = 0; i < n; i++) {
		int b = (a[i] - minValue) / interval;
		buckets[b].data[buckets[b].j] = a[i];
		buckets[b].j++;
	}
	
	for (i = 0; i < bucket_n; i++)
		insert_sort(buckets[i].data, buckets[i].n);

	//收集所有桶的元素
	for (i = 0,k = 0; i < bucket_n; i++) {
		for (int j = 0; j < buckets[i].n; j++,k++)
			a[k] = buckets[i].data[j];
	}
	for (i = 0; i < bucket_n; i++)
		free(buckets[i].data);
	free(buckets);
}

//------------heap_sort--------------
void down_adjust(T data[], int s, int n) {
	if (2 * s + 1 >= n) return;
	T t = data[s];   int m = n - 1;
	for (int j = 2 * s + 1; j < n; ) {
		if (j < m && data[j] < data[j + 1])
			j++;  //j指向较大的孩子
		if (!(t < data[j]))  break;
		data[s] = data[j];
		s = j; j = 2 * j + 1;
	}
	data[s] = t;
}

#include <math.h>
void heap_sort(T a[], int n) {
	for (int i = floor((n - 1 - 1) / 2); i >= 0; i--)
		down_adjust(a, i, n );

	printf("建堆的结果是:\n");
	print(a, n);

	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);//将a[0]和a[i]交换
		down_adjust(a, 0, i );
		print2(a, 0, i - 1); 
		printf("[");print2(a, i, n - 1); printf("]\n");
	}
}

int main() {
	int arr[] = { 49,38,65,97,76,13,27 };
	print(arr, 7);
//	insert_sort(arr, 7);	print(arr, 7);
//	binary_insert_sort(arr, 7);	print(arr, 7);
//	shell_sort(arr, 7);	print(arr, 7);
//	bubble_sort(arr, 7);	print(arr, 7);
//	quick_sort(arr, 7);	print(arr, 7);
//	select_sort(arr, 7);	print(arr, 7);

#if 0 
	int data[] = { 8,21,25,25,49,62,72,93,   16,37,54 }; //s=0,M = 7,N=10
	int out[11];
	merge(data, out, 0, 7, 10);
	print2(out,0,10);
#endif 

#if 0
	int out[7];
	merge_sort_iter(arr, out, 7); print(arr, 7);
	merge_sort_recursive(arr, out, 0,6); print(arr, 7);
#endif 

#if 0
	bucket_sort(arr,7,3); 
	print(arr, 7);

	int data[] = { -1, 25, -58964, 8547, -119, 0, 78596 };
	bucket_sort(data, 7, 3);
	print(data, 7);
#endif 
	heap_sort(arr, 7);
	return 0;
}
