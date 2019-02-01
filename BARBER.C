#include<stdio.h>
#include<conio.h>
#define MAX 10
// variables, flags, methods required for successful execution of the the project
int mutex=1,c_mutex=1,flag=0,ans;
int cnt=0;
int waitingroom[MAX];
int i=0;
int j=0;
void barber();
void customer();
int wait(int);
int signal(int);

// Main entry point
void main()
{
int ans;
clrscr();
printf(" --- BARBER SHOP PROBLEM ---");
printf("\nThe following is an illustrations of the real time Barber Shop");
printf("\nConsidering it a hypothetical barber shop which has only 1 barber");
while(1)
{
printf("\n1.Barber \n2.Customer \n3.Exit");
printf("\nEnter your choice:");
scanf("%d",&ans);
//switch case for selecting the fucntion to be performed
switch(ans)
{
// check conditions for the barber functions
// if mutex ==1 i.e barber is free and is searching for customers
case 1: if(mutex==1)
	barber();
// if mutex =0 and flaf is not 1 i.e babrber is serving some customer
	else if(mutex==0 && flag!=1)
	printf("\nBarber is busy serving a customer");
// if mutex  = 0 and flaf = 1 i.e barber is sleeping as there are no customers
	else if (mutex==0 && flag==1)
	printf("\nBarber is sleeping as there're no customers");
	break;

//check condition for the customer ti get served by the barber
case 2: if(c_mutex==1)
	customer();
	break;
case 3: exit(0);
}
}
//getch();
}

// use of semphore concepts to achieve mutual exclusion
// the below fucntion reduces the counter by 1 which indicates that
// i.e either barber is serving a customer or a customer is waiting for the barber
int wait(int s)
{
return(--s);
}
// the below function increases the counterby 1 which indicates that
//i.e either the barber is searching for a customer or the customer
//is enteringthe shop and checking for availability of the barber
int signal(int s)
{
return(++s);
}

/*the following function manages the functions of the barber
if the barber is free it takes on the task of a customer
by calling the wait function and making the barber busy
once the work of the barber is finished it hits the signal function
and searched for the new customer
if a new customer is found it continues serving else it goes to sleep
making thr flag variable 1
*/
void barber()
{
int n;
while(cnt!=0){
mutex=wait(mutex);
n=waitingroom[i++];
printf("\nBarber is working with customer %d",n);
cnt--;
mutex=signal(mutex);
//c_mutex=signal(c_mutex);
}
if(cnt == 0){
printf("\nSince no customers ,Barber is going to sleep!");
mutex=wait(mutex);
flag=1;
i=j=0;
//this	 is cos of testing if someone smart hits the barber function twice
//it will take the mutex value to negative
if(mutex<0)
mutex=0;
}
}

/* the following function is used for serving the purpose of the client
this function increaments the value or keeps the track of the number of
customers that are waiting for the barber.
its the duty of the customer to wake up the sleeping barber. making the mutex
1 and setting the flag =0  is the code for waking the barber by the customer
*/
void customer()
{
int num;
int k;
printf("\nEnter the current customer's number:");
scanf("%d",&num);
cnt++;
waitingroom[j++]=num;
printf("\nCustomer's in line:");
for(k=0;k<j;k++)
printf("%d\t",waitingroom[k]);
if(mutex == 0 && flag==1){
printf("\nWaking up barber");
mutex=signal(mutex);
flag=0;
//barber();
}
}