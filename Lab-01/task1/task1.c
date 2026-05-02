
/*
a. Count the parameters of removeAt. Does this feel natural? What would happen if
you needed a third field, say a student id?
Ans: Four parameters for a siingle function is never optimal. This does not feel "natural". 
     If we were to require a third field we would have to increase number of paramaters. As none
     of those parameters are actually "connected" in memory or reality, the parameters feel a bit redundant.

b. In removeAt, how many separate shift operations did you write? Why two instead
of one?
Ans: As marks array and name array are not actually connected to each to other in memory or do not have a built in relation,
     we had to write two instead of one.

c. If a colleague accidentally passed the wrong array to update, could the code detect
it? What kind of bugs could silently occur?
Ans: No, code will not detect it itself. We can write precautionary measure so that doesnt happen.
     But then again that precautionary measures are prone to mistakes themselves. 
     We can update the name array instead of marks array, therefore changing the name field.
*/




#include <stdio.h>
#include <string.h>

# define MAX 50
# define NLEN 50

/*
* Two parallel arrays + a count variable .
* Declare them in main () and pass them to every function .
* Do NOT make them global .
*/

void add (char names [][ NLEN ] , int marks [] , int * count ,
const char * name , int mark ) ;

void removeAt ( char names [][ NLEN ] , int marks [] , int * count ,
int index) ;

void update (int marks [] , int count ,
int index , int newMark ) ;

void display ( char names [][ NLEN ] , int marks [] , int count ) ;

int search ( char names [][ NLEN ] , int count ,
const char * query ) ;

void topN ( char names [][ NLEN ] , int marks [] , int count ,
int n ) ;

/* ---- implement each function below ---- */

int main ( void ) {
char names [ MAX ][ NLEN ];
int marks [ MAX ];
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

        add(names, marks, &count, name, mark);
    }
    else if (task == 'r')
    {
        int index;
        printf("Enter index: ");
        scanf("%d", &index);
        removeAt(names, marks, &count, index);
    }

    else if (task == 'u')
    {
        int newMark;
        int index;
        printf("Enter index and newMark: ");
        scanf("%d %d", &index, &newMark);
        update(marks, count, index, newMark);
    }

    else if (task == 'd')
    {
        display(names, marks, count);
    }

    else if (task == 's')
    {
        char query[NLEN];
        printf("Enter name: ");
        scanf("%s", query);
        search(names, count, query);
    }

    else if (task == 't')
    {
        int n;
        printf("Enter n: ");
        scanf("%d", &n);
        topN(names, marks, count, n);
    }

    else
    {
        printf("INVALID COMMAND\n");
    }

}


return 0;
}

void add ( char names [][ NLEN ] , int marks [] , int * count ,
const char * name , int mark ) 
{
    (*count)++;
    strcpy(names[(*count)-1], name);
    marks[(*count)-1] = mark;
    return;
}

void removeAt ( char names [][ NLEN ] , int marks [] , int * count ,
int index )
{
    for (int i = index; i < (*count)-1; i++)
    {
        marks[i] = marks[i+1];
        strcpy(names[i], names[i+1]);
    }
    (*count)--;
}

void update (int marks [] , int count ,
int index , int newMark ) 
{
    if (index < count)
    marks[index] = newMark;
}

void display ( char names [][ NLEN ] , int marks [] , int count )
{
    for (int i = 0; i < count; i++)
    {
        printf("%d %s %d\n", i+1, names[i], marks[i]);
    }
}


int search ( char names [][ NLEN ] , int count ,
const char * query )
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if(strcmp(names[i], query) == 0)
        {
            printf("%s", names[i]);
            found = 1;
            break;
        }
    }
    if(found == 0) printf("NOT FOUND\n");

    return found;
}

void topN ( char names [][ NLEN ] , int marks [] , int count ,
int n )
{
    int copymarks[count+1];
    char copyname[count+1][NLEN];

    for (int i = 0; i < count; i++)
    {
        copymarks[i] = marks[i];
        strcpy(copyname[i], names[i]);
    }

    int temp;
    char str[NLEN];

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; i++)
        {
            if (copymarks[j] < copymarks[j+1])
            {
                int temp = copymarks[j];
                copymarks[j] = copymarks[j+1];
                copymarks[j+1] = temp;

                
                strcpy(str, copyname[j]);
                strcpy(copyname[j], copyname[j+1]);
                strcpy(copyname[j+1], str);
            }
        }

        for (int i = 0; i < n; i++)
        {
            printf("%s %d\n", names[i], marks[i]);
        }
    }


}