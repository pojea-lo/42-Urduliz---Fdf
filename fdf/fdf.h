#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "mlx.h"

char	**ft_read(int fd, size_t y);//funciones del fdf
size_t	ft_count_rows(int fd);
char	**ft_cut(char *s);
int		*ft_put_int(char **sch, size_t x);
void	ft_print_mat(int **sin, size_t x, size_t y);
double	*ft_max (int **sin, size_t x, size_t y);
double	*ft_wd_size(size_t x, size_t y, double *mm);
double	ft_center_y(double *size, double *mm);


char	*get_next_line(int fd);//funciones del gnl
char	*ft_join(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_strchr(char *s, char c);
int		ft_strlen(char *str);
char	*ft_line(char *rest, char *buf, int bread);
char	*ft_updrest(char *rest, int bread);
void	*ft_memcpy(void *dest, const void *org, size_t n);
char	*ft_copyrest(char *rest, size_t i);

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
size_t	ft_count_columns(char *s, char c);
char	**ft_malloc(char *s, char c);

int		ft_atoi(char *str);//funciones del atoi

#endif
