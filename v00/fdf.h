#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./mlx/mlx.h"

typedef struct s_num//estructura para todas las variables numéricas necesarias
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	y;//numero de filas
	size_t	x;//numero de columnas
	size_t	esc;//escala del dibujo
	double	xx;//valor de x del origen
	double	yy;//valor de y del origen
	double	xxx;
	double	yyy;
	int		x0;//de aqui hasta la avR son para pintar la linea
	int		y0;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		dx;
	int		dy;
	int		IncXi;
	int		IncXr;
	int		IncYi;
	int		IncYr;
	int		av;
	int		avI;
	int		avR;
}	t_num;	

typedef struct s_str//estructura para todas las variables tipo array
{
	char	**st;//cadena de cadenas que recoge el gnl
	char	**sch;//cadena de cadenas que recoge el spli
	int		**sin;//matriz de numeros int
	double	*mm;//máximo y mínimo de altura
	double	*size;//tamaños de ventana mínimos necesarios
}	t_str;

typedef struct s_mlx//estructura para la mlx
{
	void	*mlx;//puntero de la mlx
	void	*mlx_win;//puntero de la ventana
}	t_mlx;

//funciones del fdf_utils_1
char	**ft_read(int fd, size_t y, char *st);//lectura del archivo metiendo en cadenas las lineas
size_t	ft_count_rows(int fd);//cuenta las lineas del mapa para el malloc
char	**ft_cut(char *s);//divido las filas dejándolas en un array de arrays
int		*ft_put_int(char **sch, size_t x);//convierto las cadenas anteriores a int 
void	ft_print_mat(int **sin, size_t x, size_t y);//función que imprime el array de int bidimensional
//funciones del fdf_utils_2
double	*ft_max (int **sin, size_t x, size_t y);//busca los máximos y m´ínimos de altura
double	ft_wde_size(double *size);//saca la ventana mínima necesaria
double	*ft_wd_size(size_t x, size_t y, double *mm);//calcula una escala proporcional al tamaño mínimo necesario
double	ft_center_y(double *size, double *mm);//busca el centro para y
size_t	ft_count_columns(char *s, char c);//cuenta las columnas de cada fila
//funciones del fdf_utils_3
void	ft_print_pixel(t_mlx *gr, t_num *num, t_str *str);//imprime los puntos de la matriz
void	ft_line_ppx(t_mlx *gr, t_num *num, t_str *str);//función que calcula los puntos de la linea
void	ft_line_ppy(t_mlx *gr, t_num *num, t_str *str);//función que calcula los puntos de la linea
void	ft_print_line_1(t_mlx *gr, int x1, int y1, int x2, int y2);//primera parte de la función que imprime la linea


char	*get_next_line(int fd);//funciones del gnl
char	*ft_join(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_strchr(char *s, char c);
int		ft_strlen(char *str);
char	*ft_line(char *rest, char *buf, int bread);
char	*ft_updrest(char *rest, int bread);
void	*ft_memcpy(void *dest, const void *org, size_t n);
char	*ft_copyrest(char *rest, size_t i);
char	*ft_malloc_1(int bufsz);

/*
char	*get_next_line(int fd);//funciones de copia gnl
int		ft_strlen(char *str);
char	*ft_join(char *rest_buff, char *buff, int bit_counter);
int		ft_find_char(char *rest_buff, char c);
char	*ft_line_out(char *rest_buff);
char	*ft_new_rest(char *rest_buff);
int		ft_rest_buff_to_null(char *rest_buff);
char	*ft_str_joined(char *rest_buff, char *buff);
*/

char	**ft_split(char *s, char c);//funciones del split
char	*ft_copy(char *s, int i, int j);
char	**ft_malloc(char *s, char c);

int		ft_atoi(char *str);//funciones del atoi

#endif
