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
	if (!(dst = ft_strnew(a + b)))
		return (NULL);
	if (a)
		ft_memcpy(dst, s1, a);
	if (b)
		ft_memcpy(dst + a, s2, b);
	free(s1);
	ft_bzero(s2, (size_t)BUFF_SIZE + 1);
	return (dst);
}

static int		ft_end_line(char *buf, char **line, t_gnl **current)
{
	(*current)->stock = ft_gnl_join((*current)->stock, buf);
	if (ft_strchr((*current)->stock, '\n') != NULL)
	{
		*line = ft_strsub((*current)->stock, 0, ft_end((*current)->stock));
		(*current)->stock = ft_strsub((*current)->stock, ft_end((*current)->stock) + 1, ft_strlen((*current)->stock) - ft_end((*current)->stock) + 1);
		return (1);
	}
	return (0);
}

static t_gnl			*ft_find_fd(t_gnl **begin_list, int const fd)
{
	t_gnl		*tmp;
	t_gnl		*new;

	tmp = *begin_list;
	while (tmp && tmp->file != fd)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		new = malloc(sizeof(t_gnl));
		new->file = fd;
		new->stock = NULL;
		new->next = *begin_list;
		*begin_list = new;
	}
	else
		return (tmp);
	return (new);
}

int		get_next_line(int const fd, char **line)
{
	static t_gnl	*begin_list = NULL;
	int			ret;
	char		*buf;
	int			verif;
	t_gnl		*current;

	if (!(buf = ft_strnew(BUFF_SIZE + 1)) || fd < 0
			|| (ret = read(fd, buf, 0)) < 0)
		return (-1);
	current = ft_find_fd(&begin_list, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if ((verif = ft_end_line(buf, line, &current)) == 1)
			return (1);
		if (ret < 0)
			return (-1);
	}
	if ((verif = ft_end_line(buf, line, &current)) == 0)
	{
		free(buf);
//		ft_strdel(&stock);
	}
	return (verif);
}

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
}
