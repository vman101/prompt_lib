/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:06:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 23:07:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

# include <io.h>
#include <io.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int64_t ft_read(int fd, char *buffer, uint32_t size_to_read) {
    int64_t bytes_read;

    if (fd == 0)
        fd = _fileno(stdin);
    else if (fd == 1)
        fd = _fileno(stdout);

    // Read input from the file descriptor
    bytes_read = _read(fd, buffer, size_to_read);

    if (bytes_read > 0) {
        // Null-terminate the buffer for safe string handling
        buffer[bytes_read] = '\0';

        // Check for the presence of \r and handle \r\n as a single newline
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\r') {
                // If \r is found and followed by \n, remove \r
                if (i + 1 < bytes_read && buffer[i + 1] == '\n') {
                    // Shift the buffer contents left to remove \r
                    memmove(&buffer[i], &buffer[i + 1], bytes_read - i - 1);
                    bytes_read--; // Adjust bytes read to reflect removed \r
                    break; // Stop processing further since \r\n has been handled
                }
            }
        }
    }

    if (bytes_read == -1) {
        if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
            return 0;
        perror("read");
        // Your memory cleanup or additional error handling code
    }

    return bytes_read;
}

// int64_t	ft_read(int fd, char *character, uint32_t size_to_read)
// {
// 	int64_t	bytes_read;
// 	char	*tmp;
//
// 	if (fd == 0)
// 		fd = _fileno(stdin);
// 	else if (fd == 1)
// 		fd = _fileno(stdout);
// 	bytes_read = _read(fd, character, size_to_read);
// 	if (bytes_read > 0)
// 	{
// 		character[bytes_read] = '\0';
// 		tmp = ft_strrchr(character, '\r');
// 		if (tmp && (tmp - character < bytes_read - 1) && *(tmp + 1) == '\n')
// 		{
// 			ft_memmove(tmp, tmp + 1, bytes_read - (tmp - character) - 1);
// 			bytes_read--;
// 		}
// 	}
// 	if (bytes_read == -1)
// 	{
// 		if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
// 			return (0);
// 		perror("read");
// 		lst_memory(NULL, NULL, CLEAN);
// 	}
// 	return (bytes_read);
// }
//
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
