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

//改变链表，只能传struct node**，不能传值，即不能传struct node*
void list_reverse(struct node** h)
{
    assert(h != NULL);
    struct node* cur = *h;
    struct node* pre = NULL;
    struct node* next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    *h = pre;
}

/*
 * 计算范围不包括空的头结点
 * 如果是偶数，那么是中间靠后的点
 */
const struct node* list_find_middle(const struct node* h) {
    assert(h != NULL);
    const struct node *fast, *slow;
    fast = slow = h;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

struct node* list_find_middle_pre(struct node** h) {
    struct node **f, **s;
    f = s = h;

    while ((*f) && (*f)->next) {
        f = &((*f)->next->next);
        s = &((*s)->next);
    }
    return *s;
}
//图形化struct node**，放到内存考虑，是一个空间，指向链表头结点
//链表定义：头结点为struct node*，后续结点为struct node
//find的结果是struct node*的位置，所以使用**
//为什么要找struct node**位置，因为后续可能会操作链表，比如删除或者插入
//为什么不能使用struct node*？找到结点后呢，只能改变相应内存的值
//入参能不能使用struct node*？不能，这个不是实际的链表地址了，链表是struct node**表示，注意不是struct node*表示
struct node** list_find_pre(struct node** h, int key) {
    assert(h != NULL);

    struct node** p = h;

    while (*p != NULL) {
        if ((*p)->data == key) {
            return p; //find the key
        }
        p = &((*p)->next);
    }
    return NULL;
}

struct node* list_alloc_node(int key, struct node* next) {
    struct node* p = malloc(sizeof(*p));
    if (p != NULL) {
        p->data = key;
        p->next = next;
    }
    return p;
}


bool list_insert_node_before(struct node** h, int src, int key) {
    struct node** p = list_find_pre(h, src);
    if (p == NULL) return false;
    //struct node* q = list_alloc_node(key, (*p)->next);
    struct node* q = list_alloc_node(key, (*p));
    if (q == NULL) return false;
    //(*p)->next = q;
    *p = q;
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
    list_reverse(&head);
    list_print(head);
    struct node** res = list_find_pre(&head, 1);
    printf("res: %d\n", (*res)->data);
    int ret = list_insert_node_before(&head, 1, 2);
    assert(true == ret);
    list_print(head);
    ret = list_insert_node_before(&head, 0, 3);
    assert(true == ret);
    ret = list_insert_node_before(&head, 0, 7);
    assert(true == ret);
    ret = list_insert_node_before(&head, 0, 8);
    assert(true == ret);
    ret = list_insert_node_before(&head, 0, 9);
    assert(true == ret);
    ret = list_insert_node_before(&head, 0, 10);
    assert(true == ret);
    list_print(head);
    const struct node* f = list_find_middle(head);
    printf("middle node is %d\n", f->data);
    f = list_find_middle_pre(&head);
    printf("middle node is %d\n", f->data);
    return 0;
}
