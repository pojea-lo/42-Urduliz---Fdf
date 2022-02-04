#include "fdf.h"

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*rest_buff;
	int			bit_counter;
	int			BUFFER_SIZE;
	char		*line;

	bit_counter = 1;
	BUFFER_SIZE = 1000;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (ft_find_char(rest_buff, '\n') && bit_counter != 0)
	{
		bit_counter = read(fd, buff, BUFFER_SIZE);
		buff[bit_counter] = 00;
		if (bit_counter == -1)
		{
			free(buff);
			return (NULL);
		}
		rest_buff = ft_join(rest_buff, buff, bit_counter);
	}
	line = ft_line_out(rest_buff);
	rest_buff = ft_new_rest(rest_buff);
	free(buff);
	return (line);
}

char	*ft_line_out(char *rest_buff)
{
	char	*line_out;
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	if (!rest_buff)
		return (NULL);
	if (ft_find_char(rest_buff, '\n'))
		return (rest_buff);
	while (rest_buff[i] != '\n')
		i++;
	line_out = malloc(sizeof(char) * i + 2);
	while (i + 1 > 0)
	{
		line_out[k] = rest_buff[k];
		i--;
		k++;
	}
	line_out[k] = 00;
	return (line_out);
}

char	*ft_new_rest(char *rest_buff)
{
	char	*aux_rest_buff;
	size_t	count;
	size_t	i;
	char	*r;

	r = rest_buff;
	i = 0;
	if (!rest_buff || ft_find_char(rest_buff, '\n'))
		return (NULL);
	if (ft_rest_buff_to_null(rest_buff))
		return (NULL);
	while (rest_buff[i] != '\n')
		i++;
	count = 0;
	aux_rest_buff = malloc(sizeof(char) * (ft_strlen(rest_buff) - ++i + 1));
	while (rest_buff[i])
	{
		aux_rest_buff[count] = rest_buff[i];
		count++;
		i++;
	}
	aux_rest_buff[count] = 00;
	free(rest_buff);
	return (aux_rest_buff);
}

int	ft_rest_buff_to_null(char *rest_buff)
{
	size_t	i;
	char	*r;

	r = rest_buff;
	i = 0;
	while (rest_buff[i] != '\n')
		i++;
	if (!rest_buff || ft_find_char(rest_buff, '\n'))
		return (1);
	if ((r[0] == '\n' && !r[1]) || (r[i] == '\n' && r[i + 1] == 00))
	{
		free(rest_buff);
		return (1);
	}
	return (0);
}
