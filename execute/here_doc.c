/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:29:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/12 17:14:07 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	here_doc(t_redire *redir, char **env)
{
	int		fd;
	char	*str;

	signal(SIGINT, sigint_handler);
	fd = open("/tmp/minishell", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("minishell");
		return ;
	}
	str = readline("> ");
	while (str
		&& ft_strncmp(str, redir->delimiter, ft_strlen(redir->delimiter)))
	{
		if (!redir->quotes)
			str = expand_env(str, env);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
}

void	opening(t_shell *shell, t_env *env)
{
	t_redire	*x;
	t_shell		*here;

	here = shell;
	while (here)
	{
		x = here->redir;
		while (x)
		{
			if (x->type == DELIMITER)
				here_doc(x, env->env);
			x = x->next;
		}
		here = here->next;
	}
}

void	open_heredocs(t_shell *shell, t_env *env)
{
	t_redire	*tmp;
	int			i;

	i = 0;
	tmp = shell->redir;
	while (tmp)
	{
		if (tmp->type == DELIMITER)
			i++;
		tmp = tmp->next;
	}
	if (i > 16)
		error("maximum here-document count exceeded", 2);
	opening(shell, env);
}
