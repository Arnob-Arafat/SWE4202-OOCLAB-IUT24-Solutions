/*
a. Compare the signature of removeAt in Task 1 and Task 2. What was removed and
why?
Ans: We do not have to use two shift operations. The number of parameters has also decreased.
     Now both those fields are stored continuosly in memory and they do have a relation between them.

b. The struct keeps data together, but the functions (add, display, . . . ) are still
floating around separately. Could someone call update with a completely wrong
array by accident? Can the code prevent it?
Ans: Yes someone could call a wrong array and code would not prevent it.

c. main can still write list[0].mark = -999; directly without going through any func-
tion. Is this a problem? What would prevent it?
Ans: This may not be a problem depending upon the code. As we are keeping track of count,
    any later input will just simply overwrite it. What could be a problem is changing count
    in main(). Again, list[0].mark = -999 in main() is not ideal its best to avoid it in this case.
    What we could do is everytime check whether any field that is outside of the range of count 
    any values except zero and correct it in each function. But then again it is a bit redundant as
    we are already keeping track of count. 
*/



#include <stdio.h>
#include <string.h>

# define MAX 50
# define NLEN 50

typedef struct {
    char name [ NLEN ];
    int mark ;
} Student ;

/*
* Every function now takes ONE array of Students
* instead of two separate arrays .
* Compare each signature carefully with Task 1.
*/

void add ( Student list [] , int * count ,
const char * name , int mark ) ;

void removeAt ( Student list [] , int * count , int index ) ;

void update ( Student list [] , int count ,
int index , int newMark ) ;
void display ( Student list [] , int count ) ;

int search ( Student list [] , int count , const char * query ) ;

void topN ( Student list [] , int count , int n ) ;

/* ---- implement each function below ---- */

int main ( void ) 
{
    Student list [ MAX ];
    int count = 0;

    /* test your functions here */
    char task;

    while ((task = getchar()) != 'q')
    {
        if (task == 'a') 
        {
            char name[NLEN];
            int mark;
            printf("Enter [Name Marks]:");
            scanf("%s %d", name, &mark);

            add(list, &count, name, mark);
        }
        else if (task == 'r')
        {
            int index;
            printf("Enter index: ");
            scanf("%d", &index);
            removeAt(list, &count, index);
        }

        else if (task == 'u')
        {
            int newMark;
            int index;
            printf("Enter index and newMark: ");
            scanf("%d %d", &index, &newMark);
            update(list, count, index, newMark);
        }

        else if (task == 'd')
        {
            display(list, count);
        }

        else if (task == 's')
        {
            char query[NLEN];
            printf("Enter name: ");
            scanf("%s", query);
            search(list, count, query);
        }

        else if (task == 't')
        {
            int n;
            printf("Enter n: ");
            scanf("%d", &n);
            topN(list, count, n);
        }

        else
        {
            printf("INVALID COMMAND\n");
        }

        getchar();
    }


    return 0;
}

void add ( Student list[] , int * count ,
const char * name , int mark ) 
{
    (*count)++;
    strcpy(list[(*count)-1].name, name);
    list[(*count)-1].mark = mark;
    return;
}

void removeAt ( Student list[]  , int * count ,
int index )
{
    for (int i = index; i < (*count)-1; i++)
    {
        list[i] = list[i+1];
    }
    (*count)--;
}

void update ( Student list[]  , int count ,
int index , int newMark ) 
{
    if (index < count)
    list[index].mark = newMark;
}

void display ( Student list[]  , int count )
{
    for (int i = 0; i < count; i++)
    {
        printf("%d %s %d\n", i+1, list[i].name, list[i].mark);
    }
}


int search ( Student list[]  , int count ,
const char * query )
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if(strcmp(list[i].name, query) == 0)
        {
            printf("%s\n", list[i].name);
            found = 1;
            break;
        }
    }
    if(found == 0) printf("NOT FOUND\n");

    return found;
}

void topN ( Student list[]  , int count ,
int n )
{
    Student copylist[count];

    for (int i = 0; i < count; i++)
    {
        copylist[i].mark = list[i].mark;
        strcpy(copylist[i].name, list[i].name);
    }

    int temp;
    char str[NLEN];

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (copylist[j].mark < copylist[j+1].mark)
            {
                temp = copylist[j].mark;
                copylist[j].mark = copylist[j+1].mark;
                copylist[j+1].mark = temp;

                
                strcpy(str, copylist[j].name);
                strcpy(copylist[j].name, copylist[j+1].name);
                strcpy(copylist[j+1].name, str);
            }
        }

        
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", copylist[i].name, copylist[i].mark);
    }

}