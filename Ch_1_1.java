package ch_1_1;

import java.lang.Math;

public class Ch_1_1 {
    public static double one_a() {
        return (0 + 15) / 2;
    }

    public static double one_b() {
        return Math.pow(2.0, -6.0) * 100000000.1;
    }

    public static boolean one_c() {
        return true && false || true && true;
    }

    public static double two_a() {
        return (1 + 2.236) / 2;
    }

    public static double two_b() {
        return 1 + 2 + 3 + 4.0;
    }

    public static boolean two_c() {
        return 4.1 >= 4;
    }

    public static double two_d() {
        return 1 + 2 + Integer.parseInt("3");
    }

    public static void main(String args[]) {
        System.out.println(one_a());
        System.out.println(one_b());
        System.out.println(one_c());
        System.out.println(two_a());
        System.out.println(two_b());
        System.out.println(two_c());
        System.out.println(two_d());
    }
}
