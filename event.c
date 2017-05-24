#include <stdio.h>

/*system support event number*/
#define EVENT_NUMBER 2

/*the callback function of event*/
typedef int (*CB)(void *arg);
CB func[EVENT_NUMBER];

int event_init()
{
	int i;
	for (i = 0; i < EVENT_NUMBER; i++) {
		func[i] = NULL;
	}
	return 0;
}

int reg(CB user_func, int event)
{
	if ((user_func == NULL) && (event >= EVENT_NUMBER)) {
		printf("error: %s event(%d) >= EVENT_NUMBER(%d)\n",
			__func__, event, EVENT_NUMBER);
		return -1;
	}
	if (func[event] != NULL) {
		printf("attention: event is registered, now overwrite\n");
	}
	func[event] = user_func;

	return 0;
}

int unreg(int event)
{
	if (event >= EVENT_NUMBER) {
		printf("error: %s event(%d) >= EVENT_NUMBER(%d)\n",
			__func__, event, EVENT_NUMBER);
		return -1;
	}

	func[event] = NULL;
	return 0;
}

int send(int event, void *arg)
{
	if (event >= EVENT_NUMBER) {
		printf("error %s event(%d) >= EVENT_NUMBER(%d)\n",
			__func__, event, EVENT_NUMBER);
		return -1;
	}

	if (func[event] != NULL)
		func[event](arg);
	else
		printf("event(%d) not register\n", event);
	return 0;
}

int hello(void *arg)
{
	if (arg != NULL)
		printf("%s\n", (char *)arg);

	return 0;
}

int main()
{
	event_init();
	reg(hello, 1);
	reg(hello, 1);
	reg(hello, 2);
	reg(hello, 0);
	reg(hello, 0);
	send(1, "abc");
	send(2, "defg");
	send(2, "defg");
	send(2, "defg");
	send(6, "defg");
	send(0, "defg");
	return 0;
}
