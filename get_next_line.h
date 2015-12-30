#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"
# define BUFF_SIZE 50

int		get_next_line(int const fd, char **line);

#endif
