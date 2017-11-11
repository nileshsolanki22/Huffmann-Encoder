#include<stdio.h>
#include<malloc.h>
#define max 100

//structure for tree
struct tree
{
	int data;
	char ch;
	struct tree *left;
	struct tree *right;
};

//structure for linked list
struct list
{
	int info;
	struct list *link;
	struct list *node;
}*start=NULL;

int main()
{
	struct list *newlistnode,*ptr;
	struct tree *newtreenode,*pos;
	int i,n,item,x,c=65,flag=0,num;

    int a[max];
    //int a[]={6,4,9,1,3,10};

	char ch[max];
	//char ch[]={'A','B','C','D','E','F'};
	char ch1;

    //no. of elements
    printf(" Enter number of elements: ");
    scanf("%d",&n);
    printf("\n");

    //switch case
    do
    {
        printf(" Enter your choice:- \n\n");
        printf(" 1.Enter your input \n 2.Generate input\n 3.Generate Huffman code\n 4.Exit\n\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                //User Input
                flag=1;
                printf(" Enter characters: \n\n");
                for(i=0;i<n;i++)
                {
                    printf(" Enter character %d: ",i+1);
                    fflush(stdin);
                    scanf("%c",&ch[i]);
                }
                printf("\n\n\n");

                printf(" Enter Frequency of Characters\n");
                for(i=0;i<n;i++)
                {
                    printf(" Enter freq of %c: ",ch[i]);
                    scanf("%d",&a[i]);
                }
                printf("\n\n\n");
                break;\

            case 2:
                //Randomly generated input
                printf("\n Generated Input\n\n");
                flag=1;
                for(i=0;i<n;i++)
                {
                    ch[i]=c;
                    c++;
                    if(c==91)
                        c=97;
                }
                for (i=0;i<n;i++)
                {
                    num=5*n;
                    a[i] = rand()%num + 1;
                }

                for(i=0;i<n;i++)
                printf(" %c:   %d\n",ch[i],a[i]);
                printf("\n\n");
                break;

            case 3:
                //Generate Huffman code
                if(flag==0)
                {
                    printf("\nPlease Enter characters and their frequency first\n\n");
                    break;
                }
                else
                {
                    //creating the nodes of the link list and binary tree from array
                    for(i=0;i<n;i++)
                    {
                        //item is frequency of char
						item=a[i];
                        //ch1 is char
						ch1=ch[i];
                        addnode(&newlistnode,&newtreenode,item,ch1);
                    }

                    Huffman(n);
                    search();
                }
                //break;
            case 4:
            exit(1);

            default:
                printf(" Wrong choice... Please try again\n");
                }
    }while(x!=4);
	return 0;
}

//add node for linked list
addnode(struct list* new,struct tree* new2,int item,char ch1[])
{
    struct list *ptr;
    new=(struct list *)malloc(sizeof(struct list));
    new2=(struct tree *)malloc(sizeof(struct tree));
    if(new==NULL)
    {
        printf("Overflow");
        return;
    }
    //set next of linklist to NULL
    new->link=NULL;
    new->info=item;
    //(struct list *)
    new->node=(struct list *)new2;

    //set left and right nodes of tree NULL
    new2->data=item;
    new2->left=NULL;
    new2->right=NULL;
    //(int)
    new2->ch=(int)ch1;

    if(start==NULL)
    {
        start=new;
     //   printf("llinfo: %d\n",new->info);
    }
    else
    {
        ptr=start;
        while(ptr->link!=NULL)
        ptr=ptr->link;
        ptr->link=new;
      //  printf("llinfo: %d\n",new->info);
    }
    //printf("tree: %d\n",new2->data);
}

Huffman(int n)
{
    struct list *ptr;
    struct tree *new;
    int i=0;

    sortlinkedlist();
    ptr=start;
    for(i=0;i<n;i++)
    {
        insertnewtreenode(&new,i);
        sortlinkedlist();
    }

   // for(ptr=start;ptr!=NULL;ptr=ptr->link)
    //{
    //    printf("linked list node: %d\n",ptr->info);
    //}
    printf("\n\n\n");
}

sortlinkedlist()
{
    struct list *ptr1,*ptr2,*t;
    int temp;
    char ch1;

    for(ptr1=start;ptr1->link!=NULL;ptr1=ptr1->link)
    {
        for(ptr2=ptr1->link;ptr2!=NULL;ptr2=ptr2->link)
        {
            if((ptr1->info)>(ptr2->info))
            {
                //swap tree nodes
                t=ptr1->node;
                ptr1->node=ptr2->node;
                ptr2->node=t;

                //swap linkedlist nodes
                temp=ptr1->info;
                ptr1->info=ptr2->info;
                ptr2->info=temp;
            }
        }
    }
}


//Function to combine two nodes and insert it to the beginning of the linked list
insertnewtreenode(struct tree *new,int i)
{
    struct tree *tptr,*temp;
    struct list *new2,*ptr;
    struct list *ptr1,*ptr2;
    int sum;

    ptr1=start;
    ptr2=start->link;
    //(struct tree *)
    tptr=(struct tree *)start->node;

    new=(struct tree *)malloc(sizeof(struct tree));
    new2=(struct list *)malloc(sizeof(struct list));
    //(struct list *)
    new2->node=(struct list *)new;
    new->ch=' ';

    if(ptr1->link==NULL)
    {
        printf(" Huffman tree created successfully........");
        return;
    }

    //when tree has only one node
    if(tptr->left!=NULL||tptr->right!=NULL)
    {
        //(struct tree *)
        new->right=(struct tree *)start->node;
        //(struct tree *)
        new->left=(struct tree *)start->link->node;



        sum=(new->left->data)+(new->right->data);
        new->data=sum;

        new2->info=sum;
        new2->link=ptr2->link;
        start=new2;
    }
    else
    {
        //(struct tree *)
        new->left=(struct tree *)start->node;
        //(struct tree *)
        new->right=(struct tree *)(start->link->node);
        sum=(start->info)+(start->link->info);
       // printf("\nsum: %d\n\n",sum);
        new->data=sum;

        new2->info=sum;
        new2->link=ptr2->link;
        start=new2;
    }


    free(ptr1);
    free(ptr2);


    tptr=(struct tree *)start->node;
    if(tptr->left->data>=tptr->right->data)
        {
            temp=tptr->left;
            tptr->left=tptr->right;
            tptr->right=temp;
        }

    printf(" Step %d:- \n",i+1);
    display(start->node,i++);
    printf("\n\n");
}


//Function to display the Huffman tree
display(struct tree *root,int i)
{
    if(root==NULL)
        return;
    display(root->left,i);
    printf(" treedata: %d\t%c\n",root->data,root->ch);
    display(root->right,i);
}



//Function to call Character frequency Code
search()
{
    struct list *ptr;
    int s[max],top=0;
    ptr=start;
    printf("\n Huffman Code\n\n");
    characterCode(ptr->node,s,top);
}

//Function to calculate char frequency code
characterCode(struct tree *root,int s[],int top)
{
    if(root!=NULL)
        {
            if (root->left!=NULL)
            {
                s[top]=0;
                characterCode(root->left,s,top+1);
            }
            if (root->right!=NULL)
            {
                s[top]=1;
                characterCode(root->right,s,top+1);
            }
            if (root->left==NULL && root->right==NULL)
            {
                {
                    printf("  %c->  ",root->ch);
                    printCode(s,top);
                    return;
                }
            }
        }
}

//Function to print character code
printCode(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}





