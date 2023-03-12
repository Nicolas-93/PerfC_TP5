/**
 * @brief Implémetation minimale d'une queue, dans l'esprit
 * de STAILQ.
 * L'utilité principale est d'éviter la redondance
 * de fonctions similaires, pour des types différents
 */

/**
 * @brief Initialise une entête de liste
 * 
 */
#define LIST_INIT(head) do {    \
    (head)->first = NULL;       \
    (head)->last = NULL;        \
} while (0)

/**
 * @brief Détermine si la liste est vide
 * 
 */
#define LIST_EMPTY(head) \
    ((head)->first == NULL)

/**
 * @brief Renvoie l'élément suivant de la liste
 * 
 */
#define LIST_NEXT(elem) \
    ((elem)->next)

/**
 * @brief Renvoie le premier élément de la liste
 * 
 */
#define LIST_FIRST(head) \
    ((head)->first)

/**
 * @brief Renvoie le dernier élément de la liste 
 * 
 */
#define LIST_LAST(head) \
    ((head)->last)

/**
 * @brief Ajoute un élément en tête de liste
 * 
 */
#define LIST_INSERT_HEAD(head, elem) do {   \
    (elem)->next = (head)->first;           \
    \
    if ((head)->first == NULL)              \
        (head)->last = (elem);        \
    \
    (head)->first = (elem);                 \
} while (0)

/**
 * @brief Ajoute un élément en fin de liste
 * 
 */
#define LIST_INSERT_TAIL(head, elem) do {   \
    (elem)->next = NULL;                    \
    (head)->last->next = elem;              \
    (head)->last = elem;                    \
} while (0)

/**
 * @brief Retire un élement en tête de liste
 * 
 */
#define LIST_REMOVE_HEAD(head) do {         \
    (head)->first = (head)->first->next;    \
    if ((head)->first == NULL)              \
        (head)->last = NULL;                \
} while (0)

#define LIST_FOREACH(iter, head) \
    for ((iter) = (head)->first; (iter); (iter) = LIST_NEXT(iter))

/**
 * @brief Libère les entrées d'une liste
 * 
 * @param head Entête de liste
 * @param type Type des entrées de liste
 */
#define LIST_FREE(head, type) do {                          \
    type* entry = LIST_FIRST(head), *entry2;                \
    while (entry != NULL) {                                 \
        entry2 = LIST_NEXT(entry);                          \
        free(entry);                                        \
        entry = entry2;                                     \
    }                                                       \
    LIST_INIT(head);                                        \
} while (0)
