#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
template <class Item, class SizeType>
class set {
public:
	//������ & �ı���
	set() {
		data_count = 0;
		child_count = 0;
	}
	~set() {
		delete data;
		delete subset;
	}

	//Ư�� �� ���� �Ǵ�
	int count(Item target);

	//Btree�� ���ο� �� �߰�
	bool insert(Item entry, set<Item, SizeType>*& root);
	bool loose_insert(Item entry);
	void fix_excess(set<Item, SizeType>* parent, set<Item, SizeType>*& sub);

	//Btree���� Ư�� �� ����
	bool erase(Item target, set<Item, SizeType>*& root);
	bool loose_erase(Item target);
	void fix_shortage(set<Item, SizeType>* root, Item i);
	Item remove_biggest(SizeType i, set<Item, SizeType>* root);

	//Btree ���
	void print(set<Item, SizeType>* root, SizeType depth);

private:
	static const SizeType MINIMUM = 1;				//��� �� �ּ� ������ ��
	static const SizeType MAXIMUM = 2 * MINIMUM;	//��� �� �ִ� ������ ��
	SizeType data_count;							//���� ������ ��
	Item data[MAXIMUM + 1];							//������ �� �迭
	SizeType child_count;							//�ڽ� ����Ű�� ������ ����
	set* subset[MAXIMUM + 2];						//�ڽ� ����Ű�� ������ �迭
};

template <class Item, class SizeType>
int set<Item, SizeType>::count(Item target) {
	//Post: set�� target�� ������ 1, ������ 0 ��ȯ

	//��Ʈ���� data[i]>=target �� ù ��° i �� ã��
	SizeType i = 0;
	for (;i < data_count;i++)
		if (data[i] >= target)
			break;
	//������ i=data_count
	if (i == data_count - 1 && data[i] < target)
		i = data_count;

	//data[i]�� target�� ���� ���
	if (data[i] == target)
		return 1;
	//data[i]�� �ڽ��� ���� ���(leaf�� ���)
	else if (child_count == 0)
		return 0;
	//���� ����Ʈ���� ��� ȣ��
	else
		return subset[i]->count(target);
}

template <class Item, class SizeType>
bool set<Item, SizeType>::insert(Item entry, set<Item, SizeType>*& root) {
	//Post: ��Ģ�� ���� Btree�� �� �� �� �߰�

	//�� �߰� �������� ���
	if (!loose_insert(entry))
		return false;
	//��Ʈ�� �����Ͱ� MAXIMUM �̻��� ��
	if (data_count > MAXIMUM) {
		set<Item, SizeType>* r = new set<int, size_t>();
		fix_excess(r, root);
		root = r;
		return true;
	}
}

template <class Item, class SizeType>
bool set<Item, SizeType>::loose_insert(Item entry) {
	//Post: Btree�� �� �� �� �߰� (MAXIMUM+1 ���)

	//��Ʈ���� data[i]>=entry �� ù ��° i �� ã��
	SizeType i = 0;
	for (;i < data_count;i++)
		if (data[i] >= entry)
			break;
	//������ i=data_count
	if (i == data_count - 1 && data[i] < entry)
		i = data_count;

	//data[i]�� entry�� �̹� ���� ���
	if (data[i] == entry)
		return false;
	//data[i]�� �ڽ��� ���� ���
	else if (child_count == 0) {
		//i ��° ������ ��� �� �� ĭ�� �ű��
		for (SizeType j = data_count;j > i;j--)
			data[j] = data[j - 1];
		//data[i]�� entry �߰�
		data[i] = entry;
		data_count++;
		return true;
	}
	//data[i]�� �ڽ��� ���� ���
	else {
		SizeType size = subset[i]->data_count;
		//��� ȣ��
		bool b = subset[i]->loose_insert(entry);
		//subset[i]�� ��Ʈ�� ���ο� ���� �߰��ƴٸ� subset[i] ����
		if (size != subset[i]->data_count && subset[i]->data_count > subset[i]->MAXIMUM)
			fix_excess(this, subset[i]);
		return b;
	}
}

template <class Item, class SizeType>
void set<Item, SizeType>::fix_excess(set<Item, SizeType>* parent, set<Item, SizeType>*& sub) {
	//Post: ��� ������ ���� ����

	//MAXIMUM + 1���� �׸��� ������ ��带 �� ���� ���� ����
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

	//�߰� entry�� ���� �׸����� �̵�
	Item entry = sub->data[sub->MAXIMUM / 2];
	//Ʈ�� ��ü�� ��Ʈ�� �ٲ�� ���
	if (parent->data_count == 0) {
		parent->data[0] = entry;
		parent->data_count++;
		parent->subset[0] = a;
		parent->subset[1] = b;
		parent->child_count += 2;
	}
	//parent�� ���� �߰��� �� (MAXIMUM+1 ���)
	else if (parent->data_count != 0) {
		//parent���� data[i]>=entry �� ù ��° i �� ã��
		SizeType i = 0;
		for (;i < parent->data_count;i++)
			if (parent->data[i] >= entry)
				break;
		//������ parent �������� �߰�
		if (i == parent->data_count - 1 && parent->data[i] < entry)
			parent->data[data_count] = entry;
		else {
			//i ��° ������ ��� data �� �� ĭ�� �ű��
			for (SizeType j = parent->data_count;j > i;j--)
				parent->data[j] = parent->data[j - 1];
			for (SizeType j = parent->child_count;j > i;j--)
				parent->subset[j] = parent->subset[j - 1];
			//data[i]�� entry �߰�
			parent->data[i] = entry;
		}
		parent->data_count++;
		parent->subset[i] = a;
		parent->subset[i + 1] = b;
		parent->child_count++;
		//parent�� data�� MAXIMUM �̻��� �� ���
		if (parent->data_count > parent->MAXIMUM) {
			set<Item, SizeType>* r = new set<int, size_t>();
			fix_excess(r, parent);
			parent = r;
		}
	}
}

template <class Item, class SizeType>
bool set<Item, SizeType>::erase(Item target, set<Item, SizeType>*& root) {
	//Post: ��Ģ�� ���� Btree���� �� �ϳ� ����

	//���� ������ ���
	if (!loose_erase(target))
		return false;
	//���� �� ���� �ʿ��� ���
	for (SizeType j = 0;j < child_count;j++) {
		if (subset[j]->data_count == 0)
			fix_shortage(this, j);
	}
	if (data_count == 0 && child_count == 1)
		root = subset[0];	//Ʈ���� ��Ʈ ����

	return true;
}

template <class Item, class SizeType>
bool set<Item, SizeType>::loose_erase(Item target) {
	//Post: Btree���� �� �ϳ� ���� (MINIMUM-1 ���)

	//��Ʈ���� data[i]>=entry �� ù ��° i �� ã��
	SizeType i = 0;
	for (;i < data_count;i++)
		if (data[i] >= target)
			break;
	//������ i=data_count
	if (i == data_count - 1 && data[i] < target)
		i = data_count;

	//��Ʈ�� �ڽ��� ����
	if (child_count == 0) {
		//target�� �� ã�� ���
		if (data[i] != target || i == data_count)
			return false;
		//target�� ã�� ��� data ��̿��� target ����
		else if (data[i] == target) {
			for (Item j = i;j < data_count - 1;j++)
				data[j] = data[j + 1];
			data_count--;
			return true;
		}
	}
	else { //��Ʈ�� �ڽ��� �ְ�
		//target�� �� ã�� ���
		if (data[i] != target || i == data_count) {
			bool b = subset[i]->loose_erase(target);
			//���� ������ ���
			if (!b)
				return false;
			//���� ������ ���
			else {
				if (subset[i]->data_count == 0)
					child_count--;
				if (subset[i]->data_count == MINIMUM - 1) {
					fix_shortage(this, i);
					return true;
				}
			}
		}
		//target�� ã�� ��� ���� ū ������ ��ü
		else if (data[i] == target) {
			data[i] = remove_biggest(i, this);
			//�ʿ��� ��� ��� ����
			if (subset[i]->data_count < MINIMUM)
				fix_shortage(this, i);
			return true;
		}
	}
}

template <class Item, class SizeType>
void set<Item, SizeType>::fix_shortage(set<Item, SizeType>* root, Item i) {
	//Post: ��� ������ ���� ����

	SizeType j;
	set<Item, SizeType>* targetSub = root->subset[i];

	if (i > 0) {
		set<Item, SizeType>* preSub = root->subset[i - 1];

		//Case1: MINIMUM���� ���� ������ �ִ� subset[i - 1]���� �߰� entry ����
		if (preSub->data_count > MINIMUM) {
			//subset[i]�� ������ ���������� �� ĭ�� �ű��
			for (j = targetSub->data_count;j > 0;j--)
				targetSub->data[j] = targetSub->data[j - 1];
			//data[i - 1]�� subset[i]->data�� ������ �̵�
			if (targetSub->data_count == 0)
				root->child_count++;
			targetSub->data[0] = root->data[i - 1];
			//subset[i - 1]->data�� ������ ������ data[i - 1] ��ü
			root->data[i - 1] = preSub->data[preSub->data_count - 1];
			//subset[i - 1]�� �ڽ��� ������ ������ �ڽ��� subset[i] ������
			if (preSub->child_count != 0) {
				//subset[i]�� �ڽ� ���������� �� ĭ�� �ű��
				for (j = targetSub->child_count;j > 0;j--)
					targetSub->subset[j] = targetSub->subset[j - 1];
				//subset[i - 1] ������ �ڽ��� subset[i] ������
				targetSub->subset[0] = preSub->subset[preSub->child_count - 1];
				targetSub->child_count++;
				preSub->child_count--;
			}
			targetSub->data_count++;
			preSub->data_count--;
		}

		//Case3: MINIMUM - 1�� ���� subset[i]�� MINIMUM�� ���� subset[i - 1] ����
		else if (targetSub->data_count == MINIMUM - 1 && preSub->data_count == MINIMUM) {
			//data[i - 1]�� subset[i - 1]->data ������ �̵�
			preSub->data[preSub->data_count++] = root->data[i - 1];
			//subset[i]�� ��� ���� �ڽ��� subset[i - 1]�� ������ �̵�
			for (j = 0;j < targetSub->data_count;j++)
				preSub->data[preSub->data_count++] = targetSub->data[j];
			if (targetSub->child_count != 0)
				for (j = 0;j < targetSub->child_count;j++)
					preSub->subset[preSub->child_count++] = targetSub->subset[j];
			//subset[i + 1], subset[i + 2], �� �������� �� ĭ�� �̵�
			for (j = i + 1;j < root->child_count;j++)
				root->subset[j - 1] = root->subset[j];
			root->data_count--;
		}
	}

	else if (i <= root->data_count - 1) {
		set<Item, SizeType>* postSub = root->subset[i + 1];

		//Case2: MINIMUM���� ���� ������ �ִ� subset[i + 1]���� �߰� entry ����
		if (postSub->data_count > MINIMUM) {
			//data[i]�� subset[i]->data�� ������ �̵�
			if (targetSub->data_count == 0)
				root->child_count++;
			targetSub->data[targetSub->data_count] = root->data[i];
			//subset[i + 1]->data�� ù ��° ������ data[i] ��ü
			root->data[i] = postSub->data[0];
			//subset[i + 1]->data ������ �������� �� ĭ��
			for (j = 0;j < postSub->data_count - 1;j++)
				postSub->data[j] = postSub->data[j + 1];
			//subset[i]�� �ڽ��� ������ 
			if (targetSub->child_count != 0) {
				//subset[i + 1]�� ù ��° �ڽ��� subset[i] �ڷ�
				targetSub->subset[targetSub->child_count] = postSub->subset[0];
				//subset[i + 1]->data �ڽ� �������� �� ĭ��
				for (j = targetSub->child_count - 1;j > 0;j--)
					targetSub->subset[j - 1] = targetSub->subset[j];
				targetSub->child_count++;
				postSub->child_count--;
			}
			targetSub->data_count++;
			postSub->data_count--;
		}

		//Case4: MINIMUM - 1�� ���� subset[i]�� MINIMUM�� ���� subset[i + 1] ����
		else if (targetSub->data_count == MINIMUM - 1 && postSub->data_count == MINIMUM) {
			//data[i]�� subset[i]->data ������ �̵�
			targetSub->data[targetSub->data_count++] = root->data[i];
			//subset[i + 1]�� ��� ���� �ڽ��� subset[i]�� ������ �̵�
			for (j = 0;j < postSub->data_count;j++)
				targetSub->data[targetSub->data_count++] = postSub->data[j];
			if (postSub->child_count != 0)
				for (j = 0;j < postSub->child_count;j++)
					targetSub->subset[targetSub->child_count++] = postSub->subset[j];
			//subset[i + 1], subset[i + 2], �� �������� �� ĭ�� �̵�
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
	//�ڽ��� ���� ���
	if (sub->child_count == 0) {
		//������ �׸� ����
		rtn_entry = sub->data[sub->data_count - 1];
		sub->data_count--;
		if (sub->data_count == 0)
			root->child_count--;
	}
	//�ڽ��� �ִ� ���
	else {
		//���� ������ �ڽĿ��� ���� ū �׸� ����
		rtn_entry = remove_biggest(child_count - 1, sub);
		//�ʿ��ϸ� fix_shortage ȣ��
		if (sub->data_count < MINIMUM)
			fix_shortage(root, i);
	}
	return rtn_entry;
}

template <class Item, class SizeType>
void set<Item, SizeType>::print(set<Item, SizeType>* root, SizeType depth) {
	//Pre: Btree�� ��尡 ���� ��
	//Post: 90�� ȸ���� ������� Btree ���

	if (root->data_count != 0) {
		for (SizeType i = root->data_count; i > 0; i--) {
			//���� ���ȣ��
			if (root->child_count != 0)
				print(root->subset[i], depth + 1);
			//��Ʈ
			cout << setw(4 * depth) << root->data[i - 1] << endl;
		}
		//���� ���ȣ��
		if (root->child_count != 0)
			print(root->subset[0], depth + 1);
	}
}