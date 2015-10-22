#include <stdio.h>
#include <string.h>

#include "memorypool.h"

struct MemoryPool
{
	unsigned int max_size;
	unsigned int index;

	char *buffer;

	void *objs;
};

static struct MemoryPool mp;


int MP_set(unsigned int size)
{
	mp.index = 0;
	mp.max_size = 0;
	mp.buffer = NULL;

	if (size != 0)
	{
		mp.buffer = malloc(size);

		if (mp.buffer == NULL)
			return 1;

		mp.max_size = size;
	}
	else
		free(mp.buffer);

	return 0;
}

int MP_add(unsigned int size)
{
	if (size != 0)
	{
		char *tbuff = (int *)realloc(mp.buffer, mp.max_size + size);

		if (tbuff == NULL)
			return 1;

		mp.buffer = tbuff;
		mp.max_size += size;
	}

	return 0;
}


void MP_draw(int visual)
{
	printf("[Pool allocator]\n\t[Size]: %d\n\t[Current]: %d\n", mp.max_size, mp.index);

	if (visual)
	{
		printf("\t[Visual]: ");
		for (unsigned int i = 0; i < mp.max_size; i++)
		{
			printf("%c", i < mp.index ? 254 : 'X');
		}
		printf("\n");
	}

}


void* MP_alloc(unsigned int obj_size)
{
	if (mp.index + obj_size <= mp.max_size)
	{
		unsigned int old_index = mp.index;

		mp.index += obj_size;

		return &mp.buffer[old_index];
	}

	// if there's no enough mem we reallocate it
	// and (if success) retry the operation
	if (MP_add((int)(mp.max_size * 0.5)))
		return NULL;

	return MP_alloc(obj_size);
}

void MP_dealloc(unsigned int size)
{
	// todo implement defragmentation
}