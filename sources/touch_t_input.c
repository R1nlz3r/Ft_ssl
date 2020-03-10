/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_t_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:50:51 by mapandel          #+#    #+#             */
/*   Updated: 2020/02/05 15:14:44 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_input:
**		Frees up a t_input* pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void		del_t_input(t_input **input)
{
	if (input && *input) {
		if ((*input)->input)
			ft_strdel(&(*input)->input);
		if ((*input)->msg)
			ft_strdel((char**)&(*input)->msg);
		if ((*input)->digest)
			ft_strdel(&(*input)->digest);
		ft_memdel((void**)input);
		*input = NULL;
	}
}

/*
**	init_t_input:
**		Allocates in memory a t_input* structure
**		Initializes its variables
**		Returns it or NULL if the allocation failed
*/

t_input		*init_t_input(void)
{
	t_input		*node;

	if (!(node = ft_memalloc(sizeof(t_input))))
		return (NULL);
	node->input = NULL;
	node->msg = NULL;
	node->digest = NULL;
	node->msg_len = 0;
	node->msg_total_len = 0;
	node->flags = 0;
	return (node);
}
