#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
template <class Item, class SizeType>
class set {
public:
	//생성자 & 파괴자
	set() {
		data_count = 0;
		child_count = 0;
	}
	~set() {
		delete data;
		delete subset;
	}

	//특정 값 유무 판단
	int count(Item target);

	//Btree에 새로운 값 추가
	bool insert(Item entry, set<Item, SizeType>*& root);
	bool loose_insert(Item entry);
	void fix_excess(set<Item, SizeType>* parent, set<Item, SizeType>*& sub);

	//Btree에서 특정 값 삭제
	bool erase(Item target, set<Item, SizeType>*& root);
	bool loose_erase(Item target);
	void fix_shortage(set<Item, SizeType>* root, Item i);
	Item remove_biggest(SizeType i, set<Item, SizeType>* root);

	//Btree 출력
	void print(set<Item, SizeType>* root, SizeType depth);

private:
	static const SizeType MINIMUM = 1;				//노드 당 최소 데이터 수
	static const SizeType MAXIMUM = 2 * MINIMUM;	//노드 당 최대 데이터 수
	SizeType data_count;							//현재 데이터 수
	Item data[MAXIMUM + 1];							//데이터 값 배열
	SizeType child_count;							//자식 가리키는 포인터 개수
	set* subset[MAXIMUM + 2];						//자식 가리키는 포인터 배열
};

template <class Item, class SizeType>
int set<Item, SizeType>::count(Item target) {
	//Post: set에 target이 있으면 1, 없으면 0 반환

	//루트에서 data[i]>=target 인 첫 번째 i 값 찾기
	SizeType i = 0;
	for (;i < data_count;i++)
		if (data[i] >= target)
			break;
	//없으면 i=data_count
	if (i == data_count - 1 && data[i] < target)
		i = data_count;

	//data[i]에 target이 있을 경우
	if (data[i] == target)
		return 1;
	//data[i]에 자식이 없을 경우(leaf인 경우)
	else if (child_count == 0)
		return 0;
	//왼쪽 하위트리로 재귀 호출
	else
		return subset[i]->count(target);
}

template <class Item, class SizeType>
bool set<Item, SizeType>::insert(Item entry, set<Item, SizeType>*& root) {
	//Post: 규칙에 맞춰 Btree에 값 한 개 추가

	//값 추가 실패했을 경우
	if (!loose_insert(entry))
		return false;
	//루트의 데이터가 MAXIMUM 이상일 때
	if (data_count > MAXIMUM) {
		set<Item, SizeType>* r = new set<int, size_t>();
		fix_excess(r, root);
		root = r;
		return true;
	}
}

template <class Item, class SizeType>
bool set<Item, SizeType>::loose_insert(Item entry) {
	//Post: Btree에 값 한 개 추가 (MAXIMUM+1 허용)

	//루트에서 data[i]>=entry 인 첫 번째 i 값 찾기
	SizeType i = 0;
	for (;i < data_count;i++)
		if (data[i] >= entry)
			break;
	//없으면 i=data_count
	if (i == data_count - 1 && data[i] < entry)
		i = data_count;

	//data[i]에 entry가 이미 있을 경우
	if (data[i] == entry)
		return false;
	//data[i]에 자식이 없을 경우
	else if (child_count == 0) {
		//i 번째 이후의 모든 값 한 칸씩 옮기기
		for (SizeType j = data_count;j > i;j--)
			data[j] = data[j - 1];
		//data[i]에 entry 추가
		data[i] = entry;
		data_count++;
		return true;
	}
	//data[i]에 자식이 있을 경우
	else {
		SizeType size = subset[i]->data_count;
		//재귀 호출
		bool b = subset[i]->loose_insert(entry);
		//subset[i]의 루트에 새로운 값이 추가됐다면 subset[i] 조정
		if (size != subset[i]->data_count && subset[i]->data_count > subset[i]->MAXIMUM)
			fix_excess(this, subset[i]);
		return b;
	}
}

template <class Item, class SizeType>
void set<Item, SizeType>::fix_excess(set<Item, SizeType>* parent, set<Item, SizeType>*& sub) {
	//Post: 노드 데이터 개수 조정

	//MAXIMUM + 1개의 항목을 가지는 노드를 두 개의 노드로 분할
	set<Item, SizeType>* a = new set<int, size_t>();
	set<Item, SizeType>* b = new set<int, size_t>();
	for (SizeType i = 0; i < sub->MAXIMUM / 2;i++) {
		a->insert(sub->data[i], a);
		if (sub->child_count) {
			a->subset[i] = sub->subset[i];
			a->child_count++;
		}
	}
	if (sub->child_count) {
		a->subset[sub->MAXIMUM / 2] = sub->subset[sub->MAXIMUM / 2];
		a->child_count++;
	}

	for (SizeType i = (sub->MAXIMUM / 2) + 1; i < sub->data_count;i++) {
		b->insert(sub->data[i], b);
		if (sub->child_count) {
			b->subset[i - (sub->MAXIMUM / 2 + 1)] = sub->subset[i];
			b->child_count++;
		}
	}
	if (sub->child_count) {
		b->subset[b->child_count] = sub->subset[sub->child_count - 1];
		b->child_count++;
	}

	//중간 entry는 상위 항목으로 이동
	Item entry = sub->data[sub->MAXIMUM / 2];
	//트리 전체의 루트가 바뀌는 경우
	if (parent->data_count == 0) {
		parent->data[0] = entry;
		parent->data_count++;
		parent->subset[0] = a;
		parent->subset[1] = b;
		parent->child_count += 2;
	}
	//parent에 값을 추가할 때 (MAXIMUM+1 허용)
	else if (parent->data_count != 0) {
		//parent에서 data[i]>=entry 인 첫 번째 i 값 찾기
		SizeType i = 0;
		for (;i < parent->data_count;i++)
			if (parent->data[i] >= entry)
				break;
		//없으면 parent 마지막에 추가
		if (i == parent->data_count - 1 && parent->data[i] < entry)
			parent->data[data_count] = entry;
		else {
			//i 번째 이후의 모든 data 값 한 칸씩 옮기기
			for (SizeType j = parent->data_count;j > i;j--)
				parent->data[j] = parent->data[j - 1];
			for (SizeType j = parent->child_count;j > i;j--)
				parent->subset[j] = parent->subset[j - 1];
			//data[i]에 entry 추가
			parent->data[i] = entry;
		}
		parent->data_count++;
		parent->subset[i] = a;
		parent->subset[i + 1] = b;
		parent->child_count++;
		//parent의 data가 MAXIMUM 이상이 될 경우
		if (parent->data_count > parent->MAXIMUM) {
			set<Item, SizeType>* r = new set<int, size_t>();
			fix_excess(r, parent);
			parent = r;
		}
	}
}

template <class Item, class SizeType>
bool set<Item, SizeType>::erase(Item target, set<Item, SizeType>*& root) {
	//Post: 규칙에 맞춰 Btree에서 값 하나 제거

	//제거 실패한 경우
	if (!loose_erase(target))
		return false;
	//제거 후 조정 필요한 경우
	for (SizeType j = 0;j < child_count;j++) {
		if (subset[j]->data_count == 0)
			fix_shortage(this, j);
	}
	if (data_count == 0 && child_count == 1)
		root = subset[0];	//트리의 루트 조정

	return true;
}

template <class Item, class SizeType>
bool set<Item, SizeType>::loose_erase(Item target) {
	//Post: Btree에서 값 하나 제거 (MINIMUM-1 허용)

	//루트에서 data[i]>=entry 인 첫 번째 i 값 찾기
	SizeType i = 0;
	for (;i < data_count;i++)
		if (data[i] >= target)
			break;
	//없으면 i=data_count
	if (i == data_count - 1 && data[i] < target)
		i = data_count;

	//루트에 자식이 없고
	if (child_count == 0) {
		//target을 못 찾은 경우
		if (data[i] != target || i == data_count)
			return false;
		//target을 찾은 경우 data 어레이에서 target 제거
		else if (data[i] == target) {
			for (Item j = i;j < data_count - 1;j++)
				data[j] = data[j + 1];
			data_count--;
			return true;
		}
	}
	else { //루트에 자식이 있고
		//target을 못 찾은 경우
		if (data[i] != target || i == data_count) {
			bool b = subset[i]->loose_erase(target);
			//제거 실패한 경우
			if (!b)
				return false;
			//제거 성공한 경우
			else {
				if (subset[i]->data_count == 0)
					child_count--;
				if (subset[i]->data_count == MINIMUM - 1) {
					fix_shortage(this, i);
					return true;
				}
			}
		}
		//target을 찾은 경우 가장 큰 값으로 대체
		else if (data[i] == target) {
			data[i] = remove_biggest(i, this);
			//필요한 경우 노드 조정
			if (subset[i]->data_count < MINIMUM)
				fix_shortage(this, i);
			return true;
		}
	}
}

template <class Item, class SizeType>
void set<Item, SizeType>::fix_shortage(set<Item, SizeType>* root, Item i) {
	//Post: 노드 데이터 개수 조정

	SizeType j;
	set<Item, SizeType>* targetSub = root->subset[i];

	if (i > 0) {
		set<Item, SizeType>* preSub = root->subset[i - 1];

		//Case1: MINIMUM보다 많이 가지고 있는 subset[i - 1]에서 추가 entry 전송
		if (preSub->data_count > MINIMUM) {
			//subset[i]의 데이터 오른쪽으로 한 칸씩 옮기고
			for (j = targetSub->data_count;j > 0;j--)
				targetSub->data[j] = targetSub->data[j - 1];
			//data[i - 1]을 subset[i]->data의 앞으로 이동
			if (targetSub->data_count == 0)
				root->child_count++;
			targetSub->data[0] = root->data[i - 1];
			//subset[i - 1]->data의 마지막 값으로 data[i - 1] 대체
			root->data[i - 1] = preSub->data[preSub->data_count - 1];
			//subset[i - 1]에 자식이 있으면 마지막 자식을 subset[i] 앞으로
			if (preSub->child_count != 0) {
				//subset[i]의 자식 오른쪽으로 한 칸씩 옮기고
				for (j = targetSub->child_count;j > 0;j--)
					targetSub->subset[j] = targetSub->subset[j - 1];
				//subset[i - 1] 마지막 자식을 subset[i] 앞으로
				targetSub->subset[0] = preSub->subset[preSub->child_count - 1];
				targetSub->child_count++;
				preSub->child_count--;
			}
			targetSub->data_count++;
			preSub->data_count--;
		}

		//Case3: MINIMUM - 1을 가진 subset[i]와 MINIMUM을 가진 subset[i - 1] 결합
		else if (targetSub->data_count == MINIMUM - 1 && preSub->data_count == MINIMUM) {
			//data[i - 1]를 subset[i - 1]->data 끝으로 이동
			preSub->data[preSub->data_count++] = root->data[i - 1];
			//subset[i]의 모든 값과 자식을 subset[i - 1]의 끝으로 이동
			for (j = 0;j < targetSub->data_count;j++)
				preSub->data[preSub->data_count++] = targetSub->data[j];
			if (targetSub->child_count != 0)
				for (j = 0;j < targetSub->child_count;j++)
					preSub->subset[preSub->child_count++] = targetSub->subset[j];
			//subset[i + 1], subset[i + 2], … 왼쪽으로 한 칸씩 이동
			for (j = i + 1;j < root->child_count;j++)
				root->subset[j - 1] = root->subset[j];
			root->data_count--;
		}
	}

	else if (i <= root->data_count - 1) {
		set<Item, SizeType>* postSub = root->subset[i + 1];

		//Case2: MINIMUM보다 많이 가지고 있는 subset[i + 1]에서 추가 entry 전송
		if (postSub->data_count > MINIMUM) {
			//data[i]을 subset[i]->data의 끝으로 이동
			if (targetSub->data_count == 0)
				root->child_count++;
			targetSub->data[targetSub->data_count] = root->data[i];
			//subset[i + 1]->data의 첫 번째 값으로 data[i] 대체
			root->data[i] = postSub->data[0];
			//subset[i + 1]->data 데이터 왼쪽으로 한 칸씩
			for (j = 0;j < postSub->data_count - 1;j++)
				postSub->data[j] = postSub->data[j + 1];
			//subset[i]에 자식이 있으면 
			if (targetSub->child_count != 0) {
				//subset[i + 1]의 첫 번째 자식을 subset[i] 뒤로
				targetSub->subset[targetSub->child_count] = postSub->subset[0];
				//subset[i + 1]->data 자식 왼쪽으로 한 칸씩
				for (j = targetSub->child_count - 1;j > 0;j--)
					targetSub->subset[j - 1] = targetSub->subset[j];
				targetSub->child_count++;
				postSub->child_count--;
			}
			targetSub->data_count++;
			postSub->data_count--;
		}

		//Case4: MINIMUM - 1을 가진 subset[i]와 MINIMUM을 가진 subset[i + 1] 결합
		else if (targetSub->data_count == MINIMUM - 1 && postSub->data_count == MINIMUM) {
			//data[i]를 subset[i]->data 끝으로 이동
			targetSub->data[targetSub->data_count++] = root->data[i];
			//subset[i + 1]의 모든 값과 자식을 subset[i]의 끝으로 이동
			for (j = 0;j < postSub->data_count;j++)
				targetSub->data[targetSub->data_count++] = postSub->data[j];
			if (postSub->child_count != 0)
				for (j = 0;j < postSub->child_count;j++)
					targetSub->subset[targetSub->child_count++] = postSub->subset[j];
			//subset[i + 1], subset[i + 2], … 왼쪽으로 한 칸씩 이동
			for (j = i + 1;j < root->child_count;j++)
				root->subset[j - 1] = root->subset[j];
			root->data_count--;
		}
	}
}

template <class Item, class SizeType>
Item set<Item, SizeType>::remove_biggest(SizeType i, set<Item, SizeType>* root) {
	Item rtn_entry;
	set<Item, SizeType>* sub = root->subset[i];
	//자식이 없는 경우
	if (sub->child_count == 0) {
		//마지막 항목 리턴
		rtn_entry = sub->data[sub->data_count - 1];
		sub->data_count--;
		if (sub->data_count == 0)
			root->child_count--;
	}
	//자식이 있는 경우
	else {
		//가장 오른쪽 자식에서 가장 큰 항목 제거
		rtn_entry = remove_biggest(child_count - 1, sub);
		//필요하면 fix_shortage 호출
		if (sub->data_count < MINIMUM)
			fix_shortage(root, i);
	}
	return rtn_entry;
}

template <class Item, class SizeType>
void set<Item, SizeType>::print(set<Item, SizeType>* root, SizeType depth) {
	//Pre: Btree에 노드가 있을 때
	//Post: 90도 회전한 모양으로 Btree 출력

	if (root->data_count != 0) {
		for (SizeType i = root->data_count; i > 0; i--) {
			//우측 재귀호출
			if (root->child_count != 0)
				print(root->subset[i], depth + 1);
			//루트
			cout << setw(4 * depth) << root->data[i - 1] << endl;
		}
		//좌측 재귀호출
		if (root->child_count != 0)
			print(root->subset[0], depth + 1);
	}
}