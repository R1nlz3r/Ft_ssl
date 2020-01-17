/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 01:28:47 by mapandel          #+#    #+#             */
/*   Updated: 2020/01/17 01:59:24 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_command_name:
**		Checks if no argument was passed
**		Duplicates the found char* command name
**		An invalid command is considered a parsing error,
**			it then displays the appropriate error message
**		Returns a negative value for a failed allocation or a parsing error
*/

static int		parsing_command_name (t_ssl *ssl)
{
	// No command passed
	if (ssl->argc == 1)
		return (display_parsing_error(ssl, ERR_NO_ARG, NULL));

	// Parsing command name
	if (ssl->argc >= 2)
	{
		if (ft_strequ(ssl->argv[1], "md5") || ft_strequ(ssl->argv[1], "sha256"))
		{
			if (!(ssl->command_name = ft_strdup(ssl->argv[1])))
				return (-1);
		}
		else
			return (display_parsing_error(ssl, ERR_INVALID_CMD_NAME,
				ssl->argv[1]));
	}

	return (0);
}


/*
**	parsing:
**		Iterates on arguments to find valuable informations
**		Searches for the command name of the choosen algorithm
**		Then flags and files with their own specific parsing
**		Further executions follows a file parsing and at the end
**			all the digests are computed for any argument given
**		No arguments given after the command name makes the program parse stdin
**		Returns a negative value for a failed allocation or an error
*/

int				parsing (t_ssl *ssl)
{
	size_t		argv_i;

	// Parsing command name
	if (parsing_command_name(ssl))
		return (-1);

	// Parsing flags
	argv_i = 2;
	while (argv_i < ssl->argc && !(ssl->flags & 1)
		&& ssl->argv[argv_i][0] == '-')
	{
		if (parsing_flags(ssl, &argv_i))
			return (-1);
		++argv_i;
	}

	// No arguments
	if (argv_i == ssl->argc && !ssl->bool_one_conversion_done
		&& parsing_file(ssl, NULL, FLAG_NO_ARGUMENT))
		return (-1);

	// Parsing files
	while (argv_i < ssl->argc)
	{
		if (parsing_file(ssl, ssl->argv[argv_i], 0))
			return (-1);
		++argv_i;
	}

	return (0);
}
