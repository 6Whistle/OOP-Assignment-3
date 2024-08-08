#include <iostream>
#include <cstring>
#include <windows.h>
#include <time.h>
using namespace std;


class Node
{
public:
	int horse[4] = {0,0,0,0};
	bool cross = false;			//사거리 표시
	bool end = false;

	Node* prev = NULL;		//이전 노드
	Node* next = NULL;		//다음 노드
	Node* fast = NULL;		//지름길 노드(해당 노드 위에 서있을때만 이동 가능)

	void MakeMap(void)		//맵 생성 함수
	{
		Node* Rightside = this;			//우측 길
		Rightside->end = true;			//종착지 지정

		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			Rightside->next = newtemp;
			newtemp->prev = Rightside;

			Rightside = Rightside->next;
		}

		Node* Upside = Rightside;		//위쪽 길

		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			Upside->next = newtemp;
			newtemp->prev = Upside;

			Upside = Upside->next;
		}

		Node* Leftside = Upside;		//왼쪽 길

		for (int i = 0; i < 5; i++)
		{
			Node* newtemp = new Node;
			Leftside->next = newtemp;
			newtemp->prev = Leftside;

			Leftside = Leftside->next;
		}

		Node* Downside = Leftside;		//아래쪽 길

		for (int i = 0; i < 4; i++)
		{
			Node* newtemp = new Node;
			Downside->next = newtemp;
			newtemp->prev = Downside;

			Downside = Downside->next;
		}

		Downside->next = this;
		this->prev = Downside;		//아래 길과  우측 길 연결

	
		Node* Crossright = Rightside;		//우측 상단 대각선 길(직진)
		
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
				newtemp->cross = true;		//교차점 지정
				Crosspoint = newtemp;
			}

			Crossright = Crossright->next;
		}

		Crossright->next = Leftside;


		Node* Crossleft = Upside;		//우측 상단 대각선 길

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

	void PrintHorse(void)		//말 출력 함수
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

	void PrintMap(void)		//맵 출력 함수
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

		for (int i = 0; i < 6; i++)				//1줄 출력
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

			Left->PrintHorse();				//2줄 출력
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

			Left->PrintHorse();				//3줄 출력
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

			cout << "\t\t\t";				//4줄 출력
			CrossLeft->PrintHorse();
			cout << "\n\n";
			CrossLeft = CrossLeft->fast;
			CrossRight = CrossRight->next;

			Left->PrintHorse();				//5줄 출력
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

			Left->PrintHorse();				//5줄 출력
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

			for (int i = 0; i < 6; i++)				//1줄 출력
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
	int Yut[4];		//0->뒷면, 1->앞면
	MoveNode* next = NULL;
	


};

class MoveLink
{
public:
	MoveNode* head = NULL;

	bool Throw(void)			//윳 던지기 함수
	{
		MoveNode* temp = head;

		if (head == NULL)		//첫 윳 던지기일 때
		{
			head = new MoveNode;
			temp = head;
		}
		else
		{
			while (temp->next)		//기존에 던진 기록이 있을 경우
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
			prob[i] = rand() % 5;		//60프로 확률로 앞면
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

		


		if (count == 0)		//모일 경우 1 반환
		{
			temp->go = 5;
			cout << "Result is mo" << endl;
			return 1;
		}
		else if (count == 1)		//도일 경우 0 반환
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
		else if (count == 2)		//개일 경우 0 반환
		{
			temp->go = 2;
			cout << "Result is gae" << endl;
			return 0;
		}
		else if (count == 3)		//걸일 경우 0 반환
		{
			temp->go = 3;
			cout << "Result is goel" << endl;
			return 0;
		}
		else if (count == 4)		//윳일 경우 0 반환
		{
			temp->go = 4;
			cout << "Result is yut" << endl;
			return 1;
		}

	}

	int UseMoveNode(int selectMove)		//이동 거리를 고르는 함수
	{
		MoveNode* temp = head;

		if (selectMove == 1)		//처음 것을 고른 경우
		{
			int num = head->go;
			head = head->next;
			delete temp;
			return num;
		}

		for (int i = 1; i < selectMove - 1; i++)		//나중의 것을 고른 경우
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
	Player P1;			//P1 말
	Player P2;			//P2 말
	map->MakeMap();
	
	int turn = 2;

	while (true)
	{
		if (turn == 2)			//플레이어 순서
			turn = 1;
		else
			turn = 2;


		system("cls");
		map->PrintMap();
		cout << "Player " << turn << " turn!(throw/exit)" << endl;

		int state1 = Command();		//throw를 입력받을 시
		if (state1 == true)
		{
			if (YUT->Throw())			//윷이나 모가 나오면 다시 던짐
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
			cout << "Yut Results: ";			//던진 결과 출력
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

			move = YUT->UseMoveNode(selectMove);		//해당 이동을 사용하고 MoveNode에서 지움

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

				if (turn == 1)						//움직일 수 있는 말 표시
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

			//horse 움직이는 함수

		}
		else
		{
			return 0;
		}
	}

}
