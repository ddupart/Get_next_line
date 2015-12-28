int		ft_end_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	return (i - 1);
}

int		get_next_line(int fd, char **line)
{
	char 	*buf;
	int		ret;

	if (!(buf = ft_strnew(BUF_SIZE + 1)) || fd < 0)
		return (-1);
	free(line);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUF_SIZE);
		if (!(*line = ft_strjoin(line, buf)) || ret < 0)
			return (-1);
		if (ft_strchr(buf, '\n') != NULL)
		{
			*line + ft_end_line(line) = '\0';
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		get_next_line(fd, &line);
		ft_putendl(line);
	}
	return (0);
}
