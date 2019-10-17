/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 01:28:47 by mapandel          #+#    #+#             */
/*   Updated: 2019/10/18 01:41:45 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		parsing_error_display(int display_code, char *justification) {
	// nothing passed
	if (display_code == 1)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	// invalid command
	else if (display_code == 2) {
		ft_printf("\
ft_ssl: Error: '%s' is an invalid command.\n\n\
Standard commands:\n\n\
Message Digest commands:\n\
md5\n\
sha256\n\n\
Cipher commands:\n", justification);
	}
	// invalid option
	else if (display_code == 3) {
		ft_printf("md5: illegal option -- %c\n\
usage: ft_ssl [command] [-pqr] [-s string] [files ...]\n", justification[0]);
	}
}

static t_ssl		*parsing_flags(t_ssl *ssl, int argc, char **argv) {
	int		i;

	i = 2;
	while (i < argc) {
		if (argv[i][0] == '-' && ft_strlen(argv[i]) >= 2) {
			if (!(ft_strcmp(argv[i], "-p"))) {
				if (!(ssl->flags & 1))
					ssl->flags += 1;
			}
			else if (!(ft_strcmp(argv[i], "-q"))) {
				if (!(ssl->flags & 2))
				ssl->flags += 2;
			}
			else if (!(ft_strcmp(argv[i], "-r"))) {
				if (!(ssl->flags & 4))
				ssl->flags += 4;
			}
			else if (!(ft_strcmp(argv[i], "-s"))) {
				if (!(ssl->flags & 8))
				ssl->flags += 8;
			}
			else if (!(ft_strcmp(argv[i], "--")) && ++i)
				break;
			else
				parsing_error_display(3, &argv[i][1]);
		}
		else
			break;
		++i;
	}

	// parsing files
	if (!(ssl->files = ft_strmapdup((const char**)(unsigned long)(&argv[i]))))
		return (NULL);

	return (ssl);
}

t_ssl		*parsing (t_ssl *ssl, int argc, char **argv) {
	// no argument passed
	if (argc == 1) {
		parsing_error_display(1, NULL);
		return (NULL);
	}
	// parsing command name
	if (argc >= 2) {
		if (!(ft_strcmp(argv[1], "md5")) || !(ft_strcmp(argv[1], "sha256")))
			ssl->command_name = ft_strdup(argv[1]);
		else {
			parsing_error_display(2, argv[1]);
			return (NULL);
		}
	}
	// parsing flags then files
	ssl = parsing_flags(ssl, argc, argv);

	return (ssl);
}
