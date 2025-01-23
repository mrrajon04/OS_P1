#ifndef LAB_H
#define LAB_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A node in the list
 */
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node_t;

/**
 * @brief Struct to represent a list.
 * The list maintains 2 function pointers to help manage the data it stores.
 */
typedef struct list {
    void (*destroy_data)(void *);                  /* Frees allocated memory */
    int (*compare_to)(const void *, const void *); /* Returns 0 if data are the same */
    size_t size;                                   /* Number of elements in the list */
    struct node *head;                             /* Sentinel node */
} list_t;

/**
 * @brief Create a new list with callbacks to manage stored data.
 *
 * @param destroy_data Function that frees memory for user-supplied data.
 * @param compare_to Function that compares two user data elements.
 * @return A pointer to the newly allocated list.
 */
list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *));

/**
 * @brief Destroy the list and all associated data. Calls destroy_data on each node's data element.
 *
 * @param list A pointer to the list that needs to be destroyed.
 */
void list_destroy(list_t **list);

/**
 * @brief Add data to the front of the list.
 *
 * @param list A pointer to an existing list.
 * @param data The data to add.
 * @return A pointer to the list.
 */
list_t *list_add(list_t *list, void *data);

/**
 * @brief Remove the data at the specified index. Returns NULL if the index is invalid.
 *
 * @param list The list to remove the element from.
 * @param index The index.
 * @return The data that was removed or NULL if nothing was removed.
 */
void *list_remove_index(list_t *list, size_t index);

/**
 * @brief Search for an occurrence of data in the list.
 * Returns the index if found, or -1 if not found.
 *
 * @param list The list to search.
 * @param data The data to look for.
 * @return The index of the item if found, or -1 if not found.
 */
int list_indexof(list_t *list, void *data);

#ifdef __cplusplus
}
#endif

#endif /* LAB_H */
