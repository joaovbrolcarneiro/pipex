/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:37 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/20 18:52:38 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*strdup_until(const char *start, const char *end)
{
	size_t	len;
	char	*str;
	size_t	i;

	len = end - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = start[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

static void	free_split_result(char **result, size_t i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

static char	**process_splits(char const *s, char c, size_t words)
{
	char		**result;
	size_t		i;
	const char	*start;

	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			result[i] = strdup_until(start, s);
			if (!result[i])
			{
				free_split_result(result, i);
				return (NULL);
			}
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	return (process_splits(s, c, words));
}
