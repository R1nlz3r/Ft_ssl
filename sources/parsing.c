/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 01:28:47 by mapandel          #+#    #+#             */
/*   Updated: 2019/10/16 00:45:22 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		parsing (int argc, char **argv) {
	if (argc == 1)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (argc == 2 &&
		ft_strcmp(argv[1], "md5") &&
		ft_strcmp(argv[1], "sha256")) {
		ft_printf("\
ft_ssl: Error: '%s' is an invalid command.\n\
Standard commands:\n\
Message Digest commands:\n\
md5 sha256\n\
Cipher commands:\n\
none\n", argv[1]);
	}
	return (0);
}
