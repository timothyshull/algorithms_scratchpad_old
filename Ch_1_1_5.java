package ch_1_1;

public class Ch_1_1_5 {
    public static boolean testVals(double x, double y) {
        return (x > 0 && x < 1) && (y > 0 && y < 1);
    }

    public static void main(String args[]) {
        if (args.length != 2) {
            System.err.println("Usage: double double");
        }

        if (testVals(Integer.parseInt(args[0]), Integer.parseInt(args[1]))) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }
}
