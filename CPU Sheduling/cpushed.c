#include<stdio.h>
#include<stdlib.h>
#define max 30
int i, j, n;
int bt[max], tat[max], wt[max], pro[max];
float awt = 0, atat = 0;
void display_table (int n)
{
  wt[i] = 0, 
  tat[i] = 0;
  wt[0] = 0;

  for (i = 1; i < n; i++){
    for (j = 0; j < i; j++){
	    wt[i] = wt[i] + bt[j];
	  }
  }
  printf ("\nProcess\tBurst time\tWaiting time\tTurnAround Time\n");
  for (i = 0; i < n; i++)
    {
      tat[i] = bt[i] + wt[i];
      awt = awt + wt[i];
      atat = atat + tat[i];
      printf ("\n%d\t\t\t%d\t\t\t%d\t\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
  awt = awt / n;
  atat = atat / n;
  printf ("\nAverage Waiting Time:%0.2f", awt);
  printf ("\nAverage Turnaround Time:%0.2f", atat);
}

int sjf (int n)
{
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n - i - 1; j++){
	    if (bt[j] > bt[j + 1]){
	      int t = bt[j];
	      bt[j] = bt[j + 1];
	      bt[j + 1] = t;
	      t = pro[j];
	      pro[j] = pro[j + 1];
	      pro[j + 1] = t;
	    }
	  }
  }
  display_table (n);
  return 0;
}

int priority (int n){
  int pos, pr[max];
  printf ("Enter the priority of the processes:");
  for (i = 0; i < n; i++)
      scanf ("%d", &pr[i]);
//Sorting position based on priority
  for (i = 0; i < n; i++)
    {
      pos = i;
      for (j = i + 1; j < n; j++){
        if (pr[j] < pr[pos])
          {
            pos = j;
          }
	}
      int t = pr[i];
      pr[i] = pr[pos];
      pr[pos] = t;
      t = bt[i];
      bt[i] = bt[pos];
      bt[pos] = t;
    }
  display_table (n);
  return 0;
}

int
round_robin (int n)
{
  int qt, count = 0, temp, cur = 0, rem_bt[max];
  for (i = 0; i < n; i++)
    {
      rem_bt[i] = bt[i];
    }
  printf ("Enter the time quantum:");

  scanf ("%d", &qt);
  while (1)
    {
      for (i = 0; i < n; i++)
	{
	  temp = qt;
	  if (rem_bt[i] > qt)
	    {
	      rem_bt[i] = rem_bt[i] - qt;
	      cur = cur + qt;
	    }
	  else
	    {
	      if (rem_bt[i] > 0)
		{
		  temp = rem_bt[i];
		  rem_bt[i] = 0;
		  count++;
		  cur = cur + temp;
		  tat[i] = cur;
		}
	    }
	}
      if (n == count)
	break;
    }

  printf ("\nProcess\t\tBurst time\t\tTurnaround time\t\tWaiting time");
  for (i = 0; i < n; i++)
    {
      wt[i] = tat[i] - bt[i];
      awt = awt + wt[i];
      atat = atat + tat[i];
      printf ("\n%d\t\t\t%d\t\t\t%d\t\t\t%d", i + 1, bt[i], tat[i], wt[i]);
    }
  awt = awt / n;
  atat = atat / n;
  printf ("\nAverage Waiting Time:%0.2f", awt);
  printf ("\nAverage Turnaround Time:%0.2f", atat);
  return 0;
}

int
main ()
{
  int ch, n;
  printf ("Enter the no of processes:");
  scanf ("%d", &n);
  printf ("Enter the burst time of the processes:");
  for (int i = 0; i < n; i++)
    {
      scanf ("%d", &bt[i]);
    }
    
  while (1)
    {

      printf ("\nSelect the algorithm:\n1. fcfs \n2. sjf \n3. priority \n4. round robin \n5. exit\n\n");
      scanf ("%d", &ch);
      switch (ch){
	case 1:
	  display_table (n);
	  break;
	case 2:
	  sjf (n);
	  break;
	case 3:
	  priority (n);
	  break;
	case 4:
	  round_robin (n);
	  break;
	case 5:
	  exit (0);
	  break;
	default:
	  printf ("Please enter a valid choice ");
	  break;
	}
    }
}
