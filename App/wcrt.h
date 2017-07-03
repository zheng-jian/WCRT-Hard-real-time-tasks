#ifndef _WCRT_
#define _WCRT_

struct task
{
	int execution_time;
	int inter_arrival_time;
	int deadline;
	int priority;

	struct task *next;
	struct task *last;
};

struct task *read_information(FILE *fp, char *filename);

void all_wcrt(struct task *t);

int wcrt(struct task *t,int priority);

#endif