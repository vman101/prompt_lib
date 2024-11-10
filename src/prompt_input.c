/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:40:20 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 19:17:49 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

static void	prompt_handle_accepted_input_internal(t_prompt *prompt, uint32_t cursor_position[2], char **input, char buffer[])
{
	bool	do_refresh;

	do_refresh = true;
	if (buffer[0] == ESC)
		do_refresh = prompt_handle_escape_sequence_internal(prompt, &buffer[1], input, cursor_position);
	else if (buffer[0] == '\t')
		prompt_handle_tab_internal(input, prompt);
	else if (buffer[0] == DEL)
		prompt_handle_backspace_internal(*input, cursor_position, \
				ft_strlen(*input));
	else if (buffer[0] == '\n')
	{
		prompt_handle_new_character_to_input_internal(input, buffer[0], cursor_position, ft_strlen(*input));
		prompt->prompt_display_func(prompt->prompt);
		cursor_position[0]++;
		return ;
	}
	else
		prompt_handle_single_char_input_internal(input, buffer, cursor_position, &do_refresh);
	if (do_refresh == true)
		prompt_refresh_line_internal(*input, prompt->prompt_length, cursor_position);
}

static bool	prompt_is_delimiter(char *input, const char *delimiter)
{
	char		*tmp;
	uint32_t	delimiter_length;

	if (*delimiter == '\n')
		return (true);
	delimiter_length = ft_strlen(delimiter);
	tmp = ft_strrchr(input - (*input == '\n' && ft_strlen(input) > 0), '\n');
	if (tmp)
		if (tmp++ && ((*tmp == *delimiter && delimiter_length == 1) \
					|| ft_strncmp(tmp, delimiter, delimiter_length) == 0))
			return (*tmp = 0, true);
	if ((*input == *delimiter && delimiter_length == 1) \
		|| ft_strncmp(input, delimiter, delimiter_length) == 0)
		return (*input = 0, true);
	return (false);
}

static char	*prompt_handle_input(	t_prompt *prompt, \
							char *input, \
							uint32_t cursor_position[2], \
							const char *delimiter)
{
	char		buffer[100];
	int64_t		bytes_read;

	while (1)
	{
		ft_bzero(buffer, 100);
		bytes_read = ft_read(0, buffer, 20);
		if (bytes_read > 3)
			prompt_handle_rapid_input_internal(buffer, cursor_position, &input, prompt->prompt_length);
		else if (bytes_read >= 1)
		{
			bytes_read = ft_strlen(buffer);
			if (buffer[bytes_read - (bytes_read > 0)] == '\n')
				if (prompt_is_delimiter(input, delimiter))
					break ;
			prompt_handle_accepted_input_internal(prompt, cursor_position, &input, buffer);
		}
	}
	return (input);
}

static void	prompt_handle_history(t_history_buffer *buffer, char *input)
{
	buffer->buffer[buffer->write++] = input;
	buffer->write %= buffer->buffer_capacity;
	buffer->buffer[buffer->write] = 0;
	buffer->read = buffer->write;
}

char	*prompt_get_input_internal(	t_prompt *prompt, \
							uint32_t prompt_initial_size, \
							const char *delimiter)
{
	char		*input;

	input = ft_calloc(prompt_initial_size, sizeof(*input));
	if (!input)
		return (perror("malloc"), NULL);
	lst_memory(input, free, ADD);
	/*terminal_raw_mode_enable(ECHOCTL | ICANON);*/
	prompt->prompt_display_func(prompt->prompt);
	cursor_position_get(prompt->cursor_position);
	prompt->cursor_position[1] = 0;
	if (!delimiter)
		delimiter = "\n";
	input = prompt_handle_input(prompt, input, prompt->cursor_position, delimiter);
	prompt_handle_history(&prompt->history, input);
	/*terminal_raw_mode_disable(ECHO | ECHOCTL | ICANON);*/
	if (!input)
		return (NULL);
	prompt->command = input;
	return (input);
}
