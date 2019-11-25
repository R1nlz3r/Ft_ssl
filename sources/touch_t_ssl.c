/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_t_ssl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:45:46 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/26 00:18:19 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_ssl:
**		Frees up a t_ssl* pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void		del_t_ssl(t_ssl *ssl)
{
	if (ssl) {
		if (ssl->command_name)
			ft_strdel(&ssl->command_name);
		if (ssl->argv)
			ft_strmapdel(&ssl->argv);
		ft_lstdel(&ssl->inputs, (void (*)(void *, size_t))&del_t_input);
		ft_memdel((void**)&ssl);
	}
}


/*
**	init_t_ssl:
**		Allocates in memory a t_ssl* structure
**		Initializes its variables
**		Duplicates argv as a char** in the structure for easy access
**		Returns it or NULL if an allocation failed
*/

t_ssl		*init_t_ssl(t_ssl *ssl, int argc, char **argv)
{
	if (!(ssl = ft_memalloc(sizeof(t_ssl))))
		return (NULL);
	ssl->command_name = NULL;
	ssl->flags = 0;
	ssl->return_value = 0;
	ssl->argc = (size_t)argc;
	ssl->inputs = NULL;
	if (!(ssl->argv = ft_strmapdup((const char**)(unsigned long)argv)))
		return (NULL);

	return (ssl);
}
