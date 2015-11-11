/*
 * main8.c
 *
 *  Created on: Nov 8, 2015
 *      Author: acw3f
 */

#include <stdio.h>
#include <string.h>
#include "match_dyn.h"

struct match *get_match(int date, char *sport, char *contestant1, char *contestant2, int contestant1_score, int contestant2_score)
{
    struct match *info = new_match();
    if (info == NULL)
    {
        return NULL;
    }
    info->date = date;
    strncpy(info->sport, sport, sizeof(info->sport) - 1);
    strncpy(info->contestant1, contestant1, sizeof(info->contestant1) - 1);
    strncpy(info->contestant2, contestant2, sizeof(info->contestant2) - 1);
    info->contestant1_score = contestant1_score;
    info->contestant2_score = contestant2_score;
    return info;
}

int main()
{
    int i;
    init_matches();

    struct match * match = get_match(20151018, "Baseball", "Cubs", "Mets", 1, 4);

    struct match *match2 = get_match(20151018, "Football", "Ravens", "49ers", 20, 25);

    match->next = match2;

    dump_matches();

    del_match(match);

    dump_matches();

    match = new_match();
    match2 = match;

    for (i = 0; i < 10; i++)
    {
        match2->next = new_match();
        match2 = match2->next;
    }

    dump_matches();

    clean_matches();

    dump_matches();


    match2 = match->next;
    match->next = NULL;
    del_match(match);

    match2->next = NULL;
    del_match(match2);
    dump_matches();

    clean_matches();

    dump_matches();
    return 0;
}
