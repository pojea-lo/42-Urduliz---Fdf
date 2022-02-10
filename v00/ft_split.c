/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:31:01 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/02/08 14:22:47 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_split(char *s, char c)
{
	char	**r;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	if (s == NULL)
		return (NULL);
	r = ft_malloc (s, c);
	while (s[i] != '\0' && r != NULL)
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != c && i < (int)ft_strlen(s))
				i++;
			r[l++] = ft_copy(s, i, j);
		}
		else
			i++;
	}
	if (r != NULL)
		r[l] = NULL;
	return (r);
}

char	*ft_copy(char *s, int i, int j)
{
	char	*r;
	int		m;

	m = 0;
	r = (char *)malloc (sizeof(char) * (((i - 1) - j) + 2));
	if (r == NULL)
		return (NULL);
	while (j <= (i - 1))
		r[m++] = (char)s[j++];
	r[m] = '\0';
	return (r);
}

char	**ft_malloc(char *s, char c)
{
	char	**r;

	r = (char **)malloc (sizeof(char *) * (ft_count_columns(s, c) + 1));
	if (r == NULL)
		r = NULL;
	return (r);
}
