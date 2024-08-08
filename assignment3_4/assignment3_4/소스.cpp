#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <ctime>
#include <windows.h>
using namespace std;

class Deck
{
private:
	char data[4];
	Deck* next;
public:
	void makeCard(void)
	{
		char Finput[3] = "SA";			//헤드에 들어갈 카드

		strcpy(data, Finput);

		Deck* temp = this;

		for (int i = 0; i < 4; i++)
		{
			char input[4];
			if (i == 0)				// 문자 배치
			{
				input[0] = 'S';
			}
			else if (i == 1)
			{
				input[0] = 'D';
			}
			else if (i == 2)
			{
				input[0] = 'H';
			}
			else
			{
				input[0] = 'C';
			}

			for (int j = 1; j < 14; j++)		//숫자 배치
			{

				if (j == 1)
				{
					input[1] = 'A';
					input[2] = '\0';
				}
				else if (j == 10)
				{
					input[1] = '1';
					input[2] = '0';
					input[3] = '\0';
				}
				else if (j == 11)
				{
					input[1] = 'J';
					input[2] = '\0';
				}
				else if (j == 12)
				{
					input[1] = 'Q';
					input[2] = '\0';
				}
				else if (j == 13)
				{
					input[1] = 'K';
					input[2] = '\0';
				}
				else
				{
					input[1] = j + 48;
					input[2] = '\0';
				}

				if (strcmp(input, "SA") != 0)
				{

					Deck* newTemp = new Deck;
					newTemp->setData(input);
					temp->setNext(newTemp);
					temp = temp->getNext();
				}

			}
		}
		temp->setNext(NULL);

		return;
	};

	char* getData(void)
	{
		return data;
	}

	void setData(char* input)
	{
		strcpy(data, input);
	}

	void setNext(Deck* input)
	{
		next = input;
	}

	Deck* getNext()
	{
		return next;
	}

	Deck* CardSuf(int& count)		//카드를 섞는 함수
	{


		if (next == NULL || count < 2)		//섞을 카드가 1장 이하일 경우 카드 주소 반환
		{
			return this;
		}
		else
		{
			int suf = rand() % (count - 1);		//카드 개수에서 일정 뭉치만큼 선택

			Deck* temp = this;
			for (int i = 0; i < suf; i++)
			{
				temp = temp->getNext();
			}
			suf = count - suf - 1;

			Deck* sufhead = temp->getNext();
			Deck* suffedhead = sufhead->CardSuf(suf);		//남은 카드를 그 갯수만큼 다시 섞음
			Deck* suffedtemp = suffedhead;

			while (suffedtemp->getNext())			//섞인 카드를 현재 카드 위에 올러둠
			{
				suffedtemp = suffedtemp->getNext();
			}
			suffedtemp->setNext(this);
			temp->setNext(NULL);

			return suffedhead;
		}
	}

	int checkCard(void)		//남은 카드의 갯수를 확인하는 함수
	{
		int i = 0;

		Deck* temp = this;

		while (temp)
		{
			i++;
			temp = temp->getNext();
		}

		return i;
	}


	void PrintCard(bool state)		//state에 따라 딜러가 출력하는 카드와 플레이어가 출력하는 카드 구별
	{
		if (state == true)
		{
			cout << '?' << '\t';
		}
		else
		{
			cout << data << '\t';
		}

		if (next != NULL)
		{
			next->PrintCard(false);
		}
		return;
	}

	void DeleteCard(void)		//카드 메모리 할당 해제
	{
		if (next)
		{
			next->DeleteCard();
		}

		delete next;
	}

};

class Discard_tray
{
private:
	Deck* head;
public:
	Discard_tray() { head = NULL; }

	~Discard_tray() {};

	Deck* Gethead(void)
	{
		return head;
	}

	void Sethead(Deck* input)
	{
		head = input;
	}

	void GetDiscard(Deck* input)		//덱을 버린 카드 위에 올려두는 함수
	{
		if (head == NULL)			//버린 덱이 없을 경우
		{
			head = input;
			return;
		}

		if (input == NULL)		//남은 카드가 없을 경우
		{
			return;
		}

		Deck* temp = input;
		while (temp->getNext())
		{
			temp = temp->getNext();
		}
		temp->setNext(head);
		head = input;

		return;

	}

	void Shuffle(Deck** UnusedDeck, int num)		//모든 카드를 버리는 카드 위에 올려두고 지정된 숫자만큼 셔플을 하는 함수
	{
		if (head != NULL)
		{
			Deck* temp = *UnusedDeck;

			while (temp->getNext())
			{
				temp = temp->getNext();
			}
			temp->setNext(head);
			head = *UnusedDeck;
		}
		else
		{
			head = *UnusedDeck;
		}



		for (int i = 0; i < num; i++)		//지정된 숫자만큼 셔플
		{
			int suf = 52;
			head = head->CardSuf(suf);
		}

		*UnusedDeck = head;
		head = NULL;

		return;
	}

};

class Player
{
private:
	Deck* card;			//플레이어의 덱
	int minsum;			//플레이어 카드의 최소합
	int Anum;			//A의 갯수
public:
	Player() { card = NULL; minsum = 0; Anum = 0; }

	void setCard(Deck** input)			//카드를 받는 함수
	{
		if ((*input)->getData()[1] == 'A')		//받은 카드가 A인 경우
		{
			Anum++;
			minsum++;
		}
		else if ((*input)->getData()[1] == '1' || (*input)->getData()[1] == 'J' || (*input)->getData()[1] == 'Q' || (*input)->getData()[1] == 'K')		//받은 카드가 10, J, Q, K인 경우
		{
			minsum += 10;
		}
		else
		{
			minsum += (int)(*input)->getData()[1] - 48;		//이외의 경우
		}

		if (card == NULL)			//기존 카드가 없던 경우
		{
			card = *input;
			*input = (*input)->getNext();
			card->setNext(NULL);
			return;
		}

		Deck* temp = card;
		while (temp->getNext())		//기존 카드가 있는 경우
		{
			temp = temp->getNext();
		}

		temp->setNext(*input);
		*input = (*input)->getNext();
		temp->getNext()->setNext(NULL);
		return;
	}

	Deck* gethead()
	{
		return card;
	}

	void sethead(Deck* input)
	{
		card = input;
	}

	int getMinsum(void)
	{
		return minsum;
	}

	void setAnum(int input)
	{
		Anum = input;
	}
	int getAnum(void)
	{
		return Anum;
	}

	void PrintCard(void)
	{
		card->PrintCard(false);			//플레이어는 모든 카드 출력
	}
};

class Dealer		//플레이어와 동일한 함수이나 약간 다름
{
private:
	Deck* card;
	int minsum;
	int Anum;
public:
	Dealer() { card = NULL; minsum = 0; Anum = 0; }

	void setCard(Deck** input)
	{
		if ((*input)->getData()[1] == 'A')
		{
			Anum++;
			minsum++;
		}
		else if ((*input)->getData()[1] == '1' || (*input)->getData()[1] == 'J' || (*input)->getData()[1] == 'Q' || (*input)->getData()[1] == 'K')
		{
			minsum += 10;
		}
		else
		{
			minsum += (int)(*input)->getData()[1] - 48;
		}

		if (card == NULL)
		{
			card = *input;
			*input = (*input)->getNext();
			card->setNext(NULL);
			return;
		}

		Deck* temp = card;
		while (temp->getNext())
		{
			temp = temp->getNext();
		}

		temp->setNext(*input);
		*input = (*input)->getNext();
		temp->getNext()->setNext(NULL);
		return;
	}

	Deck* gethead()
	{
		return card;
	}

	void sethead(Deck* input)
	{
		card = input;
	}

	int getMinsum(void)
	{
		return minsum;
	}

	void setAnum(int input)
	{
		Anum = input;
	}
	int getAnum(void)
	{
		return Anum;
	}


	void PrintCard(bool state)
	{
		card->PrintCard(state);			//출력 시 state에 따라 카드 한장을 공개하거나 숨김
	}
};



int main(void)
{
	srand((unsigned)time(NULL));

	Deck* BJ = new Deck;			//덱 생성
	Discard_tray suf;

	BJ->makeCard();

	while (true)
	{
		suf.Shuffle(&BJ, rand()%100);	//버려진 카드들을 모두 덱으로 불러들임

		char cmd[20];
		char cmd2[10];

		cout << "Command list(game/shuffle/exit)\n";
		cout << "CMD>> ";
		cin.getline(cmd, sizeof(cmd), '\n');
		int j = 0;
		bool state = false;
		for (int i = 0; cmd[i] != '\0' && i < 20; i++)			//하나의 입력을 공백을 기준으로 2가지 명령어로 나눔
		{
			if (state)
			{
				cmd2[j] = cmd[i];
				j++;
			}

			if (cmd[i] == ' ')
			{
				cmd[i] = '\0';
				state = true;
			}

		}
		cmd2[j] = '\0';

		if (strcmp(cmd, "game") == 0)			//게임 시작
		{
			while (true)
			{
				Player P1;
				Dealer Deal;

				P1.setCard(&BJ);
				Deal.setCard(&BJ);
				P1.setCard(&BJ);
				Deal.setCard(&BJ);

				cout << "Dealer Cards : ";				//카드를 건내받음
				Deal.PrintCard(true);
				cout << endl;

				cout << "Player Cards : ";
				P1.PrintCard();
				cout << endl;


				bool state = true;

				while (state)		//게임 종료 시 false로 탈출
				{
					char cmd3[10];
					cout << "Command list(hit/stand)\n";
					cout << "CMD>> ";
					cin.getline(cmd3, sizeof(cmd3), '\n');

					if (strcmp(cmd3, "hit") == 0)		//카드를  한 장 더 받음
					{
						system("cls");
						P1.setCard(&BJ);

						cout << "Dealer Cards : ";
						Deal.PrintCard(true);
						cout << endl;

						cout << "Player Cards : ";
						P1.PrintCard();
						cout << endl;

						if (P1.getMinsum() > 21)		//21 초과 시 게임 패배
						{
							cout << "Player Lose!\n";
							state = false;
						}
					}
					else if (strcmp(cmd3, "stand") == 0)
					{
						system("cls");
						while ((Deal.getMinsum() < 17 || (Deal.getAnum() == 1 && Deal.getMinsum() < 7)) && Deal.getMinsum() < 19)		//딜러가 주어진 조건에 따라 카드를 더 받음
						{
							Deal.setCard(&BJ);
						}
						cout << "Dealer Cards : ";
						Deal.PrintCard(false);
						cout << endl;

						cout << "Player Cards : ";
						P1.PrintCard();


						int P1num = P1.getMinsum();

						int Dealnum = Deal.getMinsum();				//21을 초과하지 않는 최대값 개산
						if (Deal.getAnum() > 0 && Deal.getMinsum() + 10 < 22)
						{
							Dealnum += 10;
						}
						if (P1.getAnum() > 0 && P1.getMinsum() + 10 < 22)
						{
							P1num += 10;
						}

						if (Dealnum > 21)				//딜러가 21 초과 시 게임 승리
						{
							cout << "Player win!\n";
						}
						else if (Dealnum > P1num)		//딜러보다 수가 작을 시 게임 패배
						{
							cout << "Player Lose!\n";
						}
						else if (Dealnum < P1num)		//딜러보다 수가 많을 시 게임 승리
						{
							cout << "Player win!\n";
						}
						else
						{
							cout << " Draw...\n";		//동점일 시 무승부
						}
						state = false;
					}
				}

				if (BJ->checkCard() < 13)		//남은 카드 계산 후 13장 미만 시 초기로 돌아감
				{
					cout << "Not Enough Cards\n";
					suf.GetDiscard(P1.gethead());
					suf.GetDiscard(Deal.gethead());
					suf.Shuffle(&BJ, 0);
					BJ->DeleteCard();
					delete BJ;
					break;
				}


				bool state2 = true;
				while (state2 == 1)			//남은 카드로 게임을 더 진행할 것인지 확인
				{
					char cmd4[10];

					cout << "Command list(bet/end)\n";
					cout << "CMD>> ";
					cin.getline(cmd4, sizeof(cmd4), '\n');



					if (strcmp(cmd4, "bet") == 0)		//게임을 더 진행할 경우
					{
						suf.GetDiscard(P1.gethead());
						suf.GetDiscard(Deal.gethead());
						state2 = false;
					}
					else if (strcmp(cmd4, "end") == 0)			//진행하지 않을 경우 메모리 할당 해제 후 함수 종료
					{
						suf.GetDiscard(P1.gethead());
						suf.GetDiscard(Deal.gethead());
						suf.Shuffle(&BJ, 0);
						BJ->DeleteCard();
						delete BJ;
						return 0;
					}


				}


			}
		}
		else if (strcmp(cmd, "shuffle") == 0)			//카드를 섞을 경우
		{
			int num;
			num = atoi(cmd2);
			suf.Shuffle(&BJ, num);
		}
		else if (strcmp(cmd, "exit") == 0)			//게임 종료 시 메모리 할당 해제 후 함수 종료
		{
			BJ->DeleteCard();
			delete BJ;
			return 0;
		}


	}
}