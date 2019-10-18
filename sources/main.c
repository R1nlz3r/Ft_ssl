/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:21 by mapandel          #+#    #+#             */
/*   Updated: 2019/10/18 11:20:05 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			*del_t_ssl(t_ssl *ssl) {
	if (ssl) {
		if (ssl->command_name)
			ft_strdel(&ssl->command_name);
		if (ssl->files)
			ft_strmapdel(&ssl->files);
		ft_memdel((void**)&ssl);
	}
	return (NULL);
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

	for (size_t i = 0; i < ft_strmaplen((const char**)(unsigned long)ssl->files); ++i) {
		ft_printf("%s\n", ssl->files[i]);
	}

	//free
	del_t_ssl(ssl);

	// ssl = NULL;
	// while(1 < 2) {}
	return (0);
}
