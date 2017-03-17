#include <cstring>
#include <iostream>

// from apple source
//char *strcpy(char *s1, const char *s2) {
//    char *s = s1;
//    while ((*s++ = *s2++) != 0) {}
//    return s1;
//}
//
//char *strcat(char *s1, const char *s2) {
//    strcpy(&s1[strlen(s1)], s2);
//    return s1;
//}

char *alloc_strcpy(const char *s2) {
    char *s = new char[strlen(s2)];
    while ((*s++ = *s2++) != 0) {}
    return s;
}

char *alloc_strcat(char *s1, const char *s2) {
    size_t size1 = strlen(s1);
    size_t size2 = strlen(s2);

    char *s = new char[size1 + size2];
    strcpy(s, s1);
    strcpy(&s[size1], s2);
    return s;
}