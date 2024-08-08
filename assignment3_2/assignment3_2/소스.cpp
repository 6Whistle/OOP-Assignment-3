#include <iostream>
#include <cctype>
using namespace std;


class BSTNode		//이진 트리
{
public:
	int data;
	BSTNode* left;
	BSTNode* right;

	BSTNode() { left = NULL; right = NULL; };
	~BSTNode() {};
	void PrintPre(void)		//이진 트리 Pre출력 함수
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

	void PrintIn(void)		//이진 트리 In출력 함수
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

	void PrintPost(void)		//이진 트리 Post출력 함수
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

	void Search(int num)		//이진 탐색 함수
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

	void Exitbst(void)		//이진 트리 메모리 할당 해제 함수
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

	void InputBST(int index)		//이진트리 데이터 추가 함수
	{
		if (head == NULL)		//이진트리가 비어있을 때
		{
			head = new BSTNode;
			head->data = index;

			return;
		}

		BSTNode* curhead = head;
		while (true)
		{
			if (curhead->data > index)		//현재 위치의 데이터보다 작을 때
			{
				if (curhead->left != NULL)		//좌측 노드가 있을 때
				{
					curhead = curhead->left;
				}
				else
				{
					curhead->left = new BSTNode;			//좌측 노드가 없을 때
					curhead->left->data = index;
					return;
				}
			}
			else if (curhead->data < index)		//현재 위치의 데이터보다 클 때
			{
				if (curhead->right != NULL)		//우측 노드가 있을 때
				{
					curhead = curhead->right;
				}
				else
				{
					curhead->right = new BSTNode;		//우츨 노드가 없을 때
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

	void PrintBST(int cmd)		//이진트리 출력 함수
	{
		if (head == NULL)		//비어있는 경우
		{
			cout << "Error 700" << endl;
			return;
		}

		if (cmd == 1)		//Pre 출력 시
		{
			head->PrintPre();
		}
		else if (cmd == 2)		//In 출력 시
		{
			head->PrintIn();
		}
		else
		{
			head->PrintPost();		//Post 출력 시
		}
		cout << endl;

		return;
	}

	void SearchBST(int num)		//이진 트리 탐색 함수
	{
		if (head == NULL)		//트리가 비어있을 때
		{
			cout << "Error 600" << endl;
			return;
		}

		head->Search(num);

		return;
	}

	void DeleteBST(void)
	{
		if (head == NULL)		//이진트리 삭제 함수
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
	void InsertQueue(int index)		//Linked List 삽입 함수
	{
		if (head == NULL)		//Linked List가 비어있을 때
		{
			head = new QueueNode;
			head->data = index;

			return;
		}

		QueueNode* curhead = head;

		while (curhead->next != NULL)		//다음 노드의 위치가 NULL인 구간으로 이동
		{
			curhead = curhead->next;
		}
		curhead->next = new QueueNode;
		curhead->next->data = index;

		return;
	}

	void Dequeue(BST& inputbst, int count)		//해당 갯수만큼 Linked List를 삭제하고 해당 데이터를 BST로 보내는 함수
	{
		

		if (head == NULL)		//Linked List가 비어있을 경우
		{
			cout << "Error 400" << endl;
			return;
		}

		QueueNode* curhead = head;

		for (int i = 0; i < count && head != NULL; i++)		//입력한 갯수나 입력한도까지만 데이터를 삭제하고 이 데이터를 InputBST를 통해 보냄
		{
			inputbst.InputBST(head->data);
			head = head->next;
			delete curhead;
			curhead = head;
		}

		return;
	}
	void PrintQueue(void)		//Linked List 출력 함수
	{
		if (head == NULL)		//비어있을 때
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
	void ExitQueue(void)		//함수 종료 시 메모리 할당 해제 함수
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

bool Command(char*);	//입력한 명령어가 숫자로만 구성되어있는지 확인하는 함수

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
		for (int i = 0, state = 0; cmd[i] != '\0'; i++)		//입력 명령어 ' '를 기준으로 분리시킴
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

		if (strcmp(cmd, "Enqueue") == 0)		//Enqueue 입력 시
		{

			if (Command(cmd2))		//cmd2가 숫자일 경우
			{
				if (count < 5)		//입력한 데이터가 5기 미만일 경우
				{
					int input = atoi(cmd2);
					que.InsertQueue(input);
					count++;
				}
				else
				{
					cout << "Error 300" << endl;		//입력한 데이터가 5개 이상인 경우
				}
			}
			else
			{
				cout << "Error 200" << endl;		//cmd2가 숫자가 아닌 경우
			}
		}
		else if (strcmp(cmd, "Dequeue") == 0)		//Dequeue를 입력한 경우
		{
			if (Command(cmd2))		//cmd2가 숫자인 경우
			{
				int input = atoi(cmd2);
				que.Dequeue(bst, input);
				if (count < input)		//cmd의 수가 입력된 수를 초과한 경우
				{
					count = 0;
				}
				else
				{
					count -= input;		//초과하지 않는 경우
				}
			}
			else
			{
				cout << "Error 200" << endl;		//cmd2가 숫자가 아닌 경우
			}
		}
		else if (strcmp(cmd, "Print_Queue") == 0)		//Print_Queue 입력 시
		{
			que.PrintQueue();
		}
		else if (strcmp(cmd, "SEARCH") == 0)		//SEARCH 입력 시
		{
			if (Command(cmd2))			//cmd2가 숫자인 경우
			{
				int input = atoi(cmd2);
				bst.SearchBST(input);
			}
			else
			{
				cout << "Error 100" << endl;		//cmd2가 숫자가 아닌 경우
			}
		}
		else if (strcmp(cmd, "PRINT") == 0)		//PRINT를 입력받은 경우
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
				cout << "Error 100" << endl;		//cmd2가 위의 명령어들이 아닌 경우
			}
		}
		else if (strcmp(cmd, "EXIT") == 0)		//함수 종료 시 메모리 할당 해제
		{
			que.ExitQueue();
			bst.DeleteBST();

			return 0;
		}
		else
		{
			cout << "Error 100" << endl;		//명령어가 맞지 않을 시
		}
	}
}

bool Command(char* input)		//입력한 명령어가 숫자들로만 구성됬는지 확인하는 함수
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