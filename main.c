#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "debug_mem.h"

void test1()
{
	char *p = DEBUG_MALLOC(156);
	p = DEBUG_MALLOC(6);
	DEBUG_FREE(p);

	p = DEBUG_MALLOC(9);
	p = DEBUG_MALLOC(10);
	DEBUG_FREE(p);
}


int main(void)
{
	mem_init();		

	test1();

	printList();
	
	return 0;
}
