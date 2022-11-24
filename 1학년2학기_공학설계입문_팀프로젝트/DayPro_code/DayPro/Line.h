#include <stdio.h>

void HomeLine(void)
{
	printf("\n ");
	for (int i = 0; i < 4;i++)
		printf("┌─────────────┐");
	printf("\n ");
	for (int i = 0; i < 4;i++)
		printf("│             │");
	printf("\n ");

	printf("│    도움말   │");
	printf("│  디데이추가 │");
	printf("│  수정및삭제 │");
	printf("│   문구수정  │");

	printf("\n ");
	for (int i = 0; i < 4;i++)
		printf("│             │");
	printf("\n ");
	for (int i = 0; i < 4;i++)
		printf("└─────────────┘");
	printf("\n ");

	printf("┌");
	for (int i = 0;i < 58;i++)
		printf("─");
	printf("┐");

	for (int k = 0;k < 4;k++) {
		for (int j = 0;j < 5;j++) {
			printf("\n ");
			printf("│");
			for (int i = 0;i < 58;i++)
				printf(" ");
			printf("│");
		}
		printf("\n ");
		printf("├");
		for (int i = 0;i < 58;i++)
			printf("─");
		printf("┤");
	}

	for (int j = 0;j < 5;j++) {
		printf("\n ");
		printf("│");
		for (int i = 0;i < 58;i++)
			printf(" ");
		printf("│");
	}
	printf("\n ");
	printf("└");
	for (int i = 0;i < 58;i++)
		printf("─");
	printf("┘");
	printf("\n ");
}


void Line(void)
{
	for (int i = 0;i < 62;i++)
		printf("━");
	printf("\n");
	for (int i = 0;i < 62;i++)
		printf("─");
	printf("\n");
}