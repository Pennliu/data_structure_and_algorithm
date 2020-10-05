#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

// gcc -o -g list list.c

struct node {
    int data;
    struct node* next;
};

bool list_add_node(struct node** h, struct node* n)
{
    assert(h != NULL);
    assert(n != NULL);
    n->next = (*h); //(*h)右值表示(*h)内存的值
    (*h) = n; //左值表示(*h)内存的地址
    return true;
}

void list_print(struct node* h)
{
    while (h != NULL)
    {
        printf("->%d", h->data);
        h = h->next; //循环递增条件遗漏
    }
    printf("\n");
}

int main()
{
    //create list
    //add a node from head
    //delete a node  from head
    struct node* head = NULL;
    struct node* n = (struct node*)malloc(sizeof(struct node));
    //memset(n, 0, sizeof(struct node));
    n->data = 0;
    n->next = NULL;
    list_add_node(&head, n);
    n = (struct node*)malloc(sizeof(struct node));
    n->data = 1;
    n->next = NULL;
    list_add_node(&head, n);
    list_print(head);
    return 0;
}
