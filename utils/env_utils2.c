/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:40:07 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/12 16:40:48 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_strndup(char *s1, int n)
{
	char	*copy;
	size_t	s1_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	copy = malloc(sizeof(char) * (s1_len + 1));
	if (!copy)
		return (NULL);
	while (s1[i] && i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*search_env_var(char *key, char **env)
{
	int		i;
	int		pos;
	char	*var;

	i = 0;
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(status));
	while (env[i] && ft_strncmp(env[i], key, ft_strlen(key)))
		i++;
	if (!env[i])
		return (NULL);
	pos = ft_strchr(env[i], '=');
	if (pos == -1)
		return (NULL);
	var = ft_substr(env[i], pos + 1, ft_strlen(env[i]) - (pos + 1));
	return (var);
}

char	*get_expanded_value(char **line, char **env)
{
	int		key_len;
	char	key[100];

	key_len = 0;
	(*line)++;
	if (**line == '?')
		key[key_len++] = *((*line)++);
	else
	{
		while (**line && ft_isalnum(**line))
			key[key_len++] = *((*line)++);
	}
	key[key_len] = '\0';
	return (search_env_var(key, env));
}

char	*expand_env(char *line, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	res[300];

	i = -1;
	value = NULL;
	while (line[++i] && line[i] != '$')
		res[i] = line[i];
	if (line[i] == '$')
	{
		line = line + i;
		value = get_expanded_value(&line, env);
		if (value)
		{
			j = 0;
			while (value[j])
				res[i++] = value[j++];
		}
	}
	while (*line)
		res[i++] = *(line++);
	res[i] = '\0';
	return (ft_strdup(res));
}
