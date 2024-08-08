#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


class Student_Node		//������ ���� Ŭ����
{
public:
	long int ID = 0;
	char Major[100];
	char name[20];

	Student_Node* nextInput = NULL;			//�Է� �� ���� Linked List
	Student_Node* nextMajor = NULL;			//���� �� ���� Linked List
	Student_Node* nextID = NULL;			//�й� �� ���� Linked List
	Student_Node* nextName = NULL;			//�̸� �� ���� Linked List

	Student_Node* inputData(long int InputID, char* InputMajor, char* InputName)		//�����͸� �Է¹޾� nextInput Linked List�� �����ϰ� ������ �迭�� ��ȯ�ϴ� �Լ�
	{
		if (ID == 0)		//�ʱ� �Է��� ������ ���
		{
			ID = InputID;
			strcpy(Major, InputMajor);
			strcpy(name, InputName);
			return this;
		}

		Student_Node* temp = this;
		while (temp->nextInput)		//���� �Է��� ���� ���
		{
			if (InputID == temp->ID && strcmp(InputMajor, temp->Major) == 0 && strcmp(InputName, temp->name) == 0)		//�ߺ� �Ǵ�
			{
				return NULL;
			}
			temp = temp->nextInput;
		}

		temp->nextInput = new Student_Node;			//�������� ��� ����
		temp = temp->nextInput;
		temp->ID = InputID;
		strcpy(temp->Major, InputMajor);
		strcpy(temp->name, InputName);
		return temp;
	}



	void Print(int mode)		//0�� �� �Է� ��, 1�� �� ID ��, 2�� �� ���� ��, 3�� �� �̸� �� Linked List�� �迭 ���
	{
		Student_Node* temp = this;
		while (temp)
		{
			cout.width(15);
			cout << left << temp->ID;
			cout.width(30);
			cout << left << temp->Major;
			cout.width(50);
			cout << left << temp->name;
			cout << endl;

			if (mode == 0)
			{
				temp = temp->nextInput;
			}
			else if (mode == 1)
			{
				temp = temp->nextID;
			}
			else if (mode == 2)
			{
				temp = temp->nextMajor;
			}
			else if (mode == 3)
			{
				temp = temp->nextName;
			}
		}

		return;
	}

	void DeleteNode(void)		//�޸� �Ҵ� ���� �Լ�
	{
		if (nextInput)
			nextInput->DeleteNode();

		return;
	}

};




class IDLink		//ID 2���� Linked List
{
public:
	Student_Node* head = NULL;
	IDLink* nextRow = NULL;

	void PrintID(void)			//ID ��� �Լ�
	{
		cout << "Print by ID\n";
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;

		IDLink* temp = this;
		while (temp)
		{
			cout << (temp->head->ID / 1000000) << endl;
			cout.width(15);
			cout << left << "StudentID";
			cout.width(30);
			cout << left << "Major";
			cout.width(50);
			cout << left << "Name" << endl;

			temp->head->Print(1);			//�ش� head�� ��� �Լ��� �������� ���� ���
			cout << endl;

			temp = temp->nextRow;
		}
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;
	}

	int Compare(long int compare2)
	{
		if (head->ID / 1000000 == compare2 / 1000000)
			return 0;
		else if (head->ID / 1000000 > compare2 / 1000000)
			return 1;
		else
			return -1;
	}

};

class MajorLink		//���� 2���� Linked List
{
public:
	Student_Node* head = NULL;
	MajorLink* nextRow = NULL;


	void PrintMajor(void)		//���� 2���� Linked List ��� �Լ�
	{
		cout << "Print by Major\n";
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;

		MajorLink* temp = this;
		while (temp)
		{
			cout << temp->head->Major << endl;
			cout.width(15);
			cout << left << "StudentID";
			cout.width(30);
			cout << left << "Major";
			cout.width(50);
			cout << left << "Name" << endl;

			temp->head->Print(2);		//�������� 2�� ����
			cout << endl;

			temp = temp->nextRow;
		}
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;
	}

	int Compare(char* compare2)
	{
		if (strcmp(head->Major, compare2) == 0)
			return 0;
		else if (strcmp(head->Major, compare2) > 0)
			return 1;
		else
			return -1;
	}

};

class NameLink		//�̸� 2���� Linked List Ŭ����
{
public:
	Student_Node* head = NULL;
	NameLink* nextRow = NULL;

	void PrintName(void)		//�̸� 2���� Linked List ��� �Լ�
	{
		cout << "Print by Name\n";
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;

		NameLink* temp = this;
		while (temp)
		{
			cout << (temp->head->name)[0] << endl;
			cout.width(15);
			cout << left << "StudentID";
			cout.width(30);
			cout << left << "Major";
			cout.width(50);
			cout << left << "Name" << endl;

			temp->head->Print(3);		//������ 3���� ����
			cout << endl;

			temp = temp->nextRow;
		}
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;
	}

	int Compare(char compare2)		// �� ��ü �� ���� ����Ʈ�� ���;� �ϴ� ���� �˷��ִ� �Լ�
	{
		if (head->name[0] == compare2)
			return 0;
		else if (head->name[0] > compare2)
			return 1;
		else
			return -1;
	}


};


void InputLink(Student_Node** head, Student_Node* input, int mode)		//2���� ��ũ�� ����Ʈ�� ������ ���� next�� �ٸ��� �Ͽ� �����ϴ� �Լ�
{

	if ((*head)->ID > input->ID)			//head���� �տ� ���� ��
	{
		if (mode == 1)
		{
			input->nextID = (*head);
		}
		else if (mode == 2)
		{
			input->nextMajor = (*head);
		}
		else
		{
			input->nextName = (*head);
		}
		*head = input;
		return;
	}

	Student_Node* temp = *head;
	while (true)
	{
		if ((mode == 1) && (temp->nextID == NULL))			//�������� ���� ����� ���
		{
			temp->nextID = input;
			return;
		}
		else if ((mode == 2) && (temp->nextMajor == NULL))
		{
			temp->nextMajor = input;
			return;
		}
		else if ((mode == 3) && (temp->nextName == NULL))
		{
			temp->nextName = input;
			return;
		}


		if (mode == 1 && temp->nextID->ID > input->ID)			//�߰��� ���ԵǴ� ����� ���
		{
			input->nextID = temp->nextID;
			temp->nextID = input;
			return;
		}
		else if (mode == 2 && temp->nextMajor->ID > input->ID)
		{
			input->nextMajor = temp->nextMajor;
			temp->nextMajor = input;
			return;
		}
		else if (mode == 3 && temp->nextName->ID > input->ID)
		{
			input->nextName = temp->nextName;
			temp->nextName = input;
			return;
		}

		if (mode == 1)				//���� ��ġ�� ������ �̵�
		{
			temp = temp->nextID;
		}
		else if (mode == 2)
		{
			temp = temp->nextMajor;
		}
		else
		{
			temp = temp->nextName;
		}

	}
}

template <typename T1, typename Tdata>
void input2DLink(T1* Link, Student_Node* input, Tdata dataform, int mode)
{
	if (input == NULL)		//�Է��� ���� ���
		return;


	if (Link->head == NULL)		//�ʱ� ��尡 ���� ���
	{
		Link->head = input;
		return;
	}

	if (Link->Compare(dataform) > 0)			//�Էµ� ������ head���� ���� ���;� �� ���
	{
		T1* newRow = new T1;
		newRow->nextRow = Link->nextRow;
		Link->nextRow = newRow;
		newRow->head = Link->head;
		Link->head = input;
		return;

	}
	else if (Link->Compare(dataform) == 0)		//head�� List�� ���ԵǾ� �ϴ� ���
	{
		InputLink(&(Link->head), input, mode);
		return;
	}
	else
	{
		T1* temp = Link;

		while (true)
		{
			if (temp->nextRow == NULL)		//�������� ���ԵǾ� �ϴ� ���
			{
				T1* newRow = new T1;
				newRow->head = input;
				temp->nextRow = newRow;
				return;
			}

			if (temp->nextRow->Compare(dataform) > 0)		//�߰��� ���ԵǾ� �ϴ� ���
			{
				T1* newRow = new T1;
				newRow->head = input;
				newRow->nextRow = temp->nextRow;
				temp->nextRow = newRow;
				return;
			}

			if (temp->nextRow->Compare(dataform) == 0)		//�ش� ����Ʈ�� ���ԵǾ� �ϴ� ���
			{
				InputLink(&(temp->nextRow->head), input, mode);
				return;
			}

			temp = temp->nextRow;
		}
	}

}



int main(void)
{
	Student_Node* inputHead = new Student_Node;
	IDLink* IDHead = new IDLink;
	MajorLink* MajorHead = new MajorLink;
	NameLink* NameHead = new NameLink;

	ifstream file;

	file.open("student.txt");			
	if (!file.is_open())		//���� �б� ���� �� ���� ���
	{
		cout << "File can't be open" << endl;
		return -1;
	}

	while (!file.eof())			//���Ͽ��� �����͸� ������ input Linked List�� ������ 2���� Linked List�� ����
	{

		long int inID;
		char inMajor[100];
		char inName[20];

		file >> inID;
		file.get();
		file.getline(inMajor, sizeof(inMajor), ',');
		file.getline(inName, sizeof(inName), '\n');

		Student_Node* input = inputHead->inputData(inID, inMajor, inName);
		input2DLink(IDHead, input, inID, 1);
		input2DLink(MajorHead, input, inMajor, 2);
		input2DLink(NameHead, input, inName[0], 3);

	}
	file.close();

	while (true)
	{
		int cmd;

		cout << "1.Print File" << endl;
		cout << "2.Print by ID" << endl;
		cout << "3.Print by Major" << endl;
		cout << "4.Print by Name" << endl;
		cout << "5.Program End" << endl;
		cout << "CMD>> ";
		cin >> cmd;

		if (cmd == 1)		//1 �Է� �� ���� ������ ������ ���
		{
			cout << "Print File" << endl;
			for (int i = 0; i < 50; i++)
				cout << "=";
			cout << endl;
			inputHead->Print(0);
			for (int i = 0; i < 50; i++)
				cout << "=";
			cout << endl;

		}
		else if (cmd == 2)		//2 �Է� �� ���� ������ ������ ���
		{
			IDHead->PrintID();
		}
		else if (cmd == 3)		//3 �Է� �� ���� ������ ������ ���
		{
			MajorHead->PrintMajor();
		}
		else if (cmd == 4)		//4 �Է� �� �̸� ù ���ĺ� ������ ������ ���
		{
			NameHead->PrintName();
		}
		else if (cmd == 5)		//5 �Է� �� �޸� �Ҵ� ���� �� �Լ� ����
		{
			inputHead->DeleteNode();
			delete inputHead;
			delete IDHead;
			delete MajorHead;
			delete NameHead;
			return 0;
		}
	}
}
