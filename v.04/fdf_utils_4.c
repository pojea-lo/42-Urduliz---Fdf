#include "fdf.h"

//función que imprime puntos
void	ft_print_pixel(t_mlx *gr, t_num *num, t_str *str)
{
	t_num	c;

//	ft_print_mat(str->sin, num->x, num->y);
	c.i = -1;
	c.xxx = num->xx;
	c.yyy = num->yy;
	while (++c.i < num->x)
	{
		c.j = -1;
		c.k = 0;
		if (c.i != 0)
		{
			c.xxx = c.xxx + 0.75;
			c.yyy = c.yyy + 0.433;
		}
		while (++c.j < num->y)
		{
			mlx_pixel_put(gr->mlx, gr->mlx_win, (c.xxx - (c.j * 0.75)) \
			* num->esc, ((c.yyy + (c.k * 0.433)) - str->sin[c.j][c.i]) \
			* num->esc, 0xFFFFFF);
			c.k++;
		}
	}
}

//función que calcula las parejas de puntos en el eje x
void	ft_line_ppx_c(t_mlx *gr, t_num *num, t_str *str)
{
	t_num	l;

	l.i = -1;
	l.xxx = num->xx;
	l.yyy = num->yy;
	while (++l.i < num->x)
	{
		l.j = -1;
		l.k = 0;
		if (l.i != 0)
		{
			l.xxx = l.xxx + 0.75;
			l.yyy = l.yyy;
		}
		while (++l.j < (num->y) - 1)
		{
			l.x1 = (l.xxx - (l.j * 0.75)) * num->esc;
			l.x2 = (l.xxx - ((l.j + 1) * 0.75)) * num->esc;
			l.y1 = ((l.yyy + (l.k * 0.433)) - str->sin[l.j][l.i]) * num->esc;
			l.y2 = ((l.yyy + ((l.k + 1) * 0.433)) - str->sin[l.j + 1][l.i]) \
			* num->esc;
			ft_print_line_1 (gr, &l);
			l.k++;
		}
	}
	mlx_put_image_to_window(gr->mlx, gr->mlx_win, gr->img, 0, 0);//vuelca la imagen a la ventana
}

//función que calcula las parejas de puntos en el eje y
void	ft_line_ppy_c(t_mlx *gr, t_num *num, t_str *str)
{
	t_num	l;

	l.i = -1;
	l.xxx = num->xx;
	l.yyy = num->yy;
	while (++l.i < num->y)
	{
		l.j = -1;
		l.k = 0;
		if (l.i != 0)
		{
			l.xxx = l.xxx - 0.75;
			l.yyy = l.yyy + 0.433;
		}
		while (++l.j < (num->x) - 1)
		{
			l.x1 = (l.xxx + (l.j * 0.75)) * num->esc;
			l.x2 = (l.xxx + ((l.j + 1) * 0.75)) * num->esc;
			l.y1 = (l.yyy + - str->sin[l.i][l.j]) * num->esc;
			l.y2 = (l.yyy - str->sin[l.i][l.j + 1])	* num->esc;
			ft_print_line_1 (gr, &l);
			l.k++;
		}
	}
	mlx_put_image_to_window(gr->mlx, gr->mlx_win, gr->img, 0, 0);//vuelca la imagen a la ventana
}
