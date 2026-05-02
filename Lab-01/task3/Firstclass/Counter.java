public class Counter {

    private int count = 0;

    public void increment() {
        count++;
    }

    public void reset() {
        count = 0;
    }

    public int get() {
        return count;
    }
}
