public class MainCounter {

    public static void main(String[] args)
    {
        Counter x = new Counter();

        x.increment();
        System.out.println(x.get());
        x.reset();
        System.out.println(x.get());

    }
}
