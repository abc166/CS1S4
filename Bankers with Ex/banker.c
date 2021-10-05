#include <stdio.h>
#include <stdlib.h>

void display(int [][10], int , int );
int calculate(int , int , int [][10], int [][10], int[], int [][10], int [], int []);

int main()
{
    int Alloc[10][10], Max[10][10], Need[10][10], Avail[10], pno, rno;
    int completed[10], safe[10], count;
    char ch;

    printf("Enter the total number of processes:");
    scanf("%d", &pno);

    printf("Enter the total number of resources:");
    scanf("%d", &rno);
    for (int i = 0; i < pno; i++)
    {
        printf("\n Process %d\n", i + 1);
        printf("Enter the allocation matrix for each process:");
        for (int j = 0; j < rno; j++)
        {
            scanf("%d", &Alloc[i][j]);
        }
        printf("Enter the Max matrix for each process:");
        for(int j = 0; j < rno; j++)
        {
            scanf("%d", &Max[i][j]);
        }
    }
    printf("Enter the available resources:");
    for (int i = 0; i < rno; i++)
    {
        scanf("%d", &Avail[i]);
    }
   
    count=calculate(pno, rno, Need, Max, Avail, Alloc, completed, safe);
    printf("\nAllocaton\n");
    display(Alloc, rno, pno);
    printf("\n\nMaximum\n");
    display(Max, rno, pno);
    printf("\n\nNeed\n");
    display(Need, rno, pno); 
    if(count==1)
    {
        printf("\n\nSafe sequence generated\n");
        for(int i=0;i<pno;i++)
            printf("P%d\t",safe[i]);
        printf("\nDo you want resource request\n");
        scanf("%s",&ch);
        if(ch=='y')
        {
          int req[0][10];
          int i,pid;
          printf("\nenter the process id\n");
          scanf("%d",&pid);
          printf("\nenter the new request for that process:");
          for(i=0;i<rno;i++)
            scanf("%d",&req[0][i]);
          
          for(i=0;i<rno;i++)
          {
            if(req[0][i]>Avail[i])
              printf("Not possible");
              exit(0);
          }
          for(i=0;i<rno;i++)
          {
            if(req[0][i]>Need[pid][i])
              printf("Not possible due to need");
              exit(0);
          }

          for(i=0;i<rno;i++)
          {
            Avail[i]-=req[0][i];
            Alloc[pid][i]+=req[0][i];
            Need[pid][i]-=req[0][i];
          }
          int val=calculate(pno,rno,Need,Max,Avail,Alloc,completed,safe);
          if(val==1)
          {
             printf("\n\nSafe sequence generated\n");
            for(int i=0;i<pno;i++)
              printf("P%d\t",safe[i]);
          }
          else{
            printf("Deaadlock!!Not possible");
          }

        }
    }
    else
        printf("\nDeadlock occurs");

  
}

int calculate(int pno, int rno, int Need[][10], int Max[][10], int Avail[], int Alloc[][10], int completed[], int safe[])
{
    int i, j, k, x = 0, finish = 0, flag = 0;
    int Work[1][10];
    for (int i = 0; i < pno; i++)
    {
        completed[i] = 0;
    }
    for (i = 0; i < rno; i++)
        Work[0][i] = Avail[i];
    for (i = 0; i < pno; i++)
    {
        for (j = 0; j < rno; j++)
        {
            Need[i][j] = Max[i][j] - Alloc[i][j];
        }
    }
    for (k = 0; k < pno; k++)
    {
        for (i = 0; i < pno; i++)
        {
            if (completed[i] == 0)
            {
                flag = 0;
                for (j = 0; j < rno; j++)
                {
                    if (Need[i][j] > Work[0][j])
                        flag = 1;
                }
                if (flag == 0 && completed[i] == 0)
                {
                    for (j = 0; j < rno; j++)
                        Work[0][j] += Alloc[i][j];
                    completed[i] = 1;
                    finish++;
                    safe[x++] = i;
                }
            }
        }
        if (finish == pno)
            return 1;
    }
    return 0;
}

void display(int k[10][10], int n, int p)
{
    int i, j;
    for (i = 0; i < p; i++)
    {
        printf("\n");
        for (j = 0; j < n; j++)
        {
            printf("%d\t", k[i][j]);
        }
    }
}