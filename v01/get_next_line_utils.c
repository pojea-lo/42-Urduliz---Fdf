/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:39:11 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/02/07 18:39:13 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_join(char *s1, char *s2)
{
	int		i;
	char	*des;
	int		ls1;
	int		ls2;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (!s1)
	{
		s1 = (char *)malloc (sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	des = (char *) malloc (sizeof (char) * (ls1 + ls2 + 1));
	if (!des)
		return (NULL);
	ft_memcpy(des, s1, ls1);
	i = -1;
	while (i++ < ls2)
		des[ls1 + i] = s2[i];
	des[ls1 + ls2] = '\0';
	free(s1);
	return (des);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*des;
	int		i;

	if (!s)
		return (NULL);
	des = (char *) malloc (sizeof(char) * (len + 1));
	if (des == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{	
		des[i] = s[start + i];
		i++;
	}
	des[i] = '\0';
	return (des);
}

int	ft_strlen(char *str)
{
	long unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(char *s, char c)

{
	if (!s)
		return (0);
	while (*s != c && *s != '\0')
		s++;
	if (*s == c)
		return (1);
	return (0);
}

void	*ft_memcpy(void *dest, const void *org, size_t n)
{
	size_t	i;
	char	*cdest;
	char	*corg;
	void	*ccdest;

	cdest = (char *)dest;
	corg = (char *)org;
	if (dest == org || !n)
		return (dest);
	i = 0;
	while (i < n)
	{
		cdest[i] = corg[i];
		i++;
	}
	ccdest = (void *)cdest;
	return (ccdest);
}
