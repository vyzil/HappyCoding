#include <cstdio>
#include <cstring>

int word_sum(const char *str) {
    int sum = 0;
    for (int c = 0; str[c] != '\0' && str[c] != ' '; c++) {
        sum += str[c] - 'a' + 1;
    }
    return sum;
}

int main(){
    static const char s1[] = "computer preferred bulk tourist biographies";
    static const char s2[] = "worldwide resistance implemented magical viruses";
    static const char s3[] = "theorem";

    static auto sentence_sum = [&](const char *str) {
        int sum = 0;
        for (int c = 0; str[c] != '\0'; c++) {
            sum *= 100;
            sum += word_sum(str + c) % 100;
            while (str[c] != ' ' && str[c] != '\0')
                c++;
            if (str[c] == '\0')
                break;
        }
        return sum;
    };

    printf("%c\n", sentence_sum(s1));
    printf("%c\n", sentence_sum(s2));
    printf("%c\n", sentence_sum(s3));
}
