#include "fdf.h"

char	*get_next_line(int fd)
{
	char		*buf;
	int			bufsz;
	char		*s;
	static char	*rest;
	int			bread;

	bufsz = 1;
	bread = 1;
	if (fd == -1 || bufsz <= 0)
		return (NULL);
	buf = (char *) malloc (sizeof(char) * (bufsz + 1));
	if (buf == NULL)
		return (NULL);
	while (ft_strchr (rest, '\n') != 1 && bread != 0)
	{
		bread = read (fd, buf, bufsz);
		buf[bread] = '\0';
		if (bread == -1)
		{
			free (buf);
			return (NULL);
		}
		rest = ft_join (rest, buf);
	}
	s = ft_line(rest, buf, bread);
	rest = ft_updrest(rest, bread);
	return (s);
}

char	*ft_line(char *rest, char *buf, int bread)
{
	int		i;
	char	*s;

	free (buf);
	i = 0;
	if (*rest != '\0' || bread != 0)
	{
		while (rest[i] != '\0')
		{
			if (rest[i] == '\n')
			{
				i++;
				s = ft_substr (rest, 0, i);
				return (s);
			}
			i++;
		}
		s = ft_substr (rest, 0, i);
	}
	else
		s = NULL;
	return (s);
}

char	*ft_updrest(char *rest, int bread)
{
	char	*des;
	size_t	i;

	i = 0;
	if (*rest != '\0' || bread != 0)
	{
		while (rest[i] != '\n' && rest[i] != '\0')
			i++;
		if (rest[i] == '\0')
		{
			free(rest);
			return (NULL);
		}
		else
			des = ft_copyrest(rest, i);
		free (rest);
	}
	else
	{
		free (rest);
		return (0);
	}
	return (des);
}

char	*ft_copyrest(char *rest, size_t i)
{
	char	*des;
	int		j;

	j = 0;
	des = (char *)malloc (sizeof(char) * (ft_strlen(rest) - i + 1));
	if (!des)
		return (NULL);
	while (i++ < (size_t) ft_strlen(rest))
		des[j++] = rest[i];
	des[j] = '\0';
	return (des);
}
