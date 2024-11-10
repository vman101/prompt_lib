/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_blocking_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:14:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 18:58:42 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

#include <windows.h>

void toggle_non_blocking_mode(int enable)
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    if (hStdin == INVALID_HANDLE_VALUE)
	{
        fprintf(stderr, "Error getting standard input handle.\n");
        exit(1);
    }

    if (!GetConsoleMode(hStdin, &mode))
	{
        fprintf(stderr, "Error getting console mode.\n");
        exit(1);
    }
    if (enable)
	{
        mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    }
	else
	{
        mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    }

    if (!SetConsoleMode(hStdin, mode))
	{
        fprintf(stderr, "Error setting console mode.\n");
        exit(1);
    }
}

#else

# include <sys/ioctl.h>

void	blocking_mode_toggle(int fd, int flag)
{
	if (ioctl(fd, FIONBIO, &flag) == -1)
	{
		perror("ioctl");
		exit(1);
	}
}

#endif
