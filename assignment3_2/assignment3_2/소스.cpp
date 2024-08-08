#include <iostream>
#include <cctype>
using namespace std;


class BSTNode		//���� Ʈ��
{
public:
	int data;
	BSTNode* left;
	BSTNode* right;

	BSTNode() { left = NULL; right = NULL; };
	~BSTNode() {};
	void PrintPre(void)		//���� Ʈ�� Pre��� �Լ�
	{
		cout << data << '\t';

		if (left != NULL)
		{
			left->PrintPre();
		}

		if (right != NULL)
		{
			right->PrintPre();
		}

		return;
	}

	void PrintIn(void)		//���� Ʈ�� In��� �Լ�
	{
		if (left != NULL)
		{
			left->PrintIn();
		}

		cout << data << '\t';

		if (right != NULL)
		{
			right->PrintIn();
		}

		return;
	}

	void PrintPost(void)		//���� Ʈ�� Post��� �Լ�
	{
		if (left != NULL)
		{
			left->PrintPost();
		}

		if (right != NULL)
		{
			right->PrintPost();
		}

		cout << data << '\t';

		return;
	}

	void Search(int num)		//���� Ž�� �Լ�
	{
		if (data == num)
		{
			cout << num << "is exists" << endl;
			return;
		}
		else if (data > num && left != NULL)
		{
			left->Search(num);
			return;
		}
		else if (data < num && right != NULL)
		{
			right->Search(num);
			return;
		}

		cout << "Error 600" << endl;
		return;
	}

	void Exitbst(void)		//���� Ʈ�� �޸� �Ҵ� ���� �Լ�
	{
		if (left != NULL)
		{
			left->Exitbst();
		}

		if (right != NULL)
		{
			right->Exitbst();
		}

		delete this;
	}
};

class BST {
public:
	BST() { head = NULL; };
	~BST() {};

	void InputBST(int index)		//����Ʈ�� ������ �߰� �Լ�
	{
		if (head == NULL)		//����Ʈ���� ������� ��
		{
			head = new BSTNode;
			head->data = index;

			return;
		}

		BSTNode* curhead = head;
		while (true)
		{
			if (curhead->data > index)		//���� ��ġ�� �����ͺ��� ���� ��
			{
				if (curhead->left != NULL)		//���� ��尡 ���� ��
				{
					curhead = curhead->left;
				}
				else
				{
					curhead->left = new BSTNode;			//���� ��尡 ���� ��
					curhead->left->data = index;
					return;
				}
			}
			else if (curhead->data < index)		//���� ��ġ�� �����ͺ��� Ŭ ��
			{
				if (curhead->right != NULL)		//���� ��尡 ���� ��
				{
					curhead = curhead->right;
				}
				else
				{
					curhead->right = new BSTNode;		//���� ��尡 ���� ��
					curhead->right->data = index;
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	void PrintBST(int cmd)		//����Ʈ�� ��� �Լ�
	{
		if (head == NULL)		//����ִ� ���
		{
			cout << "Error 700" << endl;
			return;
		}

		if (cmd == 1)		//Pre ��� ��
		{
			head->PrintPre();
		}
		else if (cmd == 2)		//In ��� ��
		{
			head->PrintIn();
		}
		else
		{
			head->PrintPost();		//Post ��� ��
		}
		cout << endl;

		return;
	}

	void SearchBST(int num)		//���� Ʈ�� Ž�� �Լ�
	{
		if (head == NULL)		//Ʈ���� ������� ��
		{
			cout << "Error 600" << endl;
			return;
		}

		head->Search(num);

		return;
	}

	void DeleteBST(void)
	{
		if (head == NULL)		//����Ʈ�� ���� �Լ�
		{
			return;
		}

		head->Exitbst();
		return;
	}
private:
	BSTNode* head;
};

class QueueNode {
public:
	int data;
	QueueNode* next;

	QueueNode() { next = NULL; };
	~QueueNode() {};
};

class Queue {
public:
	Queue(void) { head = NULL; };
	~Queue(void) {};

	QueueNode* Gethead(void)
	{
		return head;
	}
	void InsertQueue(int index)		//Linked List ���� �Լ�
	{
		if (head == NULL)		//Linked List�� ������� ��
		{
			head = new QueueNode;
			head->data = index;

			return;
		}

		QueueNode* curhead = head;

		while (curhead->next != NULL)		//���� ����� ��ġ�� NULL�� �������� �̵�
		{
			curhead = curhead->next;
		}
		curhead->next = new QueueNode;
		curhead->next->data = index;

		return;
	}

	void Dequeue(BST& inputbst, int count)		//�ش� ������ŭ Linked List�� �����ϰ� �ش� �����͸� BST�� ������ �Լ�
	{
		

		if (head == NULL)		//Linked List�� ������� ���
		{
			cout << "Error 400" << endl;
			return;
		}

		QueueNode* curhead = head;

		for (int i = 0; i < count && head != NULL; i++)		//�Է��� ������ �Է��ѵ������� �����͸� �����ϰ� �� �����͸� InputBST�� ���� ����
		{
			inputbst.InputBST(head->data);
			head = head->next;
			delete curhead;
			curhead = head;
		}

		return;
	}
	void PrintQueue(void)		//Linked List ��� �Լ�
	{
		if (head == NULL)		//������� ��
		{
			cout << "Error 500" << endl;
			return;
		}

		QueueNode* curhead = head;
		while (curhead != NULL)
		{
			cout << curhead->data << '\t';
			curhead = curhead->next;
		}
		cout << endl;

		return;
	}
	void ExitQueue(void)		//�Լ� ���� �� �޸� �Ҵ� ���� �Լ�
	{
		QueueNode* curhead = head;

		while (head != NULL)
		{
			head = curhead->next;
			delete curhead;
			curhead = head;
		}

		return;
	}
private:
	QueueNode* head;
};

bool Command(char*);	//�Է��� ��ɾ ���ڷθ� �����Ǿ��ִ��� Ȯ���ϴ� �Լ�

int main(void)
{
	Queue que;
	BST bst;
	int count = 0;

	while (true)
	{

		char cmd[100];
		char cmd2[100];

		cout << "CMD>> ";
		cin.getline(cmd, sizeof(cmd), '\n');
		int j = 0;
		for (int i = 0, state = 0; cmd[i] != '\0'; i++)		//�Է� ��ɾ� ' '�� �������� �и���Ŵ
		{
			if (state)
			{
				cmd2[j] = cmd[i];
				j++;
			}
			else
			{
				if (cmd[i] == ' ')
				{
					cmd[i] = '\0';
					state = true;
				}
			}
		}
		cmd2[j] = '\0';

		if (strcmp(cmd, "Enqueue") == 0)		//Enqueue �Է� ��
		{

			if (Command(cmd2))		//cmd2�� ������ ���
			{
				if (count < 5)		//�Է��� �����Ͱ� 5�� �̸��� ���
				{
					int input = atoi(cmd2);
					que.InsertQueue(input);
					count++;
				}
				else
				{
					cout << "Error 300" << endl;		//�Է��� �����Ͱ� 5�� �̻��� ���
				}
			}
			else
			{
				cout << "Error 200" << endl;		//cmd2�� ���ڰ� �ƴ� ���
			}
		}
		else if (strcmp(cmd, "Dequeue") == 0)		//Dequeue�� �Է��� ���
		{
			if (Command(cmd2))		//cmd2�� ������ ���
			{
				int input = atoi(cmd2);
				que.Dequeue(bst, input);
				if (count < input)		//cmd�� ���� �Էµ� ���� �ʰ��� ���
				{
					count = 0;
				}
				else
				{
					count -= input;		//�ʰ����� �ʴ� ���
				}
			}
			else
			{
				cout << "Error 200" << endl;		//cmd2�� ���ڰ� �ƴ� ���
			}
		}
		else if (strcmp(cmd, "Print_Queue") == 0)		//Print_Queue �Է� ��
		{
			que.PrintQueue();
		}
		else if (strcmp(cmd, "SEARCH") == 0)		//SEARCH �Է� ��
		{
			if (Command(cmd2))			//cmd2�� ������ ���
			{
				int input = atoi(cmd2);
				bst.SearchBST(input);
			}
			else
			{
				cout << "Error 100" << endl;		//cmd2�� ���ڰ� �ƴ� ���
			}
		}
		else if (strcmp(cmd, "PRINT") == 0)		//PRINT�� �Է¹��� ���
		{

			if (strcmp(cmd2, "PRE") == 0)
			{
				bst.PrintBST(1);
			}
			else if (strcmp(cmd2, "IN") == 0)
			{
				bst.PrintBST(2);
			}
			else if (strcmp(cmd2, "POST") == 0)
			{
				bst.PrintBST(3);
			}
			else
			{
				cout << "Error 100" << endl;		//cmd2�� ���� ��ɾ���� �ƴ� ���
			}
		}
		else if (strcmp(cmd, "EXIT") == 0)		//�Լ� ���� �� �޸� �Ҵ� ����
		{
			que.ExitQueue();
			bst.DeleteBST();

			return 0;
		}
		else
		{
			cout << "Error 100" << endl;		//��ɾ ���� ���� ��
		}
	}
}

bool Command(char* input)		//�Է��� ��ɾ ���ڵ�θ� ��������� Ȯ���ϴ� �Լ�
{
	bool state = true;

	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] > '9' || input[i] < '0')
		{
			state = false;
		}
	}

	if (input[0] == '\0')
	{
		state = false;
	}

	return state;
}