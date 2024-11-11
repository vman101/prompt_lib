/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:46:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/11 11:38:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stdlib.h>

enum e_alloc
{
	ADD,
	FAIL,
	END,
	FREE,
	AT_EXIT,
};

void	lst_memory(void *mem, void (*del)(void *c), int mode);
void	ft_free(void *ptr);

#endif
