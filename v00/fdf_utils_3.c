#include "fdf.h"

void	ft_print_pixel(t_mlx *gr, t_num *num, t_str *str)
//función que imprime puntos
{
	t_num	c;

	c.i = 0;
	c.xxx = num->xx;
	c.yyy = num->yy;
	while (c.i < num->x)
	{
		c.j = 0;
		c.k = 0;
		if (c.i != 0)
		{
			c.xxx = c.xxx + 0.75;
			c.yyy = c.yyy + 0.433;
		}
		while (c.j < num->y)
		{
			if (c.i == 0 && c.j == 0)
			mlx_pixel_put(gr->mlx, gr->mlx_win, (c.xxx - (c.j * 0.75)) * num->esc, ((c.yyy + (c.k * 0.433)) - str->sin[c.j][c.i]) * num->esc, 0xFF0000);
			else
			mlx_pixel_put(gr->mlx, gr->mlx_win, (c.xxx - (c.j * 0.75)) * num->esc, ((c.yyy + (c.k * 0.433)) - str->sin[c.j][c.i]) * num->esc, 0x00FF00);
			c.j++;
			c.k++;
		}
		c.i++;
	}
}

void	ft_line_ppx(t_mlx *gr, t_num *num, t_str *str)
{
	t_num	l;

	l.i = 0;
	l.xxx = num->xx;
	l.yyy = num->yy;
	while (l.i < num->x)
	{
		l.j = 0;
		l.k = 0;
		if (l.i != 0)
		{
			l.xxx = l.xxx + 0.75;
			l.yyy = l.yyy + 0.433;
		}
		while (l.j < (num->y) - 1)
		{
			l.x1 = (l.xxx - (l.j * 0.75)) * num->esc;
			l.x2 = (l.xxx - ((l.j + 1) * 0.75)) * num->esc;
			l.y1 = ((l.yyy + (l.k * 0.433)) - str->sin[l.j][l.i]) * num->esc;
			l.y2 = ((l.yyy + ((l.k + 1) * 0.433)) - str->sin[l.j + 1][l.i]) * num->esc;
			ft_print_line_1 (gr, l.x1, l.y1, l.x2, l.y2);
			l.j++;
			l.k++;
		}
		l.i++;
	}
}

void	ft_line_ppy(t_mlx *gr, t_num *num, t_str *str)
{
	t_num	l;

	l.i = 0;
	l.xxx = num->xx;
	l.yyy = num->yy;
	while (l.i < num->y)
	{
		l.j = 0;
		l.k = 0;
		if (l.i != 0)
		{
			l.xxx = l.xxx - 0.75;
			l.yyy = l.yyy + 0.433;
		}
		while (l.j < (num->x) - 1)
		{
			l.x1 = (l.xxx + (l.j * 0.75)) * num->esc;
			l.x2 = (l.xxx + ((l.j + 1) * 0.75)) * num->esc;
			l.y1 = ((l.yyy + (l.k * 0.433)) - str->sin[l.i][l.j]) * num->esc;
			l.y2 = ((l.yyy + ((l.k + 1) * 0.433)) - str->sin[l.i][l.j + 1]) * num->esc;
			ft_print_line_1 (gr, l.x1, l.y1, l.x2, l.y2);
			l.j++;
			l.k++;
		}
		l.i++;
	}
}

void	ft_print_line_1(t_mlx *gr, int x1, int y1, int x2, int y2)
{
	t_num	l;

	l.dx = x2 - x1;
	l.dy = y2 - y1;
	if (l.dx >= 0)
		l.IncXi = 1;
	else
	{
		l.dx = -l.dx;
		l.IncXi = -1;
	}
	if (l.dy >= 0)
		l.IncYi = 1;
	else
	{
		l.dy = -l.dy;
		l.IncYi = -1;
	}
	if (l.dx >= l.dy)
	{
		l.IncYr = 0;
		l.IncXr = l.IncXi;
	}
	else
	{
		l.IncXr = 0;
		l.IncYr = l.IncYi;
		l.k = l.dx;
		l.dx = l.dy;
		l.dy = l.k;
	}
	l.x = x1;
	l.y = y1;
	l.avR = 2 * l.dy;
	l.av = l.avR - l.dx;
	l.avI = l.av - l.dx;
	while ((int)l.x != x2)
	{
		mlx_pixel_put(gr->mlx, gr->mlx_win, l.x, l.y, 0xFF0000);
		if (l.av >= 0)
		{
			l.x = l.x + l.IncXi;
			l.y = l.y + l.IncYi;
			l.av = l.av + l.avI;
		}
		else
		{
			l.x = l.x + l.IncXr;
			l.y = l.y + l.IncYr;
			l.av = l.av + l.avR;
		}
	}
}
