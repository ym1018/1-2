#define CRT_SECURE_NO_WARNINGS
#include "std_lib_facilities.h"
#include <stdlib.h>

typedef struct Hanoi {
	vector <vector<int>> V_towers = { {},{},{} };
	int moving = 1, size, sel1, sel2;
}Hanoi;

void StartGame(void);
void PrintTowers(Hanoi*);
void GetAnswer(Hanoi*);
int IsMoveAllowed(Hanoi*);
void MoveDisk(int, int, Hanoi*);
bool CheckTowers(Hanoi*);

void main() {
	StartGame();
}

void StartGame(void) {
	Hanoi H;
	bool B = false;
	int temp = 0;

	system("cls"); //ȭ�� Ŭ���� (stdlib.h)
	cout << "\n�ϳ��� ž �⺻���� ���� '1'��, �������� ���� '2'���� �����ּ���.\n=> ";

	while (temp == 0) {
		cin >> temp;

		if (temp == 1)
			H.size = 3;
		else if (temp == 2) {
			cout << "\nHow many towers you want? : ";
			cin >> H.size;
		}
		else {
			cout << "�߸��� ���Դϴ�. �ٽ� �Է����ּ���.\n=> ";
			temp == 0;
		}
	}

	//�ϳ��� �ʱ� ����
	for (int i = 0;i < 3;i++)
		for (int j = H.size;j > 0;j--) {
			if (i == 0)
				H.V_towers[i].push_back(j);
			else
				H.V_towers[i].push_back(0);
		}

	while (B != true) {
		PrintTowers(&H);
		GetAnswer(&H);
		IsMoveAllowed(&H);
		B = CheckTowers(&H);
	}
}

void PrintTowers(Hanoi* P) {
	for (int i = 0;i < 3;i++) {
		cout << "\n[" << i + 1 << "]";
		for (int x : P->V_towers[i])
			if (x != 0)
				cout << " " << x;
	}
}

void GetAnswer(Hanoi* P) {
	cout << "\n\n[" << P->moving << "] From which tower will you move a disk to which tower? (from = [1 | 2 | 3], to = [1 | 2 | 3]) : ";
	cin >> P->sel1 >> P->sel2;
}

int IsMoveAllowed(Hanoi* P) {
	int max1 = -1, max2 = -1;
	P->sel1 -= 1;
	P->sel2 -= 1;

	if (0 > P->sel1 || P->sel1 > 2 || 0 > P->sel2 || P->sel2 > 2) { //�������� �ʴ� �ڸ� ����
		cerr << "=> Move failed!\n";
		return 0;
	}
	else if (P->sel1 == P->sel2 || P->V_towers[P->sel1][0] == 0) { //���� ĭ ���� �Ǵ� ���� ���� �ڸ��� ���� �������� ����
		cerr << "=> Move failed!\n";
		return 0;
	}

	//�� �ڸ��� ���� ���� �ִ� �� Ȯ��
	for (int x : P->V_towers[P->sel1])
		if (x != 0)
			max1++;
	for (int x : P->V_towers[P->sel2])
		if (x != 0)
			max2++;

	if (max2 != -1 && P->V_towers[P->sel1][max1] > P->V_towers[P->sel2][max2]) //���� �� ���� ū ���� �ö�
		cerr << "=> Move failed!\n";
	else
		MoveDisk(max1, max2 + 1, P);
}

void MoveDisk(int max1, int max2, Hanoi* P) {
	P->V_towers[P->sel2][max2] = P->V_towers[P->sel1][max1];
	P->V_towers[P->sel1][max1] = 0;
	P->moving++;
	cout << "=> Move succeeded!\n";
}

bool CheckTowers(Hanoi* P) {
	char temp = '0';

	for (int i = 0;i < P->size;i++)
		if (P->V_towers[2][i] != P->size - i)
			return false;

	PrintTowers(P);
	cout << "\n\nCongratulation! You solved it in " << P->moving - 1 << " moves! \n";
	while (temp != 'Y' && temp != 'N') {
		cout << "Do you want to play again? (Y/N): ";
		cin >> temp;

		if (temp == 'Y')
			StartGame();
		else if (temp == 'N')
			return true;
		else
			cerr << "worng answer!\n\n";
	}
}