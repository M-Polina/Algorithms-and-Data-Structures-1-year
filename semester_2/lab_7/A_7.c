#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
 
struct Node
{
    int key;
    int left_ind;
    int right_ind;
    int length_below;
};
 
void count_lengths(int ind, struct Node *elements);
 
void add_lengths(struct Node *elements);
 
int main()
{
    FILE *file;
    file = fopen("balance.in", "r");
    int n;
    fscanf(file, "%d", &n);
    FILE *file_out;
    file_out = fopen("balance.out", "w");
 
    if (n == 0)
    {
        return 0;
        fclose(file_out);
    }
 
    struct Node *elements = malloc((n + 1) * sizeof(struct Node));
    elements[0].key = 0;
    elements[0].left_ind = 0;
    elements[0].right_ind = 0;
    elements[0].length_below = 0;
 
    for (int i = 1; i < n + 1; i++)
    {
        fscanf(file, "%d %d %d", &elements[i].key, &elements[i].left_ind, &elements[i].right_ind);
        elements[i].length_below = 0;
    }
 
    add_lengths(elements);
 
    for (int i = 1; i <= n; i++)
    {
        if (elements[i].right_ind != 0 && elements[i].left_ind != 0)
        {
            fprintf(file_out, "%d\n", elements[elements[i].right_ind].length_below - elements[elements[i].left_ind].length_below);
        }
        else if (elements[i].right_ind == 0 && elements[i].left_ind == 0)
        {
            fprintf(file_out, "%d\n", 0);
        }
        else if (elements[i].right_ind == 0)
        {
            fprintf(file_out, "%d\n", 0 - 1 - elements[elements[i].left_ind].length_below);
        }
        else if (elements[i].left_ind == 0)
        {
            fprintf(file_out, "%d\n", elements[elements[i].right_ind].length_below + 1 - 0);
        }
    }
 
    fclose(file_out);
    return 0;
}
 
void add_lengths(struct Node *elements)
{
    count_lengths(1, elements);
}
 
void count_lengths(int ind, struct Node *elements)
{
    if (elements[ind].left_ind != 0)
    {
        count_lengths(elements[ind].left_ind, elements);
        elements[ind].length_below = elements[elements[ind].left_ind].length_below + 1;
    }
 
    if (elements[ind].right_ind != 0)
    {
        count_lengths(elements[ind].right_ind, elements);
        if (elements[elements[ind].right_ind].length_below >= elements[ind].length_below)
            elements[ind].length_below = elements[elements[ind].right_ind].length_below + 1;
    }
}