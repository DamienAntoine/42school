/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:36:30 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/20 16:51:17 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

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

#endif
