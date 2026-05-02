import java.util.Scanner;
/*
1. What concrete problem did replacing parallel arrays with a struct solve?
Ans: We reduced number of  parameters and operations in functions.

2. What concrete problem did replacing the struct and standalone functions with a
class solve?
Ans: We reduced parameters and heavily organized the student list. They have a in built
     relation. Again, redundancy in code is reduced.

3. StudentList is currently just a list. What change to the add and removeAt methods
would turn it into a stack? Into a queue? You do not need to implement this now
— just describe it in one sentence each. You will implement it in Lab 2.
Ans: Currently I have very less knowledge of stack and queue. But after some research,
    we would need to add and remove to and from the end of the stack in add or remove methods (LIFO):')???
    And in a queue we would need to add to the back and remove from the back(FIFO)?????

*/
public class Main {

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        StudentList list = new StudentList();
        char task;

        while(true)
        {
            task = sc.next().charAt(0);

            if (task == 'a')
            {
                String name;
                int mark;
                System.out.print("Enter [Name Marks]:");
                name = sc.next();
                mark = sc.nextInt();
                list.add(name, mark);
            }
            else if (task == 'r') {
                int index;
                System.out.print("Enter index: ");
                index = sc.nextInt();
                list.removeAt(index);
            }
            else if (task == 'u')
            {
                int newMark;
                int index;
                System.out.print("Enter index and newMark: ");
                index = sc.nextInt();
                newMark = sc.nextInt();
                list.update(index, newMark);
            }

            else if (task == 'd')
            {
                list.display();
            }

            else if (task == 's')
            {
                String query;
                System.out.print("Enter name: ");
                sc.nextLine();
                query = sc.nextLine();
                list.search(query);
            }

            else if (task == 't')
            {
                int n;
                System.out.print("Enter n: ");
                n = sc.nextInt();
                list.topN(n);
            }

            else if (task == 'q')
            {
                break;
            }

            else
            {
                System.out.print("INVALID COMMAND\n");
            }

        }


    }
}

