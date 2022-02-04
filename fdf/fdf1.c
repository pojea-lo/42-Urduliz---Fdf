#include "fdf.h"

int main(void)
{
	int		fd;//descriptor
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	y;//numero de filas
	size_t	x;//numero de columnas
	char	**str;//cadena de cadenas que recoge el gnl
	char	**sch;//cadena de cadenas que recoge el split
	int		**sin;//matriz de numeros int
	size_t	esc;//escala del dibujo

	i = 0;
	esc = 10;//marco la escala del dibujo
//	fd = open ("maps/42.fdf", O_RDWR);
	fd = open ("maps/pyramide.fdf", O_RDWR);
//	fd = open ("maps/mars.fdf", O_RDWR);
//	fd = open ("maps/julia.fdf", O_RDWR);
//	fd = open ("maps/3.fdf", O_RDWR);
	if (fd == -1)
	{
		write (1, "ERROR", 5);
		return (0);
	}
	y = ft_count_rows(fd);
	str = ft_read(fd, y);
	sin = (int **) malloc (sizeof(int *) * (y));
	if (sin == NULL)
		return (0);
	while (i < y)
	{
		x = ft_count_columns (str[i], ' ');//cuento las columnas de cada fila
		printf ("La str da: %s\n", str[i]);
		sch = ft_cut (str[i]);
//		printf ("La sch da: %s\n", sch[i]);
		sin[i] = ft_put_int(sch, x);
		i++;
	}
	free (str);
	free (sch);
//	ft_print_mat(sin, x, y);
		




	free (sin);
	close (fd);
	return (0);
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

int		*ft_put_int(char **sch, size_t x)//función que transforma la matriz de chars en matriz de int
{
	int		*sin;
	size_t	i;

	i = 0;
	sin = (int	*) malloc (sizeof(int) * x);
	if (sin == NULL)
		return (0);
	while (i < x)
	{
		sin[i] = ft_atoi(sch[i]);
		i++;
	}
	return (sin);
}


char	**ft_cut(char *s)//funcion que divide cada fila en columnas guardandolo en un array de arrys
{
	char	**sch;
	size_t	i;

	i = 0;
	sch = ft_split(s, ' ');
	return (sch);
}

char	**ft_read(int fd, size_t y)//función para pasar toda la información del archivo poniendo cada fila en una cadena
{
	char	**str;
	size_t	i;

//	fd = open ("maps/42.fdf", O_RDWR);
	fd = open ("maps/pyramide.fdf", O_RDWR);
//	fd = open ("maps/mars.fdf", O_RDWR);
//	fd = open ("maps/julia.fdf", O_RDWR);
//	fd = open ("maps/3.fdf", O_RDWR);
	i = 0;
	str = (char **) malloc (sizeof(char *) * (y + 1));
	if (str == NULL)
		return (NULL);
	str[i] = get_next_line(fd);
//	printf ("Para i = %zu\n", i);
//	printf ("%s", str[i]);
	while (str[i] != NULL)
	{
		i++;
		str[i] = get_next_line(fd);
//		printf ("Para i = %zu\n", i);
//		printf ("%s", str[i]);
	}
	close (fd);
	return (str);
}

size_t	ft_count_rows(int fd)//función que cuenta las filas que haya para dimensionar la cadena de cadenas
{
	size_t	y;

	y = 0;
	while (get_next_line(fd) != NULL)
		y++;
	return (y);
}
