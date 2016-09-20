#include "debug_mem.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern memManager g_storeMgr; 

void *debug_malloc(char *function, int line, size_t size)
{
	void *ptr = malloc(size);		
	if(!ptr)
		assert(0);

	insertElem(&(g_storeMgr.list), function, line, size, ptr);

	return ptr;
}

void debug_free(void *ptr)
{
	deleteElem(&(g_storeMgr.list), ptr);

	if(ptr)
		free(ptr);
}

void *debug_calloc(char *function, int line, size_t nmemb, size_t size)
{
	void *ptr = calloc(nmemb, size);
	if(!ptr)
		assert(0);

	insertElem(&(g_storeMgr.list), function, line, nmemb*size);	

	return ptr;
}
