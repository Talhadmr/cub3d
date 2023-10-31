/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:40:21 by ykissiko          #+#    #+#             */
/*   Updated: 2023/10/31 15:40:23 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_input(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("Wrong number of arguments\n"));
	if (ft_check_ext(argv[1], 4, ".cub") != 1)
		return (printf("Map have to be in .cub file format\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Map doesn't exist\n"));
	close(fd);
	return (1);
}

int	ft_check_ext(char *file, int len, char *ext)
{
	int	flen;
	int	i;

	flen = ft_strlen(file);
	i = 0;
	while (i < len)
	{
		if (file[flen - len + i] != ext[i])
			return (0);
		i++;
	}
	return (1);
}
