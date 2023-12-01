#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    const char *filename = "input.txt"; 
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("FILE: an error occured\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    int sum = 0;
    while((getline(&line, &len, file) != -1)) {
        int number = 0;
        short i = 0;
        short linel = strlen(line);

        while (i < linel) {
            if (isdigit(line[i])) {
                number = number + 10 * (line[i] - 48);
                break;
            }
            i++;
        }
        i = linel - 1;
        while (i >= 0) {
            if (isdigit(line[i])) {
                number = number + (line[i] - 48);
                break;
            }
            i--;
        }
        sum+=number;
    }
    fclose(file);
    if (line) free(line);

    printf("%d\n", sum);
    return 0;
}