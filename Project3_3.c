#define _CRT_SECURE_NO_WARNINGS
#define MAX_VIDEO 100 
#define MAX_CUST 200 // max customer 
#define MAX_CHAR 100 // 문자열의 max 문자
#include <stdio.h> 
#include <string.h> 
typedef struct { // 재고 대장: 현재 보유하고 있는 Video 정보 저장
	char title[MAX_CHAR];
	int qty; // 수량
} VideoInfo;
typedef struct { // 대출 대장: 대출해간 (고객 id와 video id)들을 저장
	int custId; // 고객 id : 1, 2, 3 
	char title[MAX_CHAR]; // Video 제목
} RentInfo;
void printAllVideo(VideoInfo videoList[], int videoCount) {
	//구현
	int i;
	printf("Video제목\t수량\n------------------------------\n");
	for (i = 0; i < videoCount; i++) {
		printf("%s\t%d\n", videoList->title, videoList->qty);
		videoList++;
	}
}

VideoInfo* searchVideoByTitle(VideoInfo videoList[], int videoCount, char* title) {
	//구현
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
	//구현
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
	//구현
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
	//구현
	int i; printf("고객id\tVideo제목\n------------------------------\n");
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
		printf("입력 파일 오픈 실패\n"); exit(1);
	}
	// 비디오 정보를 입력파일에서 읽기
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
		printf("출력 파일 오픈 실패\n"); exit(1);
	}
	// 비디오 정보를 출력 파일으로 쓰기
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
		printf("출력 파일 오픈 실패\n"); exit(1);
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
	int rentCount = 0; // 현재 대출 건수는 0임
	RentInfo rentList[MAX_CUST];
	int choice;
	VideoInfo* videoPtr;
	char title[MAX_CHAR];
	int custId, qty;

	//readVideo(videoList, &videoCount);

	printf("1(All Video 출력), 2(구입), 3(검색), 4(대여), 5(All 대여정보 출력), 6(종료): ");
	scanf("%d", &choice);

	while (choice != 6) {
		switch (choice) {
		case 1: printAllVideo(videoList, videoCount); break;
		case 2:
			printf("Enter video 제목: ");
			scanf("%s", title);
			printf("Enter video 수량: ");
			scanf("%d", &qty);
			purchaseVideo(videoList, &videoCount, title, qty);
			break;
		case 3:
			printf("Enter video 제목: ");
			scanf("%s", title);
			videoPtr = searchVideoByTitle(videoList, videoCount, title);
			if (videoPtr == NULL)
				printf("그런 비디오는 없습니다.\n");
			else if (videoPtr->qty != 0)
				printf("대여 가능합니다.\n");
			else
				printf("다 대여중 입니다.\n");
			break;
		case 4:
			printf("Enter video 제목: ");
			scanf("%s", title);
			printf("Enter 고객 id: ");
			scanf("%d", &custId);
			rentVideo(videoList, videoCount, rentList, &rentCount, title, custId); break;
		case 5:
			printAllRent(rentList, rentCount); break;
		}
		printf("1(All Video 출력), 2(구입), 3(검색), 4(대여), 5(All 대여정보 출력), 6(종료): ");
		scanf("%d", &choice);
	}
	writeVideo(videoList, videoCount);
	writeRent(rentList, rentCount);
	readVideo(videoList, &videoCount);
}