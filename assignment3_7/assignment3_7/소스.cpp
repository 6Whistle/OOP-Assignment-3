#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


class Student_Node		//데이터 저장 클래스
{
public:
	long int ID = 0;
	char Major[100];
	char name[20];

	Student_Node* nextInput = NULL;			//입력 순 다음 Linked List
	Student_Node* nextMajor = NULL;			//전공 순 다음 Linked List
	Student_Node* nextID = NULL;			//학번 순 다음 Linked List
	Student_Node* nextName = NULL;			//이름 순 다음 Linked List

	Student_Node* inputData(long int InputID, char* InputMajor, char* InputName)		//데이터를 입력받아 nextInput Linked List로 저장하고 저장한 배열을 반환하는 함수
	{
		if (ID == 0)		//초기 입력이 없었을 경우
		{
			ID = InputID;
			strcpy(Major, InputMajor);
			strcpy(name, InputName);
			return this;
		}

		Student_Node* temp = this;
		while (temp->nextInput)		//기존 입력이 있을 경우
		{
			if (InputID == temp->ID && strcmp(InputMajor, temp->Major) == 0 && strcmp(InputName, temp->name) == 0)		//중복 판단
			{
				return NULL;
			}
			temp = temp->nextInput;
		}

		temp->nextInput = new Student_Node;			//마지막에 노드 삽입
		temp = temp->nextInput;
		temp->ID = InputID;
		strcpy(temp->Major, InputMajor);
		strcpy(temp->name, InputName);
		return temp;
	}



	void Print(int mode)		//0일 시 입력 순, 1일 시 ID 순, 2일 시 전공 순, 3일 시 이름 순 Linked List의 배열 출력
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

	void DeleteNode(void)		//메모리 할당 해제 함수
	{
		if (nextInput)
			nextInput->DeleteNode();

		return;
	}

};




class IDLink		//ID 2차원 Linked List
{
public:
	Student_Node* head = NULL;
	IDLink* nextRow = NULL;

	void PrintID(void)			//ID 출력 함수
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

			temp->head->Print(1);			//해당 head를 출력 함수와 조정값을 통해 출력
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

class MajorLink		//전공 2차원 Linked List
{
public:
	Student_Node* head = NULL;
	MajorLink* nextRow = NULL;


	void PrintMajor(void)		//전공 2차원 Linked List 출력 함수
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

			temp->head->Print(2);		//조정값을 2로 설정
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

class NameLink		//이름 2차원 Linked List 클래스
{
public:
	Student_Node* head = NULL;
	NameLink* nextRow = NULL;

	void PrintName(void)		//이름 2차원 Linked List 출력 함수
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

			temp->head->Print(3);		//조정값 3으로 설정
			cout << endl;

			temp = temp->nextRow;
		}
		for (int i = 0; i < 50; i++)
			cout << "=";
		cout << endl;
	}

	int Compare(char compare2)		// 두 객체 중 먼저 리스트에 나와야 하는 것을 알려주는 함수
	{
		if (head->name[0] == compare2)
			return 0;
		else if (head->name[0] > compare2)
			return 1;
		else
			return -1;
	}


};


void InputLink(Student_Node** head, Student_Node* input, int mode)		//2차원 링크드 리스트의 종류에 따라 next를 다르게 하여 삽입하는 함수
{

	if ((*head)->ID > input->ID)			//head보다 앞에 나올 시
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
		if ((mode == 1) && (temp->nextID == NULL))			//마지막에 들어가는 노드일 경우
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


		if (mode == 1 && temp->nextID->ID > input->ID)			//중간에 삽입되는 노드의 경우
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

		if (mode == 1)				//다음 위치로 포인터 이동
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
	if (input == NULL)		//입력이 없는 경우
		return;


	if (Link->head == NULL)		//초기 노드가 없는 경우
	{
		Link->head = input;
		return;
	}

	if (Link->Compare(dataform) > 0)			//입력된 정보가 head보다 먼저 나와야 할 경우
	{
		T1* newRow = new T1;
		newRow->nextRow = Link->nextRow;
		Link->nextRow = newRow;
		newRow->head = Link->head;
		Link->head = input;
		return;

	}
	else if (Link->Compare(dataform) == 0)		//head의 List에 삽입되야 하는 경우
	{
		InputLink(&(Link->head), input, mode);
		return;
	}
	else
	{
		T1* temp = Link;

		while (true)
		{
			if (temp->nextRow == NULL)		//마지막에 삽입되야 하는 경우
			{
				T1* newRow = new T1;
				newRow->head = input;
				temp->nextRow = newRow;
				return;
			}

			if (temp->nextRow->Compare(dataform) > 0)		//중간에 삽입되야 하는 경우
			{
				T1* newRow = new T1;
				newRow->head = input;
				newRow->nextRow = temp->nextRow;
				temp->nextRow = newRow;
				return;
			}

			if (temp->nextRow->Compare(dataform) == 0)		//해당 리스트에 삽입되야 하는 경우
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
	if (!file.is_open())		//파일 읽기 실패 시 오류 출력
	{
		cout << "File can't be open" << endl;
		return -1;
	}

	while (!file.eof())			//파일에서 데이터를 가져와 input Linked List와 각각의 2차원 Linked List에 삽입
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

		if (cmd == 1)		//1 입력 시 파일 순으로 데이터 출력
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
		else if (cmd == 2)		//2 입력 시 연도 순으로 데이터 출력
		{
			IDHead->PrintID();
		}
		else if (cmd == 3)		//3 입력 시 전공 순으로 데이터 출력
		{
			MajorHead->PrintMajor();
		}
		else if (cmd == 4)		//4 입력 시 이름 첫 알파벳 순으로 데이터 출력
		{
			NameHead->PrintName();
		}
		else if (cmd == 5)		//5 입력 시 메모리 할당 해제 후 함수 종료
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
