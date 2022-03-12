#include "fdf.h"

int	close_key(int keycode, t_conv *hook)//t_conv *hook)//cierra con esc la pantalla
{
	if (keycode == 53)
	{
		mlx_destroy_window(hook->gr->mlx, hook->gr->mlx_win);
		mlx_destroy_image(hook->gr->mlx, hook->gr->img);
		free (hook->gr->mlx);
		ft_free(hook, hook->num->y);
//		system ("leaks fdf");
		exit(1);
	}
	return(0);
}

int chg_center(int keycode, t_conv *hook)//cambia el centro del dibujo
{
	if (keycode == 69)
	{
		if (hook->num->esc < 2)//condiciones para escalas iniciales muy bajas que no recuperan por el incremento
			hook->num->esc *= 3;
		else if (hook->num->esc < 3)
			hook->num->esc *= 1.5;
		else
			hook->num->esc *= 1.334;
		hook->num->hk = 'h';//condicion para que no entre en esc ni abra ventana nueva
//		hook->num->xx; 
		mlx_destroy_window(hook->gr->mlx, hook->gr->mlx_win);
		mlx_destroy_image(hook->gr->mlx, hook->gr->img);
		ft_calculs (hook->str, hook->num);
	}
	if (keycode == 78)
	{
		if (hook->num->esc > 2)//condicion para que no baje mucho el numero y pueda recuperar en funcion del incremento
			hook->num->esc /= 1.33;
		else if (hook->num->esc > 1)
			hook->num->esc /= 1.1;
		hook->num->hk = 'h';//condicion para que no entre en esc ni abra ventana nueva
		mlx_destroy_window(hook->gr->mlx, hook->gr->mlx_win);
		mlx_destroy_image(hook->gr->mlx, hook->gr->img);
		ft_calculs (hook->str, hook->num);
	}
	return (0);
}

int	close_button(t_conv *hook)//cierra con boton rojo
{
	mlx_destroy_window(hook->gr->mlx, hook->gr->mlx_win);
	mlx_destroy_image(hook->gr->mlx, hook->gr->img);
	free (hook->gr->mlx);	
	ft_free(hook, hook->num->y);
	system ("leaks fdf");
	exit(1);
}
