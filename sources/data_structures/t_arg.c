/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:50:51 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/20 01:29:58 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_arg:
**		Frees up a t_arg* pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void		del_t_arg(t_arg **arg)
{
	if (arg && *arg) {
		if ((*arg)->file_name)
			ft_strdel(&(*arg)->file_name);
		if ((*arg)->msg)
			ft_strdel((char**)&(*arg)->msg);
		if ((*arg)->digest)
			ft_strdel(&(*arg)->digest);
		ft_memdel((void**)arg);
		*arg = NULL;
	}
}


/*
**	init_t_arg:
**		Allocates in memory a t_arg* structure
**		Initializes its variables
**		Returns it or NULL if the allocation failed
*/

t_arg		*init_t_arg(void)
{
	t_arg		*node;

	if (!(node = ft_memalloc(sizeof(t_arg))))
		return (NULL);
	node->file_name = NULL;
	node->msg = NULL;
	node->digest = NULL;
	node->msg_len = 0;
	node->msg_total_len = 0;
	return (node);
}
