#include <stdio.h>
#include <stdlib.h>

int i, j, np, s;
float atat = 0.00, awt = 0.00, act = 0.00;
int total_tat = 0, total_wt = 0, total_ct = 0;
int temp, sch, tq, sum = 0;
int bt_remain[10];

int pro[10], bt[10], at[10], tat[10], wt[10], ct[10],pri[10];

void Display();
void Display_Gant();
void Insert();
void FCFS();
void SJF();
void Priority();
void RR();
void Sort_AT(), Sort_BT();
void Sort_AT_Priority();
void Sort_Priority();

int main()
{
    printf("\nCPU SCHEDULING\n");
    while (1)
    {
        printf("\n\n\nAvailable Type of Scheduling:");
        printf("\n1.FCFS\t2.SJF\t3.Priority\t4.RR\t5.Exit");
        printf("\nPlease choose the scheduling type: ");
        scanf("%d", &sch);

        switch (sch)
        {
        case 1:atat = awt = act = 0.00;
            FCFS();
            break;
        case 2:atat = awt = act = 0.00;
            SJF();
            break;
        case 3:atat = awt = act = 0.00;
            Priority();
            break;
        case 4:atat = awt = act = 0.00;
            RR();
            break;
        case 5:
            printf("\nSuccessfully Exited");
            exit(0);
            break;
        default:
            printf("\nEnter correct option:");
        }
    }
}

void Insert_Process()
{
    printf("\nEnter the no of process: ");
    scanf("%d", &np);

    for (i = 0; i < np; i++)
    {
        printf("\nEnter the Process No:");
        scanf("%d", &pro[i]);

        printf("Enter the Arrival Time of Process %d : ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter the Burst Time of Process %d :", i + 1);
        scanf("%d", &bt[i]);
    }
}

void Insert_Process_Priority()
{
    printf("\nEnter the no of process: ");
    scanf("%d", &np);

    for (i = 0; i < np; i++)
    {
        printf("\nEnter the Process No:");
        scanf("%d", &pro[i]);

        printf("Enter the Arrival Time of Process %d : ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter the Burst Time of Process %d :", i + 1);
        scanf("%d", &bt[i]);

        printf("Enter Priority of P%d\n", i + 1);
        scanf("%d", &pri[i]);
    }
}

void Sort_AT()
{
    for (i = 0; i < np - 1; i++)
    {
        for (j = 0; j < np - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }
}

void Sort_AT_Priority()
{
    for (i = 0; i < np - 1; i++)
    {
        for (j = 0; j < np - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = pri[j];
                pri[j] = pri[j + 1];
                pri[j + 1] = temp;
            }
        }
    }
}

void Sort_BT()
{
    for (i = 0; i < np - 1; i++)
    {
        for (j = 0; j < np - i - 1; j++)
        {
            if (at[j] == at[j + 1])
            {
                if (bt[j] > bt[j + 1])
                {
                    temp = pro[j];
                    pro[j] = pro[j + 1];
                    pro[j + 1] = temp;

                    temp = at[j];
                    at[j] = at[j + 1];
                    at[j + 1] = temp;

                    temp = bt[j];
                    bt[j] = bt[j + 1];
                    bt[j + 1] = temp;
                }
            }
        }
    }
}

void Sort_Priority()
{
    for (i = 0; i < np - 1; i++)
    {
        for (j = 0; j < np - i - 1; j++)
        {
            if (at[j] == at[j + 1])
            {
                if (pri[j] > pri[j + 1])
                {
                    temp = pri[j];
                    pri[j] = pri[j + 1];
                    pri[j + 1] = temp;

                    temp = at[j];
                    at[j] = at[j + 1];
                    at[j + 1] = temp;

                    temp = bt[j];
                    bt[j] = bt[j + 1];
                    bt[j + 1] = temp;

                    temp = pro[j];
                    pro[j] = pro[j + 1];
                    pro[j + 1] = temp;
                }
            }
        }
    }
}

void FCFS()
{
    Insert_Process();
    Sort_AT();

    for (i = 0; i < np; i++)
    {
        if (i == 0)
        {
            s = at[0];
        }
        wt[i] = s - at[i];
        s = s + bt[i];
        tat[i] = bt[i] + wt[i];
    }

    for (i = 0; i < np; i++)
    {
        total_tat += tat[i];
        total_wt += wt[i];
    }

    awt = (float)total_wt / (float)np;
    atat = (float)total_tat / (float)np;

    Display();
}

void SJF()
{
    Insert_Process();
    Sort_AT();
    Sort_BT();

    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    int vl = 1, check = 0;
    int tc = ct[vl - 1];

    while (vl < np)
    {
        int min = bt[vl];
        int point = vl;
        for (i = vl; i < np; i++)
        {
            if (at[i] <= tc)
            {
                check = 1;
                if (bt[i] < min)
                {
                    min = bt[i];
                    point = i;
                }
            }
        }
        if (check != 0)
        {
            temp = at[vl];
            at[vl] = at[point];
            at[point] = temp;

            temp = bt[vl];
            bt[vl] = bt[point];
            bt[point] = temp;

            temp = pro[vl];
            pro[vl] = pro[point];
            pro[point] = temp;

            if (at[vl] < ct[vl - 1])
            {
                ct[vl] = bt[vl] + ct[vl - 1];
            }
            else
            {
                ct[vl] = at[vl] + bt[vl];
            }
            tat[vl] = ct[vl] - at[vl];
            wt[vl] = tat[vl] - bt[vl];
            vl = vl + 1;
            tc = ct[vl - 1];
            check = 0;
        }
        else
        {
            tc = tc + 1;
        }
    }

    for (i = 0; i < np; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        total_ct = total_ct + ct[i];
    }

    awt = (float)total_wt / (float)np;
    atat = (float)total_tat / (float)np;
    act = (float)total_ct / (float)np;

    Display();
}

void Priority()
{
    Insert_Process_Priority();
    Sort_AT_Priority();
    Sort_Priority();

    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];

    int vl = 1, check = 0;
    int tc = ct[vl - 1];
    while (vl < np)
    {
        int min = pro[vl];
        int point = vl;
        for (i = vl; i < np; i++)
        {
            if (at[i] <= tc)
            {
                check = 1;
                if (pro[i] < min)
                {
                    min = pro[i];
                    point = i;
                }
            }
        }
        if (check != 0)
        {
            temp = at[vl];
            at[vl] = at[point];
            at[point] = temp;

            temp = bt[vl];
            bt[vl] = bt[point];
            bt[point] = temp;

            temp = pro[vl];
            pro[vl] = pro[point];
            pro[point] = temp;

            temp = pri[vl];
            pri[vl] = pri[point];
            pri[point] = temp;

            if (at[vl] < ct[vl - 1])
            {
                ct[vl] = bt[vl] + ct[vl - 1];
            }
            else
            {
                ct[vl] = at[vl] + bt[vl];
            }
            tat[vl] = ct[vl] - at[vl];
            wt[vl] = tat[vl] - bt[vl];
            vl = vl + 1;
            tc = ct[vl - 1];
            check = 0;
        }
        else
        {
            tc = tc + 1;
        }
    }

    for (i = 0; i < np; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        total_ct = total_ct + ct[i];
    }

    awt = (float)total_wt / (float)np;
    atat = (float)total_tat / (float)np;
    act = (float)total_ct / (float)np;

    Display();
}

void RR()
{
    Insert_Process();
    printf("\nEnter the Time Quantum: ");
    scanf("%d", &tq);
    Sort_AT();

    for (i = 0; i < np; i++)
    {
        bt_remain[i] = bt[i];
    }
    int exec_time = 0, completed = 0;
    while (1)
    {

        for (i = 0; i < np; i++)
        {
            if (bt_remain[i] > 0 && at[i] <= exec_time)
            {
                completed = 1;
                if (bt_remain[i] >= tq)
                {
                    bt_remain[i] = bt_remain[i] - tq;
                    exec_time = exec_time + tq;
                }
                else
                {
                    exec_time = exec_time + bt_remain[i];
                    bt_remain[i] = 0;
                }
                if (bt_remain[i] <= 0)
                {
                    ct[i] = exec_time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                }
            }
            else if (bt_remain[i] > 0 && at[i] > exec_time)
            {
                completed = 1;
            }
        }
        if (completed == 0)
        {
            break;
        }
        else
        {
            completed = 0;
        }
    }

    for (i = 0; i < np; i++)
    {
        // tat[i]=ct[i] - at[i];
        total_tat = total_tat + tat[i];
        total_wt = total_wt + wt[i];
    }

    awt = (float)total_wt / (float)np;
    atat = (float)total_tat / (float)np;
    act = (float)total_ct / (float)np;

    Display();
}

void Display()
{
    printf("Process   Burst Time   Arrival Time    Waiting Time   Turn Around Time   Completion Time\n");

    for (i = 0; i < np; i++)
    {
        //total_wt = total_wt + wt[i];
        //total_tat = total_tat + tat[i];
        printf("   %d ", pro[i]);
        printf("         %d", bt[i]);
        printf("              %d", at[i]);
        printf("               %d", wt[i]);
        printf("           %d", tat[i]);
        printf("           %d\n", ct[i]);
    }
    printf("Average waiting time = %0.2f", awt);
    printf("\n");
    printf("Average turn around time = %0.2f ", atat);
    printf("\n");
    printf("Average Complettion time = %0.2f ", atat);
}

void Display_Gant()
{
}