/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:37:10 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/12 17:41:30 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_putstr(char *s)
{
	int	i;
	int	len;

	i = 0;
	if (!s)
		return ;
	len = ft_strlen(s);
	while (i < len)
		write(1, &s[i++], 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnstr(char *str, int n)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[++i] && i < (int)ft_strlen(str) + n)
			ft_putchar(str[i]);
	}
	else
	{
		while (str[++i] && i < n)
			ft_putchar(str[i]);
	}
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
