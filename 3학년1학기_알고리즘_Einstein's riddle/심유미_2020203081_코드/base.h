#include <stdbool.h>
#include <stdio.h>

typedef enum bese_col { blue = 0, green, red, white, yellow } bese_col;
typedef enum bese_nat { Brit = 0, Dane, German, Norwegian, Swede } bese_nat;
typedef enum bese_bev { beer = 0, coffee, milk, tea, water } bese_bev;
typedef enum bese_cig { Blue_Master = 0, Dunhill, Pall_Mall, Prince, Blend } bese_cig;
typedef enum bese_pet { cat = 0, bird, dog, fish, horse } bese_pet;

typedef struct Node { //각 집마다의 특징
    bese_col colors;
    bese_nat nationality;
    bese_bev beverage;
    bese_cig cigar;
    bese_pet pet;
} Node;

bool allocate_node(Node*, int, int, int, int, int, int); //깊이에 따라 노드에 특징 추가 할당
void print_node(Node*, int); //모든 조건을 만족하는 노드 출력
bool promising(Node*, int); //특징을 할당할 때마다 관련된 힌트 확인

bool hint1(Node*); //영국인은 빨간 집에 산다.
bool hint2(Node*); //스웨덴인은 개를 애완동물로 기른다.
bool hint3(Node*); //덴마크인은 차를 마신다.
bool hint4(Node*); //초록 집은 하얀 집의 왼쪽에 있다.
bool hint5(Node*); //초록 집 주인은 커피를 마신다.
bool hint6(Node*); //Pall Mall을 피우는 사람은 새를 키운다.
bool hint7(Node*); //노란 집 주인은 Dunhill을 피운다.
bool hint8(Node*); //바로 중앙에 있는 집 주인은 우유를 마신다.
bool hint9(Node*); //노르웨이인은 맨 앞집에 산다.
bool hint10(Node*); //Blend를 피우는 사람은 고양이를 키우는 사람 옆에 산다.
bool hint11(Node*); //말을 기르는 사람은 Dunhill을 피우는 사람 옆에 산다.
bool hint12(Node*); //Blue Master 담배를 피우는 주인은 맥주를 마신다.
bool hint13(Node*); //독일인은 Prince를 피운다.
bool hint14(Node*); //노르웨이 사람은 파란 집 옆에 산다.
bool hint15(Node*); //Blend를 피우는 남자는 물을 마시는 이웃이 있다.