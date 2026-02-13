#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    void *value;
    struct Node* next;
};

void* allocate_generic(void *value, size_t size) {
    if (value == NULL || size == 0) {
        printf("Invalid value or size for allocation\n");
        return NULL;
    }

    void *v = malloc(size);
    if (v == NULL) {
        printf("Malloc returned error during generic allocation\n");
        return NULL;
    }

    memcpy(v, value, size);
    return v;
}

struct Node* create_node(void *value, size_t value_size) {
    void *v = allocate_generic(value, value_size);
    if (v == NULL) {
        printf("Couldn't generically allocate node value\n");
        return NULL;
    }

    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Couldn't allocate memory for node stuct\n");
        free(v); // Free the allocated value, otherwise memory leak
        return NULL;
    }
    struct Node node = { .value=v, .next=NULL };
    *n = node;

    return n;
}

struct Node* create_next(struct Node *current, void *value, size_t value_size) {
    void *v = allocate_generic(value, value_size);
    if (v == NULL) {
        return NULL;
    }

    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        return NULL;
    }
    struct Node node = { .value=v, .next=NULL };
    *n = node;
    current->next = n;

    return n;
}

void delete_node(struct Node *node) {
    free(node->value);
    free(node);
}

int delete_child(struct Node *node) {
    struct Node *next_node = node->next;
    if (node == NULL || next_node == NULL) {
        return -1;
    }
    node->next = next_node->next;
    delete_node(next_node); // Frees all the memory ofthe node
    return 1;
}

void print_int(void* v) {
    if (v != NULL) printf("%d\n", *((int*)v));
}

void print_list(struct Node *head, void (*callback)(void*)) {
    if (head == NULL) {
        return;
    }

    callback(head->value);
    if (head->next != NULL)  print_list(head->next, callback);

    return;
}

// // TODO: deletes the list from the last node to the first
// int delete_list(struct Node *node) {
// }

int main(void) {
    struct Node *head = create_node(&(int){10}, sizeof(int));
    struct Node *next = create_next(head, &(int){50}, sizeof(int));

    print_list(head, print_int);

    // delete_list(head);
}
