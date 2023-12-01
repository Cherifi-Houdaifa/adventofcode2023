#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef char bool;

// returns digit if found else -1
int checkDigit(char *s, int i)
{
    if (isdigit(s[i]))
    {
        return s[i] - 48;
    }
    
    // check for one ... nine
    // "yes, i know this isn't the best way to go about solving it"
    if (s[i] == 'e' && s[i - 1] == 'n' && s[i - 2] == 'o')
    {
        return 1;
    }
    else if (s[i] == 'o' && s[i - 1] == 'w' && s[i - 2] == 't')
    {
        return 2;
    }
    else if (s[i] == 'e' && s[i - 1] == 'e' && s[i - 2] == 'r' && s[i - 3] == 'h' && s[i - 4] == 't')
    {
        return 3;
    }
    else if (s[i] == 'r' && s[i - 1] == 'u' && s[i - 2] == 'o' && s[i - 3] == 'f')
    {
        return 4;
    }
    else if (s[i] == 'e' && s[i - 1] == 'v' && s[i - 2] == 'i' && s[i - 3] == 'f')
    {
        return 5;
    }
    else if (s[i] == 'x' && s[i - 1] == 'i' && s[i - 2] == 's')
    {
        return 6;
    }
    else if (s[i] == 'n' && s[i - 1] == 'e' && s[i - 2] == 'v' && s[i - 3] == 'e' && s[i - 4] == 's')
    {
        return 7;
    }
    else if (s[i] == 't' && s[i - 1] == 'h' && s[i - 2] == 'g' && s[i - 3] == 'i' && s[i - 4] == 'e')
    {
        return 8;
    }
    else if (s[i] == 'e' && s[i - 1] == 'n' && s[i - 2] == 'i' && s[i - 3] == 'n')
    {
        return 9;
    }
    else if (s[i] == 'o' && s[i - 1] == 'r' && s[i - 2] == 'e' && s[i - 3] == 'z')
    {
        return 0;
    }
    return -1;
}

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

    int sum = 0;
    while ((getline(&line, &len, file) != -1))
    {
        int number = 0;
        short i = 0;
        short linel = strlen(line);

        bool isFirst = 1;
        int lastDigit;

        while (i < linel)
        {
            if (checkDigit(line, i) != -1 && isFirst)
            {
                number = number + 10 * checkDigit(line, i);
                isFirst = 0;
            }
            if (checkDigit(line, i) != -1) {
                lastDigit = checkDigit(line, i);
            }
            
            i++;
        }
        number += lastDigit;
        sum += number;
    }
    fclose(file);
    if (line)
        free(line);

    printf("%d\n", sum);
    return 0;
}