#ifndef _WCRT_
#define _WCRT_

struct task
{
	int execution_time;
	int inter_arrival_time;
	int deadline;
	int priority;

	struct task *next=NULL;
	struct task *last=NULL;
};

void read_information();

int find_max(int *table);

int wcrt(task t);