/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:45 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/20 17:34:48 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ft_strncmp: Compares up to n characters of two strings.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// ft_strlen: Returns the length of the string (excluding the null terminator).
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

// ft_strncpy: Copies up to n characters from src to dest.
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

// ft_memcpy: Copies n bytes from memory area src to memory area dest.
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*d;

	d = dest;
	while (*src)
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';
	return (dest);
}
