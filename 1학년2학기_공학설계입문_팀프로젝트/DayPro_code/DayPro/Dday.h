typedef struct {
	int year, month, day, total;
	char name[50], memo[100];
}Dday;

Dday User_Dday[10][5];

int LeapYear(int yy) {
	int dd;

	if ((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0)
		dd = 29;
	else
		dd = 28;

	return dd;
}

int Calculation(int yy, int mm, int dd) {
	int total = 0;
	int days[2][12] = { {31,29,31,30,31,30,31,31,30,31,30,31},
		{31,28,31,30,31,30,31,31,30,31,30,31} };

	for (int i = 1;i < yy;i++)
		if (LeapYear(i) == 29)
			total += 366;
		else
			total += 365;

	for (int i = 1;i < mm;i++)
		if (i == 2 && LeapYear(yy) == 29)
			total += days[0][i - 1];
		else
			total += days[1][i - 1];

	total += dd;

	return total;
}

void SaveDday(void) {
	FILE* fp2;
	fp2 = fopen("Dday.txt", "w");
	fwrite(User_Dday, sizeof(User_Dday), 1, fp2);
	fclose(fp2);

	return 0;
}

void ReadDday(void) {
	FILE* fp2;
	fp2 = fopen("Dday.txt", "r");
	fread(User_Dday, sizeof(User_Dday), 1, fp2);
	fclose(fp2);
	return 0;
}