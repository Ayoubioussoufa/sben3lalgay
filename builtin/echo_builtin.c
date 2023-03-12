/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:12:51 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/12 18:12:51 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	echo(char **str, int pos)
{
	int		start;
	int		end;
	int		strl;

	start = is_quote(str[pos][0]);
	strl = ft_strlen(str[pos]);
	end = is_quote(str[pos][strl - 1]);
	if (end && start)
		ft_putnstr(str[pos] + 1, -1);
	else
		ft_putstr(str[pos]);
}

int	checkings(char **cmd)
{
	int	i;
	int	f;

	f = 0;
	i = 1;
	while (cmd[1][i] == 'n')
		i++;
	if (cmd[1][i] && cmd[1][i] != 'n')
		f = 0;
	else
		f = 1;
	return (f);
}

void	writing(char **cmd, int j, int f)
{
	while (cmd[++j])
	{
		if (cmd[j])
			echo(cmd, j);
		if (!cmd[j + 1] && f)
			ft_putchar('\0');
		else if (!cmd[j + 1] && !f)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

int	echo_builtin(char **cmd)
{
	int	j;
	int	f;
	int	i;

	j = 0;
	i = 1;
	f = 0;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == 'n')
		f = checkings(cmd);
	if (f)
		j++;
	writing(cmd, j, f);
	status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
