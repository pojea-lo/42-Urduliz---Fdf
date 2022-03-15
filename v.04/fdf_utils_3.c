/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:13 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/03/15 17:36:26 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//función que calcula las parejas de puntos en el eje x
void	ft_line_ppx(t_mlx *gr, t_num *num, t_str *str)
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
			l.yyy = l.yyy + 0.433;
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
void	ft_line_ppy(t_mlx *gr, t_num *num, t_str *str)
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
			l.y1 = ((l.yyy + (l.k * 0.433)) - str->sin[l.i][l.j]) * num->esc;
			l.y2 = ((l.yyy + ((l.k + 1) * 0.433)) - str->sin[l.i][l.j + 1]) \
			* num->esc;
			ft_print_line_1 (gr, &l);
			l.k++;
		}
	}
	mlx_put_image_to_window(gr->mlx, gr->mlx_win, gr->img, 0, 0);//vuelca la imagen a la ventana
}

void	ft_print_line_1(t_mlx *gr, t_num *l)
{
	t_num	n;

	n.dx = l->x2 - l->x1;
	n.dy = l->y2 - l->y1;
	n.IncXi = 1;
	if (n.dx < 0)
	{
		n.dx = -n.dx;
		n.IncXi = -1;
	}
	n.IncYi = 1;
	if (n.dy < 0)
	{
		n.dy = -n.dy;
		n.IncYi = -1;
	}
	ft_print_line_2(gr, l, &n);
}

void	ft_print_line_2(t_mlx *gr, t_num *l, t_num *n)
{
	if (n->dx >= n->dy)
	{
		n->IncYr = 0;
		n->IncXr = n->IncXi;
	}
	else
	{
		n->IncXr = 0;
		n->IncYr = n->IncYi;
		n->k = n->dx;//invierto los valores para aprovechar el bucle final
		n->dx = n->dy;
		n->dy = n->k;
	}
	n->x = l->x1;
	n->y = l->y1;
	n->avR = 2 * n->dy;
	n->av = n->avR - n->dx;
	n->avI = n->av - n->dx;
	ft_print_line_3 (gr, l, n);
}

void	ft_print_line_3(t_mlx *gr, t_num *l, t_num *n)
{
	char	*dst;
	int		color;

	color = 0x48E120;
//	printf ("HOLA\n");
	while ((int)n->x != l->x2 || (int)n->y != l->y2)
	{
	//	printf ("la x: %d  /  la y: %d \n", (int)n->x, (int)n->y);
	//	printf ("la esc: %d\n", gr->esc);
		if (((int)n->x > 0) && ((int)n->x < gr->size_x *  gr->esc) && ((int)n->y > 0) && ((int)n->y < gr->size_y * gr->esc))
		{
			dst = gr->addr + (n->y * gr->line_length + n->x * (gr->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		if (n->av >= 0)
		{
			n->x = n->x + n->IncXi;
			n->y = n->y + n->IncYi;
			n->av = n->av + n->avI;
		}
		else
		{
			n->x = n->x + n->IncXr;
			n->y = n->y + n->IncYr;
			n->av = n->av + n->avR;
		}
	}
}
