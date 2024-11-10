/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:06:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 18:31:39 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

# include <io.h>

int64_t	ft_read(int fd, char *character, uint32_t size_to_read)
{
	int64_t	bytes_read;

	bytes_read = _read(fd, character, size_to_read);
	if (bytes_read == -1)
	{
		if (errno == EINTR \
			|| errno == EAGAIN \
			|| errno == EWOULDBLOCK)
			return (0);
		perror("read");
		lst_memory(NULL, NULL, CLEAN);
	}
	return (bytes_read);
}

# else

# include <unistd.h>

int64_t	ft_read(int fd, char *character, uint32_t size_to_read)
{
	int64_t	bytes_read;

	bytes_read = read(fd, character, size_to_read);
	if (bytes_read == -1)
	{
		if (errno == EINTR \
			|| errno == EAGAIN \
			|| errno == EWOULDBLOCK)
			return (0);
		perror("read");
		lst_memory(NULL, NULL, CLEAN);
	}
	return (bytes_read);
}

#endif
