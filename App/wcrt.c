#include <stdio.h>
#include <stdlib.h>
//#include "wcrt.h"

struct task
{
	int execution_time;
	int inter_arrival_time;
	int deadline;
	int priority;

	struct task *next;
	struct task *last;
};

void read_information(FILE *fp, char *filename, struct task *a,int nmax){	
	int i=0;
	if((fp=fopen(filename,"r"))==NULL){
		perror("fopen");
		exit(1);
	}

	while(fscanf(fp,"%d %d %d %d",&a->execution_time,&a->inter_arrival_time,&a->deadline,&a->priority)!=EOF){
		if(i==0)
			a->last=NULL;
		else
			a->last=a-1;

		if(i+1==nmax)
		{	
			a->next=NULL;
			break;
		}
		else
			a->next=a+1;

		a++;
	}
	rewind(fp);
	fclose(fp);

}

int count_lines_number(FILE *fp,char *name){
	int n=0;
	int ch;

	if((fp=fopen(name,"r"))==NULL)
	{
		fprintf(stderr,"open file error");
	}

	while((ch = fgetc(fp))!=EOF){
		if(ch=='\n')
			n++;
	}
	n=n+1;
	rewind(fp);
	fclose(fp);
	return n;
}



int main(int argc, char *argv[]){
	FILE *fp=NULL;
	int a=count_lines_number(fp,argv[1]);
	printf("%d\n",a );
	struct task *t=(struct task*)malloc(a*sizeof(struct task));
	for(int j=0;j<a;j++){
		(t+j)->next=(struct task*)malloc(sizeof(struct task));
		(t+j)->last=(struct task*)malloc(sizeof(struct task));
	}
	read_information(fp,argv[1],t,a);
	for(int k=0;k<a;k++){
		printf("%d %d %d %d\n",(t+k)->execution_time,(t+k)->inter_arrival_time,(t+k)->deadline,(t+k)->priority);
	}

	return 0;
}