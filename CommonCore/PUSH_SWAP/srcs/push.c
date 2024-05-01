static void	push(t_stack **src, t_stack **dest)
{

}

//pa (push a): Take the first element at the top of b and put it at the top of a. Do nothing if b is empty
void	pa(t_stack **astack, t_stack **bstack)
{
	push(bstack, astack);
	ft_putstr("pa\n");
}
//pb (push b): Take the first element at the top of a and put it at the top of b. Do nothing if a is empty
void    pb(t_stack **astack, t_stack **bstack)
{
        push(astack, bstack);
        ft_putstr("pb\n");                                                                                                                                                 }
