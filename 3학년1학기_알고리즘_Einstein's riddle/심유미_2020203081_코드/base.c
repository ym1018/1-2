#include "base.h"

bool allocate_node(Node* node, int depth, int a, int b, int c, int d, int e) {
	//중복되는 값이 있다면 false 반환
	if (a == b || a == c || b == c || a == d || b == d || c == d || a == e || b == e || c == e || d == e)
		return false;

	switch (depth) {
	case 1: //depth가 1인 노드는 nationality가 할당된 상태
		node[0].nationality = a;	node[1].nationality = b;
		node[2].nationality = c;	node[3].nationality = d;
		node[4].nationality = e;
		return true;

	case 2: //depth가 2인 노드는 colors가 추가 할당된 상태
		node[0].colors = a;			node[1].colors = b;
		node[2].colors = c;			node[3].colors = d;
		node[4].colors = e;
		return true;

	case 3: //depth가 3인 노드는 beverage가 추가 할당된 상태
		node[0].beverage = a;		node[1].beverage = b;
		node[2].beverage = c;		node[3].beverage = d;
		node[4].beverage = e;
		return true;

	case 4: //depth가 4인 노드는 cigar가 추가 할당된 상태
		node[0].cigar = a;			node[1].cigar = b;
		node[2].cigar = c;			node[3].cigar = d;
		node[4].cigar = e;
		return true;

	case 5: //depth가 5인 노드는 pet이 추가 할당된 상태
		node[0].pet = a;			node[1].pet = b;
		node[2].pet = c;			node[3].pet = d;
		node[4].pet = e;
		return true;
	}
}

void print_node(Node* node, int count) {
	printf("%-15s %-15s %-15s %-15s %-15s\n", "1번째 집", "2번째 집", "3번째 집", "4번째 집", "5번째 집");
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
	printf("\n\n> 탐색한 노드 수: %d\n\n", count);
}

bool promising(Node* node, int depth) {
	switch (depth) {
	//아무 것도 할당하지 않은, root 노드
	case 0: return true;	break;

	case 1:	//nationality 할당 후, 힌트 9 확인
		//Hint 9를 만족하지 못하면 Non-promising, false 반환
		if (!hint9(node))	return false;
		break;

	case 2:	//colors 할당 후, 힌트 14, 1 확인
		//Hint 1, 14를 만족하지 못하면 Non-promising, false 반환
		if (!hint14(node))	return false;
		if (!hint1(node))	return false;
		break;

	case 3:	//beverage 할당 후, 힌트 8, 3, 5, 4 확인
		//Hint 3, 4, 5, 8을 만족하지 못하면 Non-promising, false 반환
		if (!hint8(node))	return false;
		if (!hint3(node))	return false;
		if (!hint5(node))	return false;
		if (!hint4(node))	return false;
		break;

	case 4:	//cigar 할당 후, 힌트 7, 12, 13, 15 확인
		//Hint 7, 12, 13, 15를 만족하지 못하면 Non-promising, false 반환
		if (!hint7(node))	return false;
		if (!hint12(node))	return false;
		if (!hint13(node))	return false;
		if (!hint15(node))	return false;
		break;

	case 5:	//pet 할당 후, 힌트 2, 6, 10, 11 확인
		//Hint 2, 6, 10, 11을 만족하지 못하면 Non-promising, false 반환
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
	//영국인이 사는 집과 빨간색 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Brit)	Bri_loc = location;
		if (node[location].colors == red)		R_loc = location;
	}
	//영국인이 사는 집과 빨간색 집이 같은 위치면 true 반환, 아니면 false 반환
	if (Bri_loc == R_loc)	return true;
	return false;
}
bool hint2(Node* node) { //The Swede keeps dogs as pets.
	int Swe_loc, dog_loc;
	//스웨덴인이 사는 집과 개를 키우는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Swede)	Swe_loc = location;
		if (node[location].pet == dog)				dog_loc = location;
	}
	//스웨덴인이 사는 집과 개를 키우는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (Swe_loc == dog_loc)	return true;
	return false;
}
bool hint3(Node* node) { //The Dane drinks tea.
	int Dan_loc, tea_loc;
	//덴마크인이 사는 집과 차를 마시는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Dane)		Dan_loc = location;
		if (node[location].beverage == tea)			tea_loc = location;
	}
	//덴마크인이 사는 집과 차를 마시는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (Dan_loc == tea_loc)	return true;
	return false;
}
bool hint4(Node* node) { //The green house is on the left of the white house
	int G_loc, W_loc;
	//초록색 집과 하얀색 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].colors == green)		G_loc = location;
		if (node[location].colors == white)		W_loc = location;
	}
	//하얀색 집 왼쪽에 초록색 집이 있으면 true 반환, 아니면 false 반환
	if (W_loc - G_loc == 1)	return true;
	return false;
}
bool hint5(Node* node) { //The green house owner drinks coffee.
	int G_loc, coffee_loc;
	//초록색 집과 커피를 마시는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].colors == green)		G_loc = location;
		if (node[location].beverage == coffee)	coffee_loc = location;
	}
	//초록색 집과 커피를 마시는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (G_loc == coffee_loc)	return true;
	return false;
}
bool hint6(Node* node) { //The person who smokes Pall Mall rears birds.
	int PM_loc, bird_loc;
	//Pall Mall을 피우는 집과 새를 키우는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Pall_Mall)	PM_loc = location;
		if (node[location].pet == bird)			bird_loc = location;
	}
	//Pall Mall을 피우는 집과 새를 키우는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (PM_loc == bird_loc)	return true;
	return false;
}
bool hint7(Node* node) { //The owner of the yellow house smokes Dunhill.
	int Y_loc, DH_loc;
	//노란색 집과 Dunhill을 피우는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].colors == yellow)	Y_loc = location;
		if (node[location].cigar == Dunhill)	DH_loc = location;
	}
	//노란색 집과 Dunhill을 피우는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (Y_loc == DH_loc)	return true;
	return false;
}
bool hint8(Node* node) { //The man living in the house right in the center drinks milk.
	//가운데 집 주인이 우유를 마시면 true 반환, 아니면 false 반환
	if (node[2].beverage == milk)	return true;
	return false;
}
bool hint9(Node node[]) { //The Norwegian lives in the first(leftmost) house.
	//맨 앞집 주인이 노르웨이인이라면 true 반환, 아니면 false 반환
	if(node[0].nationality == Norwegian)	return true;
	return false;
}
bool hint10(Node* node) { //The man who smokes Blend lives next to the one who keeps cats.
	int BD_loc, cat_loc;
	//Blend를 피우는 집과 고양이를 키우는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Blend)	BD_loc = location;
		if (node[location].pet == cat)		cat_loc = location;
	}
	//Blend를 피우는 집과 고양이를 키우는 집이 옆집 사이이면 true 반환, 아니면 false 반환
	if (BD_loc - cat_loc == 1 || cat_loc - BD_loc == 1)	return true;
	return false;

}
bool hint11(Node* node) { //The man who keeps horses lives next to the man who smokes Dunhill.
	int DH_loc, horse_loc;
	//Dunhill을 피우는 집과 말을 키우는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Dunhill)	DH_loc = location;
		if (node[location].pet == horse)		horse_loc = location;
	}
	//Dunhill을 피우는 집과 말을 키우는 집이 옆집 사이이면 true 반환, 아니면 false 반환
	if (DH_loc - horse_loc == 1 || horse_loc - DH_loc == 1)	return true;
	return false;
}
bool hint12(Node* node) { //The owner who smokes Blue Master drinks beer.
	int BM_loc, beer_loc;
	//Blue Master를 피우는 집과 맥주를 마시는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Blue_Master)	BM_loc = location;
		if (node[location].beverage == beer)		beer_loc = location;
	}
	//Blue Master를 피우는 집과 맥주를 마시는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (BM_loc == beer_loc)	return true;
	return false;
}
bool hint13(Node* node) { //The German smokes Prince.
	int Ger_loc, PC_loc;
	//독일인이 사는 집과 Prince를 피우는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == German)	Ger_loc = location;
		if (node[location].cigar == Prince)			PC_loc = location;
	}
	//독일인이 사는 집과 Prince를 피우는 집이 같은 위치면 true 반환, 아니면 false 반환
	if (Ger_loc == PC_loc)	return true;
	return false;
}
bool hint14(Node* node) { //The Norwegian lives next to the blue house.
	int Nor_loc, B_loc;
	//노르웨이인이 사는 집과 파란색 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].nationality == Norwegian)	Nor_loc = location;
		if (node[location].colors == blue)				B_loc = location;
	}
	//노르웨이인이 사는 집과 파란색 집이 옆집 사이이면 true 반환, 아니면 false 반환
	if(Nor_loc - B_loc == 1 || B_loc - Nor_loc == 1)	return true;
	return false;
}
bool hint15(Node* node) { //The man who smokes Blend has a neighbor who drinks water.
	int BD_loc, water_loc;
	//Blend를 피우는 집과 물을 마시는 집의 위치를 찾고
	for (int location = 0; location <= 4; location++) {
		if (node[location].cigar == Blend)		BD_loc = location;
		if (node[location].beverage == water)	water_loc = location;
	}
	//Blend를 피우는 집과 물을 마시는 집이 옆집 사이이면 true 반환, 아니면 false 반환
	if (BD_loc - water_loc == 1 || water_loc - BD_loc == 1)	return true;
	return false;
}