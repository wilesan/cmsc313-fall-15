/*
 * add_test_ta.c
 *
 *  Created on: Oct 25, 2015
 *      Author: acw3f
 */

/* Prototypes for external functions */
int write(int fd, const void *buffer, unsigned int size);

/* Our own assembly routine:  adder takes a variable number of parameters.  The
 * first parameter is the count of numbers to add (the total number of parameters - 1).
 * The remaining parameters are assumed to be of type "int" and are numbers that will be
 * summed.  The return value from the function is the sum of the parameters.
 */
int adder(unsigned int num, ...);

/* Some constants */
#define STDOUT              1

/* Prints a number to STDOUT */
void print_num(unsigned int num)
{
    char buffer[11];
    char *buf_ptr = &buffer[9];
    char remainder;
    buffer[10] = 0;
    do
    {
        remainder = num % 10;
        *buf_ptr = remainder + '0';
        buf_ptr--;
        num /= 10;
    } while(num);
    buf_ptr++;
    write(STDOUT, buf_ptr, 11 - (int)(buf_ptr - buffer));
}

const char output_str[] = "The score is: ";
const char newline[] = " as long as echo $? = 82\n";

void write_result(unsigned int result)
{
    write(STDOUT, output_str, sizeof(output_str) - 1);
    print_num(result);
    write(STDOUT, newline, sizeof(newline) - 1);
}

int main()
{
    unsigned int score = 100;
    unsigned int result;

    /* Add 4 numbers: 1 + 1 + 1 + 1 */
    result = adder(4, 1, 1, 1, 1);
    if (result != 4)
    {
        score -= 4;
    }

    /* Add 2 numbers: 765 + 35 */
    result = adder(2, 765, 35);
    if (result != 800)
    {
        score -= 4;
    }

    /* Add 3 numbers: 10000 + 25 + 75 */
    result = adder(3, 10000, 25, 75);
    if (result != 10100)
    {
        score -= 4;
    }

    /* Add 8 numbers: 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 */
    result = adder(8, 1, 2, 3, 4, 5, 6, 7, 8);
    if (result != 36)
    {
        score -= 4;
    }

    /* Result = 0 */
    result = adder(4, 2, -2, 2, -2);
    if (result != 0)
    {
        score -= 4;
    }

    /* Result = 25 (though an extra 5 is in the parameter list) */
    result = adder(5, 5, 5, 5, 5, 5, 5);
    if (result != 25)
    {
        score -= 4;
    }

    /* Result = 12 */
    result = adder(6, 2, 2, 2, 2, 2, 2);
    if (result != 12)
    {
        score -= 4;
    }

    write_result(score);
    return 82;
}

