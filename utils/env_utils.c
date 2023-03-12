/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:37:22 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/12 16:42:40 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = -1;
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int		i;
	int		j;

	if (!s)
		return (0);
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = start;
	j = 0;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (s[i] && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}

char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	ft_strchr(char const *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strtrime(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed_str = ft_substrr(s1, start + 1, end - start - 2);
	if (!trimmed_str)
		return (NULL);
	return (trimmed_str);
}
