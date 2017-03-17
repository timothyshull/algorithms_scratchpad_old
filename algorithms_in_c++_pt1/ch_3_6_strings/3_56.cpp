#include <iostream>

// NOTE: does not account for lower case vs. upper case
bool is_palindrome(const char str[]) {
    int size;
    for (size = 0; str[size] != '\0'; size++) {}
    // size++; not needed here because we want the end index to start before '\0'
    int i;
    int j;
    for (i = 0, j = size - 1; i < size / 2; i++, j--) {
        // does not check the center character for odd length strings, but this is ok
        if (str[i] != str[j]) { return false; }
    }
    return true;
}

int main() {
    std::cout << std::boolalpha << is_palindrome("abba") << "\n";
    std::cout << std::boolalpha << is_palindrome("abcba") << "\n";
    return 0;
}