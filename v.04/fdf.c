#include "fdf.h"

static t_conv	*init(t_str *str, t_num *num);

int	main(int argc, char* argv[])
{
	int		fd;//descriptor

	fd = open (argv[1], O_RDWR);
	if (fd == -1 || argc != 2)
	{
		write (1, "ERROR", 5);
		return (0);
	}
	ft_traspas(fd, argv[1]);
	close (fd);
	return (0);
}

void	ft_traspas(int fd, char *map)
{
	t_num	num;
	t_str	str;
	t_conv	*hook;

	hook = NULL;	
	num.i = 0;
	num.y = ft_count_rows(fd);//cuento las filas del mapa
	str.st = ft_read(fd, num.y, map);//primera lectura metiendo en cadenas cada linea
	str.sin = (int **) malloc (sizeof(int *) * (num.y));
	if (str.sin == NULL)
		exit (0);
	while (num.i < num.y)
	{
		num.x = ft_count_columns (str.st[num.i], ' ');//cuento las columnas de cada fila
		str.sch = ft_split (str.st[num.i], ' ');//le hago el split a cada una de las filas
		str.sin[num.i] = ft_put_int(str.sch, num.x);//convierto las cadenas anteriores a int
		free (str.sch);
		num.i++;
	}
	close(fd);
	free (str.st);
	num.hk = 's';//inicio hk para los hooks de despues
	ft_calculs (&str, &num, hook);
	hook = init (&str, &num);
	ft_draw (hook);
}

void	ft_calculs(t_str *str, t_num *num, t_conv *hook)
{
	str->mm = ft_max (str->sin, num->x, num->y);//busco los maximos y minimos de altura
	str->size = ft_wd_size(num->x, num->y, str->mm);//saco la ventana mínima necesaria
	if (num->hk == 's')//condicion para que no entre con hooks
		num->esc = ft_wde_size(str->size);//calcula una escala proporcional al tamaño mínimmo necesario
	if (num->hk == 's')//condicion para cambiar el origen
	{
		num->xx = (str->size[0] * 0.1) + (num->y * 0.75);//centrado en x junto con el valor de margen
		num->yy = ft_center_y(str->size, str->mm);//busco el centro en y
	}
	if (hook != NULL)
		ft_draw(hook);
}

static t_conv	*init(t_str *str, t_num *num)
{
	t_conv	*hook;
	t_mlx	*gr;

	hook = NULL;
	gr = NULL;
	hook = (t_conv *)malloc(sizeof(t_conv));
	gr = (t_mlx *)malloc(sizeof(t_mlx));
	hook->gr = gr;
	hook->num = num;
	hook->str = str;
	gr->mlx = mlx_init();
	gr->esc = (int) num->esc;
	gr->size_x = (int) str->size[0];
	gr->size_y = (int) str->size[1];
	return (hook);
}
	
void	ft_draw(t_conv *hook)
{
	if (hook->num->hk == 's')
	{
		hook->num->esc_hk = hook->num->esc;
		hook->gr->mlx_win = mlx_new_window(hook->gr->mlx, (hook->str->size[0]) * hook->num->esc_hk, (hook->str->size[1]) * hook->num->esc_hk, "Prueba");//abrimos ventana
	}
	if (hook->num->hk != 's')	
	{
		mlx_destroy_image(hook->gr->mlx, hook->gr->img);
	}
	
	hook->gr->img = mlx_new_image(hook->gr->mlx, (hook->str->size[0]) * hook->num->esc_hk, (hook->str->size[1]) * hook->num->esc_hk);//generamos imagen del mismo tamaño que la ventana

	hook->gr->addr = mlx_get_data_addr(hook->gr->img, &hook->gr->bits_per_pixel, &hook->gr->line_length, &hook->gr->endian);

//	ft_print_pixel(hook->gr, hook->num, hook->str);
	if (hook->num->hk == 'i' || hook->num->hk == 's')
	{
		ft_line_ppx(hook->gr, hook->num, hook->str);
		ft_line_ppy(hook->gr, hook->num, hook->str);
	}
	if (hook->num->hk == 'c' )
	{
		ft_line_ppx_c(hook->gr, hook->num, hook->str);
		ft_line_ppy_c(hook->gr, hook->num, hook->str);
	}
	mlx_hook(hook->gr->mlx_win, 17, 0, close_button, hook);
	mlx_hook(hook->gr->mlx_win, 2, 1L<<0, keyw, hook);
	mlx_hook(hook->gr->mlx_win, 4, 1L<<2, chg_center_m, hook);
	mlx_loop(hook->gr->mlx);
}

void	ft_free(t_conv *hook, int	y)
{
	int i;

	i = 0;
	while (i < y)
	{
		free (hook->str->sin[i]);
		i++;
	}
	free (hook->str->sin);
	free (hook->str->mm);
	free (hook->str->size);
	free (hook->gr);
	free (hook);
}
