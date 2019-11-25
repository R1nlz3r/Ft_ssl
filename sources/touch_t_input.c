/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_t_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:50:51 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/26 00:02:24 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	add_t_input_to_t_list:
**		Allocates a new t_list node and a t_input
**		Stocks the input in this new node
**		And plugs the node at the end of the chain list of inputs
**		Returns a pointer on the new input
**		Returns this new input or NULL if an allocation failed
*/

t_input		*add_t_input_to_t_list(t_ssl *ssl)
{
	t_list		*new_node;
	t_input		*new_input;

	if (!(new_input = init_t_input())
		|| !(new_node = ft_lstnew(NULL, 0)))
		return (NULL);
	new_node->content = new_input;
	ft_lstadd(&ssl->inputs, new_node);
	return (new_input);
}


/*
**	del_t_input:
**		Frees up a t_input* pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void		del_t_input(t_input *node, size_t unused_value)
{
	(void)unused_value;
	if (node) {
		if (node->input)
			ft_strdel(&node->input);
		if (node->digest)
			ft_strdel(&node->digest);
		ft_memdel((void**)&node);
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
	node->digest = NULL;
	node->flags = 0;
	return (node);
}
