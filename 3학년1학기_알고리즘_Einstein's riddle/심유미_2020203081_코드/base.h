#include <stdbool.h>
#include <stdio.h>

typedef enum bese_col { blue = 0, green, red, white, yellow } bese_col;
typedef enum bese_nat { Brit = 0, Dane, German, Norwegian, Swede } bese_nat;
typedef enum bese_bev { beer = 0, coffee, milk, tea, water } bese_bev;
typedef enum bese_cig { Blue_Master = 0, Dunhill, Pall_Mall, Prince, Blend } bese_cig;
typedef enum bese_pet { cat = 0, bird, dog, fish, horse } bese_pet;

typedef struct Node { //�� �������� Ư¡
    bese_col colors;
    bese_nat nationality;
    bese_bev beverage;
    bese_cig cigar;
    bese_pet pet;
} Node;

bool allocate_node(Node*, int, int, int, int, int, int); //���̿� ���� ��忡 Ư¡ �߰� �Ҵ�
void print_node(Node*, int); //��� ������ �����ϴ� ��� ���
bool promising(Node*, int); //Ư¡�� �Ҵ��� ������ ���õ� ��Ʈ Ȯ��

bool hint1(Node*); //�������� ���� ���� ���.
bool hint2(Node*); //���������� ���� �ֿϵ����� �⸥��.
bool hint3(Node*); //����ũ���� ���� ���Ŵ�.
bool hint4(Node*); //�ʷ� ���� �Ͼ� ���� ���ʿ� �ִ�.
bool hint5(Node*); //�ʷ� �� ������ Ŀ�Ǹ� ���Ŵ�.
bool hint6(Node*); //Pall Mall�� �ǿ�� ����� ���� Ű���.
bool hint7(Node*); //��� �� ������ Dunhill�� �ǿ��.
bool hint8(Node*); //�ٷ� �߾ӿ� �ִ� �� ������ ������ ���Ŵ�.
bool hint9(Node*); //�븣�������� �� ������ ���.
bool hint10(Node*); //Blend�� �ǿ�� ����� ����̸� Ű��� ��� ���� ���.
bool hint11(Node*); //���� �⸣�� ����� Dunhill�� �ǿ�� ��� ���� ���.
bool hint12(Node*); //Blue Master ��踦 �ǿ�� ������ ���ָ� ���Ŵ�.
bool hint13(Node*); //�������� Prince�� �ǿ��.
bool hint14(Node*); //�븣���� ����� �Ķ� �� ���� ���.
bool hint15(Node*); //Blend�� �ǿ�� ���ڴ� ���� ���ô� �̿��� �ִ�.