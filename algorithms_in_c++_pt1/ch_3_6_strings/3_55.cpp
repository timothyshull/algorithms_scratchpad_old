#include <iostream>
#include <cstdlib>
#include <iomanip>

// assumes it is null character terminated
void char_freq(const char str[]) {
    int size;
    double freqs[256] = {0};

    for (size = 0; str[size] != '\0'; size++) {
        if (!freqs[str[size]]) {
            freqs[str[size]] = 1;
        } else {
            freqs[str[size]]++;
        }
    }

    size++; // to account for null character
    freqs['\0'] = 1.0;

    for (int i = 0; i < 256; i++) {
        if (freqs[i]) {
            double count = freqs[i];
            double frequency = (count / size) * 100.0;
            freqs[i] = frequency;
        }
    }

    for (int i = 0; i < 256; i++) {
        char current_char = static_cast<char>(i);
        if (freqs[i]) {
            std::cout << "The frequency of the occurrences of the character: \'" << current_char << "\' in the string \'"
                      << str
                      << "\' is: " << std::setprecision(4) << freqs[i] << "%\n";
        }
    }
}

int main(int argc, char *argv[]) {
    char_freq(argv[1]);


    return 0;
}