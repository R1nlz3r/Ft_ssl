/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 01:28:47 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/24 00:42:43 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_error_display:
**		***
*/

static int		parsing_error_display(t_ssl *ssl, int error_code,
	char *justification) {
	// No argument passed
	if (error_code == ERR_NO_ARG)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");

	// Invalid command name
	else if (error_code == ERR_INVALID_CMD_NAME) {
		ft_printf("\
ft_ssl: Error: '%s' is an invalid command.\n\n\
Standard commands:\n\n\
Message Digest commands:\n\
md5\n\
sha256\n\n\
Cipher commands:\n",
			justification);
	}

	// Option require an argument
	// else if (error_code == ERR_OPT_WITHOUT_ARG) {
	// 	ft_printf("md5: option requires an argument -- %c\n\
	// 		usage: md5 [-pqrtx] [-s string] [files ...]\n",
	// 		justification[0]);
	// }

	// invalid option
	else if (error_code == ERR_INVALID_OPT) {
		ft_printf("md5: illegal option -- %c\n\
usage: ft_ssl [command] [-pqr] [-s string] [files ...]\n",
			justification[0]);
	}

	ssl->return_value = -1;
	return (-1);
}


/*
**	parsing_files:
**		***
*/

static int		parsing_files(t_ssl *ssl, int *argv_i, int flag) {
	t_list		*new_node;
	t_input		*new_input;

	// Init t_input
	if (!(new_input = init_t_input()))
		return (-1);
	if (!(new_node = ft_lstnew(NULL, 0)))
		return (-1);
	new_node->content = new_input;
	ft_lstadd(&ssl->inputs, new_node);

	// Touch variables
	if (!flag)
	{
		if (!(new_input->input = ft_strdup(ssl->argv[*argv_i])))
			return (-1);
	}
	else if (flag == FLAG_P)
	{
		if (get_next_char(1, &new_input->input, EOF) == -1)
			return (-1);
		new_input->flags += FLAG_P;
	}
	new_input->flags += ssl->flags;

	return (0);
}


/*
**	parsing_flags:
**		***
*/

static int		parsing_flags(t_ssl *ssl, int *argv_i) {
	size_t		argv_j;
	size_t		len;

	len = ft_strlen(ssl->argv[*argv_i]);

	// Stops parameters parsing
	if (len == 1)
	{
		ssl->flags += FLAG_END_OF_PARAMETERS;
		if (parsing_files(ssl, argv_i, 0) == -1)
			return (-1);
		return (0);
	}
	else if (ft_strequ(ssl->argv[*argv_i], "--"))
	{
		ssl->flags += FLAG_END_OF_PARAMETERS;
		return (0);
	}

	// Iterates on potential flags
	argv_j = 1;
	while (argv_j < len)
	{
		if (ssl->argv[*argv_i][argv_j] == 'p')
		{
			if (parsing_files(ssl, 0, FLAG_P) == -1)
				return (-1);
			// compute digest
			// display digest
		}
		else if (ssl->argv[*argv_i][argv_j] == 'q')
		{
			if (!(ssl->flags & FLAG_Q))
				ssl->flags += FLAG_Q;
		}
		else if (ssl->argv[*argv_i][argv_j] == 'r')
		{
			if (!(ssl->flags & FLAG_R))
				ssl->flags += FLAG_R;
		}
		// else if (ssl->argv[*argv_i][argv_j] == 's')
		// {
		//		initialize and set a FLAG_S mask on the input node
		//		parse the rest of this string or the next argv parameter
		//			input
		// }
		else
			return (parsing_error_display(ssl, ERR_INVALID_OPT,
				&ssl->argv[*argv_i][argv_j]));
		++argv_j;
	}

	return (0);
}


/*
**	parsing_command_name:
**		Checks if no argument was passed
**		Duplicates the found char* command name
**		Returns a negative value for a failed allocation or a parsing error
*/

static int		parsing_command_name (t_ssl *ssl) {
	// No argument passed
	if (ssl->argc == 1)
		return (parsing_error_display(ssl, ERR_NO_ARG, NULL));

	// Parsing command name
	if (ssl->argc >= 2)
	{
		if (ft_strequ(ssl->argv[1], "md5") || ft_strequ(ssl->argv[1], "sha256"))
		{
			if (!(ssl->command_name = ft_strdup(ssl->argv[1])))
			{
				ssl->return_value = -1;
				return (-1);
			}
		}
		else
			return (parsing_error_display(ssl, ERR_INVALID_CMD_NAME,
				ssl->argv[1]));
	}

	return (0);
}


/*
**	parsing:
**		Iterates on argv arguments to find valuable informations
**		Searches for the command name char* first: "md5" or "sh256"
**		Then flags and finaly files with their own specific parsing
**		Returns a negative value for a failed allocation or an error
*/

int				parsing (t_ssl *ssl) {
	int		argv_i;

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

	// Parsing files
	while (argv_i < ssl->argc)
	{
		if (parsing_files(ssl, &argv_i, 0))
			return (-1);
		++argv_i;
	}

	return (0);
}
