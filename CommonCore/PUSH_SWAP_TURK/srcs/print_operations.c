#include "../includes/push_swap.h"

void    store_op(int move)
{
    static t_moves *head = NULL;
    static t_moves *current = NULL;

    t_moves *new_node = malloc(sizeof(t_moves));
    new_node->move = move;
    new_node->next = NULL;
    if (move == 0)
    {
        print_op(head);
        return;
    }
    if (head == NULL)
    {
        head = new_node;
        current = head;
    }
    else
    {
        current->next = new_node;
        current = new_node;
    }
}

void print_op(t_moves *head)
{
    t_moves *current = head;
    while (current != NULL)
    {
        if (current->next != NULL && ((current->move == 1 && current->next->move == 2) || (current->move == 2 && current->next->move == 1)))
        {
            printf("rr\n");
            current = current->next;
        }
        else if (current->move == 1)
            printf("ra\n");
        else if (current->move == 2)
            printf("rb\n");
        else if (current->move == 3)
            printf("rr\n");
        else if (current->move == 4)
            printf("sa\n");
        else if (current->move == 5)
            printf("sb\n");
        else if (current->move == 6)
            printf("ss\n");
        else if (current->move == 7)
            printf("rra\n");
        else if (current->move == 8)
            printf("rrb\n");
        else if (current->move == 9)
            printf("rrr\n");
        else if (current->move == 10)
            printf("pa\n");
        else if (current->move == 11)
            printf("pb\n");
        t_moves *to_free = current;
        current = current->next;
        free(to_free);
    }
}
//stock all operations in a list, print all after sorting
