#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BOARD_SIZE 10 // 추후에 10으로 바꾸어서 진행한다
int winCheck(char b[][BOARD_SIZE], int r, int c, char player) {
	int i = 0, cntX = 0, cntO = 0;
	int sum = 1;
	int ri, ci;
	ri = r; ci = c - 1;
	while (ci != -1 && b[ri][ci] == player) {
		sum++;
		ci--;
	}
	ri = r; ci = c + 1;
	while (ci != -1 && b[ri][ci] == player) {
		sum++;
		ci++;
	}
	if (sum == 5)return 1;
	sum = 1;
	ri = r - 1; ci = c;
	while (ri != -1 && b[ri][ci] == player) {
		sum++;
		ri--;
	}
	ri = r + 1; ci = c;
	while (ri != -1 && b[ri][ci] == player) {
		sum++;
		ri++;
	}
	if (sum == 5)return 1;

	sum = 1;
	ri = r - 1; ci = c - 1;
	while (ri != -1 && ci != -1 && b[ri][ci] == player) {
		sum++;
		ri--;
		ci--;
	}
	ri = r + 1; ci = c + 1;
	while (ri != -1 && ci != -1 && b[ri][ci] == player) {
		sum++;
		ri++;
		ci++;
	}
	if (sum == 5)return 1;

	sum = 1;
	ri = r - 1; ci = c + 1;
	while (ri != -1 && ci != -1 && b[ri][ci] == player) {
		sum++;
		ri--;
		ci++;
	}
	ri = r + 1; ci = c - 1;
	while (ri != -1 && ci != -1 && b[ri][ci] == player) {
		sum++;
		ri++;
		ci--;
	}
	if (sum == 5)return 1;




}
void display(char b[][BOARD_SIZE])
{
	char ch;
	int i, j;
	printf("    ");
	for (i = 0; i < BOARD_SIZE; i++)
		printf("%2d", i);
	printf("\n ------------------------\n");
	for (i = 0; i < BOARD_SIZE; i++) {
		printf("%3d |", i);
		for (j = 0; j < BOARD_SIZE; j++)
			printf(" %c", b[i][j]);
		printf("\n");
	}
}
void main()
{
	char board[BOARD_SIZE][BOARD_SIZE];
	char turnX = 'X';
	char turnO = 'O';
	int r, c;
	int i, j;
	int count;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = ' ';
	count = 1;
	display(board);
	do
	{
		printf("Player %c(행 열):", turnX);
		scanf("%d %d", &r, &c);
		if (board[r][c] != ' ')
			while (board[r][c] != ' ') {
				printf("Player %c(행 열):", turnX);
				scanf("%d %d", &r, &c);
			}
		board[r][c] = turnX;
		display(board);
		if (winCheck(board, r, c, turnX) == 1) {
			printf("Player X wins!\n");
			break;
		}
		printf("Player %c(행 열):", turnO);
		scanf("%d %d", &r, &c);
		if (board[r][c] != ' ')
			while (board[r][c] != ' ') {
				printf("Player %c(행 열):", turnO);
				scanf("%d %d", &r, &c);
			}
		board[r][c] = turnO;
		display(board);
		if (winCheck(board, r, c, turnO) == 1) {
			printf("Player O wins!\n");
			break;
		}
		count++;
	} while (count <= BOARD_SIZE * BOARD_SIZE);
	if (count == BOARD_SIZE)
		printf("Nobody wins!");
}