#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class WORD
{
public:
	char words[1024];

	WORD* link;
};

void Addlist(WORD**, char*);		//단어 추가 함수
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
		if (strcmp(cmd, "exit") == 0)		//명령어가 exit인 경우
		{
			Deletelist(head);		//Linked List 삭제
			return 0;
		}
		else
		{
			Addlist(&head, cmd);		//단어 추가
			Printlist(head);		//단어 출력
		}
	}
}

void Addlist(WORD** head, char* input)		//LinkedList에 단어 추가 함수
{
	WORD* temp = new WORD;
	strcpy(temp->words, input);

	if (*head == NULL)			//처음 입력일 경우
	{
		temp->link = (*head);
		(*head) = temp;
	}
	else
	{
		WORD* cur = *head;
		while (cur->link != NULL)
		{
			if (strcmp(cur->words, temp->words) == 0)		//같은 단어일 경우
			{
				cout << "Already Exists" << endl;
				delete temp;
				return;
			}
			cur = cur->link;
		}

		if (strcmp(cur->words, temp->words) == 0)		//마지막 단어가 같을 경우
		{
			cout << "Already Exists" << endl;
			delete temp;
			return;
		}

		if (temp->words[0] != EndWord(cur->words))		//마지막 단어가 입력한 단어와 이어지지 않는 경우
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

char EndWord(char* words)		//마지막 단어를 가져오는 함수
{
	char temp;
	for (int i = 0; words[i] != '\0'; i++)
	{
		temp = words[i];
	}
	return temp;
}

void Printlist(WORD* head)		//리스트 출력 함수
{
	for (WORD* temp = head; temp != NULL; temp = temp->link)
	{
		cout << temp->words << "->";
	}
	cout << "\n";

	return;
}

void Deletelist(WORD* head)		//리스트 메모리 할당 해제 함수
{
	WORD* temp = head->link;

	if (temp != NULL)
	{
		Deletelist(temp);
	}
	return;
}