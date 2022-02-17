#include "fdf.h"

int	close_key(int keycode, t_mlx *gr)//cierra con esc a pantalla
{
	if (keycode == 53)
	{
		printf ("HOLA\n");
		mlx_destroy_window(gr->mlx, gr->mlx_win);
		mlx_destroy_image(gr->mlx, gr->img);
		free (gr->mlx);	
		free (gr->img);	
		system ("leaks fdf");
		exit(0);
	}
	return(0);
}

int	close_button(t_mlx *gr)//cierra con boton rojo
{
	mlx_destroy_window(gr->mlx, gr->mlx_win);
	mlx_destroy_image(gr->mlx, gr->img);
	free (gr->mlx);	
	free (gr->img);	
	system ("leaks fdf");
	exit(0);
	return(0);
}
