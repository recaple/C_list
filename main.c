#include <stdio.h>
#include <stdlib.h>

//определяем тип данных как структуру
typedef struct listItem
{
	int data;			//информационное поле
	listItem* next;		//ссылка на аналогичную структуру
} listItem;

listItem* add_inHead(listItem* head, int value)
{
	//выделяем память под новый элемент с использованием malloc
	//в этом случае время существования элемента определяется
	//программистом - до тех пор пока не будет вызван free
	listItem* newItem = (listItem*)malloc(sizeof(listItem));
	//инициализируем информационное поле
	newItem->data = value;
	//связываем новый элемент с существующим списком
	//деже если head=NULL, всё равно всё будет корректно
	newItem->next = head;
	//важно: возвращаем указатель на новый элемент,
	//он теперь будет новой головой списка
	return newItem;
}

listItem* add_inTail(listItem* head, int value)
{
	//создаём новый элемент
	listItem* newItem = (listItem*)malloc(sizeof(listItem));
	//инициализируем информационное поле
	newItem->data = value;
	//элемент будет последним в списке,
	//поэтому указатель на следующий - заведом NULL
	newItem->next = NULL;

	//если изначально список был пуст
	if (!head)
		//новый элемент будет его головой
		return newItem;

	//вводим вспомогательный указатель
	//для перемещения по списку
	listItem* current = head;

	//перебираем элементы списка
	while (current->next)
		current = current->next;
	//после выхода из цикла current
	//будет указывать на последний элемент списка

	//связваем последний элемент списка
	//с новым элементом
	current->next = newItem;

	//голова не изменилась, возвращаем старое значение
	return head;
}

void print(listItem* head)
{
	//вводим вспомогательный указатель
	//для перемещения по списку
	listItem* current = head;

	//перебираем элементы списка
	while (current)
	{
		//печатаем информационное поле
		//текущего элемента списка
		printf("%4d", current->data);
		current = current->next;
	}
	printf("\n");
}



listItem* add_Value(listItem* head, int value)		//добавление по возрастанию
{
	listItem* newItem = (listItem*)malloc(sizeof(listItem));
	newItem->data = value;
	newItem->next = NULL;

	if (!head)
		return newItem;

	listItem* current = head;

	while (current)
	{
		if (value > current->data)
			return add_inHead(head, value);
		if (current->next == NULL)
			return add_inTail(head, value);
		if (value > current->next->data && value <= current->data)
		{
			newItem->next = current->next;
			current->next = newItem;
			return head;
		}
		current = current->next;
	}
	return head;
}

void destroyList(listItem* head)
{
	//вводим вспомогательный указатель
	//для перемещения по списку
	listItem* current = head;

	//вводим вспомогательный указатель
	//для сохранения адреса предыдущего
	//элемента списка
	listItem* temp;

	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}


int main()
{
	listItem* head = NULL;

	head = add_Value(head, 1);
	print(head);
	head = add_Value(head, 5);
	print(head);
	head = add_Value(head, 3);
	print(head);
	head = add_Value(head, 4);
	print(head);
	head = add_Value(head, 2);
	print(head);
	head = add_Value(head, 2);
	print(head);
	head = add_Value(head, 0);
	print(head);
	head = add_Value(head, 6);
	print(head);

	destroyList(head);

	return 0;
}

