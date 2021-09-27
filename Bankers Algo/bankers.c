#include <stdio.h>
#include <stdlib.h>

void display(int [][10], int , int );
int calculate(int , int , int [][10], int [][10], int[], int [][10], int [], int []);
int main()
{
    int Alloc[10][10], Max[10][10], Need[10][10], Avail[10], pno, rno;
    int completed[10], safe[10], count;

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
           // printf(" Resource Allocation %d : ", j + 1);
            scanf("%d", &Alloc[i][j]);
            //printf(" Resource Maximum %d : ", j + 1);
            //scanf("%d", &Max[i][j]);
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
    //printf("\nAllocaton\n");
    //display(Alloc, rno, pno);
    //printf("\n\nMaximum\n");
    //display(Max, rno, pno);

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