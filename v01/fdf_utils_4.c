#include "fdf.h"

//función que imprime puntos
void	ft_print_pixel(t_mlx *gr, t_num *num, t_str *str)
{
	t_num	c;

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
			* num->esc, 0x0000FF);
			c.k++;
		}
	}
}
