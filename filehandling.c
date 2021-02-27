#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef unsigned long long int LL;
typedef double D;
typedef struct stock
{
        LL stock_code;
        char stock_name[50];
        D amount_invested;
        int shares_held;
        D current_price;
}STOCK;
int main()
{
  STOCK sp;
  FILE *fp;
  char ch;
  fp=fopen("stock8.txt","w");
  if(fp==NULL)
    {
            printf("\nFile is not created");
            return;
    }
    char x;
    do
    {
            printf("\nEnter Stock Code : ");
            scanf("%lld",&sp.stock_code);
            scanf("%c",&ch);
            printf("\nEnter Stock Name : ");
            scanf("%[^\n]s",sp.stock_name);
            printf("\nEnter Amount Invested : ");
            scanf("%lf",&sp.amount_invested);
            printf("\nEnter Shares Held : ");
            scanf("%d",&sp.shares_held);
            printf("\nEnter Current Price : ");
            scanf("%lf",&sp.current_price);
            fprintf(fp,"%lld %s %lf %d %lf\n",sp.stock_code,sp.stock_name,sp.amount_invested,sp.shares_held,sp.current_price );
            printf("\nDo you want to enter another data?\n");
            x=getche();
      }while(x=='y'||x=='Y');
      fclose(fp);
      return 0;
}

