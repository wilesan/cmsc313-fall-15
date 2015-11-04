/*
 * main7.c
 *
 *  Created on: Nov 1, 2015
 *      Author: acw3f
 */

#include <stdio.h>
#include <string.h>
#include "match.h"

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

void print_info(const struct match *info)
{
    printf("Date: %d\n", info->date);
    printf("Sport: %s\n", info->sport);
    printf("Contestant 1: %s, Score: %d\n", info->contestant1, info->contestant1_score);
    printf("Contestant 2: %s, Score: %d\n", info->contestant2, info->contestant2_score);
}

int main()
{
    struct match *info1, *info2, *info3;

    init_heap();

    info1 = get_match(20151018, "Baseball", "Cubs", "Mets", 1, 4);

    print_info(info1);

    dump_heap();

    del_match(info1);

    info1 = get_match(20151018, "Football", "Ravens", "49ers", 20, 25);

    info2 = get_match(20151019, "Baseball", "Royals", "Blue Jays", 8, 1);

    info3 = get_match(20151019, "Football", "Giants", "Eagles", 7, 27);

    dump_heap();

    del_match(info2);

    dump_heap();
    return 0;
}
