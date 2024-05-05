#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <name>,<phone_number>\n", argv[0]);
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