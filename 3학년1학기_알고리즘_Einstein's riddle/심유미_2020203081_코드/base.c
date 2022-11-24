#include "base.h"

bool allocate_node(Node* node, int depth, int a, int b, int c, int d, int e) {
	//�ߺ��Ǵ� ���� �ִٸ� false ��ȯ
	if (a == b || a == c || b == c || a == d || b == d || c == d || a == e || b == e || c == e || d == e)
		return false;

	switch (depth) {
	case 1: //depth�� 1�� ���� nationality�� �Ҵ�� ����
		node[0].nationality = a;	node[1].nationality = b;
		node[2].nationality = c;	node[3].nationality = d;
		node[4].nationality = e;
		return true;

	case 2: //depth�� 2�� ���� colors�� �߰� �Ҵ�� ����
		node[0].colors = a;			node[1].colors = b;
		node[2].colors = c;			node[3].colors = d;
		node[4].colors = e;
		return true;

	case 3: //depth�� 3�� ���� beverage�� �߰� �Ҵ�� ����
		node[0].beverage = a;		node[1].beverage = b;
		node[2].beverage = c;		node[3].beverage = d;
		node[4].beverage = e;
		return true;

	case 4: //depth�� 4�� ���� cigar�� �߰� �Ҵ�� ����
		node[0].cigar = a;			node[1].cigar = b;
		node[2].cigar = c;			node[3].cigar = d;
		node[4].cigar = e;
		return true;

	case 5: //depth�� 5�� ���� pet�� �߰� �Ҵ�� ����
		node[0].pet = a;			node[1].pet = b;
		node[2].pet = c;			node[3].pet = d;
		node[4].pet = e;
		return true;
	}
}

void print_node(Node* node, int count) {
	printf("%-15s %-15s %-15s %-15s %-15s\n", "1��° ��", "2��° ��", "3��° ��", "4��° ��", "5��° ��");
	for (int i = 0; i < 5; i++)
		switch (node[i].colors) {
		case 0:	printf("%15s", "blue");		break;
		case 1: printf("%15s", "green");	break;
		case 2: printf("%15s", "red");		break;
		case 3: printf("%15s", "white");	break;
		case 4: printf("%15s", "yellow");	break;
		}
	printf("\n");
	for (int i = 0; i < 5; i++)
		switch (node[i].nationality) {
		case 0:	printf("%15s", "Brit");		break;
		case 1: printf("%15s", "Dane");		break;
		case 2: printf("%15s", "German");	break;
		case 3: printf("%15s", "Norwegian");break;
		case 4: printf("%15s", "Swede");	break;
		}
	printf("\n");
	for (int i = 0; i < 5; i++)
		switch (node[i].beverage) {
		case 0:	printf("%15s", "beer");		break;
		case 1: printf("%15s", "coffee");	break;
		case 2: printf("%15s", "milk");		break;
		case 3: printf("%15s", "tea");		break;
		case 4: printf("%15s", "water");	break;
		}
	printf("\n");
	for (int i = 0; i < 5; i++)
		switch (node[i].cigar) {
		case 0:	printf("%15s", "Blue Master");	break;
		case 1: printf("%15s", "Dunhill");		break;
		case 2: printf("%15s", "Pall Mall");	break;
		case 3: printf("%15s", "Prince");		break;
		case 4: printf("%15s", "Blend");		break;
		}
	printf("\n");
	for (int i = 0; i < 5; i++)
		switch (node[i].pet) {
		case 0:	printf("%15s", "cat");		break;
		case 1: printf("%15s", "bird");		break;
		case 2: printf("%15s", "dog");		break;
		case 3: printf("%15s", "fish");		break;
		case 4: printf("%15s", "horse");	break;
		}
	printf("\n\n> Ž���� ��� ��: %d\n\n", count);
}

bool promising(Node* node, int depth) {
	switch (depth) {
	//�ƹ� �͵� �Ҵ����� ����, root ���
	case 0: return true;	break;

	case 1:	//nationality �Ҵ� ��, ��Ʈ 9 Ȯ��
		//Hint 9�� �������� ���ϸ� Non-promising, false ��ȯ
		if (!hint9(node))	return false;
		break;

	case 2:	//colors �Ҵ� ��, ��Ʈ 14, 1 Ȯ��
		//Hint 1, 14�� �������� ���ϸ� Non-promising, false ��ȯ
		if (!hint14(node))	return false;
		if (!hint1(node))	return false;
		break;

	case 3:	//beverage �Ҵ� ��, ��Ʈ 8, 3, 5, 4 Ȯ��
		//Hint 3, 4, 5, 8�� �������� ���ϸ� Non-promising, false ��ȯ
		if (!hint8(node))	return false;
		if (!hint3(node))	return false;
		if (!hint5(node))	return false;
		if (!hint4(node))	return false;
		break;

	case 4:	//cigar �Ҵ� ��, ��Ʈ 7, 12, 13, 15 Ȯ��
		//Hint 7, 12, 13, 15�� �������� ���ϸ� Non-promising, false ��ȯ
		if (!hint7(node))	return false;
		if (!hint12(node))	return false;
		if (!hint13(node))	return false;
		if (!hint15(node))	return false;
		break;

	case 5:	//pet �Ҵ� ��, ��Ʈ 2, 6, 10, 11 Ȯ��
		//Hint 2, 6, 10, 11�� �������� ���ϸ� Non-promising, false ��ȯ
		if (!hint2(node))	return false;
		if (!hint6(node))	return false;
		if (!hint10(node))	return false;
		if (!hint11(node))	return false;
		break;
	}
	return true;
}

bool hint1(Node* node) { //The Brit lives in a red house.
	int Bri_loc, R_loc;
	//�������� ��� ���� ������ ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Brit)	Bri_loc = location;
		if (node[location].colors == red)		R_loc = location;
	}
	//�������� ��� ���� ������ ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (Bri_loc == R_loc)	return true;
	return false;
}
bool hint2(Node* node) { //The Swede keeps dogs as pets.
	int Swe_loc, dog_loc;
	//���������� ��� ���� ���� Ű��� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Swede)	Swe_loc = location;
		if (node[location].pet == dog)				dog_loc = location;
	}
	//���������� ��� ���� ���� Ű��� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (Swe_loc == dog_loc)	return true;
	return false;
}
bool hint3(Node* node) { //The Dane drinks tea.
	int Dan_loc, tea_loc;
	//����ũ���� ��� ���� ���� ���ô� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Dane)		Dan_loc = location;
		if (node[location].beverage == tea)			tea_loc = location;
	}
	//����ũ���� ��� ���� ���� ���ô� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (Dan_loc == tea_loc)	return true;
	return false;
}
bool hint4(Node* node) { //The green house is on the left of the white house
	int G_loc, W_loc;
	//�ʷϻ� ���� �Ͼ�� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].colors == green)		G_loc = location;
		if (node[location].colors == white)		W_loc = location;
	}
	//�Ͼ�� �� ���ʿ� �ʷϻ� ���� ������ true ��ȯ, �ƴϸ� false ��ȯ
	if (W_loc - G_loc == 1)	return true;
	return false;
}
bool hint5(Node* node) { //The green house owner drinks coffee.
	int G_loc, coffee_loc;
	//�ʷϻ� ���� Ŀ�Ǹ� ���ô� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].colors == green)		G_loc = location;
		if (node[location].beverage == coffee)	coffee_loc = location;
	}
	//�ʷϻ� ���� Ŀ�Ǹ� ���ô� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (G_loc == coffee_loc)	return true;
	return false;
}
bool hint6(Node* node) { //The person who smokes Pall Mall rears birds.
	int PM_loc, bird_loc;
	//Pall Mall�� �ǿ�� ���� ���� Ű��� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Pall_Mall)	PM_loc = location;
		if (node[location].pet == bird)			bird_loc = location;
	}
	//Pall Mall�� �ǿ�� ���� ���� Ű��� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (PM_loc == bird_loc)	return true;
	return false;
}
bool hint7(Node* node) { //The owner of the yellow house smokes Dunhill.
	int Y_loc, DH_loc;
	//����� ���� Dunhill�� �ǿ�� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].colors == yellow)	Y_loc = location;
		if (node[location].cigar == Dunhill)	DH_loc = location;
	}
	//����� ���� Dunhill�� �ǿ�� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (Y_loc == DH_loc)	return true;
	return false;
}
bool hint8(Node* node) { //The man living in the house right in the center drinks milk.
	//��� �� ������ ������ ���ø� true ��ȯ, �ƴϸ� false ��ȯ
	if (node[2].beverage == milk)	return true;
	return false;
}
bool hint9(Node node[]) { //The Norwegian lives in the first(leftmost) house.
	//�� ���� ������ �븣�������̶�� true ��ȯ, �ƴϸ� false ��ȯ
	if(node[0].nationality == Norwegian)	return true;
	return false;
}
bool hint10(Node* node) { //The man who smokes Blend lives next to the one who keeps cats.
	int BD_loc, cat_loc;
	//Blend�� �ǿ�� ���� ����̸� Ű��� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Blend)	BD_loc = location;
		if (node[location].pet == cat)		cat_loc = location;
	}
	//Blend�� �ǿ�� ���� ����̸� Ű��� ���� ���� �����̸� true ��ȯ, �ƴϸ� false ��ȯ
	if (BD_loc - cat_loc == 1 || cat_loc - BD_loc == 1)	return true;
	return false;

}
bool hint11(Node* node) { //The man who keeps horses lives next to the man who smokes Dunhill.
	int DH_loc, horse_loc;
	//Dunhill�� �ǿ�� ���� ���� Ű��� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Dunhill)	DH_loc = location;
		if (node[location].pet == horse)		horse_loc = location;
	}
	//Dunhill�� �ǿ�� ���� ���� Ű��� ���� ���� �����̸� true ��ȯ, �ƴϸ� false ��ȯ
	if (DH_loc - horse_loc == 1 || horse_loc - DH_loc == 1)	return true;
	return false;
}
bool hint12(Node* node) { //The owner who smokes Blue Master drinks beer.
	int BM_loc, beer_loc;
	//Blue Master�� �ǿ�� ���� ���ָ� ���ô� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Blue_Master)	BM_loc = location;
		if (node[location].beverage == beer)		beer_loc = location;
	}
	//Blue Master�� �ǿ�� ���� ���ָ� ���ô� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (BM_loc == beer_loc)	return true;
	return false;
}
bool hint13(Node* node) { //The German smokes Prince.
	int Ger_loc, PC_loc;
	//�������� ��� ���� Prince�� �ǿ�� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == German)	Ger_loc = location;
		if (node[location].cigar == Prince)			PC_loc = location;
	}
	//�������� ��� ���� Prince�� �ǿ�� ���� ���� ��ġ�� true ��ȯ, �ƴϸ� false ��ȯ
	if (Ger_loc == PC_loc)	return true;
	return false;
}
bool hint14(Node* node) { //The Norwegian lives next to the blue house.
	int Nor_loc, B_loc;
	//�븣�������� ��� ���� �Ķ��� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Norwegian)	Nor_loc = location;
		if (node[location].colors == blue)				B_loc = location;
	}
	//�븣�������� ��� ���� �Ķ��� ���� ���� �����̸� true ��ȯ, �ƴϸ� false ��ȯ
	if(Nor_loc - B_loc == 1 || B_loc - Nor_loc == 1)	return true;
	return false;
}
bool hint15(Node* node) { //The man who smokes Blend has a neighbor who drinks water.
	int BD_loc, water_loc;
	//Blend�� �ǿ�� ���� ���� ���ô� ���� ��ġ�� ã��
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Blend)		BD_loc = location;
		if (node[location].beverage == water)	water_loc = location;
	}
	//Blend�� �ǿ�� ���� ���� ���ô� ���� ���� �����̸� true ��ȯ, �ƴϸ� false ��ȯ
	if (BD_loc - water_loc == 1 || water_loc - BD_loc == 1)	return true;
	return false;
}