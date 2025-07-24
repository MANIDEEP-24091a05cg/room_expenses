#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 100
char names[MAX][25];
struct node
{
    char item[25],name[25];
    int cost;
    struct node*link;
}*first=NULL,*last=NULL;
struct node*create()
{
    struct node*newnode=(struct node*)malloc(sizeof(struct node));
    printf("Enter the name (who spend money):");
    scanf("%s",newnode->name);
    printf("Enter the item:");
    scanf("%s",newnode->item);
    printf("Enter how much does item costes:");
    scanf("%d",&newnode->cost);
    newnode->link=NULL;
    return newnode;
}
void expenes()
{
    int count;
    while(1)
    {
        struct node*temp=create();
        if(first==NULL)
        {
            first=temp;
            last=temp;
            first->link=NULL;
        }
        else
        {
            last->link=temp;
            last=temp;
            last->link=NULL;
        }
        printf("Do you want to exit(0)/1:");
        scanf("%d",&count);
        if(count==0)
        {
            break;
        }
    }
}
void display()
{
    struct node*temp=first;
    if(first==NULL)
    {
        printf("NO data");
        return;
    }
    while(temp!=NULL)
    {
        printf("name:%s\n",temp->name);
        printf("item:%s\n",temp->item);
        printf("cost:%d\n\n",temp->cost);
        temp=temp->link;
    }
}
float Total()
{
    float amount=0.0;
    struct node*temp=first;
    if(first==NULL)
    {
        return amount;
    }
    while(temp!=NULL)
    {
        amount=amount+temp->cost;
        temp=temp->link;
    }
    return amount;
}
float balence(char name[25])
{
    float cost=0.0;
    struct node*temp=first;
    if(first==NULL)
    {
        return cost;
    }
    while(temp!=NULL)
    {
        if(strcmp(temp->name,name)==0)
        {
            cost=cost+temp->cost;
        }
        temp=temp->link;
    }
    return cost;
}
float indbalence(char name[25],int num)
{
    float cost=0.0,pri=balence(name)-(Total()/num);
    struct node*temp=first;
    if(first==NULL)
    {
        return cost;
    }
    return pri;
}
void due(char name[25],int num)
{
    float a;
    printf("%s:\n",name);
    printf("\tpaid:%f\n",balence(name));
    a=indbalence(name,num);
    if(a>0)
    {
        printf("\tToget:%f",a);
    }
    else if(a<0)
    {
        printf("\tTOpay:%f\n",-a);
    }
    else
    {
        printf("NO need to give money");
    }
}
void save_file(char name[][25],int num)
{
    struct node*temp=first;
    FILE *fp;
    fp=fopen("expenese.txt","w");
    if(fp==NULL)
    {
        printf("file does not exist");
        return;
    }
    fprintf(fp,"------------EXPENES REPORT-----------\n\n");
    while(temp!=NULL)
    {
        fprintf(fp,"Name:%s\n",temp->name);
        fprintf(fp,"item:%s\n",temp->item);
        fprintf(fp,"cost:%d\n\n",temp->cost);
        temp=temp->link;
    }
    fprintf(fp,"Total Expenses:%f\n",Total());
    fprintf(fp,"Indivisual Epenses:%f\n\n",Total()/num);
    for (int i = 0; i < num; i++)
    {
        float paid = balence(names[i]);
        float due = indbalence(names[i],num);
        fprintf(fp, "%s:\n", names[i]);
        fprintf(fp, "\tPaid: ₹%f\n", paid);
        if (due > 0)
            fprintf(fp, "\tTo Receive: ₹%f\n", due);
        else if (due < 0)
            fprintf(fp, "\tTo Pay: ₹%f\n", -due);
        else
            fprintf(fp, "\tSettled\n");
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("file saved sucessfully");
}
void freeList() {
    struct node *temp = first;
    while (temp != NULL) 
    {
        struct node *next = temp->link;
        free(temp);
        temp = next;
    }
    first = NULL;
    last = NULL;
    printf("All memory has been freed.\n");
}
int main()
{
    int num;
    printf("Enter number of people: ");
    scanf("%d", &num);
    printf("Enter names of each person:\n");
    for (int i = 0; i < num; i++)
    {
        printf("Person %d: ", i + 1);
        scanf("%s", names[i]);
    }
    expenes(); 
    printf("\nDisplaying All Expenses \n:");
    display(); 
    printf("Total Expenses: %f \n", Total());
    printf("Individual Share: %f \n", Total() / num);
    printf("\nDues Summary\n");
    for (int i = 0; i < num; i++) 
    {
        due(names[i], num); 
        printf("\n");
    }
    save_file(names, num);
    freeList();
    return 0;
}
