#include "fdf.h"

static void	ft_draw(t_str *str, t_num *num);
static void	ft_free_1(t_str *str);
static void	ft_free_2(t_str *str);

int		main(int argc, char* argv[])
{
	int		fd;//descriptor

	fd = open (argv[1], O_RDWR);
	if (fd == -1 || argc != 2)
	{
		write (1, "ERROR", 5);
		return (0);
	}
	ft_calculs(fd, &argv[1]);
	close (fd);
	return (0);
}

static void	ft_draw(t_str *str, t_num *num)
{
	t_mlx	gr;
	
	gr.mlx = mlx_init();
	gr.mlx_win = mlx_new_window(gr.mlx, (str->size[0] * 1.3) * num->esc, (str->size[1] * 1.3) * num->esc, "Prueba");//abrimos ventana
	gr.img = mlx_new_image(gr.mlx, (str->size[0] * 1.3) * num->esc, (str->size[1] * 1.3) * num->esc);//generamos imagen del mismo tamaño que la ventana
//	ft_print_pixel(&gr, &num, &str);
	ft_line_ppx(&gr, num, str);
	ft_line_ppy(&gr, num, str);
	mlx_hook(gr.mlx_win, 2, 0, close_key, &gr);
	mlx_hook(gr.mlx_win, 17, 0, close_button, &gr);
	mlx_loop(gr.mlx);
}

int	ft_calculs(int fd, char **argv)
{
	t_num	num;
	t_str	str;
	
	num.i = 0;
	num.y = ft_count_rows(fd);//cuento las filas del mapa
	printf ("%zu", num.y);
	str.st = ft_read(fd, num.y, argv[1]);//primera lectura metiendo en cadenas cada linea
	str.sin = (int **) malloc (sizeof(int *) * (num.y));
	if (str.sin == NULL)
		return (0);
	while (num.i < num.y)
	{
		num.x = ft_count_columns (str.st[num.i], ' ');//cuento las columnas de cada fila
		str.sch = ft_cut (str.st[num.i]);//divido las filas dejandolas en un array de arrays
		str.sin[num.i] = ft_put_int(str.sch, num.x);//convierto las cadenas anteriores a int
		num.i++;
	}
	ft_free_1 (&str);
	str.mm = ft_max (str.sin, num.x, num.y);//busco los maximos y minimos de altura
	str.size = ft_wd_size(num.x, num.y, str.mm);//saco la ventana mínima necesaria
	num.esc = ft_wde_size(str.size);//calcula una escala proporcional al tamaño mínimmo necesario
	num.xx = (str.size[0] * 0.1) + (num.y * 0.75);//centrado en x junto con el valor de margen
	num.yy = ft_center_y(str.size, str.mm);//busco el centro en y
	ft_draw(&str, &num);
	ft_free_2 (&str);
	return (0);
}

static void	ft_free_1(t_str *str)
{
	free (str->st);
	free (str->sch);
}

static void	ft_free_2(t_str *str)
{
	free (str->mm);
	free(str->size);
	free (str->sin);
}

