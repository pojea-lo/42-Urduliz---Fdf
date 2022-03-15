#include "fdf.h"

//change center with click mouse
int	chg_center_m(int button, int x, int y, t_conv *hook)
{
	if (button == 2)
	{
		if (hook->num->hk == 's' || hook->num->hk == 'i')
			hook->num->hk = 'i';//condicion para cambiar el origen
		else
			hook->num->hk = 'c';//condicion para cambiar el origen
		hook->num->xx = x / hook->num->esc;
		hook->num->yy = y / hook->num->esc;
		ft_calculs (hook->str, hook->num, hook);
	}
	return (0);
}

//cierra con boton rojo
int	close_button(t_conv *hook)
{
	mlx_destroy_window(hook->gr->mlx, hook->gr->mlx_win);
	mlx_destroy_image(hook->gr->mlx, hook->gr->img);
	ft_free(hook, hook->num->y);
	system ("leaks fdf");
	exit(1);
}

//tape keyboard
int keyw(int keycode, t_conv *hook)
{
	if (keycode == 69 || keycode == 78)
		zoom (keycode, hook);
	else if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		chg_center_k (keycode, hook);
	else if (keycode == 53)
		close_key (keycode, hook);
	else if (keycode == 8 || keycode == 34)
		change_view (keycode, hook);
	return (0);
}

//change view
int	change_view (int keycode, t_conv *hook)
{
	if (keycode == 8)
	{
		hook->num->hk = 'c';
	}
	if (keycode == 34)
	{
		hook->num->hk = 'i';
	}
	ft_calculs (hook->str, hook->num, hook);
	return (0);
}

//change zoom
int zoom(int keycode, t_conv *hook)
{
	if (keycode == 69)
	{
		if (hook->num->esc < 2)//condiciones para escalas iniciales muy bajas que no recuperan por el incremento
			hook->num->esc *= 3;
		else if (hook->num->esc < 3)
			hook->num->esc *= 1.5;
		else
			hook->num->esc *= 1.334;
		ft_calculs (hook->str, hook->num, hook);
	}
	if (keycode == 78)
	{
		if (hook->num->esc > 2)//condicion para que no baje mucho el numero y pueda recuperar en funcion del incremento
			hook->num->esc /= 1.33;
		else if (hook->num->esc > 1)
			hook->num->esc /= 1.1;
		ft_calculs (hook->str, hook->num, hook);
	}
	if (hook->num->hk == 's' || hook->num->hk == 'i')
		hook->num->hk = 'i';//condicion para cambiar el origen
	else
		hook->num->hk = 'c';//condicion para cambiar el origen
	return (0);
}

//change center with keyword arrows
int chg_center_k(int keycode, t_conv *hook)
{
	if (keycode == 123)
		hook->num->xx -= 50 / hook->num->esc_hk;
	if (keycode == 124)
		hook->num->xx += 50 / hook->num->esc_hk;
	if (keycode == 125)
		hook->num->yy += 50 / hook->num->esc_hk;
	if (keycode == 126)
		hook->num->yy -= 50 / hook->num->esc_hk;
	if (hook->num->hk == 's' || hook->num->hk == 'i')
		hook->num->hk = 'i';//condicion para cambiar el origen
	else
		hook->num->hk = 'c';//condicion para cambiar el origen
	ft_calculs (hook->str, hook->num, hook);
	return (0);
}

//cierra con esc la pantalla
int	close_key(int keycode, t_conv *hook)//t_conv *hook)
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
