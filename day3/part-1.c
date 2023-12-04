#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char bool;

int getIntLen(int n);
bool checkLine(char *line, int i, int j);

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

    int number;
    short i, j, linel;

    int sum = 0;

    getline(&lineB, &len, file);
    lineC = lineB;
    lineB = NULL;

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
            if (isdigit(lineC[i]))
            {
                // get the number in line
                number = lineC[i] - 48;
                j = i + 1;
                while (isdigit(lineC[j]))
                {
                    number = (number * 10) + (lineC[j] - 48);
                    j++;
                }
                // check lineB and lineT and next to number
                if (checkLine(lineT, i - 1, i + getIntLen(number)) || checkLine(lineB, i - 1, i + getIntLen(number)) || checkLine(lineC, i - 1, i + getIntLen(number)))
                {
                    sum += number;
                }
                i += getIntLen(number);
            }
            else
            {
                i++;
            }
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

    printf("the sum is %d\n", sum);

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

bool checkLine(char *line, int i, int j)
{
    if (line == NULL)
        return 0;

    bool found = 0;
    if (i < 0)
    {
        i = 0;
    }
    if (j >= strlen(line) - 1)
    {
        j = strlen(line) - 2;
    }
    while (i <= j)
    {
        if (line[i] != '.' && !isdigit(line[i]))
        {
            found = 1;
        }
        i++;
    }
    return found;
}