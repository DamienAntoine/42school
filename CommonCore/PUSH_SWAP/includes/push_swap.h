
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

int	ft_printchar(int c);
int	ft_atoi(const char *str);
int	checkformat(const char specifier, va_list ap);
int	ft_printf(const char *format, ...);
int	ft_printnbr(int number);
int	ft_printstr(char *s);
int	ft_printunsigned(unsigned int nb);
int	ft_printhexa(unsigned int nb, const char spec);
int     ft_printvoid(unsigned long long int ptr);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
void	ft_allocate(char **tab, char const *s, char sep);
int	ft_count_words(char const *s, char sep);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *str);
void	populate_struct(int value, t_stack **head);
void    process_args(char **args, t_stack **head);
int		is_sorted(t_stack *a_stack);
void	algo(t_stack **astack_head, t_stack **bstack_head);
int	find_mean_value(t_stack **head);
t_stack		*find_bf(t_stack **a_stack_node, t_stack **b_stack_head);
void		until_five(t_stack **astack_head, t_stack **bstack_head);
void	untilfive_helper(t_stack **astack_head, t_stack **bstack_head, int *counter);
void bf_on_top(t_stack **astack_head, t_stack **bstack_head);
int		cost_to_top(t_stack *bstack_head, int value);
int		is_closer_to_top(t_stack *bstack_head, int value);
int	ft_isdigit(int c);
int	ft_issign(char c);
int	check_inputs(int argc, char **input);
void	sort_three(t_stack **astack_head, int smallest, int biggest);
int			find_smallest(t_stack **stack_head);
int			find_biggest(t_stack **stack_head);
void		until_three(t_stack **astack_head, t_stack **bstack_head);
void	back_to_five(t_stack *astack, t_stack *bstack);
void	reduce_backtofive(t_stack *astack, t_stack *bstack);
void	sort_five(t_stack **astack_head, t_stack **bstack_head);
void    free_stack(t_stack *a_stack);
void	push(t_stack **src_head, t_stack **dest_head);
void	pa(t_stack **astack, t_stack **bstack);
void    pb(t_stack **astack, t_stack **bstack);
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
