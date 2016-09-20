#include <stdlib.h>
#include <string.h>

#include "list.h"

int mem_init()
{
	pthread_mutex_init(&g_storeMgr.l_mutex, NULL);
	
	g_storeMgr.all_size = 0;
	g_storeMgr.list = NULL; 

	return 0;	
}

void printList()
{
	Lnode *head = g_storeMgr.list;

	if(NULL == head)
	{
		return;
	}

	printf("all memory size: %d\n", g_storeMgr.all_size);

	Lnode *p = head;
	while(p)
	{
		printf("%s;%d;%d\n", p->function, p->line, p->memSize);
		p = p->next;
	}
}

void insertElem(Lnode **head, char *func, int line, int memSize, void *ptr)
{
	Lnode *temp = NULL;

	pthread_mutex_lock(&g_storeMgr.l_mutex);	
	do
	{
		if(NULL == (*head))
		{
			(*head) = malloc(sizeof(Lnode));
			(*head)->function = strdup(func);
			(*head)->line = line;
			(*head)->memSize = memSize;
			(*head)->ptr = ptr;
			(*head)->next = NULL;
			g_storeMgr.all_size += memSize;

			break;
		}

		temp = malloc(sizeof(Lnode));
		temp->function = strdup(func);
		temp->line = line;
		temp->memSize = memSize;
		temp->ptr = ptr;

		temp->next = (*head);
		(*head) = temp;

		g_storeMgr.all_size += memSize;

	}while(0);

	pthread_mutex_unlock(&g_storeMgr.l_mutex);	

}

void deleteElem(Lnode **head, void *ptr)
{
	Lnode *p = NULL;
	Lnode *q = NULL;
	if(NULL == *head)
		return;	

	pthread_mutex_lock(&g_storeMgr.l_mutex);
	do
	{
		p = *head;
		if(ptr == p->ptr)
		{
			free(p->function);
			*head = p->next;

			g_storeMgr.all_size -= p->memSize;

			free(p);

			break;
		}

		q = (*head)->next;
		while(q)
		{
			if(ptr == q->ptr)
			{
				free(q->function);
				g_storeMgr.all_size -= q->memSize;
				p = q->next;	
				free(q);	
				q = p;
				break;
			}

			q = q->next;	
		}

	}while(0);

	pthread_mutex_unlock(&g_storeMgr.l_mutex);
}

