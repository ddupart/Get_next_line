#include "get_next_line.h"

static size_t		ft_end(char *stock)
{
	int			i;

	i = 0;
	while (stock[i] != '\n')
		i++;
	return (i);
}

static char		*ft_gnl_join(char *s1, char *s2)
{
	char		*dst;
	size_t			a;
	size_t			b;

	a = 0;
	b = 0;
	if (s1)
		a = ft_strlen(s1);
	if (s2)
		b = ft_strlen(s2);
	dst = ft_strnew(a + b);
	if (a)
		ft_memcpy(dst, s1, a);
	if (b)
		ft_memcpy(dst + a, s2, b);
	free(s1);
	ft_bzero(s2, (size_t)BUFF_SIZE + 1);
	return (dst);
}

static int		ft_end_line(char *buf, char **line, char **stock)
{
	*stock = ft_gnl_join(*stock, buf);
	if (ft_strchr(*stock, '\n') != NULL)
	{
		*line = ft_strsub(*stock, 0, ft_end(*stock));
		*stock = ft_strsub(*stock, ft_end(*stock) + 1, ft_strlen(*stock) - ft_end(*stock) + 1);
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char	*stock = NULL;
	int			ret;
	char		*buf;
	int			verif;

	if (!(buf = ft_strnew(BUFF_SIZE + 1)) || fd < 0
			|| (ret = read(fd, buf, 0)) < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if ((verif = ft_end_line(buf, line, &stock)) == 1)
			return (1);
		if (ret < 0)
			return (-1);
	}
	if ((verif = ft_end_line(buf, line, &stock)) == 0)
	{
		free(buf);
		ft_strdel(&stock);
	}
	return (verif);
}
/*
int	main(int argc, char **argv)
{
	int	fd;
	char *line;
	int	control;
	int	count;

	count = 0;
	fd = open(argv[1], O_RDONLY);
	control = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (line != NULL)
		{
		ft_putstr("Line ");
		ft_putnbr(count);
		ft_putstr(" : ");
		ft_putendl(line);
		count++;
		}
	}
	free(line);
	return (0);
}*/
