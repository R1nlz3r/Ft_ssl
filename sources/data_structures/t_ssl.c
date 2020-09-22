/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ssl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:45:46 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 18:23:40 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_ssl:
**		Frees up a t_ssl* structure pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void		del_t_ssl(t_ssl **ssl)
{
	if (!(ssl && *ssl))
		return ;

	if ((*ssl)->cmd)
		del_t_cmd(&(*ssl)->cmd);
	if ((*ssl)->flags)
		del_t_flag(&(*ssl)->flags);
	if ((*ssl)->argv)
		ft_strmapdel(&(*ssl)->argv);

	ft_memdel((void**)ssl);
	*ssl = NULL;
}


/*
**	init_t_ssl:
**		Allocates memory for a new t_ssl* structure
**		Initializes its variables and structures as needed
**		Duplicates argv as a char** in the structure for easy access
**		Returns it or NULL if an allocation failed
*/

t_ssl		*init_t_ssl(t_ssl *ssl, int argc, char **argv)
{
	if (!(ssl = ft_memalloc(sizeof(t_ssl)))
		|| !(ssl->cmd = init_t_cmd())
		|| !(ssl->flags = init_t_flag()))
		return (NULL);

	ssl->arg = NULL;
	ssl->bool_one_conversion_done = 0;
	ssl->return_value = 0;
	ssl->argc = (size_t)argc;
	if (!(ssl->argv = ft_strmapdup((const char**)(unsigned long)argv)))
		return (NULL);

	return (ssl);
}
