# Memory-Pool
Memory Pool is just a test of a memory pool written in C

### Example
```C
#include "memorypool.h"

int main()
{
	MP_set(32);

	for (int i = 0; i < 3; i++)
	{
		*(int*)MP_alloc(4) = i;
	}

	MP_draw(1);
	
	MP_set(0);
	return 0;
}
```

![alt text](https://cloud.githubusercontent.com/assets/3034904/10660605/6e43f690-78a8-11e5-9ad6-a17c37b55c81.png)