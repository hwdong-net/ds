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
#include <string.h>
#include<stdlib.h>

void test_c_str() {
	char str[4] = "GfG";                   //����'\0'���ַ���������
	char str2[] = { 'G', 'f', 'G','\0' };  //  '\0' ���ǽ����ַ�
	int ret = strcmp(str, str2);           //�Ƚ�2���ַ����Ƿ����
	printf("%d\n",ret);
	char str3[] = { 'G', 'f','G' };
	printf("%d %d %d \n", strlen(str), strlen(str2), strlen(str3));

//	char str4[3] = ��GfG";  //������4���ַ��ռ�

	printf("%d\n", '\0');	
	char binbuf[32]; //�洢�������ִ��Ŀռ�
	printf("%s\n", _itoa('\0', binbuf, 2)); //���һ������2��ʾ2����
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
	*(str + 1) = 'f';       //�ȼ��� str[1] = 'f';  
	*(str + 2) = 'G';
	*(str + 3) = '\0';
	printf("%s�ĳ�����:%d\n", str, strlen(str));	
}

int strLen(const char *s) {
	const char *p = s;
	while (*p != '\0') p++;
	return p - s;
}
void test_strlen() {
	char str[4] = "GfG";                   //����'\0'���ַ���������
	char str2[] = { 'G', 'f', 'G','\0' };
	printf("%s�ĳ�����:%d\n", str, strLen(str));
	printf("%s�ĳ�����:%d\n", str2, strLen(str2));
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
	//��str2ƴ�ӵ�str1���棬������ƴ�Ӻ���ַ���ָ��
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