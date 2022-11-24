#include "base.h"

void checknode(Node*, int, int*);

void main() {
	Node n1 = {0, }, n2 = { 0, }, n3 = { 0, }, n4 = { 0, }, n5 = { 0, };
	Node node[5] = { n1, n2, n3, n4, n5 };
	int depth = 0;
	int count = 0;

	checknode(node, depth, &count);

	return 0;
}

void checknode(Node* node, int depth, int* pcount) {
	(*pcount)++;
	int a, b, c, d, e;
	if (promising(node, depth)) {
		depth++;				//promising�ϴٸ� ���� ���̷� �̵�
		if (depth > 5)			//��� Ư¡�� ä��� ���ǵ� �����ϸ� ��� ���
			print_node(node, *pcount);
		else {					//�ߺ��� ���Բ� Ư¡ �Ҵ�
			for (a = 0;a < 5;a++)
				for (b = 0;b < 5;b++)
					for (c = 0;c < 5;c++)
						for (d = 0;d < 5;d++)
							for (e = 0;e < 5;e++)
								if(allocate_node(node, depth, a, b, c, d, e))
									checknode(node, depth, pcount);
		}
	}
}