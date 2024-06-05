/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:55:20 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 14:55:44 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}					t_stack;

typedef struct s_bf
{
	t_stack			*a_node;
	t_stack			*b_node;
	int				cost;
	struct s_bf		*next;
}					t_bf;

typedef struct s_moves
{
	int				move;
	struct s_moves	*next;
}					t_moves;

int		main(int argc, char **argv);
int		ft_printchar(int c);
int		ft_atoi(const char *str);
int		checkformat(const char specifier, va_list ap);
int		ft_printf(const char *format, ...);
int		ft_printnbr(int number);
int		ft_printstr(char *s);
int		ft_printunsigned(unsigned int nb);
int		ft_printhexa(unsigned int nb, const char spec);
int		ft_printvoid(unsigned long long int ptr);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
void	ft_allocate(char **tab, char const *s, char sep);
int		ft_isdigit(int c);
int		ft_issign(char c);
int		check_inputs(int argc, char **input);
int		check_int_limits(char **input);
int		check_stack(t_stack **stack_head);
int		ft_count_words(char const *s, char sep);
void	populate_struct(int value, t_stack **astack_head);
void	process_args(char **args, t_stack **astack_head);
void	free_args(char **args);
int		is_sorted(t_stack *a_stack);

void	store_op(int move);
void	print_op(t_moves *head);
void	print_other_op(t_moves *head);
void	algo(t_stack **astack_head, t_stack **bstack_head);
int		find_mean_value(t_stack **head);
void	free_moves(t_moves **moves);

void	until_three(t_stack **astack_head, t_stack **bstack_head);
void	sort_three(t_stack **astack_head, int smallest, int biggest);
void	sort_four(t_stack **astack_head, t_stack **bstack_head);
void	until_five(t_stack **astack_head, t_stack **bstack_head);
void	untilfive_helper(t_stack **astack_head);
void	insert_sorted(t_stack **astack, t_stack **bstack);
int		find_smallest(t_stack **stack_head);
int		find_biggest(t_stack **stack_head);

t_bf	*find_optimal_nodes(t_stack *astack_head, t_stack *bstack_head);
t_bf	*find_smaller_cost(t_bf *optimal, t_stack *astack, t_stack *bstack);
t_bf	*find_pairs(t_stack *astack_head, t_stack *bstack_head);
void	free_pairs(t_bf *pairs);
void	append_pair(t_bf **head, t_bf **tail, t_stack *astack, t_stack *bstack);
t_stack	*find_min_a_node(t_stack *astack, int b_value);

int		argcounter(t_stack *astack_head);
int		stack_length(t_stack **astack_head);

void	put_on_top_both(t_stack **a, t_stack **b, int av, int bv);
void	put_on_top(t_stack **astack_head, int value);
void	put_on_top_bstack(t_stack **bstack_head, int value);
int		cost_to_top(t_stack *bstack_head, int value);
int		is_closer_to_top(t_stack *bstack_head, int value);
void	rotate_stacks(t_stack **a, t_stack **b, int av, int bv);

void	sort_stacks(t_stack **astack_head, t_stack **bstack_head);
void	free_stack(t_stack *a_stack);

void	push(t_stack **src_head, t_stack **dest_head);
void	pa(t_stack **astack, t_stack **bstack);
void	pb(t_stack **astack, t_stack **bstack);
void	reverse_rotate(t_stack **head);
void	rra(t_stack **astack);
void	rrb(t_stack **bstack);
void	rrr(t_stack **astack, t_stack **bstack);
void	rotate(t_stack **head);
void	ra(t_stack **astack);
void	rb(t_stack **bstack);
void	rr(t_stack **astack, t_stack **bstack);
void	swap(t_stack **head);
void	sa(t_stack **astack);
void	sb(t_stack **bstack);
void	ss(t_stack **astack, t_stack **bstack);

#endif
