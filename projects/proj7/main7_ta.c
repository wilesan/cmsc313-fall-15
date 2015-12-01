/*
 * main5.c
 *
 *  Created on: Mar 25, 2015
 *      Author: acw3f
 */

#include <stdio.h>
#include <string.h>
#include "match.h"

typedef struct
{
    int date;  // Date of the match (YYYYMMDD)
    char sport[20];  // Name of the sport
    char contestant1[40]; // First Contestant's Name
    char contestant2[40]; // Second Contestant's Name
    int contestant1_score; // First Contestant's Score
    int contestant2_score; // Second Contetant's Score
    struct match *next;  // Pointer to the next citizen record
} my_match_info;

int score = 100;
int deducted_points_for_non_null = 0;

struct match *get_match(int date, char *sport, char *contestant1, char *contestant2, int contestant1_score, int contestant2_score)
{
    struct match *info = new_match();
    if (info == NULL)
    {
        return NULL;
    }
    if ((deducted_points_for_non_null == 0) && (info->sport[0] != 0 || info->contestant1[0] != 0 || info->contestant2[0] != 0 || info->contestant1_score != 0 || info->contestant2_score != 0 || info->date != 0))
    {
        printf("Got struct match w/o clean info - -5\n");
        deducted_points_for_non_null = 1;
        score -= 5;
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
    struct match *info[20] = { NULL }, *info1;

    init_heap();

    printf("The following should show 20 available entries - deduct 3 points if it does not\n");
    dump_heap();

    info[0] = get_match(20151018, "Baseball", "Cubs", "Mets", 1, 4);
    del_match(info[0]);
    info[0] = get_match(20151018, "Football", "Ravens", "49ers", 20, 25);

    info[1] = get_match(20151019, "Baseball", "Royals", "Blue Jays", 8, 1);

    info[2] = get_match(20151019, "Football", "Giants", "Eagles", 7, 27);

    del_match(info[1]);

    info[1] = new_match();
    if (info[1] == NULL)
    {
        printf("Got new_match() == NULL when should have been correct, -5\n");
        score -= 5;
    }
    else
    {
        memset(info[1]->sport, 0, sizeof(info[1]->sport));
        memset(info[1]->contestant1, 0, sizeof(info[1]->contestant1));
        memset(info[1]->contestant2, 0, sizeof(info[1]->contestant2));
        info[1]->contestant1_score = 0;
        info[1]->contestant2_score = 0;
        info[1]->date = 0;
    }
    int i;
    if (sizeof(struct match) != sizeof(my_match_info))
    {
        printf("sizeof(struct match) == %d, not %d as it should - -5\n", sizeof(struct match), sizeof(my_match_info));
        score -= 5;
    }

    int j, set_error = 0;
    for (i = 3; i < 20; i++)
    {
        info[i] = new_match();
        if (info[i] == NULL)
        {
            printf("Got new_book_info() == NULL when should have been correct, -5\n");
            score -= 5;
            break;
        }
        memset(info[i]->sport, 0, sizeof(info[i]->sport));
        memset(info[i]->contestant1, 0, sizeof(info[i]->contestant1));
        memset(info[i]->contestant2, 0, sizeof(info[i]->contestant2));
        info[i]->contestant1_score = 0;
        info[i]->contestant2_score = 0;
        info[i]->date = 0;
        for (j = 0; j < i; j++)
        {
            if (info[i] == info[j])
            {
                printf("%dth struct match is the same as %dth struct match - %p\n", i, j, info[i]);
                set_error = 1;
            }
        }
    }
    if (set_error)
    {
        printf("Allocator returns same pointer for multiple allocations - -5\n");
        score -= 5;
    }
    set_error = 0;
    printf("The following should show 18 NULL entries - deduct 3 points if it does not\n");
    dump_heap();

    struct match *last_info = info[19];

    struct match *next_info = new_match();
    if (next_info != NULL)
    {
        printf("Could allocate at least 21 entries - -5\n");
        score -= 5;
        del_match(next_info);
        next_info = NULL;
    }

    /* Free all entries */
    for (i = 19; i >= 0; i--)
    {
        if (info[i])
        {
            del_match(info[i]);
            info[i] = NULL;
        }
    }

    printf("The following should show 20 NULL entries - deduct 3 points if it does not\n");
    dump_heap();

    /* Allocate all entries */
    for (i = 0; i < 20; i++)
    {
        info[i] = new_match();
        if (info[i] == NULL)
        {
            printf("Got new_match() == NULL when should have been correct, -5\n");
            score -= 5;
            break;
        }
    }

    next_info = new_match();
    if (next_info != NULL)
    {
        printf("Could allocate at least 21 entries - -5\n");
        score -= 5;
        del_match(next_info);
        next_info = NULL;
    }

    /* Delete every other entry */
    for (i = 0; i < 20; i+= 2)
    {
        if (info[i])
        {
            del_match(info[i]);
            info[i] = NULL;
        }
    }

    /* Now, reallocate them */
    for (i = 0; i < 20; i+= 2)
    {
        info[i] = new_match();
        if (info[i] == NULL)
        {
            printf("Got new_book_info() == NULL when should have been correct, -5\n");
            score -= 5;
            break;
        }
    }

    next_info = new_match();
    if (next_info != NULL)
    {
        printf("Could allocate at least 21 entries - -5\n");
        score -= 5;
        del_match(next_info);
        next_info = NULL;
    }

    printf("If you don't see another line with \"Final Score\" at the beginning, the Final Score is: %d\n", score);
    del_match(NULL);
    score -= 5;
    printf("Failed to exit the program with a bad pointer in del_match() - -5\n");
    printf("Final Score: %d\n", score);
    return 0;
}
