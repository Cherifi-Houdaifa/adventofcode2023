#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char bool;

int getIntLen(int n);
void checkLine(char* line, int i, int* parts, int* product);

int main()
{
    const char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("FILE: an error occured\n");
        return 1;
    }

    char *lineT = NULL;
    char *lineC = NULL;
    char *lineB = NULL;

    size_t len = 0;

    short i, linel;
    int parts, product;

    getline(&lineB, &len, file);
    lineC = lineB;
    lineB = NULL;

    int sum = 0;

    bool isRunning = 1;
    while (isRunning)
    {
        if (getline(&lineB, &len, file) == -1)
        {
            isRunning = 0;
            free(lineB);
            lineB = NULL;
        }


        i = 0;
        linel = strlen(lineC);
        while (i < linel)
        {
            if (lineC[i] == '*') {
                parts = 0;
                product = 1;
                checkLine(lineT, i, &parts, &product);
                checkLine(lineC, i, &parts, &product);
                checkLine(lineB, i, &parts, &product);

                if (parts == 2) {
                    sum+=product;
                }
            }
            i++;
        }


        if (lineT)
            free(lineT);
        lineT = lineC;
        lineC = NULL;
        lineC = lineB;
        lineB = NULL;
    }
    fclose(file);
    if (lineT)
        free(lineT);
    if (lineC)
        free(lineC);
    if (lineB)
        free(lineB);

    printf("%d\n", sum);

    return 0;
}

int getIntLen(int n)
{
    short l = 1;
    while ((n = n / 10) > 0)
    {
        l += 1;
    }
    return l;
}

void checkLine(char* line, int i, int* parts, int* product) {
    
    int k;
    int number;
    int j = i + 1;
    i = i - 1;
    
    if (i < 0) {
        i = 0;
    }
    if (j >= strlen(line) - 1) {
        j = strlen(line) - 2;
    }

    while (i <= j) {
        if (isdigit(line[i])) {
            *parts += 1;
            number = 0;
            k = i;
            while (isdigit(line[k]) && k >= 0) {
                k--;
            }
            k+=1;
            while (isdigit(line[k])) {
                number = (number * 10) + (line[k] - 48);
                k++;
            }
            *product *= number;
            i = k;
        } else {
            i++;
        }
    }
    
}