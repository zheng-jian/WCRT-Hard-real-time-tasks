#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wcrt.h"


struct task *initialization(struct task *t,int a){
	t=(struct task*)malloc(a*sizeof(struct task));
	for(int j=0;j<a;j++){
		(t+j)->next=(struct task*)malloc(sizeof(struct task));
		(t+j)->last=(struct task*)malloc(sizeof(struct task));
	}
	return t;
}
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
		int max_wcrt=0;
		int response_time=0;
		int q=0;
		int q1=1;
		w0=t->execution_time;

		while(1){
			int i=0;
			while(1){
			int sum=0;
			for(int j=0;j<num_highPriority;j++){
				sum=sum+(w0+table_intT[j]-1)/table_intT[j]*table_exeT[j];
			}
			int q1=(i+1)*t->execution_time+sum;
			w0=q1;
			if(q1==q){
				response_time=q1-i*t->inter_arrival_time;
				w0=t->execution_time;
				break;
			}else{
				q=q1;
			}
		}
		if(q1<=(i+1)*t->inter_arrival_time){
			max_wcrt=response_time;
			break;
		}else{
			i++;
		}
	}
		return max_wcrt;

	}
}

void all_wcrt(struct task *t){
	while(t!=NULL){
		int worst_time=wcrt(t,t->priority);
		printf("Priority %d task's wosrt-case response time is: %d\n",t->priority,worst_time);
		t=t->next;
	}

}

int main(int argc, char *argv[]){
	FILE *fp=NULL;
	int a=count_lines_number(fp,argv[1]);
	printf("%d\n",a );
	struct task *t=NULL;
    t=initialization(t,a);
	read_information(fp,argv[1],t,a);

	for(int k=0;k<a;k++){
		printf("%d %d %d %d\n",(t+k)->execution_time,(t+k)->inter_arrival_time,(t+k)->deadline,(t+k)->priority);
	}

	all_wcrt(t);
	return 0;
}