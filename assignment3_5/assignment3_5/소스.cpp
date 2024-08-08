#include <iostream>
#include <cstring>
#include <windows.h>
#include <ctime>
using namespace std;

class Node
{
private:
	bool state;
	Node* next;
public:
	Node() { state = false; next = NULL; }
	~Node() { };

	Node* getNext(void)
	{
		return next;
	}
	void setNext(Node* input)
	{
		next = input;
	}
	void setState(void)
	{
		state = true;
	}
	bool getState(void)
	{
		return state;
	}

};

class Roulette
{
private:
	Node* head;
public:
	Roulette()		//호출 시 원형 Linked List 선언
	{
		head = new Node;
		head->setState();		//헤드에만 총알을 넣음

		Node* temp = head;
		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			temp->setNext(newtemp);
			temp = newtemp;
		}
		temp->setNext(head);
	}
	~Roulette()		//반환 시 메모리 할당 해제
	{
		Node* temp = head;
		for (int i = 0; i < 6; i++)
		{
			Node* pretemp = temp;
			temp = pretemp->getNext();
			delete temp;
		}
	}
	Node* getHead(void)
	{
		return head;
	}
	void setHead(Node* input)
	{
		head = input;
	}
	void rotate(void)		//룰렛을 돌림
	{
		srand((unsigned)time(NULL));

		int i = rand() % 6;

		Node* temp = head;
		for (int j = 0; j < i; j++)
		{
			temp = temp->getNext();
		}

		head = temp;
	}

	bool shoot(void)		//방아쇠를 당겼을 때 정해진 값 출력하는 함수
	{
		if (head->getState())		//맞았을 시
		{
			cout << "You Died..." << endl;
			return true;
		}
		else
		{
			cout << "You Survived" << endl;		//맞지 않았을 시
			head = head->getNext();
			return false;
		}
	}
};



int main(void)
{
	Roulette russian;
	russian.rotate();		//처음 룰렛을 돌려놓음

	while (true)
	{
		char cmd[20];

		cout << "Connand list(shoot/rotate)\n";
		cout << "CMD>> ";
		cin >> cmd;

		if (strcmp(cmd, "shoot") == 0)		//방아쇠를 당김
		{
			if (russian.shoot())		//맞았을 경우 함수 종료
			{
				return 0;
			}
		}
		else if (strcmp(cmd, "rotate") == 0)		//룰렛을 돌림
		{
			russian.rotate();
			system("cls");
		}
		else
		{
			cout << "Wrong Command!\n";			//잘못된 명령어
		}
	}
}