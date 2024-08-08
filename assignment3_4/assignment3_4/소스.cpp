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
		char Finput[3] = "SA";			//��忡 �� ī��

		strcpy(data, Finput);

		Deck* temp = this;

		for (int i = 0; i < 4; i++)
		{
			char input[4];
			if (i == 0)				// ���� ��ġ
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

			for (int j = 1; j < 14; j++)		//���� ��ġ
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

	Deck* CardSuf(int& count)		//ī�带 ���� �Լ�
	{


		if (next == NULL || count < 2)		//���� ī�尡 1�� ������ ��� ī�� �ּ� ��ȯ
		{
			return this;
		}
		else
		{
			int suf = rand() % (count - 1);		//ī�� �������� ���� ��ġ��ŭ ����

			Deck* temp = this;
			for (int i = 0; i < suf; i++)
			{
				temp = temp->getNext();
			}
			suf = count - suf - 1;

			Deck* sufhead = temp->getNext();
			Deck* suffedhead = sufhead->CardSuf(suf);		//���� ī�带 �� ������ŭ �ٽ� ����
			Deck* suffedtemp = suffedhead;

			while (suffedtemp->getNext())			//���� ī�带 ���� ī�� ���� �÷���
			{
				suffedtemp = suffedtemp->getNext();
			}
			suffedtemp->setNext(this);
			temp->setNext(NULL);

			return suffedhead;
		}
	}

	int checkCard(void)		//���� ī���� ������ Ȯ���ϴ� �Լ�
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


	void PrintCard(bool state)		//state�� ���� ������ ����ϴ� ī��� �÷��̾ ����ϴ� ī�� ����
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

	void DeleteCard(void)		//ī�� �޸� �Ҵ� ����
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

	void GetDiscard(Deck* input)		//���� ���� ī�� ���� �÷��δ� �Լ�
	{
		if (head == NULL)			//���� ���� ���� ���
		{
			head = input;
			return;
		}

		if (input == NULL)		//���� ī�尡 ���� ���
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

	void Shuffle(Deck** UnusedDeck, int num)		//��� ī�带 ������ ī�� ���� �÷��ΰ� ������ ���ڸ�ŭ ������ �ϴ� �Լ�
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



		for (int i = 0; i < num; i++)		//������ ���ڸ�ŭ ����
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
	Deck* card;			//�÷��̾��� ��
	int minsum;			//�÷��̾� ī���� �ּ���
	int Anum;			//A�� ����
public:
	Player() { card = NULL; minsum = 0; Anum = 0; }

	void setCard(Deck** input)			//ī�带 �޴� �Լ�
	{
		if ((*input)->getData()[1] == 'A')		//���� ī�尡 A�� ���
		{
			Anum++;
			minsum++;
		}
		else if ((*input)->getData()[1] == '1' || (*input)->getData()[1] == 'J' || (*input)->getData()[1] == 'Q' || (*input)->getData()[1] == 'K')		//���� ī�尡 10, J, Q, K�� ���
		{
			minsum += 10;
		}
		else
		{
			minsum += (int)(*input)->getData()[1] - 48;		//�̿��� ���
		}

		if (card == NULL)			//���� ī�尡 ���� ���
		{
			card = *input;
			*input = (*input)->getNext();
			card->setNext(NULL);
			return;
		}

		Deck* temp = card;
		while (temp->getNext())		//���� ī�尡 �ִ� ���
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
		card->PrintCard(false);			//�÷��̾�� ��� ī�� ���
	}
};

class Dealer		//�÷��̾�� ������ �Լ��̳� �ణ �ٸ�
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
		card->PrintCard(state);			//��� �� state�� ���� ī�� ������ �����ϰų� ����
	}
};



int main(void)
{
	srand((unsigned)time(NULL));

	Deck* BJ = new Deck;			//�� ����
	Discard_tray suf;

	BJ->makeCard();

	while (true)
	{
		suf.Shuffle(&BJ, rand()%100);	//������ ī����� ��� ������ �ҷ�����

		char cmd[20];
		char cmd2[10];

		cout << "Command list(game/shuffle/exit)\n";
		cout << "CMD>> ";
		cin.getline(cmd, sizeof(cmd), '\n');
		int j = 0;
		bool state = false;
		for (int i = 0; cmd[i] != '\0' && i < 20; i++)			//�ϳ��� �Է��� ������ �������� 2���� ��ɾ�� ����
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

		if (strcmp(cmd, "game") == 0)			//���� ����
		{
			while (true)
			{
				Player P1;
				Dealer Deal;

				P1.setCard(&BJ);
				Deal.setCard(&BJ);
				P1.setCard(&BJ);
				Deal.setCard(&BJ);

				cout << "Dealer Cards : ";				//ī�带 �ǳ�����
				Deal.PrintCard(true);
				cout << endl;

				cout << "Player Cards : ";
				P1.PrintCard();
				cout << endl;


				bool state = true;

				while (state)		//���� ���� �� false�� Ż��
				{
					char cmd3[10];
					cout << "Command list(hit/stand)\n";
					cout << "CMD>> ";
					cin.getline(cmd3, sizeof(cmd3), '\n');

					if (strcmp(cmd3, "hit") == 0)		//ī�带  �� �� �� ����
					{
						system("cls");
						P1.setCard(&BJ);

						cout << "Dealer Cards : ";
						Deal.PrintCard(true);
						cout << endl;

						cout << "Player Cards : ";
						P1.PrintCard();
						cout << endl;

						if (P1.getMinsum() > 21)		//21 �ʰ� �� ���� �й�
						{
							cout << "Player Lose!\n";
							state = false;
						}
					}
					else if (strcmp(cmd3, "stand") == 0)
					{
						system("cls");
						while ((Deal.getMinsum() < 17 || (Deal.getAnum() == 1 && Deal.getMinsum() < 7)) && Deal.getMinsum() < 19)		//������ �־��� ���ǿ� ���� ī�带 �� ����
						{
							Deal.setCard(&BJ);
						}
						cout << "Dealer Cards : ";
						Deal.PrintCard(false);
						cout << endl;

						cout << "Player Cards : ";
						P1.PrintCard();


						int P1num = P1.getMinsum();

						int Dealnum = Deal.getMinsum();				//21�� �ʰ����� �ʴ� �ִ밪 ����
						if (Deal.getAnum() > 0 && Deal.getMinsum() + 10 < 22)
						{
							Dealnum += 10;
						}
						if (P1.getAnum() > 0 && P1.getMinsum() + 10 < 22)
						{
							P1num += 10;
						}

						if (Dealnum > 21)				//������ 21 �ʰ� �� ���� �¸�
						{
							cout << "Player win!\n";
						}
						else if (Dealnum > P1num)		//�������� ���� ���� �� ���� �й�
						{
							cout << "Player Lose!\n";
						}
						else if (Dealnum < P1num)		//�������� ���� ���� �� ���� �¸�
						{
							cout << "Player win!\n";
						}
						else
						{
							cout << " Draw...\n";		//������ �� ���º�
						}
						state = false;
					}
				}

				if (BJ->checkCard() < 13)		//���� ī�� ��� �� 13�� �̸� �� �ʱ�� ���ư�
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
				while (state2 == 1)			//���� ī��� ������ �� ������ ������ Ȯ��
				{
					char cmd4[10];

					cout << "Command list(bet/end)\n";
					cout << "CMD>> ";
					cin.getline(cmd4, sizeof(cmd4), '\n');



					if (strcmp(cmd4, "bet") == 0)		//������ �� ������ ���
					{
						suf.GetDiscard(P1.gethead());
						suf.GetDiscard(Deal.gethead());
						state2 = false;
					}
					else if (strcmp(cmd4, "end") == 0)			//�������� ���� ��� �޸� �Ҵ� ���� �� �Լ� ����
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
		else if (strcmp(cmd, "shuffle") == 0)			//ī�带 ���� ���
		{
			int num;
			num = atoi(cmd2);
			suf.Shuffle(&BJ, num);
		}
		else if (strcmp(cmd, "exit") == 0)			//���� ���� �� �޸� �Ҵ� ���� �� �Լ� ����
		{
			BJ->DeleteCard();
			delete BJ;
			return 0;
		}


	}
}