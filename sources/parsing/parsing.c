/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 01:28:47 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:17:55 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*,
**	parsing_command_name:
**		Initializes the t_cmd* structure with the given command name
**			from arguments
**		An absent or invalid command is considered a parsing error,
**			it then displays the appropriate error message
**		This function do not return a value
*/

static void		parsing_command_name (t_ssl *ssl)
{
	/* No command passed */
	if (ssl->argc <= 1)
		error_handler(ssl, ERR_NO_ARG, NULL);

	/* Initializes the command related variables */
	if (set_t_cmd(ssl->cmd, ssl->argv[1]))
		error_handler(ssl, ERR_INVALID_CMD_NAME, ssl->argv[1]);
}


/*
**	parsing:
**		Iterates on arguments to find valuable informations
**		Searches for the command name of the choosen algorithm first
**		Then flags and files with their own specific parsing
**		No argument given after the command name makes the program perform
**			one execution reading from STDIN
**		This function do not return a value
*/

void			parsing (t_ssl *ssl)
{
	size_t		argv_i;

	parsing_command_name(ssl);

	argv_i = 2;

	/* Loop over potential flag arguments */
	searching_flags(ssl, &argv_i);

	/* Loop over file arguments */
	searching_files(ssl, &argv_i);
}
