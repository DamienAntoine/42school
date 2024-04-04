static void	push(t_stack **src, t_stack **dest)
{

}

void	pa(t_stack **astack, t_stack **bstack)
{
	push(bstack, astack);
	ft_putstr("pa\n");
}

void    pb(t_stack **astack, t_stack **bstack)
{
        push(astack, bstack);
        ft_putstr("pb\n");                                                                                                                                                 }
