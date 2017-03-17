package work.ch_1.s_3;

import edu.princeton.cs.algs4.StdOut;

public class ex_1_3_2 {
    public static void main(String[] args) {
        String testStr = "it was - the best - of times - - - it  was - the - -";
        String[] inputArray = testStr.split(" ");
        Stack<String> s = new Stack<>();

        for (String str : inputArray) {
            if (!str.equals("-")) s.push(str);
        }

        for (String str : s) {
            StdOut.println(str);
        }

        /*
        the
        was

        it
        times
        of
        best
        the
        was
        it
         */
    }

}
