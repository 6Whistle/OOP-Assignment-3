#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class menu_node		//가격 순 Linked List
{
private:
	char* menu;
	int price;
	menu_node* pPrev;
	menu_node* pNext;
public:
	menu_node(char* input) { menu = new char[strlen(input)]; strcpy(menu, input); pPrev = NULL; pNext = NULL; };
	~menu_node() { if(menu == nullptr) delete[] menu; }

	char* get_menu(void)
	{
		return menu;
	}

	int get_price(void)
	{
		return price;
	}
	void set_price(int input)
	{
		price = input;
		return;
	}
	menu_node* get_pPrev(void)
	{
		return pPrev;
	}
	void set_pPrev(menu_node* input)
	{
		pPrev = input;
		return;
	}
	menu_node* get_pNext(void)
	{
		return pNext;
	}
	void set_pNext(menu_node* input)
	{
		pNext = input;
		return;
	}
	void Delete_menu_node(void)			//메인함수 종료 시 메모리 할당 해제
	{
		if(pNext)
		{
			pNext->Delete_menu_node();

			delete pNext;
		}

	}

};

class bst_node		//이름 순
{
private:
	menu_node* pNode;
	bst_node* pLeft;
	bst_node* pRight;
public:

	bst_node() { pNode = NULL; pLeft = NULL; pRight = NULL; }
	~bst_node() { };

	void set_pNode(menu_node* input)
	{
		pNode = input;
	}
	menu_node* get_pNode()
	{
		return pNode;
	}
	void set_pLeft(bst_node* input)
	{
		pLeft = input;
	}
	bst_node* get_pLeft()
	{
		return pLeft;
	}
	void set_pRight(bst_node* input)
	{
		pRight = input;
	}
	bst_node* get_pRight()
	{
		return pRight;
	}
};

menu_node* InputMenu(menu_node**, char*, int);		//메뉴 Linked List 삽입 함수
void InputMenuByName(bst_node**, menu_node*);		//메뉴 이진트리 삽입 함수
void PrintByName(bst_node*);		//이진트리 출력 함수
void PrintByPrice(menu_node*);		//Linked List 출력 함수
int SearchMenu(menu_node*, char*);		//메뉴 이름 탐색 함수
bool DeleteBst_node(bst_node**, char*);		//특정 노드 이진트리에서 삭제
void DeleteMenu_node(menu_node**, char*);		//특정 노드 Linked List에서 삭제
void ExitBst(bst_node*);			//이진트리 메모리 할당 해제
void ExitMenu(menu_node*);		//Linked List 메모리 할당 해제

int main(void)
{
	menu_node* menu = NULL;
	bst_node* menu_n = NULL;

	while (true)
	{
		char cmd[10];

		cout << "Command list: LOAD, PRINT, INSERT, SEARCH, DELETE, EXIT" << endl;			//cmd 입력받음
		cout << "cmd>> ";
		cin >> cmd;

		if (strcmp(cmd, "LOAD") == 0)		//파일에서 불러오기
		{
			ifstream file;

			file.open("menu.txt");
			if (!file.is_open())			//파일이 열리지 않을 경우
			{
				cout << "File can't be open" << endl;
				return -1;
			}

			while (!file.eof())				//메모장에 입력 형태로 정보 확인 후 Linked List와 이진 트리에 노드 추가
			{
				char menu_name[100];
				int menu_price;

				file.getline(menu_name, sizeof(menu_name), ',');
				file >> menu_price;
				file.get();

				InputMenuByName(&menu_n, InputMenu(&menu, menu_name, menu_price));

			}
			file.close();
		}
		else if (strcmp(cmd, "PRINT") == 0)		//출력
		{
			if (menu == NULL)		//노드가 비어있을 경우
			{
				cout << "Cafe Menu is Empty\n";
			}
			else
			{
				char cmd2[20];

				cout << "Command list: MENU, PRICE";
				cout << "\nCMD>> ";
				cin.ignore();
				cin.getline(cmd2, sizeof(cmd2), '\n');		//cmd2 입력받음

				if (strcmp(cmd2, "MENU") == 0)			//이름 순 출력(이진트리)
				{
					cout << "Print by Name order\n";
					PrintByName(menu_n);
					cout << endl;
				}
				else if (strcmp(cmd2, "PRICE") == 0)		//가격 순 출력(Linked List)
				{
					cout << "Print by Price order\n";
					PrintByPrice(menu);
					cout << endl;
				}


			}
		}
		else if (strcmp(cmd, "INSERT") == 0)		//삽입을 입력받는 경우
		{
			char input_name[100];
			int input_price;

			cin.ignore();
			cout << "Menu Name: ";				//추가 노드의 정보를 입력받음
			cin.getline(input_name, sizeof(input_name), '\n');;
			cout << "Price: ";
			cin >> input_price;

			InputMenuByName(&menu_n, InputMenu(&menu, input_name, input_price));		//추가 노드를 Linked List와 이진 트리에 삽입
		}
		else if (strcmp(cmd, "SEARCH") == 0)		//탐색을 하는 경우
		{
			if (menu == NULL)			//입력된 정보가 없을 경우 에러 출력
			{
				cout << "Cafe Menu is Empty\n";
			}
			else
			{
				char cmd2[20];
				cin.ignore();
				cout << "Menu Name: ";
				cin.getline(cmd2, sizeof(cmd2), '\n');		//찾는 메뉴의 이름 입력

				int searchPrice = SearchMenu(menu, cmd2);		//금액 찾음(찾는 금액이 없을 경우 -1반환)
				if (searchPrice != -1)	
				{
					cout << cmd2 << "Price : " << searchPrice << endl;
				}


			}
		}
		else if (strcmp(cmd, "DELETE") == 0)		//메뉴 삭제 입력 시
		{
			if (menu == NULL)			//노드가 비어있으면 오류 출력
			{
				cout << "Cafe Menu is Empty\n";
			}
			else
			{
				cin.ignore();
				char cmd2[20];

				cout << "Menu Name: ";
				cin.getline(cmd2, sizeof(cmd2), '\n');		//삭제할 메뉴 입력받음

				if (DeleteBst_node(&menu_n, cmd2) == true)		//만약 이진트리에서 노드가 삭제되었을 경우 Linked List에서도 삭제
				{
					DeleteMenu_node(&menu, cmd2);
				}

			}
		}
		else if (strcmp(cmd, "EXIT") == 0)			//함수 종료 시 메모리 반환
		{
			ExitBst(menu_n);
			ExitMenu(menu);

			return 0;
		}
	}
}

menu_node* InputMenu(menu_node** head, char* inputmenu, int inputprice)			//데이터를 받아서 이를 Linked List에 추가하는 함수
{
	if (*head == NULL)			//노드가 비어있을 경우
	{
		*head = new menu_node(inputmenu);
		(*head)->set_price(inputprice);

		return (*head);
	}

	menu_node* curhead = *head;
	while (true)
	{
		if (strcmp(curhead->get_menu(), inputmenu) == 0)		//동일 이름 존재 시 에러 출력
		{
			cout << "Same data is exist!" << endl;
			return NULL;
		}

		if (curhead == *head && curhead->get_price() >= inputprice)			//가장 앞에 삽입되야할 경우
		{
			menu_node* temp = new menu_node(inputmenu);
			temp->set_price(inputprice);
			*head = temp;
			temp->set_pNext(curhead);
			curhead->set_pPrev(temp);

			return temp;
		}

		if (curhead->get_pNext() == NULL)			//다음 노드가 없을 경우
		{
			menu_node* temp = new menu_node(inputmenu);
			temp->set_price(inputprice);
			curhead->set_pNext(temp);
			temp->set_pPrev(curhead);

			return temp;
		}

		if (curhead->get_price() >= inputprice)		//현재 위치와 다음 위치 사이에 삽입되야할 경우
		{
			menu_node* temp = new menu_node(inputmenu);
			temp->set_price(inputprice);
			menu_node* prehead = curhead->get_pPrev();
			prehead->set_pNext(temp);
			temp->set_pPrev(prehead);
			temp->set_pNext(curhead);
			curhead->set_pPrev(temp);

			return temp;
		}
		curhead = curhead->get_pNext();
	}
}

void InputMenuByName(bst_node** head, menu_node* input)
{
	if (input == NULL)			//입력이 겹첬을 경우
	{
		return;
	}

	if ((*head) == NULL)		//입력된 노드가 없을 경우
	{
		(*head) = new bst_node;
		(*head)->set_pNode(input);

		return;
	}

	bst_node* curhead = (*head);
	while (true)
	{
		if (strcmp(input->get_menu(), curhead->get_pNode()->get_menu()) < 0)		//입력된 값이 먼저 나와야 할 경우
		{
			if (curhead->get_pLeft() == NULL)				//왼쪽 노드가 없는 경우
			{
				bst_node* temp = new bst_node;
				temp->set_pNode(input);
				curhead->set_pLeft(temp);
				return;
			}
			else
			{
				curhead = curhead->get_pLeft();			//왼쪽 노드가 있는 경우
			}
		}
		else
		{																			//입력된 값이 나중에 나와야 할 경우
			if (curhead->get_pRight() == NULL)			//오른쪽 노드가 없는 경우
			{
				bst_node* temp = new bst_node;
				temp->set_pNode(input);
				curhead->set_pRight(temp);
				return;
			}
			else
			{
				curhead = curhead->get_pRight();			//오른쪽 노드가 있는 경우
			}
		}
	}
}
void PrintByName(bst_node* head)					//in-order 방식으로 출력
{
	if (head == NULL)						//입력된 값이 없을 경우
	{
		return;
	}

	PrintByName(head->get_pLeft());	

	cout.width(20);
	cout << left << head->get_pNode()->get_menu();
	cout << head->get_pNode()->get_price() << endl;

	PrintByName(head->get_pRight());

	return;
}
void PrintByPrice(menu_node* head)		//Linked List 출력 함수
{
	if (head == NULL)
	{
		return;
	}

	cout.width(20);
	cout << left << head->get_menu();
	cout << head->get_price() << endl;

	PrintByPrice(head->get_pNext());
}

int SearchMenu(menu_node* head, char* input)		//메뉴 탐색 함수
{
	menu_node* temp = head;
	while (temp)
	{
		if (strcmp(temp->get_menu(), input) == 0)
		{
			return temp->get_price();
		}
		temp = temp->get_pNext();
	}

	cout << "Not in Menu\n";			//탐색되지 않았을 경우
	return -1;
}

bool DeleteBst_node(bst_node** head, char* input)			//bst에서 데이터를 삭제하는 함수
{
	bst_node* curTemp = *head;
	bst_node* preTemp = *head;

	while (curTemp)
	{

		if (strcmp(input, curTemp->get_pNode()->get_menu()) < 0)			//삭제하는 노드가 지금 노드보다 앞에 오는 경우
		{
			preTemp = curTemp;
			curTemp = curTemp->get_pLeft();
		}
		else if (strcmp(input, curTemp->get_pNode()->get_menu()) > 0)		//삭제하는 노드가 지금 노드보다 뒤에 오는 경우
		{
			preTemp = curTemp;
			curTemp = curTemp->get_pRight();
		}
		else
		{																	//현재 노드를 삭제해야 하는 경우
			if (curTemp == *head)				//지우는 위치가 head일 경우
			{
				bst_node* temp = NULL;
				if ((*head)->get_pLeft() != NULL)			//왼쪽 노드가 있을 경우
				{
					temp = (*head)->get_pLeft();

					while (temp->get_pRight())
					{
						temp = temp->get_pRight();
					}

					temp->set_pRight((*head)->get_pRight());
					temp = (*head)->get_pLeft();
					delete (*head);
					*head = temp;

					return true;

				}
				else if ((*head)->get_pRight() != NULL)				//오른쪽 노드만 있을 경우
				{
					bst_node* temp = (*head)->get_pRight();
					delete (*head);
					*head = temp;

					return true;
				}
				else
				{
					delete (*head);						//가장 마지막에 위치한 노드일 경우
					(*head) = NULL;
					
					return true;
				}
			}

			bst_node* curRight = curTemp->get_pRight();

			if (curTemp->get_pLeft() != NULL)				//왼쪽 노드가 있을 경우
			{
				bst_node* temp = curTemp->get_pLeft();
				while (temp->get_pRight())
				{
					temp = temp->get_pRight();
				}
				temp->set_pRight(curRight);

				if (preTemp->get_pLeft() == curTemp)
				{
					preTemp->set_pLeft(curTemp->get_pLeft());

				}
				else
				{
					preTemp->set_pRight(curTemp->get_pLeft());
				}
			}
			else if (curTemp->get_pRight() != NULL)			//오른쪽 노드만 있을 경우
			{
				if (preTemp->get_pLeft() == curTemp)
				{
					preTemp->set_pLeft(curTemp->get_pRight());

				}
				else
				{
					preTemp->set_pRight(curTemp->get_pRight());
				}
			}
			else
			{
				if (preTemp->get_pLeft() == curTemp)				//마지막 위치의 노드일 경우
				{
					preTemp->set_pLeft(NULL);

				}
				else
				{
					preTemp->set_pRight(NULL);
				}
			}

			delete curTemp;

			return true;
		}
	}

	cout << "Not in Menu\n";			//삭제가 되지 않은 경우
	return false;
}
void DeleteMenu_node(menu_node** head, char* input)			//Linked List에서 노드 삭제 함수
{
	menu_node* temp = (*head);

	while (temp)
	{
		if (strcmp(input, temp->get_menu()) == 0)		//삭제 노드 발견 시
		{

			if (temp == (*head))			//헤드일 경우
			{
				(*head) = temp->get_pNext();
				temp->get_pNext()->set_pPrev(NULL);
			}
			else
			{
				temp->get_pPrev()->set_pNext(temp->get_pNext());		//아닌 경우
				temp->get_pNext()->set_pPrev(temp->get_pPrev());
			}

			delete temp;
			return;
		}
		temp = temp->get_pNext();
	}
}

void ExitMenu(menu_node* mHead)			//Linked List 메모리 할당 해제 함수
{
	menu_node* mTemp = mHead;

	if (mHead == NULL)
		return;

	if (mTemp->get_pNext() != NULL)
	{
		ExitMenu(mTemp->get_pNext());
	}

	mTemp->Delete_menu_node();
	delete mTemp;

	return;

}

void ExitBst(bst_node* bHead)			//이진 트리 메모리 할당 해제 함수
{
	bst_node* pTemp = bHead;

	if (bHead == NULL)
		return;

	if (pTemp->get_pLeft() != NULL)
	{
		ExitBst(pTemp->get_pLeft());
	}

	if (pTemp->get_pRight() != NULL)
	{
		ExitBst(pTemp->get_pLeft());
	}

	delete pTemp;
	return;


}