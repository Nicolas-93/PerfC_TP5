/**
 * @brief Implémetation d'une queue, dans l'esprit
 * de STAILQ.
 * L'utilité principale est d'éviter la redondance
 * de fonctions similaires, pour des types différents
 */


#define LIST_INIT(head) do {    \
    (head)->first = NULL;       \
    (head)->last = NULL;        \
} while (0)

#define LIST_EMPTY(head) \
    ((head)->first == NULL)

#define LIST_NEXT(elem) \
    ((elem)->next)

#define LIST_FIRST(head) \
    ((head)->first)

#define LIST_LAST(head) \
    ((head)->last)

#define LIST_INSERT_HEAD(head, elem) do {   \
    (elem)->next = (head)->first;           \
    \
    if ((head)->first == NULL)              \
        (head)->last = NULL;                \
    \
    (head)->first = (elem);                 \
} while (0)

#define LIST_INSERT_TAIL(head, elem) do {   \
    (elem)->next = NULL;                    \
    (head)->last->next = elem;              \
    (head)->last = elem;                    \
} while (0)

#define LIST_REMOVE_HEAD(head) do {         \
    (head)->first = (head)->first->next;    \
    if ((head)->first == NULL)              \
        (head)->last = NULL;                \
} while (0)

#define LIST_FOREACH(iter, head) \
    for ((iter) = (head)->first; (iter); iter = LIST_NEXT(iter))
