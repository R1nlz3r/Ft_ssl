/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 16:11:26 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/22 01:28:43 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_flag_p:
**		Sets up an 'p' flag
**		Launches an execution of the command reading from STDIN
**		This function do not return a value
*/

static void		parsing_flag_p(t_ssl *ssl)
{
	ssl->bool_one_conversion_done = 1;
	add_t_flag_mask(ssl->flags, FLAG_P, NULL);

	execution(ssl, NULL);
}


/*
**	parsing_flag_s:
**		Sets up an 's' flag with its following string parameter
**		A missing string is considered a parsing error,
**			it then displays the appropriate error message
**		Launches an execution of the command with the string found
**		This function do not return a value
*/

static void		parsing_flag_s(t_ssl *ssl, size_t *argv_i, size_t *argv_j,
	size_t arg_len)
{
	ssl->bool_one_conversion_done = 1;

	if (*argv_j + 1 < arg_len)
		add_t_flag_mask(ssl->flags, FLAG_S, &ssl->argv[*argv_i][++*argv_j]);
	else if (*argv_i + 1 < ssl->argc)
		add_t_flag_mask(ssl->flags, FLAG_S, ssl->argv[++*argv_i]);
	else
		error_handler(ssl, ERR_OPT_WITHOUT_ARG, &ssl->argv[*argv_i][*argv_j]);

	execution(ssl, NULL);
}

/*
**	parsing_message_digest_flags:
**		Searches for potential flags linked to a message digest command
**			on a given argument
**		Saves 'qr' flags for display purposes
**		Triggers 'ps' flags specific message digest executions
**		An invalid option is considered a parsing error,
**			it then displays the appropriate error message
**		This function do not return a value
*/

void			parsing_message_digest_flags(t_ssl *ssl, size_t *argv_i,
	size_t arg_len)
{
	size_t		argv_j;

	argv_j = 1;
	while (argv_j < arg_len)
	{
		if (ssl->argv[*argv_i][argv_j] == 'p')
			parsing_flag_p(ssl);
		else if (ssl->argv[*argv_i][argv_j] == 'q')
			add_t_flag_mask(ssl->flags, FLAG_Q, NULL);
		else if (ssl->argv[*argv_i][argv_j] == 'r')
			add_t_flag_mask(ssl->flags, FLAG_R, NULL);
		else if (ssl->argv[*argv_i][argv_j] == 's')
		{
			parsing_flag_s(ssl, argv_i, &argv_j, arg_len);
			return ;
		}
		else
			error_handler(ssl, ERR_INVALID_OPT, &ssl->argv[*argv_i][argv_j]);

		++argv_j;
	}
}
