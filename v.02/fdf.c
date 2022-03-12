#include "fdf.h"

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
	ft_calculs (&str, &num);
}

void	ft_calculs(t_str *str, t_num *num)
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
	ft_draw_start(str, num);
}

void	ft_draw_start(t_str *str, t_num *num)
{
	t_mlx	gr;
	t_conv	hook;

	hook.gr = &gr;
	hook.num = num;
	hook.str = str;
	gr.mlx = mlx_init();
	ft_draw(&hook);
}

void	ft_draw(t_conv *hook)
{
	if (hook->num->hk == 's')
		hook->num->esc_hk = hook->num->esc;
	hook->gr->mlx_win = mlx_new_window(hook->gr->mlx, (hook->str->size[0] * 1.3) \
	* hook->num->esc_hk, (hook->str->size[1] * 1.3) * hook->num->esc_hk, "Prueba");//abrimos ventana
		
	hook->gr->img = mlx_new_image(hook->gr->mlx, (hook->str->size[0] * 1.3) \
	* hook->num->esc, (hook->str->size[1] * 1.3) * hook->num->esc);//generamos imagen del mismo tamaño que la ventana

//	ft_print_pixel(hook->gr, hook->num, hook->str);
	ft_line_ppx(hook->gr, hook->num, hook->str);
	ft_line_ppy(hook->gr, hook->num, hook->str);
//	ft_free(hook, hook->num->y);a veces falla el free del final
	mlx_key_hook(hook->gr->mlx_win, close_key, hook);
	mlx_hook(hook->gr->mlx_win, 17, 0, close_button, hook);
	mlx_hook(hook->gr->mlx_win, 2, 1L<<0, chg_center, hook);
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
}
