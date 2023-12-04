#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WINNING_SIZE 10
#define CARDS_COUNT 214

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

    // program variables
    short i, j, k, m, linelen;
    short winning[WINNING_SIZE];
    long cards[CARDS_COUNT] = {[0 ... CARDS_COUNT - 1] = 1};
    short countW;
    short number;


    // line counter
    m = 0;
    while (getline(&line, &len, file) != -1)
    {
        linelen = strlen(line);
        i = 5;
        while (line[i] != ':')
            i++;

        i += 2;

        // get the winning numbers into an array
        k = 0;
        while (k < WINNING_SIZE)
        {
            if (isdigit(line[i]))
            {
                number = 0;
                j = i;
                while (isdigit(line[j]))
                {
                    number = (number * 10) + (line[j] - 48);
                    j++;
                }
                winning[k] = number;
                i = j + 1;
                k++;
            }
            else
            {
                i++;
            }
        }

        i += 2;

        countW = 0;
        while (i < linelen)
        {
            if (isdigit(line[i]))
            {
                number = 0;
                j = i;
                while (isdigit(line[j]))
                {
                    number = (number * 10) + (line[j] - 48);
                    j++;
                }

                // check if the number is one of the winning numbers
                for (char l = 0; l < WINNING_SIZE; l++)
                {

                    if (number == winning[l])
                    {
                        countW++;
                        break;
                    }
                }

                i = j + 1;
            }
            else
            {
                i += 1;
            }
        }

        for (short l = m + 1; l < m + 1 + countW; l++)
        {
            cards[l] += cards[m];
        }
        m++;
    }

    long total = 0;

    for (int i = 0; i < CARDS_COUNT; i++)
    {
        total += cards[i];
    }

    fclose(file);
    if (line)
        free(line);

    printf("%d\n", total);

    return 0;
}