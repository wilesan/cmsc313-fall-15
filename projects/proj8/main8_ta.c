/*
 * main6_ta.c
 *
 *  Created on: Apr 2, 2015
 *      Author: acw3f
 */

#include <stdio.h>
#include <string.h>
#include "match_dyn.h"

struct my_match
{
    int date;  // Date of the match (YYYYMMDD)
    char sport[20];  // Name of the sport
    char contestant1[40]; // First Contestant's Name
    char contestant2[40]; // Second Contestant's Name
    int contestant1_score; // First Contestant's Score
    int contestant2_score; // Second Contetant's Score
    struct match *next;  // Pointer to the next citizen record
};

int score = 100;

int main()
{
    int i;
    init_matches();

    struct match *buf = new_match();
    strcpy(buf->contestant1, "1234");
    buf->contestant1_score = 4;

    struct match *buf2 = new_match();
    strcpy(buf2->contestant1, "5678");
    buf2->contestant1_score = 4;

    buf->next = buf2;

    printf("CHECK OUTPUT: The next dump should show exactly 8 available and a total of 10 buffers - manually subtract 3 if it does not\n");
    dump_matches();

    del_match(buf);

    printf("CHECK OUTPUT: The next dump should show exactly 10 available and a total of 10 buffers - manually subtract 5 if it does not\n");
    dump_matches();

    buf = new_match();
    buf2 = buf;

    for (i = 0; i < 10; i++)
    {
        buf2->next = new_match();
        buf2 = buf2->next;
    }

    printf("CHECK OUTPUT: The next dump should show exactly 9 available buffers and a total of 20 buffers - manually subtract 5 if it does not\n");
    dump_matches();

    clean_matches();

    printf("CHECK OUTPUT: The next dump should show exactly 9 available buffers and a total of 20 buffers - manually subtract 5 if it does not\n");
    dump_matches();


    buf2 = buf->next;
    buf->next = NULL;

    del_match(buf);
    buf = buf2->next;
    buf2->next = NULL;
    del_match(buf2);

    printf("CHECK OUTPUT: The next dump should show exactly 11 available buffers and a total of 20 buffers - manually subtract 5 if it does not\n");
    dump_matches();

    clean_matches();

    printf("CHECK OUTPUT: The next dump should show exactly 1 available buffers and a total of 10 buffers - manually subtract 5 if it does not\n");
    dump_matches();

    del_match(buf);

    printf("CHECK OUTPUT: The next dump should show exactly 10 available buffers and a total of 10 buffers - manually subtract 5 if it does not\n");
    dump_matches();

    if (sizeof(struct my_match) != sizeof(struct match))
    {
        printf("struct match length %d is not the correct length: %d - subtracting 5\n", sizeof(struct match), sizeof(struct my_match));
        score -= 5;
    }

    char buffer[20 * 4];
    for (i = 0; i < (20 * 4); i++)
    {
        buffer[i] = 'A' + (i & 0x7);
    }

    struct match *desc_array[20];
    int j, set_error = 0;
    for (i = 0; i < 20; i++)
    {
        desc_array[i] = new_match();
        if (i > 0)
        {
            desc_array[i-1]->next = desc_array[i];
        }

        if (desc_array[i] == NULL)
        {
            printf("Got new_buf_desc() == NULL when should have been correct, -5\n");
            score -= 5;
            break;
        }

        for (j = 0; j < i; j++)
        {
            if (desc_array[j] == desc_array[i])
            {
                printf("%dth buf_desc is the same as %dth buf_desc - %p\n", i, j, desc_array[i]);
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

    buf = new_match();
    if (buf != NULL)
    {
        printf("Was allowed to allocate too many buffers - -5\n");
        score -= 5;
        del_match(buf);
    }

    printf("Remember to subtract anything listed preceded with \"CHECK OUTPUT\" above from this final score: %d\n", score);
    return 0;
}
