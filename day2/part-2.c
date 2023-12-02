#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char bool;

int getIntLen (int n);

int main () {
    const char *filename = "input.txt"; 
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("FILE: an error occured\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;


    short linelen;
    short i,k;
    short currentNumber;
    int sum = 0;
    int minR, minB, minG;
    while((getline(&line, &len, file) != -1)) {
        linelen = strlen(line);
        
        minR = minB = minG = 0;

        // put i at the start of the line data
        i = 5;
        while (isdigit(line[i])) i++;
        i+=2;
        
        while (i < linelen) {
            if (isdigit(line[i])) {
                k = i;
                currentNumber = 0;
                while (isdigit(line[k])) {
                    currentNumber = (currentNumber * 10) + (line[k] - 48);
                    k++;
                }
                i += getIntLen(currentNumber) + 1;
            } else {
                if (line[i] == 'b') {
                    if (currentNumber > minB) {
                        minB = currentNumber;
                    }
                    i+=6;
                } else if (line[i] == 'r') {
                    if (currentNumber > minR) {
                        minR = currentNumber;
                    }
                    i+=5;
                } else if (line[i] == 'g') {
                    if (currentNumber > minG) {
                        minG = currentNumber;
                    }
                    i+=7;
                }
            }
        }
        
        sum+= minR * minG * minB;
    }
    fclose(file);
    if (line) free(line);

    printf("%d\n", sum);

    return 0;
}

int getIntLen (int n) {
    short l = 1;
    while ((n = n / 10) > 0) {
        l+=1;
    }
    return l;
}