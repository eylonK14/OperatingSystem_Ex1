#include <stdio.h>
#include <stdlib.h>

int validate(char *str)
{
    if (str[0] == ',')
        return 0;
    int i = 0;
    for (i = 0; str[i] != ',' ;i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' '))
            return 0;
    }
    i++;
    int hypen_count = 0;
    for (; str[i] != '\0'; i++)
    {
        if (str[i] == '-')
        {
            hypen_count++;
            if (hypen_count > 1)
                return 0;
        }
        else if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    // this program assumes that the input is enclosed in double quotes ,
    // and the name and phone number are separated by a comma
    if (argc != 2)
    {
        printf("Usage: %s \"<name>,<phone_number>\"\n", argv[0]);
        return 1;
    }
    if (!validate(argv[1]))
    {
        printf("Invalid input\n");
        return 1;
    }
    FILE *f = fopen("phonebook.txt", "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    // Write to file: name,phone_number

    fprintf(f, "%s\n", argv[1]);
    fclose(f);
}