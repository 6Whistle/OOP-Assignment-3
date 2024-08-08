#include <iostream>
#include <cstring>
#include <windows.h>
#include <time.h>
using namespace std;


class Node
{
public:
	int horse[4] = {0,0,0,0};
	bool cross = false;			//��Ÿ� ǥ��
	bool end = false;

	Node* prev = NULL;		//���� ���
	Node* next = NULL;		//���� ���
	Node* fast = NULL;		//������ ���(�ش� ��� ���� ���������� �̵� ����)

	void MakeMap(void)		//�� ���� �Լ�
	{
		Node* Rightside = this;			//���� ��
		Rightside->end = true;			//������ ����

		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			Rightside->next = newtemp;
			newtemp->prev = Rightside;

			Rightside = Rightside->next;
		}

		Node* Upside = Rightside;		//���� ��

		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			Upside->next = newtemp;
			newtemp->prev = Upside;

			Upside = Upside->next;
		}

		Node* Leftside = Upside;		//���� ��

		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			Leftside->next = newtemp;
			newtemp->prev = Leftside;

			Leftside = Leftside->next;
		}

		Node* Downside = Leftside;		//�Ʒ��� ��

		for (int i = 0; i < 4; i++)
		{
			Node* newtemp = new Node;
			Downside->next = newtemp;
			newtemp->prev = Downside;

			Downside = Downside->next;
		}

		Downside->next = this;
		this->prev = Downside;		//�Ʒ� ���  ���� �� ����

	
		Node* Crossright = Rightside;		//���� ��� �밢�� ��(����)
		
		Crossright->fast = new Node;
		Crossright->fast->prev = Crossright;
		Crossright = Crossright->fast;

		Node* Crosspoint = NULL;
		for (int i = 0; i < 4; i++)
		{
			Node* newtemp = new Node;
			Crossright->next = newtemp;	
			newtemp->prev = Crossright;
			if (i == 1)
			{
				newtemp->cross = true;		//������ ����
				Crosspoint = newtemp;
			}

			Crossright = Crossright->next;
		}

		Crossright->next = Leftside;


		Node* Crossleft = Upside;		//���� ��� �밢�� ��

		Crossleft->fast = new Node;
		Crossleft->fast->prev = Crossleft;
		Crossleft = Crossleft->fast;

		Crossleft->next = new Node;
		Crossleft->next->prev = Crossleft;
		Crossleft = Crossleft->next;
		Crossleft->cross = true;

		Crossleft->next = Crosspoint;
		Crosspoint->prev = Crossleft;
		Crossleft = Crosspoint;

		Crossleft->fast = new Node;
		Crossleft->fast->prev = Crossleft;
		Crossleft = Crossleft->fast;
		
		Crossleft->next = new Node;
		Crossleft->next->prev = Crossleft;
		Crossleft = Crossleft->next;
		
		Crossleft->next = this;

		return;

	}

	void PrintHorse(void)		//�� ��� �Լ�
	{

		for (int j = 0; j < 4; j++)
		{
			if (horse[j] == 1)
			{
				cout << "A" << (j + 1);
				return;
			}
			else if (horse[j] == -1)
			{
				cout << "B" << (j + 1);
				return;
			}
		}

		cout << "o";
		return;
	}

	void PrintMap(void)		//�� ��� �Լ�
	{
		Node* Uphead = this;

		for (int i = 0; i < 5; i++)
		{
			Uphead = Uphead->next;
		}


		Node* Lefthead = Uphead;

		for (int i = 0; i < 5; i++)
		{
			Lefthead = Lefthead->next;
		}


		Node* Downhead = Lefthead;

		for (int i = 0; i < 5; i++)
		{
			Downhead = Downhead->next;
		}

		Node* Up = Lefthead;

		for (int i = 0; i < 6; i++)				//1�� ���
		{
			Up->PrintHorse();
			if (i == 2)
			{
				cout << '\t' << '\t';
			}
			else
			{
				cout << '\t';
			}
			Up = Up->prev;
		}
		cout << "\n\n";

		Node* CrossLeft = Lefthead->fast;
		Node* CrossRight = Uphead->fast;
		Node* Right = Uphead->prev;
		Node* Left = Lefthead->next;

			Left->PrintHorse();				//2�� ���
			cout << '\t';
			Left = Left->next;
			CrossLeft->PrintHorse();
			cout << "\t\t\t\t";
			CrossLeft = CrossLeft->next;
			CrossRight->PrintHorse();
			cout << '\t';
			CrossRight = CrossRight->next;
			Right->PrintHorse();
			cout << "\n\n";

			Left->PrintHorse();				//3�� ���
			cout << '\t'<<'\t';
			Left = Left->next;
			CrossLeft->PrintHorse();
			cout << "\t\t";
			CrossLeft = CrossLeft->next;
			CrossRight->PrintHorse();
			cout << '\t'<<'\t';
			CrossRight = CrossRight->next;
			Right->PrintHorse();
			cout << "\n\n";

			cout << "\t\t\t";				//4�� ���
			CrossLeft->PrintHorse();
			cout << "\n\n";
			CrossLeft = CrossLeft->fast;
			CrossRight = CrossRight->next;

			Left->PrintHorse();				//5�� ���
			cout << '\t'<<'\t';
			Left = Left->next;
			CrossRight->PrintHorse();
			cout << '\t'<<'\t';
			CrossRight = CrossRight->next;
			CrossLeft->PrintHorse();
			cout << "\t\t";
			CrossLeft = CrossLeft->next;
			Right->PrintHorse();
			cout << "\n\n";

			Left->PrintHorse();				//5�� ���
			cout << '\t';
			Left = Left->next;
			CrossRight->PrintHorse();
			cout << "\t\t\t\t";
			CrossRight = CrossRight->next;
			CrossLeft->PrintHorse();
			cout << "\t";
			CrossLeft = CrossLeft->next;
			Right->PrintHorse();
			cout << "\n\n";

			Node* Down = Downhead;

			for (int i = 0; i < 6; i++)				//1�� ���
			{
				Down->PrintHorse();
				if (i == 2)
				{
					cout << '\t' << '\t';
				}
				else
				{
					cout << '\t';
				}
				Down = Down->next;
			}
			cout << endl;

	}



};

class MoveNode
{
public:
	int go = 0;
	int Yut[4];		//0->�޸�, 1->�ո�
	MoveNode* next = NULL;
	


};

class MoveLink
{
public:
	MoveNode* head = NULL;

	bool Throw(void)			//�� ������ �Լ�
	{
		MoveNode* temp = head;

		if (head == NULL)		//ù �� �������� ��
		{
			head = new MoveNode;
			temp = head;
		}
		else
		{
			while (temp->next)		//������ ���� ����� ���� ���
			{
				temp = temp->next;
			}

			temp->next = new MoveNode;
			temp = temp->next;
		}

		int prob[4] = { 0 };
		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			prob[i] = rand() % 5;		//60���� Ȯ���� �ո�
			if (prob[i] > 1)
			{
				temp->Yut[i] = 1;
				count++;
			}
			else
			{
				temp->Yut[i] = 0;
			}
		}

		


		if (count == 0)		//���� ��� 1 ��ȯ
		{
			temp->go = 5;
			cout << "Result is mo" << endl;
			return 1;
		}
		else if (count == 1)		//���� ��� 0 ��ȯ
		{
			if (temp->Yut[0] == 1)
			{
				temp->go = -1;
				cout << "Result is back do" << endl;
			}
			else
			{
				temp->go = 1;
				cout << "Result is do" << endl;
			}
			return 0;
		}
		else if (count == 2)		//���� ��� 0 ��ȯ
		{
			temp->go = 2;
			cout << "Result is gae" << endl;
			return 0;
		}
		else if (count == 3)		//���� ��� 0 ��ȯ
		{
			temp->go = 3;
			cout << "Result is goel" << endl;
			return 0;
		}
		else if (count == 4)		//���� ��� 0 ��ȯ
		{
			temp->go = 4;
			cout << "Result is yut" << endl;
			return 1;
		}

	}

	int UseMoveNode(int selectMove)		//�̵� �Ÿ��� ���� �Լ�
	{
		MoveNode* temp = head;

		if (selectMove == 1)		//ó�� ���� �� ���
		{
			int num = head->go;
			head = head->next;
			delete temp;
			return num;
		}

		for (int i = 1; i < selectMove - 1; i++)		//������ ���� �� ���
		{
			temp = temp->next;
		}
		
		MoveNode* deleteNode = temp->next;
		int num = deleteNode->go;
		temp->next = temp->next->next;
		delete deleteNode;
		return num;
	}

};

class Player
{
public:
	Node* H[4] = {NULL, NULL, NULL, NULL};
	bool arrive[4] = { false, false, false, false };


};



bool Command()
{
	while (true)
	{
		char cmd[20];


		cout << "CMD>> ";
		cin >> cmd;

		if (strcmp(cmd, "throw") == 0)
		{
			return true;
		}
		else if (strcmp(cmd, "exit") == 0)
		{
			return false;
		}
	}
}


void MoveHorse(Node* Map, Node** Position, int move)
{
	if ((*Position) == NULL)
	{
		(*Position) = Map;
		for (int i = 0; i < move; i++)
		{
			(*Position) = (*Position)->next;
		}

		return;
	}
	else
	{
		if (move == -1)
		{
			(*Position) = (*Position)->prev;
			return;
		}

		int isCross = (*Position)->cross;
		if ((*Position)->fast != NULL)
		{

			(*Position) = (*Position)->fast;

			for (int i = 0; i < move - 1; i++)
			{
				(*Position) = (*Position)->next;
			}
			return;
		}
		else
		{
			for (int i = 0; i < move; i++)
			{
				(*Position) = (*Position)->next;
			}
		}
	}
}



int main(void)
{
	srand((unsigned)time(NULL));

	Node* map = new Node;
	MoveLink* YUT = new MoveLink;
	Player P1;			//P1 ��
	Player P2;			//P2 ��
	map->MakeMap();
	
	int turn = 2;

	while (true)
	{
		if (turn == 2)			//�÷��̾� ����
			turn = 1;
		else
			turn = 2;


		system("cls");
		map->PrintMap();
		cout << "Player " << turn << " turn!(throw/exit)" << endl;

		int state1 = Command();		//throw�� �Է¹��� ��
		if (state1 == true)
		{
			if (YUT->Throw())			//���̳� �� ������ �ٽ� ����
			{
				int state2 = true;
				while (state2)
				{
					char cmd[20];
					cout << "Throw again!\n";
					cout << "CMD>> ";
					cin >> cmd;

					if (strcmp(cmd, "throw") == 0)
					{
						state2 = YUT->Throw();
					}
				}	

			}
			int count = 1;
			MoveNode* temp = YUT->head;
			cout << "Yut Results: ";			//���� ��� ���
			while (temp)
			{
				cout << count << ". " << temp->go << '\t';
				temp = temp->next;
				count++;
			}
			cout << endl;

			int selectMove, move;
			cout << "Select move: ";
			cin >> selectMove;

			move = YUT->UseMoveNode(selectMove);		//�ش� �̵��� ����ϰ� MoveNode���� ����

			for (int i = 0, count2 = 1; i < 4; i++)
			{
				bool state = false;
				for (int j = 0; j < i; j++)
				{
					if (turn == 1 && (P1.H[i] == P1.H[j] && P1.H[i] != NULL))
					{
						state = true;
					}
					else if (turn == 2 && (P2.H[i] == P2.H[j] && P2.H[i] != NULL))
					{
						state = true;
					}
				}

				if (turn == 1)						//������ �� �ִ� �� ǥ��
				{
					if (P1.H[i] == NULL && P1.arrive[i] == false)
					{
						cout << count2 << ". Hand\t";
						count2++;
					}
					else if (state == false)
					{
						cout << count2 << ". A" << i + 1 << "\t";
						count2++;
					}
				}
				else
				{
					if (P2.H[i] == NULL && P2.arrive[i] == false)
					{
						cout << count2 << ". Hand\t";
						count2++;
					}
					else if (state == false)
					{
						cout << count2 << ". A" << i + 1 << "\t";
						count2++;
					}
				}
			}
			cout << endl;

			int selectHorse, horse;
			cout << "Select horse: ";
			cin >> selectHorse;

			if (turn == 1)
			{
				MoveHorse(map, &(P1.H[selectHorse-1]), move);
				((P1.H[selectHorse-1])->horse)[selectHorse-1] = 1;

			}
			else
			{
				MoveHorse(map, &(P2.H[selectHorse-1]), move);
				P2.H[selectHorse-1]->horse[selectHorse-1] = -1;
			}

			//horse �����̴� �Լ�

		}
		else
		{
			return 0;
		}
	}

}
