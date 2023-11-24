#include<stdio.h>
#include<string.h>

struct job{
    char name[20];
    int at,bt,ct,tat,wt,st,tbt;
}job[10];

int n,i,j;
float awt = 0,atat = 0;

void takeinput (){
    printf("Enter the no. of jobs :");
    scanf("%d",&n);
    printf("Enter the details\n");
    printf("Name\tAT\tBT\n");
    for(i=0;i<n;i++){
        scanf("%s",&job[i].name);
        scanf("%d",&job[i].at);
        scanf("%d",&job[i].bt);
        job[i].tat = job[i].bt;
        }
    printf("\nOKAY INPUT ACCEPTED.\n");
    for(i=0;i<n;i++){
        job[i].tat = job[i].bt;
    }
    printf("\nOKAY TURN AROUND SET.\n");
}

void sort(){
    struct job temp;
    printf("\nSTARTED SORTING.\n");
    for (i = 0; i < n; i++)
    {
        for (j= i+1; j < n; j++)
        {
        printf("\n [%d] [%d].\n",i,j);
            if (job[i].at > job[j].at)
            {
                temp = job[i];
                job[i] = job[j];
                job[j] = temp;
            }
        }
    }
}
void process(){
    float tbttime = 0;
    printf("\n STARTED PROCESS.\n");
    for (i = 0; i < n; i++)
    {
        job[i].st = job[i].at;
        printf("|%d\t%s",job[i].st,job[i].name);
        tbttime += job[i].bt;
        job[i].ct = tbttime;
        job[i].tat = tbttime - job[i].at;
        job[i].wt = job[i].tat - job[i].at;
        printf("%d |",tbttime);
    }
}

void printoutput(){
    printf("Process_id\tBT\tAT\tTAT\tWT");
    printf("\n STARTED PRINTING.\n");
    for ( i = 0; i < n; i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d\n",job[i].name,job[i].bt,job[i].at,job[i].tat,job[i].wt);
        atat = atat + job[i].tat;
        awt = awt + job[i].wt;
    }
    printf("Avg. wt = %f\n",awt);
    printf("Avg. tat = %f\n",atat);
}

int main(){
    takeinput();
    sort();
    process();
    printoutput();
    printf("\n END.\n");
    return 0;
}