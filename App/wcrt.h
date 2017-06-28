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
struct task *initialization(struct task *t,int a);

void read_information(FILE *fp, char *filename, struct task *a,int nmax);

int count_lines_number(FILE *fp,char *name);

int find_max(int *table);

void all_wcrt(struct task *t);

int wcrt(struct task *t,int priority);

#endif