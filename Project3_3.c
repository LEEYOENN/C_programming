#define _CRT_SECURE_NO_WARNINGS
#define MAX_VIDEO 100 
#define MAX_CUST 200 // max customer 
#define MAX_CHAR 100 // ���ڿ��� max ����
#include <stdio.h> 
#include <string.h> 
typedef struct { // ��� ����: ���� �����ϰ� �ִ� Video ���� ����
	char title[MAX_CHAR];
	int qty; // ����
} VideoInfo;
typedef struct { // ���� ����: �����ذ� (�� id�� video id)���� ����
	int custId; // �� id : 1, 2, 3 
	char title[MAX_CHAR]; // Video ����
} RentInfo;
void printAllVideo(VideoInfo videoList[], int videoCount) {
	//����
	int i;
	printf("Video����\t����\n------------------------------\n");
	for (i = 0; i < videoCount; i++) {
		printf("%s\t%d\n", videoList->title, videoList->qty);
		videoList++;
	}
}

VideoInfo* searchVideoByTitle(VideoInfo videoList[], int videoCount, char* title) {
	//����
	int i;
	for (i = 0; i < videoCount; i++) {
		if (strcmp(title, videoList[i].title) == 0) {
			return &videoList[i];

		}
		videoList++;
	}
	return NULL;
}
void purchaseVideo(VideoInfo videoList[], int* videoCountPtr, char* title, int qty) {
	//����
	//int i;
	//for (i = 0; i < *videoCountPtr; i++) {
	//	if (strcmp(title, videoList->title) == 0) {
	//		videoList->qty += qty;
	//		break;
	//	}
	//	else
	//		videoList++;
	//}
	//if (i == *videoCountPtr) {
	//	strcpy(videoList->title, title);
	//	videoList->qty = qty;
	//	*videoCountPtr += 1;
	//}
	VideoInfo* videoPtr = searchVideoByTitle(videoList, *videoCountPtr, title);
	VideoInfo video;

	if (videoPtr == NULL) {
		strcpy(video.title, title);
		video.qty = qty;

		videoList[*videoCountPtr] = video;
		(*videoCountPtr)++;
	}
	else
		videoPtr->qty += qty;


}

void rentVideo(VideoInfo* videoList, int videoCount, RentInfo* rentList, int* rentCount, char* title, int id) {
	//����
	RentInfo rent;
	VideoInfo* videoPtr = searchVideoByTitle(videoList, videoCount, title);
	if (videoPtr != NULL) {
		strcpy(rent.title, title);
		rent.custId = id;

		rentList[*rentCount] = rent;
		(*rentCount)++;
		videoPtr->qty--;
	}
}
void printAllRent(RentInfo rentList[], int rentCount) {
	//����
	int i; printf("��id\tVideo����\n------------------------------\n");
	for (i = 0; i < rentCount; i++) {
		printf("%d\t%s\n", rentList->custId, rentList->title);
		rentList++;

	}
}
/// <FILE>

void readVideo(VideoInfo videoList[], int* videoCountPtr)
{
	FILE* fp;
	VideoInfo video;
	if ((fp = fopen("video.txt", "r")) == NULL) {
		printf("�Է� ���� ���� ����\n"); exit(1);
	}
	// ���� ������ �Է����Ͽ��� �б�
	char buf[30];
	fgets(buf, sizeof(buf), fp);
	while (!feof(fp)) {
		
		fputs(buf, stdout);
		fgets(buf, sizeof(buf), fp);
	}
	fclose(fp);
}
void writeVideo(VideoInfo videoList[], int videoCount)
{
	FILE* fp;
	int i;
	if ((fp = fopen("video.txt", "w")) == NULL) {
		printf("��� ���� ���� ����\n"); exit(1);
	}
	// ���� ������ ��� �������� ����
	for (i = 0; i < videoCount; i++) {
		fprintf(fp, "%s\t%d\n", videoList->title, videoList->qty);
		videoList++;
	}
	fclose(fp);
}
void writeRent(RentInfo rentList[], int rentCount)
{
	FILE* fp;
	int i;
	fp = fopen("rent.txt", "w");
	if (fp == NULL) {
		printf("��� ���� ���� ����\n"); exit(1);
	}
	for (i = 0; i < rentCount; i++)
	{
		fprintf(fp, "%d\t%s\n", rentList->custId, rentList->title);
		rentList++;
	}
	fclose(fp);
}
int main(void)
{
	int videoCount = 5;
	VideoInfo videoList[MAX_VIDEO] = { {"BeforeSunrise", 1}, {"BeforeSunset", 3},
	{"BeforeMidnight", 5}, {"Casablanca", 7}, {"EdgeOfTomorrow", 9} };
	int rentCount = 0; // ���� ���� �Ǽ��� 0��
	RentInfo rentList[MAX_CUST];
	int choice;
	VideoInfo* videoPtr;
	char title[MAX_CHAR];
	int custId, qty;

	//readVideo(videoList, &videoCount);

	printf("1(All Video ���), 2(����), 3(�˻�), 4(�뿩), 5(All �뿩���� ���), 6(����): ");
	scanf("%d", &choice);

	while (choice != 6) {
		switch (choice) {
		case 1: printAllVideo(videoList, videoCount); break;
		case 2:
			printf("Enter video ����: ");
			scanf("%s", title);
			printf("Enter video ����: ");
			scanf("%d", &qty);
			purchaseVideo(videoList, &videoCount, title, qty);
			break;
		case 3:
			printf("Enter video ����: ");
			scanf("%s", title);
			videoPtr = searchVideoByTitle(videoList, videoCount, title);
			if (videoPtr == NULL)
				printf("�׷� ������ �����ϴ�.\n");
			else if (videoPtr->qty != 0)
				printf("�뿩 �����մϴ�.\n");
			else
				printf("�� �뿩�� �Դϴ�.\n");
			break;
		case 4:
			printf("Enter video ����: ");
			scanf("%s", title);
			printf("Enter �� id: ");
			scanf("%d", &custId);
			rentVideo(videoList, videoCount, rentList, &rentCount, title, custId); break;
		case 5:
			printAllRent(rentList, rentCount); break;
		}
		printf("1(All Video ���), 2(����), 3(�˻�), 4(�뿩), 5(All �뿩���� ���), 6(����): ");
		scanf("%d", &choice);
	}
	writeVideo(videoList, videoCount);
	writeRent(rentList, rentCount);
	readVideo(videoList, &videoCount);
}