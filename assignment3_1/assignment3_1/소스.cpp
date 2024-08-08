#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class WORD
{
public:
	char words[1024];

	WORD* link;
};

void Addlist(WORD**, char*);		//�ܾ� �߰� �Լ�
char EndWord(char*);
void Printlist(WORD*);
void Deletelist(WORD*);

int main(void)
{
	WORD* head = NULL;

	while (true)
	{
		char cmd[1024];

		cout << "CMD(Word/exit)>> ";
		cin >> cmd;
		if (strcmp(cmd, "exit") == 0)		//��ɾ exit�� ���
		{
			Deletelist(head);		//Linked List ����
			return 0;
		}
		else
		{
			Addlist(&head, cmd);		//�ܾ� �߰�
			Printlist(head);		//�ܾ� ���
		}
	}
}

void Addlist(WORD** head, char* input)		//LinkedList�� �ܾ� �߰� �Լ�
{
	WORD* temp = new WORD;
	strcpy(temp->words, input);

	if (*head == NULL)			//ó�� �Է��� ���
	{
		temp->link = (*head);
		(*head) = temp;
	}
	else
	{
		WORD* cur = *head;
		while (cur->link != NULL)
		{
			if (strcmp(cur->words, temp->words) == 0)		//���� �ܾ��� ���
			{
				cout << "Already Exists" << endl;
				delete temp;
				return;
			}
			cur = cur->link;
		}

		if (strcmp(cur->words, temp->words) == 0)		//������ �ܾ ���� ���
		{
			cout << "Already Exists" << endl;
			delete temp;
			return;
		}

		if (temp->words[0] != EndWord(cur->words))		//������ �ܾ �Է��� �ܾ�� �̾����� �ʴ� ���
		{
			cout << "Not chained" << endl;
			delete temp;
			return;
		}

		temp->link = cur->link;
		cur->link = temp;

	}

	return;
}

char EndWord(char* words)		//������ �ܾ �������� �Լ�
{
	char temp;
	for (int i = 0; words[i] != '\0'; i++)
	{
		temp = words[i];
	}
	return temp;
}

void Printlist(WORD* head)		//����Ʈ ��� �Լ�
{
	for (WORD* temp = head; temp != NULL; temp = temp->link)
	{
		cout << temp->words << "->";
	}
	cout << "\n";

	return;
}

void Deletelist(WORD* head)		//����Ʈ �޸� �Ҵ� ���� �Լ�
{
	WORD* temp = head->link;

	if (temp != NULL)
	{
		Deletelist(temp);
	}
	return;
}