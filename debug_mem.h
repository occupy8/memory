
#define DEBUG_MALLOC(size)  debug_malloc(__func__, __LINE__, size)
#define DEBUG_FREE(ptr)  debug_free(ptr)
#define DEBUG_CALLOC(nmemb, size) debug_calloc(__func__, __LINE__, nmemb, size)

