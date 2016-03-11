#include <stdio.h>

#define EVENT_NUMBER 10
typedef int (*cb)(void *arg);
cb func[EVENT_NUMBER];

int event_init()
{
	int i;
	for (i = 0; i < EVENT_NUMBER; i++) {
		func[i] = NULL;
	}
	return 0;
}

int reg(cb user_func, int event)
{
	if ((user_func == NULL) && (event >= EVENT_NUMBER))
		return -1;

	func[event] = user_func;

	return 0;
}

int unreg(int event)
{
	if (event > EVENT_NUMBER) {
		printf("event > EVENT_NUMBER\n");
		return -1;
	}

	func[event] = NULL;
	return 0;
}

int send(int event, void *arg)
{
	if (event > EVENT_NUMBER) {
		printf("event > EVENT_NUMBER\n");
		return -1;
	}

	if (func[event] != NULL)
		func[event](arg);

	return 0;
}

int hello(void *arg)
{
	printf("%s\n", (char *)arg);

	return 0;
}

int main()
{
	event_init();
	reg(hello, 1);
	reg(hello, 2);
	send(1, "abc");
	send(2, "defg");
	return 0;
}
