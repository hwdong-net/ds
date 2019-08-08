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
#include <malloc.h>
typedef struct {
	char *s;
	int _size;
}String;

int initString(String &S,const char*s0) {
	int len = strlen(s0);
	S.s = (char *)malloc((len + 1) * sizeof(char));
	if (!S.s) return 0;
	S._size = len;
	strcpy(S.s, s0);
	return 1;
}

int getChar(String *S,int i,char *ch) {
	if (i<0||i >= S->_size) return 0;
	*ch = S->s[i]; return 1;
}
int strLen(String S) {
	return S._size;
}
String* strCpy(String *T, String *S) {
	free(T->s);
	initString(*T, S->s);
	return T;	
}
String strCat(String &T, String S) {
	int len = T._size + S._size;
	char *s = (char *)malloc((len + 1) * sizeof(char));
	char *p = s;
	for (int i = 0; i < T._size; i++, p++)
		*p = T.s[i];
	for (int i = 0; i < S._size; i++, p++)
		*p = S.s[i];
	*p = '\0';
	free(T.s);
	T.s = s;
	T._size += S._size;
	return T;
}


int find(String S, String T, int pos) {
	int i = pos, j = 0;
	while (i < S._size && j < T._size) {
		if (S.s[i] == T.s[j]) {    //��ǰ�ַ�ƥ�䣬i,j����
			i++;  j++;
		}
		else {     //����i���ˣ�j����ģʽ���ף����¿�ʼ
			i = i - j + 1;  j = 0;
		}
	}
	if (j >= T._size) return i - j; //ƥ��ɹ�
	else           return 0;         //ʧ��
}



void get_next(String S, int next[]) {
	int j = 0, k = -1;	next[0] = -1;   //�裺j=0, next[j] =k��Ҫ��next[j+1] 
	while (j < S._size - 1) {
		if (k == -1 || S.s[j] == S.s[k]) {
			j++;  k++;  next[j] = k;
		}
		else		k = next[k];
	}
}

int find_KMP(String S, String T, int pos) {
	int *next = (int *)malloc((T._size)*sizeof(int));
	get_next(T, next);

	int i = pos, j = 0;
	while (i < S._size && j < T._size) {
		if (j == -1 || S.s[i] == T.s[j]) {
			i++;		j++;
		}
		else	j = next[j];     //ģʽ������
	}
	if (j >= T._size) {
		free(next);		return i - j; //ƥ��ɹ�
	}
	else {
		free(next);		return 0;        //ʧ��	
	}
}


int main() {
#if 0
	String str;
	char ch;
	initString(str, "hello world");
	for (int i = 0; i < strLen(str); i++) {
		getChar(&str, i, &ch);
		printf("%c", ch);
	}
	printf("\n");

	String T;
	initString(T, "");
	strCpy(&T, &str);

	for (int i = 0; i < strLen(T); i++) {
		getChar(&T, i, &ch);
		printf("%c", ch);
	}
	printf("\n");

	String src;
	initString(src, "world");
	String dst;
	initString(dst, "hello ");
	strCat(dst, src);

	printf("%s\n", dst.s);	
#endif
	String S;
	initString(S, "ABCDECDH");
	String T;
	initString(T, "CD");
//	int ret = find(S, T, 3);
	int ret = find_KMP(S, T, 3);
	if(ret>=0)
		printf("find(S, T, 3)\n%s��%s��λ���ǣ�%d\n", T.s,S.s,ret);
}
