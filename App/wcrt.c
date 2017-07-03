#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wcrt.h"



/*	La fonction read_information transporte les donnees de un ficher .txt a
	les structs, et connecter les pointeurs entre les structs.
*/
struct task *read_information(FILE *fp, char *filename){	
	if((fp=fopen(filename,"r"))==NULL){
		perror("fopen");
		exit(1);
	}
	else{
		char ch=fgetc(fp);
	if(ch==EOF){
		printf("empty file\n");
		exit(1);
	}
	rewind(fp);
	struct task *ptail=NULL;
	struct task *pnew=NULL;

	struct task *phead=(struct task*)malloc(sizeof(struct task));
	fscanf(fp,"%d %d %d %d",&phead->execution_time,&phead->inter_arrival_time,&phead->deadline,&phead->priority);
	phead->next=NULL;
	phead->last=NULL;
	ptail=phead;

	while(!feof(fp)){
		pnew = (struct task*)malloc(sizeof(struct task));
		fscanf(fp,"%d %d %d %d",&pnew->execution_time,&pnew->inter_arrival_time,&pnew->deadline,&pnew->priority);
		pnew->next=NULL;
		pnew->last=ptail;
		ptail->next=pnew;
		ptail=pnew;
	}
	rewind(fp);
	fclose(fp);
	return phead;
}
}



/*	La fonction estimate detecter si le processeur peut accomplir tous les 
	tasks. C'est a dire la somme de tous les execution_time/inter_arrival_time doit 
	etre inferieur a 1.
*/
int estimate(struct task *t){
	int count=0;
	struct task *p=t;
	while(p!=NULL){
		count++;	//calculer combien de task;
		p=p->next;
	}
	int *table_exeTime=(int *)malloc(sizeof(int)*count);
	int *table_inter_arrTime=(int *)malloc(sizeof(int)*count);
	for(int i=0;i<count;i++){
		//stocker les execution time de tous les tasks
		table_exeTime[i] = t->execution_time;				
		//stocker les inter arrival time de tous les tasks
		table_inter_arrTime[i] = t->inter_arrival_time;
		t=t->next;
	}

	//denominateur
	int denominator=1;
	for(int i=0;i<count;i++)
		denominator=denominator*table_inter_arrTime[i];
	//numerateur
	int numerator=0;
	for(int i=0;i<count;i++){
		numerator=numerator+table_exeTime[i]*denominator/table_inter_arrTime[i];
	}
	free(table_exeTime);
	table_exeTime=NULL;
	free(table_inter_arrTime);
	table_inter_arrTime=NULL;
	if(numerator>denominator)
		return -1;
	else
		return 0;
}

/*	La fonction wcrt calcule le worst-case response time d'un task
*/
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

			//Cet circulation calcule la fenetre occupee de la periode i
			while(1){
			int sum=0;
			for(int j=0;j<num_highPriority;j++){
				// calculer tous les execution_time des task superieurs
				sum=sum+(w0+table_intT[j]-1)/table_intT[j]*table_exeT[j];
			}
			//temps de la fenetre occupee
			int q1=(i+1)*t->execution_time+sum;
			// si le temps occupee de cette foie egale la derniere foie, c'est fini
			if(q1==q){
				response_time=q1-i*t->inter_arrival_time;
				break;
			}else{
				q=q1;
				w0=q1;
			}
		}

		//trouver le maximal temps response 
		if(response_time>=max_wcrt)
			max_wcrt=response_time;
		//quand temps occupee est moins que (i+1) foie de periode, c'est fini,q ne augmente pas
		if(q1<=(i+1)*t->inter_arrival_time){
			break;
		}else{
			i++;
		}
	}
	free(table_exeT);
	table_exeT=NULL;
	free(table_intT);
	table_intT=NULL;
		return max_wcrt;

	}
}

/*	Cette founction affiche tous les wcrt de les tasks
*/
void all_wcrt(struct task *t){
	while(t!=NULL){
		int worst_time=wcrt(t,t->priority);
		printf("Priority %d task's wosrt-case response time is: %d\n",t->priority,worst_time);
		t=t->next;
	}

}

int main(int argc, char *argv[]){
	FILE *fp=NULL;
	struct task *t=read_information(fp,argv[1]);
	struct task *a=t;
	
	while(a!=NULL){
		printf("%d %d %d %d\n",a->execution_time,a->inter_arrival_time,a->deadline,a->priority);
		a=a->next;
	}
	if(estimate(t)==0){
		all_wcrt(t);
	}
	else
		printf("Error, cant complete all the tasks\n");
	return 0;
}