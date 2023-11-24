#include<stdio.h>
struct input{
	char name[20];
	int bt,at,tat,wt,start,end;
}p[20],temp;

int m,n;
float awt = 0 ,atat = 0;

void process();
void take_input(){
	int i,j;
	printf("Enter the no of processes :");
	scanf("%d",&n);
	printf("Enter Process detials:\nName\tBT\tAT\n");
	for(i=0;i<n;i++){
		scanf("%s %d %d",&p[i].name,&p[i].bt,&p[i].at);
	}
}

void sort(){
	int i,j;
	for(i=0;i<n;i++){
		for(j = i+1;j<n;j++){
			if(p[i].at > p[j].at){
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
			if((p[i].bt > p[j].bt) && p[i].at != 0){
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}        
                 
void process(){
	int i;
	p[0].start = 0;
	p[0].end = p[0].bt;
	p[0].tat = p[0].end - p[0].at;
	atat += p[0].tat;
	p[0].wt = p[0].start - p[0].at ;
	awt += p[0].wt;
	
	for(i = 1; i < n; i++){ // Start the loop from 1
		p[i].start = p[i-1].end;
		p[i].end = p[i-1].end + p[i].bt;
		p[i].tat = p[i].end - p[i].at; 
		atat += p[i].tat;
		p[i].wt = p[i].start - p[i].at ;
		awt += p[i].wt;
	}
}

void print_output(){
    int i;
	printf("Grantt Chart => 0 - ");
	for(i=0;i<n;i++){
		printf("%s - %d - ",p[i].name,p[i].end);
	}
	printf("\nProcess\tStart\tEnd\tTAT\tWT\n");
	for(i=0;i<n;i++){
		printf("%s\t%d\t%d\t%d\t%d\n",p[i].name,p[i].start,p[i].end,p[i].tat,p[i].wt);
	}
	atat = atat/n;
	awt = awt/n;
	printf("Avg. TAT : %f\nAvg. WT : %f",atat,awt);
}

int main(){
	take_input();
	sort();
	print_output();
	return 0;
}