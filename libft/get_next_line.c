/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:31:22 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/28 11:32:28 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include "libft.h"

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*str;
	int		nbr;

	buffer = ft_calloc(2, sizeof(char));
	str = NULL;
	nbr = read(fd, buffer, 1);
	if (nbr > 0)
		str = ft_calloc(2, sizeof(char));
	while (nbr > 0 && buffer[0] != '\n')
	{
		str = ft_strjoin(str, buffer);
		nbr = read(fd, buffer, 1);
	}
	if (buffer[0] == '\n')
		str = ft_strjoin(str, "\n");
	free (buffer);
	return (str);
}
