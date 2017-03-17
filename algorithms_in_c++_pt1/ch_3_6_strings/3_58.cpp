#include <iostream>

bool has_substring(const char test_str[], const char outer_str[]) {
    int i;
    for (i = 0; outer_str[i] != '\0'; i++) {
        int j;
        for (j = 0; test_str[j] != '\0'; j++) {
            if (outer_str[i + j] != test_str[j]) {
                break;
            }
        }
        if (test_str[j] == '\0') {
            return true;
        }
    }
    return false;
}

// using C-strings to be consistent
int main(int argc, char *argv[]) {
    const char *str = argv[1];

    char buf[100];
    while (fgets(buf, 100, stdin) != NULL) {
        if (has_substring(buf, str)) {
            fprintf(stdout, "The substring %s is contained in the string %s\n", buf, str);
        } else {
            fprintf(stdout, "The substring %s is not contained in the string %s\n", buf, str);
        }
    }
    return 0;
}