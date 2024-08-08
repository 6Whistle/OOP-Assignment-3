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
	Roulette()		//ȣ�� �� ���� Linked List ����
	{
		head = new Node;
		head->setState();		//��忡�� �Ѿ��� ����

		Node* temp = head;
		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			temp->setNext(newtemp);
			temp = newtemp;
		}
		temp->setNext(head);
	}
	~Roulette()		//��ȯ �� �޸� �Ҵ� ����
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
	void rotate(void)		//�귿�� ����
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

	bool shoot(void)		//��Ƽ踦 ����� �� ������ �� ����ϴ� �Լ�
	{
		if (head->getState())		//�¾��� ��
		{
			cout << "You Died..." << endl;
			return true;
		}
		else
		{
			cout << "You Survived" << endl;		//���� �ʾ��� ��
			head = head->getNext();
			return false;
		}
	}
};



int main(void)
{
	Roulette russian;
	russian.rotate();		//ó�� �귿�� ��������

	while (true)
	{
		char cmd[20];

		cout << "Connand list(shoot/rotate)\n";
		cout << "CMD>> ";
		cin >> cmd;

		if (strcmp(cmd, "shoot") == 0)		//��Ƽ踦 ���
		{
			if (russian.shoot())		//�¾��� ��� �Լ� ����
			{
				return 0;
			}
		}
		else if (strcmp(cmd, "rotate") == 0)		//�귿�� ����
		{
			russian.rotate();
			system("cls");
		}
		else
		{
			cout << "Wrong Command!\n";			//�߸��� ��ɾ�
		}
	}
}