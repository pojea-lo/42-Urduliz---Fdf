/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:29:45 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/03/11 17:28:56 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	*ft_max(int **sin, size_t x, size_t y)//función que extrae la máx y la mín altura
{
	size_t	i;
	size_t	j;
	double	*mm;

	i = 0;
	mm = (double *) malloc (sizeof(double) * 2);
	if (mm == NULL)
		return (0);
	mm[0] = 0;
	mm[1] = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (sin [i][j] > mm[0]) //guardo el máximo
				mm[0] = sin[i][j];
			if (sin [i][j] < mm[1]) //guardo el minimo
				mm[1] = sin[i][j];
			j++;
		}
		i++;
	}
	return (mm);
}

double	*ft_wd_size(size_t x, size_t y, double *mm)//función que saca el ancho y alto necesario de ventana minima y su centro
{
	double		*size;//recojo ancho min necesario - alto min nec - pos x de centro - pos y de centro
	size = (double *) malloc (sizeof(double) * 2);
	if (size == NULL)
		return (0);
	size[0] = round ((x + y) * cos (0.523599) * cos (0.523599));//ancho minimo de ventana necesario
	size[1] = round (((x + y) * sin (0.523599) * cos (0.523599)) + (mm[0] + (-mm[1])));//alto minimo de ventana necesario
	return (size);
}

double	ft_wde_size(double *size)//funcion que saca el valor de la escala en función del size min necesario y una ventana estándar de 900x450
{
	double		escx;
	double		escy;
	double		esc;

	escx = 900 / size[0];
	escy = 450 / size[1];
	if (escx >= escy)
		esc = escx;
	if (escx < escy)
		esc = escy;
	return (esc);
}

double	ft_center_y(double *size, double *mm)//funcion que centra en y el dibujo
{
	double	yy;

	if (mm[0] == 0 && mm[1] == 0)
		yy = ((size[1] * 1.3) - size[1]) / 2;
	else if (mm[0] != 0 && mm[1] == 0)
		yy = (((size[1] * 1.3) - size[1]) / 2) + mm[0];
	else if (mm[0] == 0 && mm[1] != 0)
		yy = (((size[1] * 1.3) - size[1]) / 2);
	else
		yy = (((size[1] * 1.3) - size[1]) / 2) + mm[0];
	return (yy);
}
