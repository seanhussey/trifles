#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TS_NSEC_MAX 999999999
static struct timespec timespec_add(struct timespec a, struct timespec b)
{
	struct timespec ret;

	ret.tv_sec = a.tv_sec + b.tv_sec;

	ret.tv_nsec = a.tv_nsec + b.tv_nsec;

	if (ret.tv_nsec > TS_NSEC_MAX) {
		ret.tv_nsec -= TS_NSEC_MAX + 1;
		ret.tv_sec += 1;
	}

	return ret;
}

int main(int argc, char **argv)
{
	static struct timespec ts_ms = { .tv_sec = 0, .tv_nsec = 10000000 };
	if (argc != 1) {
		if (argc == 3) {
			ts_ms.tv_sec = atol(argv[1]);
			ts_ms.tv_nsec = atol(argv[2]);
		} else {
			fprintf(stderr, "usage: %s [secs per count] [nano secs per count]\n", argv[0]);
			return -1;
		}
	}

	static unsigned long x;
	struct timespec hasleft = {};
	for(;;) {
		struct timespec waitfor = timespec_add(ts_ms, hasleft);
		printf("%lu\r", x);
		x ++;
		fflush(stdout);
		nanosleep(&waitfor, &hasleft);
	}

	return 0;
}
