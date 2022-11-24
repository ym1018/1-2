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
	printf("\n   %s\n\n   %s", sentence[22].srt, sentence[23].srt); // "�Է��� ����� �ߴ��� Ȯ�����ּ���." "���͸� ������ ���� ȭ������ ���ư��ϴ�."

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
		printf("%s ��  %d�� %d�� %d��\n", User_Dday[page][line].name, User_Dday[page][line].year, User_Dday[page][line].month, User_Dday[page][line].day);
		COORD XY_2 = { 5,9 + 6 * line };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY_2);
		if (Dday < 0)
			printf("%s %d %s\n", sentence[0].srt, -Dday, sentence[1].srt); // "������" "�� ���ҽ��ϴ�."
		else if (Dday > 0)
			printf("%s %d %s\n", sentence[2].srt, Dday, sentence[3].srt); // "���̷κ���" "�� �������ϴ�."
		else
			printf("%s\n", sentence[4].srt); // "�����Դϴ�."

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

	printf("\n   <����>\n\n   ���� Ű�е带 �̿��� �� ������� �̵��մϴ�.\
\n\n   > 1 ����\n    : ���α׷� ������ �ȳ��մϴ�.\n      ����Ű�� ���� ������ ���ϴ�.\
\n\n   > 2 ���� �߰�\n    : ���ο� ���̸� �߰��մϴ�.\n      ��¥�� �Է��� �� ��/��/�� ������ �����̽� ��\n      Ȥ�� ����Ű�� ���ֽñ� �ٶ��ϴ�.\n      (ex. 2020 01 01)\
\n\n   > 3 ����/����\n    : ���ϴ� ���̸� �����ϰų� �����մϴ�.\n      �Է��� ���̰� ����� �������� ������ ���� �̷����ϴ�.\n      (ex. 1��° ������, 1��° ���ο� �ִ� ����)\
\n\n   > 4 ��������\n    : ���α׷� ���� ������ �����մϴ�. (���� ����)\n      �����ϱ� ���ϴ� ������ ���� ��\n      ������ ������ ���� �Է��ϸ� �˴ϴ�.\n      �ʱ�ȭ�� �� ��� �⺻ ������ ���ư��ϴ�.");

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
	printf("\n   %s\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[5].srt, sentence[6].srt, sentence[19].srt, sentence[20].srt); // "���ϴ� ���̸� �߰��� �� �ֽ��ϴ�." "���̸� �߰��Ͻðڽ��ϱ�?"
	scanf("%d", &d);
	rewind(stdin);

	if (d == 2)
		Home();

	else if (d == 1) {
		system("cls");
		Line();

		printf("   ���� �̸�: ");
		gets(User_Dday[page][arr[page]].name);
		printf("   ���� ��¥ (�� �� ��): ");
		scanf("%d %d %d", &User_Dday[page][arr[page]].year, &User_Dday[page][arr[page]].month, &User_Dday[page][arr[page]].day);
		rewind(stdin);
		printf("   �޸�: ");
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

	printf("\n   %s\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[7].srt, sentence[8].srt, sentence[19].srt, sentence[20].srt); // "���ϴ� ���̸� ���� Ȥ�� �����Ͻ� �� �ֽ��ϴ�." "���̸� ���� Ȥ�� �����Ͻðڽ��ϱ�?"
	scanf("%d", &d);
	rewind(stdin);

	if (d == 2)
		Home();

	else if (d == 1) {
		system("cls");
		Line();

		printf("\n   %s\n\n", sentence[9].srt); // "���� Ȥ�� �����ϱ� ���ϴ� ���̸� �������ּ���."
		printf("   ������: ");
		scanf("%d", &p);
		printf("   ����: ");
		scanf("%d", &l);
		rewind(stdin);

		if (--p > page || --l > arr[page])
			GoToHome();

		printf("\n   %s\n\n", sentence[10].srt); // "���� �����Դϴ�."
		printf("   ���� �̸�: % s\n   ���� ��¥: % d��% d��% d��\n   �޸�: % s\n\n", User_Dday[p][l].name, User_Dday[p][l].year, User_Dday[p][l].month, User_Dday[p][l].day, User_Dday[p][l].memo);

		printf("\n   1. ����  2. ����\n   >> ");
		scanf("%d", &d);
		rewind(stdin);

		if (d == 1) {
			printf("\n   %s\n\n   1. ���� �̸�  2. ���� ��¥  3. �޸�\n   >> ", sentence[11].srt); // "������ ��Ҹ� �������ּ���."
			scanf("%d", &d);
			rewind(stdin);

			printf("\n   %s\n   >> ", sentence[21].srt); // "�������ּ���."
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
			printf("\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[12].srt, sentence[19].srt, sentence[20].srt); // "���� �����Ͻðڽ��ϱ�?"
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

	printf("\n   %s\n   %s\n\n   1. %s  2. %s  3. �����ʱ�ȭ\n   >> ", sentence[13].srt, sentence[14].srt, sentence[19].srt, sentence[20].srt); // "���α׷��� ���� ������ ������� �����Ͻ� �� �ֽ��ϴ�." "������ �ٲٽðڽ��ϱ�?"
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

		printf("\n   %s\n\n   >> ", sentence[15].srt); // "�����ϱ� ���ϴ� ������ �������ּ���."
		scanf_s("%d%*c", &d);
		rewind(stdin);

		if (d > 24)
			GoToHome();

	re:

		printf("\n   %s\n   >> ", sentence[21].srt); // "�������ּ���."
		gets(sentence[d - 1].srt);

		system("cls");
		Line();

		printf("\n   %s\n\n   %s", sentence[16].srt, sentence[d - 1].srt); // "���� ����� �����Դϴ�."
		printf("\n\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[17].srt, sentence[19].srt, sentence[20].srt); // "�ش� ������ �ٽ� �ٲٽðڽ��ϱ�?"
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
		printf("\n   %s\n\n   1. %s  2. %s\n   >> ", sentence[18].srt, sentence[19].srt, sentence[20].srt); // "���� �ʱ�ȭ�Ͻðڽ��ϱ�?"
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
