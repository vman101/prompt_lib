/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:56:10 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 23:14:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

# include <windows.h>

void		terminal_raw_mode_enable_internal(void)
{
	HANDLE hStd = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;

	GetConsoleMode(hStd, &mode);
	mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	mode &= ~ENABLE_PROCESSED_INPUT;
	SetConsoleMode(hStd, mode);
}

void		terminal_raw_mode_disable_internal(void)
{
	HANDLE hStd = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;

	GetConsoleMode(hStd, &mode);
	mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	SetConsoleMode(hStd, mode);
}

#else

void	terminal_raw_mode_enable(void)
{
	struct termios	raw;

	if (isatty(0) && isatty(1))
	{
		tcgetattr(STDIN_FILENO, &raw);
		raw.c_lflag &= ~(ECHOCTL | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	}
}

void	terminal_raw_mode_disable(void)
{
	struct termios	orig;

	if (isatty(0) && isatty(1))
	{
		tcgetattr(STDIN_FILENO, &orig);
		orig.c_lflag |= (ECHO | ECHOCTL | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
	}
}

#endif
