#include <stdio.h>
#include <pthread.h>

typedef struct Node
{
	char *function;
	int line;
	int memSize;
	struct Node *next;
	void *ptr;
}Lnode;

typedef struct memManager_t
{
	Lnode *list;
	pthread_mutex_t l_mutex;
	int all_size;
}memManager;


memManager g_storeMgr;


void printList();
void insertElem(Lnode **head, char *function, int line, int memSize, void *ptr);
void deleteElem(Lnode **head, void *ptr);
int mem_init();
