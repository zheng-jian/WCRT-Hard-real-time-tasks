#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
		i++;
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

int find_max(int *w){
	int temp=0;
	for (int i = 0; i < 20; ++i)
	{
		if(w[i]>temp)
			temp=w[i];
	}
	return temp;
}

int wcrt(struct task *t,int priority){
	if(t->last==NULL)
		return t->execution_time;
	else
	{	
		struct task *p=t;
		int w0=t->execution_time;
		int num_highPriority=t->priority-1;
		int *table_exeT=(int *)malloc(sizeof(int)*num_highPriority);
		int *table_intT=(int *)malloc(sizeof(int)*num_highPriority);
		for(int i=0;i<num_highPriority;i++){
			table_exeT[i]=p->last->execution_time;
			table_intT[i]=p->last->inter_arrival_time;
			p=p->last;

		}
		int w[20]={1};
		int q=0;
		int q1=1;
		w0=t->execution_time;

		for(int i=0;i<20;i++){
			while(1){
			int sum=0;
			for(int j=0;j<num_highPriority;j++){
				sum=sum+(w0+table_intT[j]-1)/table_intT[j]*table_exeT[j];
			}
			int q1=(i+1)*t->execution_time+sum;
			w0=q1;
			if(q1==q){
				w[i]=q1-i*t->inter_arrival_time;
				w0=t->execution_time;
				break;
			}else{
				q=q1;
			}
		}
	}
		int max=find_max(w);
		return max;
	}

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
	struct task *p=t;
	struct task *q=t->next;
	struct task *q2=t->next->next;
	int chigh=wcrt(p,1);
	int clow=wcrt(q,2);
	int clow2=wcrt(q2,3);
	printf("rhigh:%d,rlow:%d,rlow2:%d\n",chigh,clow,clow2);
	return 0;
}