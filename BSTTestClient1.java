package ch3_1;

import static java.lang.Integer.parseInt;

public class BSTTestClient1 {
    public static void main(String[] args) {
        BST<String, Integer> st = new BST<String, Integer>();

        StdOut.println("Enter key/value pairs as <key>=<value>, with values as integers: ");

        while(!StdIn.isEmpty()) {
            String keyVal = StdIn.readString();
            if (keyVal.equals("exit")) {
                break;
            }
            String[] parts = keyVal.split("=");
            if (parts.length != 2) {
                StdOut.println("The format of each key/value input must be <key>=<value>, where <value> is a valid integer!");
                continue;
            }
            st.put(parts[0], parseInt(parts[1]));
        }

        for (String s : st.levelOrder())
            StdOut.println(s + " " + st.get(s));

        StdOut.println();

        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));
    }
}
