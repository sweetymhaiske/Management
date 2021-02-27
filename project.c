#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef double D;
typedef unsigned long long int LL;
typedef struct stock
{
        LL stock_code;
        char stock_name[50];
        D amount_invested;
        int shares_held;
        D current_price;
}STOCK;
typedef struct node
{
            STOCK s;
            D gain;
            struct node* stock_code_next;
            struct node* stock_code_prev;
            struct node* gain_next;
            struct node* gain_prev;
}NODE;
typedef struct list
{
            NODE* head1;
            NODE* head2;
            NODE* tail1;
            NODE* tail2;

}LIST;
void addStockCode(LIST*,NODE*);
void addGain(LIST*,NODE*);
void reverseDisplaySTKCODE(LIST*);
void reverseDisplayGAIN(LIST*);
void displaySTKCODE(LIST*);
void displayGAIN(LIST*);
void init(LIST *);
void menu();
void fileDisplay();
void appendfile();
int initialise()
{
      return 0;
}
int main()
{
      FILE *fp;
      fp=fopen("stock.txt","r");
      if(fp==NULL)
      {
          printf("\nError opening in file.");
          return;
      }
      double g;
      LIST list;
      init(&list);
      STOCK s;
      fileDisplay();
      int m=initialise();
      while(fscanf(fp, "%lld %s %lf %d %lf" , &s.stock_code,s.stock_name,&s.amount_invested,&s.shares_held,&s.current_price)!=EOF)
      {
            g=(s.shares_held*s.current_price)-s.amount_invested;
            NODE* pNew=(NODE*)malloc(sizeof(NODE));
            if(!pNew)
            {
                  printf("OOpps!! Error Not Enough Memory");
                  return;
            }
            pNew->s.stock_code=s.stock_code;
            strcpy(pNew->s.stock_name,s.stock_name);
            pNew->s.amount_invested=s.amount_invested;
            pNew->s.shares_held=s.shares_held;
            pNew->s.current_price=s.current_price;
            pNew->gain=g;
            m++;
            printf("|%4d |%18.2lld |%50s |%22.2lf |%17d |%20.2lf |\n",m,s.stock_code,s.stock_name,s.amount_invested,s.shares_held,s.current_price);
            printf("________________________________________________________________________________________________________________________________________________\n");
            pNew->stock_code_next=NULL;
            pNew->stock_code_prev=NULL;
            pNew->gain_next=NULL;
            pNew->gain_prev=NULL;
            addStockCode(&list,pNew);
            addGain(&list,pNew);
      }
      fclose(fp);
      int opt;
      menu();
      printf("\nNOTE : If you want menu to be displayed again then enter character 6\n");
      while(1)
      {
            printf("\nEnter OPTION : ");
            scanf(" %d",&opt);
            printf("\n");
            if(opt>6)
                  break;
            switch(opt)
            {
                  case 1:
                        displaySTKCODE(&list);
                        break;
                  case 2:
                        displayGAIN(&list);
                        break;
                  case 3:
                        reverseDisplaySTKCODE(&list);
                        break;
                  case 4:
                        reverseDisplayGAIN(&list);
                        break;
                  case 5:
                        appendfile();
                        system("cls");
                        main();
                        break;
                  case 6:
                        menu();
                        break;
            }
    }
}

void init(LIST *list)
{
      list->head1=NULL;
      list->head2=NULL;
      list->tail1=NULL;
      list->tail2=NULL;
}
void addStockCode(LIST* list,NODE* pNew)
{
    NODE* tmp=list->head1,*a=NULL;
    if(list->head1==NULL)
    {
        pNew->stock_code_next=NULL;
        pNew->stock_code_prev=NULL;
        list->head1=pNew;
        list->tail1=pNew;
    }
    else
    {
        if(pNew->s.stock_code < tmp->s.stock_code)
        {
            tmp->stock_code_prev=pNew;
            pNew->stock_code_next=tmp;
            list->head1=pNew;
        }
        else
        {
            while(tmp!=NULL)
            {
                if(pNew->s.stock_code <= tmp->s.stock_code)
                {
                        a->stock_code_next=pNew;
                        tmp->stock_code_prev=pNew;
                        pNew->stock_code_next=tmp;
                        pNew->stock_code_prev=a;
                        break;
                }
                a=tmp;
                tmp=tmp->stock_code_next;
            }
            if(tmp==NULL)
            {
                  a->stock_code_next=pNew;
                  pNew->stock_code_prev=a;
                  list->tail1=pNew;
            }
        }
    }
}

void addGain(LIST* list,NODE* pNew)
{
    NODE* tmp=list->head2,*a=NULL;
    if(list->head2==NULL)
    {
        pNew->gain_next=NULL;
        pNew->gain_prev=NULL;
        list->head2=pNew;
        list->tail2=pNew;
    }
    else
    {
        if(pNew->gain <= tmp->gain)
        {
            tmp->gain_prev=pNew;
            pNew->gain_next=tmp;
            list->head2=pNew;
        }
        else
        {
            while(tmp!=NULL)
            {
                  if(pNew->gain <= tmp->gain)
                  {
                        a->gain_next=pNew;
                        tmp->gain_prev=pNew;
                        pNew->gain_next=tmp;
                        pNew->gain_prev=a;
                        break;
                }
                a=tmp;
                tmp=tmp->gain_next;
            }
            if(tmp==NULL)
            {
                  a->gain_next=pNew;
                  pNew->gain_prev=a;
                  list->tail2=pNew;
            }
        }
    }
}
void displaySTKCODE(LIST *list)
{
    NODE *tmp=list->head1;
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                     Increasing order of STOCK_CODE                                                                  |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|    Stock code    |                    Stock name                     |    Amount invested    |    Shares held    |    Current price    |    Gain    |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(tmp!=NULL)
    {
        printf("|%17.2lld ",tmp->s.stock_code);
        printf("|%50s ",tmp->s.stock_name);
        printf("|%22.2lf ",tmp->s.amount_invested);
        printf("|%18d ",tmp->s.shares_held);
        printf("|%20.2lf ",tmp->s.current_price);
        printf("|%11.2lf |\n",tmp->gain);
        tmp=tmp->stock_code_next;
    }
   printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void displayGAIN(LIST *list)
{
    NODE *tmp=list->head2;
       printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                   Increasing order of STOCK_GAIN                                                                    |\n");
   printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|    Stock code    |                    Stock name                     |    Amount invested    |    Shares held    |    Current price    |    Gain    |\n");
   printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(tmp!=NULL)
    {
        printf("|%17.2lld ",tmp->s.stock_code);
        printf("|%50s ",tmp->s.stock_name);
        printf("|%22.2lf ",tmp->s.amount_invested);
        printf("|%18d ",tmp->s.shares_held);
        printf("|%20.2lf ",tmp->s.current_price);
        printf("|%11.2lf |\n",tmp->gain);
        tmp=tmp->gain_next;
    }
       printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
void reverseDisplaySTKCODE(LIST *list)
{
    NODE *tmp=list->tail1;
   printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                        Decreasing order of STOCK_CODE                                                               |\n");
 printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|    Stock code    |                    Stock name                     |    Amount invested    |    Shares held    |    Current price    |    Gain    |\n");
     printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(tmp!=NULL)
    {
        printf("|%17.2lld ",tmp->s.stock_code);
        printf("|%50s ",tmp->s.stock_name);
        printf("|%22.2lf ",tmp->s.amount_invested);
        printf("|%18d ",tmp->s.shares_held);
        printf("|%20.2lf ",tmp->s.current_price);
        printf("|%11.2lf |\n",tmp->gain);
        tmp=tmp->stock_code_prev;
    }
     printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void reverseDisplayGAIN(LIST *list)
{
    NODE *tmp=list->tail2;
      printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                      Decreasing order of STOCK_GAIN                                                                 |\n");
     printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|    Stock code    |                    Stock name                     |    Amount invested    |    Shares held    |    Current price    |    Gain    |\n");
      printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(tmp!=NULL)
    {
        printf("|%17.2lld ",tmp->s.stock_code);
        printf("|%50s ",tmp->s.stock_name);
        printf("|%22.2lf ",tmp->s.amount_invested);
        printf("|%18d ",tmp->s.shares_held);
        printf("|%20.2lf ",tmp->s.current_price);
        printf("|%11.2lf |\n",tmp->gain);
        tmp=tmp->gain_prev;
    }
       printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
void menu()
{
      printf("\n\n\n**********************************************************************************************************************\n");
      printf("|                                                           MENU                                                     |\n");
      printf("**********************************************************************************************************************\n");
      printf("|  Choose option of display  |     1) According to Stock_Data in forward order                                       |\n|                            |     2) According to Stock_gain in forward order                                       |\n|                            |     3) According to Stock_Code in reverse order                                       |\n|                            |     4) According to Stock_gain in reverse order                                       |\n|                            |     5) Append the Data into the file                                                  |\n|                            |     6) Display Menu                                                                   |\n");
      printf("**********************************************************************************************************************\n");
}
void fileDisplay()
{
      printf("\n\t\t\t\t\t\tDATA STORED\t\t\t\t\t\n");
      printf("________________________________________________________________________________________________________________________________________________\n");
      printf("|Sr.No|     Stock-Code    |                     Stock-Name                    |    Amount Invested    |    Share held    |    Current Price    |");
      printf("\n________________________________________________________________________________________________________________________________________________\n");
}
void appendfile()
{
      system("cls");
      STOCK sp;
      FILE *fp;
      fp=fopen("stock8.txt","a");
      if(fp==NULL)
      {
            printf("\nFile is not created");
            return;
      }
      char x;
      char ch;
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
}


