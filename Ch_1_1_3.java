package ch_1_1;

public class Ch_1_1_3 {
    public static void main(String args[]) {
        int a, b, c;

        if (args.length != 3) {
            System.err.println("Usage: int int int");
        }

        a = Integer.parseInt(args[0]);
        b = Integer.parseInt(args[1]);
        c = Integer.parseInt(args[2]);

        if (a == b && a == c) {
            System.out.println("equal");
        } else {
            System.out.println("not equal");
        }
    }
}
