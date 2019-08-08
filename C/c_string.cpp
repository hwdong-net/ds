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
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void test_c_str() {
	char str[4] = "GfG";                   //包含'\0'的字符串文字量
	char str2[] = { 'G', 'f', 'G','\0' };  //  '\0' 就是结束字符
	int ret = strcmp(str, str2);           //比较2个字符串是否相等
	printf("%d\n",ret);
	char str3[] = { 'G', 'f','G' };
	printf("%d %d %d \n", strlen(str), strlen(str2), strlen(str3));

//	char str4[3] = “GfG";  //错：必须4个字符空间

	printf("%d\n", '\0');	
	char binbuf[32]; //存储二进制字串的空间
	printf("%s\n", _itoa('\0', binbuf, 2)); //最后一个参数2表示2进制
}
void test_c_str1() {
#if 0
	char s[]= { 'G', 'f', 'G','\0' };
	char *p = s;
	char *q = "GfG";
	const char *q2 = "GfG";
	q2[2] = 'A';
	q[2] = 'B';
#endif 
}
void test_c_str2() {
	char *str;
	int size = 4;
	str = (char *)malloc(size * sizeof(char));
	*(str + 0) = 'G';
	*(str + 1) = 'f';       //等价于 str[1] = 'f';  
	*(str + 2) = 'G';
	*(str + 3) = '\0';
	printf("%s的长度是:%d\n", str, strlen(str));	
}

int strLen(const char *s) {
	const char *p = s;
	while (*p != '\0') p++;
	return p - s;
}
void test_strlen() {
	char str[4] = "GfG";                   //包含'\0'的字符串文字量
	char str2[] = { 'G', 'f', 'G','\0' };
	printf("%s的长度是:%d\n", str, strLen(str));
	printf("%s的长度是:%d\n", str2, strLen(str2));
}

char *strCpy(char *dst, const char *src) {
	char *p = dst;
	const char *q = src;
	while (*q) {
		*p = *q;
		p++; q++;
	}
	*p = '\0';
	return dst;
}
void test_strcpy(){
	char str1[] = "hello";
	char str2[40];
	char str3[40];
	strCpy(str2, str1);
	strCpy(str3, "world");
	printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
}
char *strCat(char *dst, const char *src) {
	return dst;
}
void test_strcat() {
	char str1[] = "This is ", str2[] = "a cat";
	//char str1[50], str2[] = "a cat";
	//strcpy(str1, "This is ");
	//将str2拼接到str1后面，并返回拼接后的字符串指针
	strcat(str1, str2);
	puts(str1);
	puts(str2);	
}

#if 0
int main() {
//	test_c_str();
//	test_c_str1();
//	test_c_str2();
//	test_strlen();
	test_strcpy();
//	test_strcat();
}
#endif