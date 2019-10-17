/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:21 by mapandel          #+#    #+#             */
/*   Updated: 2019/10/18 01:43:37 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		del_t_ssl(t_ssl *ssl) {
	if (ssl) {
		if (ssl->command_name)
			ft_strdel(&ssl->command_name);
		if (ssl->files)
			ft_strmapdel(&ssl->files);
		ft_memdel((void**)&ssl);
	}
}

static t_ssl	*init_t_ssl(t_ssl *ssl) {
	if (!(ssl = ft_memalloc(sizeof(t_ssl))))
		return (NULL);
	ssl->command_name = NULL;
	ssl->flags = 0;
	ssl->files = NULL;
	return (ssl);
}

int				main (int argc, char **argv) {
	t_ssl	*ssl;

	// init
	ssl = NULL;
	if (!(ssl = init_t_ssl(ssl)))
		return (-1);
	// parsing
	if (!(ssl = parsing(ssl, argc, argv)))
		return (-1);

	// choose the algorithm
		// execute the algorithm

	//free
	del_t_ssl(ssl);

	// while(1 < 2) {}
	return (0);
}
