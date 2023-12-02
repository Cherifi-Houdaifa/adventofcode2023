#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char bool;

int getIntLen(int n);
int getGameid(char *line);

int main()
{
    const char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("FILE: an error occured\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    short gameid;
    short linelen;
    short i, k;
    short currentNumber;
    bool isPossible;
    int sum = 0;
    while ((getline(&line, &len, file) != -1))
    {
        gameid = getGameid(line);
        isPossible = 1;
        linelen = strlen(line);
        i = 5 + getIntLen(gameid) + 2;
        while (i < linelen)
        {
            if (isdigit(line[i]))
            {
                k = i;
                currentNumber = 0;
                while (isdigit(line[k]))
                {
                    currentNumber = (currentNumber * 10) + (line[k] - 48);
                    k++;
                }
                i += getIntLen(currentNumber) + 1;
            }
            else
            {
                if (line[i] == 'b')
                {
                    if (currentNumber > 14)
                    {
                        isPossible = 0;
                        break;
                    }
                    i += 6;
                }
                else if (line[i] == 'r')
                {
                    if (currentNumber > 12)
                    {
                        isPossible = 0;
                        break;
                    }
                    i += 5;
                }
                else if (line[i] == 'g')
                {
                    if (currentNumber > 13)
                    {
                        isPossible = 0;
                        break;
                    }
                    i += 7;
                }
            }
        }
        if (isPossible)
        {
            sum += gameid;
        }
    }
    fclose(file);
    if (line)
        free(line);

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

int getGameid(char *line)
{
    short k = 5;
    short gameid = 0;
    while (isdigit(line[k]))
    {
        gameid = (gameid * 10) + (line[k] - '0');
        k++;
    }
    return gameid;
}