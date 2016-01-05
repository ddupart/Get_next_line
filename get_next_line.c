/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddupart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:09:32 by ddupart           #+#    #+#             */
/*   Updated: 2016/01/05 20:34:20 by ddupart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t		ft_end(char *stock)
{
	int			i;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i);
}

static char			*ft_gnl_join(char *s1, char *s2)
{
	char			*dst;
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
	return (dst);
}

static int			ft_end_line(char *buf, char **line, char **stock)
{
	size_t		end;
	char		*clr;

	if (!(*stock = ft_gnl_join(*stock, buf)))
		return (-1);
	end = ft_end(*stock);
	if (ft_strchr(*stock, '\n') != NULL)
	{
		if (!(*line = ft_strsub(*stock, 0, end)))
			return (-1);
		clr = *stock;
		if (!(*stock = ft_strsub(*stock, end + 1, ft_strlen(*stock) - end + 1)))
			return (-1);
		free(clr);
		return (1);
	}
	return (0);
}

int					ft_no_nl(char **line, char **stock)
{
	size_t		end;

	end = ft_end(*stock);
	if (!(*line = ft_strsub(*stock, 0, end)))
		return (-1);
	if (!(*stock = ft_strsub(*stock, end + 1, ft_strlen(*stock) - end + 1)))
		return (-1);
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	static char	*stock = NULL;
	int			ret;
	char		*buf;
	int			verif;

	if (!(buf = ft_strnew(BUFF_SIZE)) || fd < 0
			|| (ret = read(fd, buf, 0)) < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		verif = ft_end_line(buf, line, &stock);
		free(buf);
		if (verif == 1)
			return (1);
		buf = ft_strnew(BUFF_SIZE);
	}
	if ((verif = ft_end_line(buf, line, &stock)) == 0)
	{
		if (ft_strlen(stock) > 0)
			verif = ft_no_nl(line, &stock);
		ft_strdel(&stock);
	}
	return (verif);
}
