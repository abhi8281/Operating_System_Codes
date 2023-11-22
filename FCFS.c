#include <stdio.h>

struct proc{
        int proc,at,bt,tat,wt;
};

void sort();
void calculate();

struct proc p[10];
int a,b,n,temp;

void main()
{
        int i;
        printf("Enter the number of processes : ");
        scanf("%d",&n);
        printf("\n");
        for(i=0;i<n;i++)
        {
                scanf("%d %d %d",&p[i].proc,&p[i].at,&p[i].bt);

        }
        printf("Process ID \t Arrival Time \t Burst Time\n");
        for(i=0;i<n;i++)
        {
                printf("%d \t\t %d \t\t  %d",p[i].proc,p[i].at,p[i].bt);
                printf("\n");
        }

        sort();
        calculate();
}

void sort()
{
        struct proc temp;
        int i,j;
        for(i=0;i<n;i++)
        {
                for(j=0;j<n-1;j++)
                {
                        if(p[j].at>p[j+1].at)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }

        printf("Processes in sorted order:\n");
        printf("Processes ID \t Arrival Time \t Burst Time \n");

        for(i=0;i<n;i++)
        {
                printf("%d \t\t %d \t\t %d",p[i].proc,p[i].at,p[i].bt);
                printf("\n");
        }
}

void calculate()
{
                int i,j;
                float  atat=0,awt=0;
                float a=0;
                float b=0;

                p[0].tat = p[0].at + p[0].bt;

                for(i=1;i<n;i++)
                {
                        if(p[i-1].tat >= p[i].at)
                                p[i].tat = p[i-1].tat + p[i].bt;
                        else
                                p[i].tat = p[i].at + p[i].bt;
                }

                for(i=0;i<n;i++)
                {
                        p[i].tat = p[i].tat - p[i].at;
                        p[i].wt = p[i].tat - p[i].bt;
                        a += p[i].tat;
                        b += p[i].wt;
                }

                atat = a/4;
                awt = b/4;

                printf("\n");

                printf("Process ID \t Arrival Time \t Burst Time \t Turnaround Time \t Waiting Time \n");
                for(i=0;i<n;i++)
                {
                        printf("%d \t\t %d \t\t %d \t\t\t %d \t\t %d",p[i].proc,p[i].at,p[i].bt,p[i].tat,p[i].wt);
                        printf("\n");
                }

                printf("Average TurnaroundTime is : %f , Average Waiting Time : %f",atat,awt);
}
