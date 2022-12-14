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
    int height;
    struct Node *left;
    struct Node *right;
};
 
void count_lengths(int ind, struct Node *elements);
 
struct Node *insert(struct Node *node, int key);
 
int height(struct Node *node)
{
    return node ? node->height : 0;
}
 
int node_balance(struct Node *node)
{
    return height(node->right) - height(node->left);
}
 
void fix_height(struct Node *node)
{
    int left_height = height(node->left);
    int right_height = height(node->right);
    node->height = (left_height > right_height ? left_height : right_height) + 1;
}
 
struct Node *rotate_left(struct Node *node)
{
    struct Node *new_node = node->right;
    node->right = new_node->left;
    new_node->left = node;
 
    fix_height(node);
    fix_height(new_node);
 
    return new_node;
}
 
struct Node *rotate_right(struct Node *node)
{
    struct Node *new_node = node->left;
    node->left = new_node->right;
    new_node->right = node;
 
    fix_height(node);
    fix_height(new_node);
 
    return new_node;
}
 
struct Node *balance(struct Node *node)
{
    fix_height(node);
    if (node_balance(node) == 2)
    {
        if (node_balance(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if (node_balance(node) == -2)
    {
        if (node_balance(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
 
    return node;
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
        elements[ind].height = elements[elements[ind].left_ind].height + 1;
    }
 
    if (elements[ind].right_ind != 0)
    {
        count_lengths(elements[ind].right_ind, elements);
        if (elements[elements[ind].right_ind].height >= elements[ind].height)
            elements[ind].height = elements[elements[ind].right_ind].height + 1;
    }
}
 
int find_line_ind(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
 
    int left_height = find_line_ind(node->left);
    int right_height = find_line_ind(node->right);
 
    return left_height + right_height + 1;
}
 
int line_ind = 1;
 
void print_tree(FILE *file_out, struct Node *node)
{
    int l_ind = (node->left != NULL) ? (line_ind + 1) : 0;
    int r_ind = (node->right != NULL) ? (find_line_ind(node->left) + line_ind + 1) : 0;
 
    fprintf(file_out, "%d %d %d\n", node->key, l_ind, r_ind);
 
    line_ind++;
 
    if (node->left)
    {
        print_tree(file_out, node->left);
    }
 
    if (node->right)
    {
        print_tree(file_out, node->right);
    }
}
 
int n;
 
int main()
{
    FILE *file;
    file = fopen("addition.in", "r");
    FILE *file_out;
    file_out = fopen("addition.out", "w");
 
    fscanf(file, "%d", &n);
 
    if (n == 0)
    {
        int insert_key;
        fscanf(file, "%d", &insert_key);
 
        fprintf(file_out, "%d\n", 1);
        print_tree(file_out, insert(NULL, insert_key));
 
        fclose(file_out);
        return 0;
    }
 
    struct Node *elements = malloc((n + 1) * sizeof(struct Node));
    elements[0].key = 0;
    elements[0].left_ind = 0;
    elements[0].right_ind = 0;
    elements[0].height = 1;
 
    for (int i = 1; i < n + 1; i++)
    {
        fscanf(file, "%d %d %d", &elements[i].key, &elements[i].left_ind, &elements[i].right_ind);
        elements[i].height = 1;
        elements[i].left = NULL;
        elements[i].right = NULL;
    }
    int insert_key;
    fscanf(file, "%d", &insert_key);
 
    add_lengths(elements);
 
    for (int i = n; i > 0; i--)
    {
        if (elements[i].left_ind != 0)
        {
            elements[i].left = malloc(sizeof(struct Node));
            elements[i].left = &elements[elements[i].left_ind];
        }
        if (elements[i].right_ind != 0)
        {
            elements[i].right = malloc(sizeof(struct Node));
            elements[i].right = &elements[elements[i].right_ind];
        }
    }
 
    struct Node *bin_tree;
    bin_tree = malloc(sizeof(struct Node));
    bin_tree = insert(&elements[1], insert_key);
 
    fprintf(file_out, "%d\n", n);
    print_tree(file_out, bin_tree);
    return 0;
}
 
struct Node *insert(struct Node *node, int key)
{
    if (node == NULL)
    {
        n++;
        struct Node *new_node;
        new_node = malloc(sizeof(struct Node));
        new_node->key = key;
        new_node->left_ind = 0;
        new_node->right_ind = 0;
        new_node->height = 1;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
 
    return balance(node);
}