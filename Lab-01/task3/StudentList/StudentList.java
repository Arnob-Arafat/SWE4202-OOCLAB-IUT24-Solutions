public class StudentList
{
    private String[] name = new String[50];
    private int[] mark = new int[50];
    private int count;

    public StudentList()
    {
        this.count = 0;
    }

    public void add(String name, int mark)
    {
        count++;
        this.name[count-1] = name;
        this.mark[count-1] = mark;
    }

    public void removeAt(int index)
    {
        for (int i = 0; i < count-1; i++)
        {
            this.name[i] = this.name[i+1];
            this.mark[i] = this.mark[i+1];
        }
        count--;
    }

    public void update(int index, int newMark)
    {
        if(index < count)
        {
            this.mark[index] = newMark;
        }

    }

    public void display()
    {
        for (int i = 0; i < count; i++)
        {
            System.out.println(this.name[i] + " " + this.mark[i]);
        }
    }

    public boolean search(final String query)
    {
        boolean found = false;
        for (int i = 0; i < count; i++)
        {
            if (this.name[i].equals(query)) {
                System.out.println(this.name[i]);
                break;
            }
        }
        return found;
    }

    public void topN(int n)
    {
        StudentList copy = new StudentList();
        for (int i = 0; i < count; i++)
        {
            copy.mark[i] = this.mark[i];
            copy.name[i] = this.name[i];
        }

        int temp;
        String str;

        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - 1 - i; j++)
            {
                if (copy.mark[j] < copy.mark[j+1]) {
                    temp = copy.mark[j];
                    copy.mark[j] = copy.mark[j + 1];
                    copy.mark[j + 1] = temp;

                    str = copy.name[j];
                    copy.name[j] = copy.name[j+1];
                    copy.name[j+1] = str;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            System.out.println(copy.name[i] + " " + copy.mark[i]);
        }
    }
}
