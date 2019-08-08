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
typedef int T;
typedef int KeyT;
int linear_search(T a[],const int n,KeyT key,int(*fp)(T e,KeyT key)) {
	for (int i = 0; i < n; i++)
		if (fp(a[i], key))
			return i;
	return -1;
}

int cmp(T e, KeyT key) {
	if (e == key) return 1;
	return 0;
}
int binary_search(T a[], const int n, KeyT key, int(*EQ)(KeyT key, T e),
	int(*LT)(KeyT key,T e)  ) {
	int low = 0,high = n - 1,mid;
	while (low < high) {
		mid = (low + high) / 2;
		if (EQ(key, a[mid])) return mid;
		else if (LT(key, a[mid])) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}

int equal(KeyT key, T e) {
	if (e == key) return 1;
	return 0;
}
int less(T e, KeyT key) {
	if (key<e) return 1;
	return 0;
}

#include <stdio.h>
int main() {
	int arr[] = { 34,25,1,71,19,21,47 };
#if 0
	int ret = linear_search(arr, 7,25, cmp);
	if (ret >= 0)
		printf("查找到元素的下标是:%d\n",ret);
	else printf("查找失败\n");

	ret = linear_search(arr, 7, 13, cmp);
	if (ret >= 0)
		printf("查找到元素的下标是:%d\n", ret);
	else printf("查找失败\n");
#endif

#if 1
	int brr[] = { 1,19,21,25,34,47,71 };
	int ret = binary_search(brr, 7, 25, equal,less);
	if (ret >= 0)
		printf("查找到元素的下标是:%d\n", ret);
	else printf("查找失败\n");

	ret = binary_search(brr, 7, 13, equal, less);
	if (ret >= 0)
		printf("查找到元素的下标是:%d\n", ret);
	else printf("查找失败\n");
#endif

}