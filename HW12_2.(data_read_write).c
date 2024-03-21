#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
int main(void) {

	int state;
	FILE* fp;
	char ch;
	fp = fopen("input.txt", "w");
	if (fp == NULL)
	{
		printf("file open error!\n");
		return 1;
	}
	fprintf(fp, "Near far\nWherever you are\nI believe that the heart does go on\nOnce more, you open the door\n");
	state = fclose(fp);
	if (state != 0) // 이 체크는 생략 가능
	{
		printf("file close error!\n");
		return 1;
	}
	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("file open error!\n");
		return 1;
	}
	FILE* fp1;
	fp1 = fopen("output.txt", "w");
	char buf[30];
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (islower(ch))
			fputc(toupper(ch), fp1);
		else
			fputc(ch, fp1);
	}
	fputs("\n", fp1);
	fseek(fp, 0, SEEK_SET);

	while (!feof(fp)) {
		ch = fgetc(fp);
		if (isupper(ch))
			fputc(tolower(ch), fp1);
		else
			fputc(ch, fp1);
	}
	fclose(fp);
	fclose(fp1);
}