#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class menu_node		//���� �� Linked List
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
	void Delete_menu_node(void)			//�����Լ� ���� �� �޸� �Ҵ� ����
	{
		if(pNext)
		{
			pNext->Delete_menu_node();

			delete pNext;
		}

	}

};

class bst_node		//�̸� ��
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

menu_node* InputMenu(menu_node**, char*, int);		//�޴� Linked List ���� �Լ�
void InputMenuByName(bst_node**, menu_node*);		//�޴� ����Ʈ�� ���� �Լ�
void PrintByName(bst_node*);		//����Ʈ�� ��� �Լ�
void PrintByPrice(menu_node*);		//Linked List ��� �Լ�
int SearchMenu(menu_node*, char*);		//�޴� �̸� Ž�� �Լ�
bool DeleteBst_node(bst_node**, char*);		//Ư�� ��� ����Ʈ������ ����
void DeleteMenu_node(menu_node**, char*);		//Ư�� ��� Linked List���� ����
void ExitBst(bst_node*);			//����Ʈ�� �޸� �Ҵ� ����
void ExitMenu(menu_node*);		//Linked List �޸� �Ҵ� ����

int main(void)
{
	menu_node* menu = NULL;
	bst_node* menu_n = NULL;

	while (true)
	{
		char cmd[10];

		cout << "Command list: LOAD, PRINT, INSERT, SEARCH, DELETE, EXIT" << endl;			//cmd �Է¹���
		cout << "cmd>> ";
		cin >> cmd;

		if (strcmp(cmd, "LOAD") == 0)		//���Ͽ��� �ҷ�����
		{
			ifstream file;

			file.open("menu.txt");
			if (!file.is_open())			//������ ������ ���� ���
			{
				cout << "File can't be open" << endl;
				return -1;
			}

			while (!file.eof())				//�޸��忡 �Է� ���·� ���� Ȯ�� �� Linked List�� ���� Ʈ���� ��� �߰�
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
		else if (strcmp(cmd, "PRINT") == 0)		//���
		{
			if (menu == NULL)		//��尡 ������� ���
			{
				cout << "Cafe Menu is Empty\n";
			}
			else
			{
				char cmd2[20];

				cout << "Command list: MENU, PRICE";
				cout << "\nCMD>> ";
				cin.ignore();
				cin.getline(cmd2, sizeof(cmd2), '\n');		//cmd2 �Է¹���

				if (strcmp(cmd2, "MENU") == 0)			//�̸� �� ���(����Ʈ��)
				{
					cout << "Print by Name order\n";
					PrintByName(menu_n);
					cout << endl;
				}
				else if (strcmp(cmd2, "PRICE") == 0)		//���� �� ���(Linked List)
				{
					cout << "Print by Price order\n";
					PrintByPrice(menu);
					cout << endl;
				}


			}
		}
		else if (strcmp(cmd, "INSERT") == 0)		//������ �Է¹޴� ���
		{
			char input_name[100];
			int input_price;

			cin.ignore();
			cout << "Menu Name: ";				//�߰� ����� ������ �Է¹���
			cin.getline(input_name, sizeof(input_name), '\n');;
			cout << "Price: ";
			cin >> input_price;

			InputMenuByName(&menu_n, InputMenu(&menu, input_name, input_price));		//�߰� ��带 Linked List�� ���� Ʈ���� ����
		}
		else if (strcmp(cmd, "SEARCH") == 0)		//Ž���� �ϴ� ���
		{
			if (menu == NULL)			//�Էµ� ������ ���� ��� ���� ���
			{
				cout << "Cafe Menu is Empty\n";
			}
			else
			{
				char cmd2[20];
				cin.ignore();
				cout << "Menu Name: ";
				cin.getline(cmd2, sizeof(cmd2), '\n');		//ã�� �޴��� �̸� �Է�

				int searchPrice = SearchMenu(menu, cmd2);		//�ݾ� ã��(ã�� �ݾ��� ���� ��� -1��ȯ)
				if (searchPrice != -1)	
				{
					cout << cmd2 << "Price : " << searchPrice << endl;
				}


			}
		}
		else if (strcmp(cmd, "DELETE") == 0)		//�޴� ���� �Է� ��
		{
			if (menu == NULL)			//��尡 ��������� ���� ���
			{
				cout << "Cafe Menu is Empty\n";
			}
			else
			{
				cin.ignore();
				char cmd2[20];

				cout << "Menu Name: ";
				cin.getline(cmd2, sizeof(cmd2), '\n');		//������ �޴� �Է¹���

				if (DeleteBst_node(&menu_n, cmd2) == true)		//���� ����Ʈ������ ��尡 �����Ǿ��� ��� Linked List������ ����
				{
					DeleteMenu_node(&menu, cmd2);
				}

			}
		}
		else if (strcmp(cmd, "EXIT") == 0)			//�Լ� ���� �� �޸� ��ȯ
		{
			ExitBst(menu_n);
			ExitMenu(menu);

			return 0;
		}
	}
}

menu_node* InputMenu(menu_node** head, char* inputmenu, int inputprice)			//�����͸� �޾Ƽ� �̸� Linked List�� �߰��ϴ� �Լ�
{
	if (*head == NULL)			//��尡 ������� ���
	{
		*head = new menu_node(inputmenu);
		(*head)->set_price(inputprice);

		return (*head);
	}

	menu_node* curhead = *head;
	while (true)
	{
		if (strcmp(curhead->get_menu(), inputmenu) == 0)		//���� �̸� ���� �� ���� ���
		{
			cout << "Same data is exist!" << endl;
			return NULL;
		}

		if (curhead == *head && curhead->get_price() >= inputprice)			//���� �տ� ���ԵǾ��� ���
		{
			menu_node* temp = new menu_node(inputmenu);
			temp->set_price(inputprice);
			*head = temp;
			temp->set_pNext(curhead);
			curhead->set_pPrev(temp);

			return temp;
		}

		if (curhead->get_pNext() == NULL)			//���� ��尡 ���� ���
		{
			menu_node* temp = new menu_node(inputmenu);
			temp->set_price(inputprice);
			curhead->set_pNext(temp);
			temp->set_pPrev(curhead);

			return temp;
		}

		if (curhead->get_price() >= inputprice)		//���� ��ġ�� ���� ��ġ ���̿� ���ԵǾ��� ���
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
	if (input == NULL)			//�Է��� ��ú�� ���
	{
		return;
	}

	if ((*head) == NULL)		//�Էµ� ��尡 ���� ���
	{
		(*head) = new bst_node;
		(*head)->set_pNode(input);

		return;
	}

	bst_node* curhead = (*head);
	while (true)
	{
		if (strcmp(input->get_menu(), curhead->get_pNode()->get_menu()) < 0)		//�Էµ� ���� ���� ���;� �� ���
		{
			if (curhead->get_pLeft() == NULL)				//���� ��尡 ���� ���
			{
				bst_node* temp = new bst_node;
				temp->set_pNode(input);
				curhead->set_pLeft(temp);
				return;
			}
			else
			{
				curhead = curhead->get_pLeft();			//���� ��尡 �ִ� ���
			}
		}
		else
		{																			//�Էµ� ���� ���߿� ���;� �� ���
			if (curhead->get_pRight() == NULL)			//������ ��尡 ���� ���
			{
				bst_node* temp = new bst_node;
				temp->set_pNode(input);
				curhead->set_pRight(temp);
				return;
			}
			else
			{
				curhead = curhead->get_pRight();			//������ ��尡 �ִ� ���
			}
		}
	}
}
void PrintByName(bst_node* head)					//in-order ������� ���
{
	if (head == NULL)						//�Էµ� ���� ���� ���
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
void PrintByPrice(menu_node* head)		//Linked List ��� �Լ�
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

int SearchMenu(menu_node* head, char* input)		//�޴� Ž�� �Լ�
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

	cout << "Not in Menu\n";			//Ž������ �ʾ��� ���
	return -1;
}

bool DeleteBst_node(bst_node** head, char* input)			//bst���� �����͸� �����ϴ� �Լ�
{
	bst_node* curTemp = *head;
	bst_node* preTemp = *head;

	while (curTemp)
	{

		if (strcmp(input, curTemp->get_pNode()->get_menu()) < 0)			//�����ϴ� ��尡 ���� ��庸�� �տ� ���� ���
		{
			preTemp = curTemp;
			curTemp = curTemp->get_pLeft();
		}
		else if (strcmp(input, curTemp->get_pNode()->get_menu()) > 0)		//�����ϴ� ��尡 ���� ��庸�� �ڿ� ���� ���
		{
			preTemp = curTemp;
			curTemp = curTemp->get_pRight();
		}
		else
		{																	//���� ��带 �����ؾ� �ϴ� ���
			if (curTemp == *head)				//����� ��ġ�� head�� ���
			{
				bst_node* temp = NULL;
				if ((*head)->get_pLeft() != NULL)			//���� ��尡 ���� ���
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
				else if ((*head)->get_pRight() != NULL)				//������ ��常 ���� ���
				{
					bst_node* temp = (*head)->get_pRight();
					delete (*head);
					*head = temp;

					return true;
				}
				else
				{
					delete (*head);						//���� �������� ��ġ�� ����� ���
					(*head) = NULL;
					
					return true;
				}
			}

			bst_node* curRight = curTemp->get_pRight();

			if (curTemp->get_pLeft() != NULL)				//���� ��尡 ���� ���
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
			else if (curTemp->get_pRight() != NULL)			//������ ��常 ���� ���
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
				if (preTemp->get_pLeft() == curTemp)				//������ ��ġ�� ����� ���
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

	cout << "Not in Menu\n";			//������ ���� ���� ���
	return false;
}
void DeleteMenu_node(menu_node** head, char* input)			//Linked List���� ��� ���� �Լ�
{
	menu_node* temp = (*head);

	while (temp)
	{
		if (strcmp(input, temp->get_menu()) == 0)		//���� ��� �߰� ��
		{

			if (temp == (*head))			//����� ���
			{
				(*head) = temp->get_pNext();
				temp->get_pNext()->set_pPrev(NULL);
			}
			else
			{
				temp->get_pPrev()->set_pNext(temp->get_pNext());		//�ƴ� ���
				temp->get_pNext()->set_pPrev(temp->get_pPrev());
			}

			delete temp;
			return;
		}
		temp = temp->get_pNext();
	}
}

void ExitMenu(menu_node* mHead)			//Linked List �޸� �Ҵ� ���� �Լ�
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

void ExitBst(bst_node* bHead)			//���� Ʈ�� �޸� �Ҵ� ���� �Լ�
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