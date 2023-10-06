/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:51:48 by tdemir            #+#    #+#             */
/*   Updated: 2022/11/15 02:01:08 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

size_t	ft_strlen(char *str);
char	*ft_buff(int fd, char *str);
char	*get_next_line(int fd);
char	*ft_strjoin(char *str, char *buff);
char	*ft_strchr(char *str, int c);
char	*ft_get_line(char *str);
char	*ft_last_str(char *str);
#endif