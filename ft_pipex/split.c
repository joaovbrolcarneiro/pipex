/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:37 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/21 17:38:18 by jbrol-ca         ###   ########.fr       */
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

static void	free_split_result(char **result, size_t i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

static int	process_word(const char **s, char c, char **result, size_t *i)
{
	const char	*start;

	while (**s == c)
		(*s)++;
	if (**s)
	{
		start = *s;
		while (**s && **s != c)
			(*s)++;
		result[*i] = strdup_until(start, *s);
		if (!result[*i])
			return (0);
		(*i)++;
	}
	return (1);
}

static char	**process_splits(char const *s, char c, size_t words)
{
	char		**result;
	size_t		i;

	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (!process_word(&s, c, result, &i))
		{
			free_split_result(result, i);
			return (NULL);
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
