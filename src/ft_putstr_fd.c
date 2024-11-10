/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:22 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 16:24:40 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#ifdef _WIN32

# include <io.h>

void	ft_putstr_fd(char *buf, int fd)
{
	_write(fd, buf, strlen(buf));
}

#else

#include <unistd.h>

void	ft_putstr_fd(char *buf, int fd)
{
	write(fd, buf, strlen(buf));
}

#endif
