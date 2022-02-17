/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:23:11 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/02/17 07:41:47 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_read(int fd, size_t y, char *st)//función para pasar toda la información del archivo poniendo cada fila en una cadena
{
	char	**str;
	size_t	i;

	fd = open (st, O_RDWR);
	i = 0;
	str = (char **) malloc (sizeof(char *) * (y + 1));
	if (str == NULL)
		return (NULL);
	str[i] = get_next_line(fd);
	while (str[i] != NULL)
	{
		i++;
		str[i] = get_next_line(fd);
	}
	close (fd);
	return (str);
}

size_t	ft_count_rows(int fd)//función que cuenta las filas que haya para dimensionar la cadena de cadenas
{
	size_t	y;
	char	*s;

	s = NULL;
	y = 0;
	while ((s = get_next_line(fd)) != NULL)
	{
		y++;
		free (s);
	}
	return (y);
}

char	**ft_cut(char *s)//funcion que divide cada fila en columnas guardandolo en un array de arrys
{
	char	**sch;
	size_t	i;

	i = 0;
	sch = ft_split(s, ' ');
	return (sch);
}

int	*ft_put_int(char **sch, size_t x)//función que transforma la matriz de chars en matriz de int
{
	int		*sin;
	size_t	i;

	i = 0;
	sin = (int *) malloc (sizeof (int) * x);
	if (sin == NULL)
		return (0);
	while (i < x)
	{
		sin[i] = ft_atoi(sch[i]);
		i++;
	}
	return (sin);
}

void	ft_print_mat(int **sin, size_t x, size_t y)//función que imprime la matriz de numeros como int
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%d ", sin[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
