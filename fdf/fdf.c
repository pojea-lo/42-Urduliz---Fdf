#include "fdf.h"

int main(void)
{
	int		fd;//descriptor
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	y;//numero de filas
	size_t	x;//numero de columnas
	double	xx;//valor de x del origen
	double	yy;//valor de y del origen
	char	**str;//cadena de cadenas que recoge el gnl
	char	**sch;//cadena de cadenas que recoge el split
	int		**sin;//matriz de numeros int
	double	*mm;//máximmo y minimo de altura
	double	*size;//tamaños de ventana minimos necesarios
	void	*mlx;//puntero de la mlx
	void	*mlx_win;//puntero de la ventana
	size_t	esc;//escala del dibujo

	i = 0;
	mlx = mlx_init();
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
//		printf ("La str da: %s\n", str[i]);
		sch = ft_cut (str[i]);
//		printf ("La sch da: %s\n", sch[i]);
		sin[i] = ft_put_int(sch, x);
		i++;
	}
	free (str);
	free (sch);
	mm = ft_max (sin, x, y);
	size = ft_wd_size(x, y, mm);
	printf ("%zu y %zu\n", x, y);
	mlx_win = mlx_new_window(mlx, (size[0] * 1.3) * esc, (size[1] * 1.3) * esc, "Prueba");
	xx = (size[0] * 0.1) + (y * 0.75);//centrado en x junto con el valor de margen
	yy = ft_center_y(size, mm);
//	yy = (size[1]) / 3;//centrado en y junto con el valor del margen 
	free (mm);
	i = 0;
	while (i < x)
	{
		j = 0;
		k = 0;
		xx = xx + 0.75;
		yy = yy + 0.433;
		while (j < y)
		{
			if (i == 0 && j == 0)
			mlx_pixel_put(mlx, mlx_win, (xx - (j * 0.75)) * esc, ((yy + (k * 0.433)) - sin[j][i]) * esc, 0xFF0000);
			else
			mlx_pixel_put(mlx, mlx_win, (xx - (j * 0.75)) * esc, ((yy + (k * 0.433)) - sin[j][i]) * esc, 0x00FF00);
			j++;
			k++;
		}
		i++;
	}		
	printf ("%zu y %zu\n", x, y);
	free(size);
	mlx_loop(mlx);
//	printf("El ancho - %f\n", size[0]);
//	printf("El alto - %f\n", size[1]);
//	ft_print_mat(sin, x, y);
	




	free (sin);
	close (fd);
	return (0);
}

double		ft_center_y(double *size, double *mm)//funcion que centra en y el dibujo
{
	double	yy;

	if (mm[0] == 0 && mm[1] == 0)
		yy = ((size[1] * 1.3) - size[1]) / 2;
	else if (mm[0] != 0 && mm[1] == 0)
		yy = (((size[1] * 1.3) - size[1]) / 2) + mm[0];
	else if (mm[0] == 0 && mm[1] != 0)
		yy = (((size[1] * 1.3) - size[1]) / 2);
	else
		yy = (((size[1] * 1.3) - size[1]) / 2) + mm[0];
	return (yy);
}

double		*ft_wd_size(size_t x, size_t y, double *mm)//función que saca el ancho y alto necesario de ventana minima y su centro
{
	double		*size;//recojo ancho min necesario - alto min nec - pos x de centro - pos y de centro

	size = (double *) malloc (sizeof(double) * 2);
	if (size == NULL)
		return (0);
	size[0] = round ((x + y) * cos (0.523599) * cos (0.523599));//ancho minimo de ventana necesario
	size[1] = round (((x + y) * sin (0.523599) * cos (0.523599)) + (mm[0] + (-mm[1])));//alto minimo de ventana necesario
	return (size);
}

double		*ft_max(int **sin, size_t x, size_t y)//función que extrae la máx y la mín altura
{
	size_t	i;
	size_t	j;
	double	*mm;

	i = 0;
	mm = (double *) malloc (sizeof(double) * 2);
	if (mm == NULL)
		return (0);
	mm[0] = 0;
	mm[1] = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (sin[i][j] > mm[0])//guardo el máximo
				mm[0] = sin[i][j];
			if (sin[i][j] < mm[1])//guardo el minimo
				mm[1] = sin[i][j];
			j++;
		}
		i++;
	}
	return (mm);
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
