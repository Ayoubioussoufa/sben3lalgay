/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:01:56 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/11 16:05:25 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	freedouble(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

t_redire	*new_redir(t_content *content, int type)
{
	t_redire	*new;

	new = malloc(sizeof(t_redire));
	if (!new)
		return (0);
	if (type == INFILE)
	{
		new->type = INFILE;
		new->infile = content->content;
	}
	if (type == OUTFILE || type == APPEND)
	{
		if (type == OUTFILE)
			new->type = OUTFILE;
		else
			new->type = APPEND;
		new->outfile = content->content;
	}
	if (type == DELIMITER)
	{
		new->type = DELIMITER;
		new->quotes = content->quotes;
		new->delimiter = content->content;
	}
	new->next = 0;
	free(content);
	return (new);
}

t_shell	*ft_lstlast(t_shell *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	check(char const *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrimfree(char *s1, char *set)
{
	int		i;
	int		len;
	char	*mem;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i] && check(set, s1[i]))
		i++;
	while (s1[len] && check(set, s1[len]))
		len--;
	mem = ft_substr(s1, i, len - i + 1);
	free(s1);
	return (mem);
}
