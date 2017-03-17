#include <cstring>

void compress_blanks(char *str) {
    char *tmp = new char[strlen(str) + 1];
    int j = 0;
    int last_char = 'a';
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' || (str[i] == ' ' && last_char != ' ')) {
            tmp[j] = str[i];
            j++;
        }
        last_char = str[i];
    }
    // maybe need to explicitly set '\0' in tmp here
    strcpy(str, tmp);
}