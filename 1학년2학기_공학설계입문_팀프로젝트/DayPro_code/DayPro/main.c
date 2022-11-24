#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>

#include "Line.h"
#include "Dday.h"
#include "Sentence.h"

void Advice(void);
void Home(void);
void Add_Dday(void);
void Modify(void);
void Custom_Phrase(void);

void GoToHome(void) {
	printf("\n   %s\n\n   %s", sentence[22].srt, sentence[23].srt); // "입력을 제대로 했는지 확인해주세요." "엔터를 누르면 메인 화면으로 돌아갑니다."

	while (1) {
		int key;
		if (_kbhit()) {
			key = _getch();

			if (key == 13)
				Home();
		}
	}
}

int page = 0, arr[10];

void main(void)
{
	system("COLOR F0");
	system("mode con: cols=63 lines=40");

	ReadDday();
	Sentence_r();

	for (int i = 0;i < 10;i++)
		for (int k = 0;k < 5;k++)
			if (User_Dday[i][k].year != 0) {
				arr[page]++;
				if (arr[page] > 4) {
					page++;
					if (page > 9)
						page = 9;
				}
			}

	Advice();
}

void Home(void) {
reset:
	system("cls");
	HomeLine();

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	int now = Calculation(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

	COORD Page = { 28,38 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Page);
	printf("%d / 10", page + 1);

	for (int line = 0;line < arr[page];line++) {
		User_Dday[page][line].total = Calculation(User_Dday[page][line].year, User_Dday[page][line].month, User_Dday[page][line].day);
		int Dday = now - User_Dday[page][line].total;

		COORD XY_1 = { 5,8 + 6 * line };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY_1);
		printf("%s │  %d년 %d월 %d일\n", User_Dday[page][line].name, User_Dday[page][line].year, User_Dday[page][line].month, User_Dday[page][line].day);
		COORD XY_2 = { 5,9 + 6 * line };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY_2);
		if (Dday < 0)
			printf("%s %d %s\n", sentence[0].srt, -Dday, sentence[1].srt); // "앞으로" "일 남았습니다."
		else if (Dday > 0)
			printf("%s %d %s\n", sentence[2].srt, Dday, sentence[3].srt); // "디데이로부터" "일 지났습니다."
		else
			printf("%s\n", sentence[4].srt); // "디데이입니다."

		COORD XY_3 = { 5,10 + 6 * line };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY_3);
		printf("%s", User_Dday[page][line].memo);
	}

	while (1) {
		int key;
		if (_kbhit()) {
			key = _getch();

			if (key == 49)
				Advice();
			else if (key == 50)
				Add_Dday();
			else if (key == 51)
				Modify();
			else if (key == 52)
				Custom_Phrase();

			if (key == 77) {
				page++;
				if (page > 9)
					page = 9;
				goto reset;

			}
			else if (key == 75) {
				page--;
				if (page < 0)
					page = 0;
				goto reset;
			}
		}
	}
}

void Advice(void) {
	system("cls");
	Line();

	printf("\n   <도움말>\n\n   숫자 키패드를 이용해 각 기능으로 이동합니다.\
\n\n   > 1 도움말\n    : 프로그램 사용법을 안내합니다.\n      엔터키를 눌러 도움말을 끕니다.\
\n\n   > 2 디데이 추가\n    : 새로운 디데이를 추가합니다.\n      날짜를 입력할 때 년/월/일 구분을 스페이스 바\n      혹은 엔터키로 해주시길 바랍니다.\n      (ex. 2020 01 01)\
\n\n   > 3 수정/삭제\n    : 원하는 디데이를 수정하거나 삭제합니다.\n      입력은 디데이가 저장된 페이지와 라인을 통해 이뤄집니다.\n      (ex. 1번째 페이지, 1번째 라인에 있는 디데이)\
\n\n   > 4 문구수정\n    : 프로그램 내의 문구를 수정합니다. (도움말 제외)\n      수정하길 원하는 문구를 선택 후\n      수정된 문구를 직접 입력하면 됩니다.\n      초기화를 할 경우 기본 문구로 돌아갑니다.");

	while (1) {
		int key;
		if (_kbhit()) {
			key = _getch();
			if (key == 13)
				Home();
		}
	}
}

void Add_Dday(void) {
	system("cls");
	int d;

	if (arr[page] > 4) {
		page++;
		if (page > 9) {
			page = 9;
			Home();
		}
	}

	Line();
	printf("\n   %s\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[5].srt, sentence[6].srt, sentence[19].srt, sentence[20].srt); // "원하는 디데이를 추가할 수 있습니다." "디데이를 추가하시겠습니까?"
	scanf("%d", &d);
	rewind(stdin);

	if (d == 2)
		Home();

	else if (d == 1) {
		system("cls");
		Line();

		printf("   디데이 이름: ");
		gets(User_Dday[page][arr[page]].name);
		printf("   디데이 날짜 (년 월 일): ");
		scanf("%d %d %d", &User_Dday[page][arr[page]].year, &User_Dday[page][arr[page]].month, &User_Dday[page][arr[page]].day);
		rewind(stdin);
		printf("   메모: ");
		gets(User_Dday[page][arr[page]].memo);

		SaveDday(arr[page]);

		arr[page]++;
		Home();
	}

	else
		GoToHome();
}

void Modify(void) {
	system("cls");
	Line();
	int p, l, d;

	printf("\n   %s\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[7].srt, sentence[8].srt, sentence[19].srt, sentence[20].srt); // "원하는 디데이를 수정 혹은 삭제하실 수 있습니다." "디데이를 수정 혹은 삭제하시겠습니까?"
	scanf("%d", &d);
	rewind(stdin);

	if (d == 2)
		Home();

	else if (d == 1) {
		system("cls");
		Line();

		printf("\n   %s\n\n", sentence[9].srt); // "수정 혹은 삭제하길 원하는 디데이를 선택해주세요."
		printf("   페이지: ");
		scanf("%d", &p);
		printf("   라인: ");
		scanf("%d", &l);
		rewind(stdin);

		if (--p > page || --l > arr[page])
			GoToHome();

		printf("\n   %s\n\n", sentence[10].srt); // "디데이 정보입니다."
		printf("   디데이 이름: % s\n   디데이 날짜: % d년% d월% d일\n   메모: % s\n\n", User_Dday[p][l].name, User_Dday[p][l].year, User_Dday[p][l].month, User_Dday[p][l].day, User_Dday[p][l].memo);

		printf("\n   1. 수정  2. 삭제\n   >> ");
		scanf("%d", &d);
		rewind(stdin);

		if (d == 1) {
			printf("\n   %s\n\n   1. 디데이 이름  2. 디데이 날짜  3. 메모\n   >> ", sentence[11].srt); // "수정할 요소를 선택해주세요."
			scanf("%d", &d);
			rewind(stdin);

			printf("\n   %s\n   >> ", sentence[21].srt); // "수정해주세요."
			if (d == 1)
				gets(User_Dday[p][l].name);
			else if (d == 2) {
				scanf("%d %d %d", &User_Dday[page][arr[page] - 1].year, &User_Dday[page][arr[page] - 1].month, &User_Dday[page][arr[page] - 1].day);
				rewind(stdin);
			}
			else if (d == 3)
				gets(User_Dday[p][l].memo);

			SaveDday(arr[page]);

			Home();
		}

		else if (d == 2) {
			printf("\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[12].srt, sentence[19].srt, sentence[20].srt); // "정말 삭제하시겠습니까?"
			scanf("%d", &d);
			rewind(stdin);

			if (d == 1) {
				for (int i = 10;i > 0;i--)
					if (arr[i] != 0)
						page = i;

				int num = ((page + 1) * 5 + arr[page] + 1) - ((p + 1) * 5 + l + 1);

				for (int k = 0;k < num;k++) {
					if (0 <= l < 4) {
						strcpy(User_Dday[p][l].name, User_Dday[p][l + 1].name);
						User_Dday[p][l].year = User_Dday[p][l + 1].year;
						User_Dday[p][l].month = User_Dday[p][l + 1].month;
						User_Dday[p][l].day = User_Dday[p][l + 1].day;
						strcpy(User_Dday[p][l].memo, User_Dday[p][l + 1].memo);
						User_Dday[p][l].total = User_Dday[p][l + 1].total;

						l++;
					}
					else if (l == 4) {
						strcpy(User_Dday[p][l].name, User_Dday[l + 1][0].name);
						User_Dday[p][l].year = User_Dday[l + 1][0].year;
						User_Dday[p][l].month = User_Dday[l + 1][0].month;
						User_Dday[p][l].day = User_Dday[l + 1][0].day;
						strcpy(User_Dday[p][l].memo, User_Dday[l + 1][0].memo);
						User_Dday[p][l].total = User_Dday[l + 1][0].total;
						l = 0;
						p++;
					}
				}

				if (arr[page] != 0)
					arr[page]--;
				else
					page--;

				SaveDday();
				Home();
			}
			else if (d == 2)
				Home();
		}
	}
}

void Custom_Phrase(void) {
	system("cls");
	Line();
	int d;

	printf("\n   %s\n   %s\n\n   1. %s  2. %s  3. 문구초기화\n   >> ", sentence[13].srt, sentence[14].srt, sentence[19].srt, sentence[20].srt); // "프로그램의 각종 문구를 마음대로 변경하실 수 있습니다." "문구를 바꾸시겠습니까?"
	scanf_s("%d%*c", &d);
	rewind(stdin);

	if (d == 2)
		Home();

	else if (d == 1) {
		system("cls");
		Line();

		for (int i = 0; i < 24; i++)
		{
			printf("   %d. ", i + 1);
			puts(sentence[i].srt);
		}

		printf("\n   %s\n\n   >> ", sentence[15].srt); // "변경하길 원하는 문구를 선택해주세요."
		scanf_s("%d%*c", &d);
		rewind(stdin);

		if (d > 24)
			GoToHome();

	re:

		printf("\n   %s\n   >> ", sentence[21].srt); // "수정해주세요."
		gets(sentence[d - 1].srt);

		system("cls");
		Line();

		printf("\n   %s\n\n   %s", sentence[16].srt, sentence[d - 1].srt); // "새로 변경된 문구입니다."
		printf("\n\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[17].srt, sentence[19].srt, sentence[20].srt); // "해당 문구를 다시 바꾸시겠습니까?"
		scanf_s("%d%*c", &d);
		rewind(stdin);

		if (d == 1)
			goto re;
		else if (d == 2) {
			Sentence_w();
			Home();
		}
	}

	else if (d == 3) {
		printf("\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[18].srt, sentence[19].srt, sentence[20].srt); // "정말 초기화하시겠습니까?"
		scanf("%d", &d);

		if (d == 1)
			for (int i = 0; i < 21; i++)
				for (int j = 0; j < 100; j++)
					sentence[i].srt[j] = Ori_sentence[i].srt[j];

		Sentence_w();
		Home();
	}

	else
		GoToHome();
}
