#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "messagerie.h"
#include "menu.h"

void generate_username(char username[], const char *prefix) 
{
    int random_number = rand() % 1000;
    sprintf(username, "%s%d", prefix, random_number);
}

    
