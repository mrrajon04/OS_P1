#include "lab.h"

/**
 * @brief Initialize for a new list
 */
list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (!list) return NULL;

    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;

    // Create sentinel node
    list->head = (node_t *)malloc(sizeof(node_t));
    if (!list->head) {
        free(list);
        return NULL;
    }

    list->head->data = NULL;
    list->head->next = list->head;
    list->head->prev = list->head;

    return list;
}

/**
 * @brief Destroy the list and its contents.
 */
void list_destroy(list_t **list) {
    if (!list || !*list) return;

    node_t *current = (*list)->head->next;
    while (current != (*list)->head) {
        node_t *next = current->next;
        if ((*list)->destroy_data) {
            (*list)->destroy_data(current->data);
        }
        free(current);
        current = next;
    }

    // Free the sentinel node and the list itself
    free((*list)->head);
    free(*list);
    *list = NULL;
}

/**
 * @brief Add data to the front of the list.
 */
list_t *list_add(list_t *list, void *data) {
    if (!list) return NULL;

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (!new_node) return NULL;

    new_node->data = data;

    // Insert new node after head
    new_node->next = list->head->next;
    new_node->prev = list->head;

    list->head->next->prev = new_node;
    list->head->next = new_node;

    list->size++;
    return list;
}

/**
 * @brief Remove the data 
 */
void *list_remove_index(list_t *list, size_t index) {
    if (!list || index >= list->size) return NULL;

    node_t *current = list->head->next;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    // Remove the node
    current->prev->next = current->next;
    current->next->prev = current->prev;

    void *data = current->data;
    free(current);
    list->size--;

    return data;
}

/**
 * @brief Find the index of a data item in the list.
 */
int list_indexof(list_t *list, void *data) {
    if (!list || list->size == 0) return -1;

    node_t *current = list->head->next;
    for (size_t i = 0; i < list->size; i++) {
        if (list->compare_to(current->data, data) == 0) {
            return (int)i;
        }
        current = current->next;
    }

    return -1; // Data not found
}
