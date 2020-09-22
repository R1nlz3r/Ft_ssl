/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 16:13:41 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/22 01:48:58 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_flag_o:
**		Sets up an 'i' flag with its following string parameter
**		A missing string is considered a parsing error,
**			it then displays the appropriate error message
**		This function do not return a value
*/

static void		parsing_flag_o(t_ssl *ssl, size_t *argv_i, size_t *argv_j,
	size_t len)
{
	ssl->bool_one_conversion_done = 1;

	if (*argv_j + 1 < len)
		add_t_flag_mask(ssl->flags, FLAG_O, &ssl->argv[*argv_i][++*argv_j]);
	else if (*argv_i + 1 < ssl->argc)
		add_t_flag_mask(ssl->flags, FLAG_O, ssl->argv[++*argv_i]);
	else
		error_handler(ssl, ERR_OPT_WITHOUT_ARG, &ssl->argv[*argv_i][*argv_j]);
}


/*
**	parsing_flag_i:
**		Sets up an 'i' flag with its following string parameter
**		A missing string is considered a parsing error,
**			it then displays the appropriate error message
**		This function do not return a value
*/

static void		parsing_flag_i(t_ssl *ssl, size_t *argv_i, size_t *argv_j,
	size_t len)
{
	ssl->bool_one_conversion_done = 1;

	if (*argv_j + 1 < len)
		add_t_flag_mask(ssl->flags, FLAG_I, &ssl->argv[*argv_i][++*argv_j]);
	else if (*argv_i + 1 < ssl->argc)
		add_t_flag_mask(ssl->flags, FLAG_I, ssl->argv[++*argv_i]);
	else
		error_handler(ssl, ERR_OPT_WITHOUT_ARG, &ssl->argv[*argv_i][*argv_j]);
}


/*
**	parsing_cipher_flags:
**		Searches for potential flags linked to a cipher command
**			on a given argument
**		Saves 'deio' flags for execution purposes
**		An invalid option is considered a parsing error,
**			it then displays the appropriate error message
**		This function do not return a value
*/

void			parsing_cipher_flags(t_ssl *ssl, size_t *argv_i, size_t arg_len)
{
	size_t		argv_j;

	argv_j = 1;
	while (argv_j < arg_len)
	{
		if (ssl->argv[*argv_i][argv_j] == 'd')
			add_t_flag_mask(ssl->flags, FLAG_D, NULL);
		else if (ssl->argv[*argv_i][argv_j] == 'e')
			add_t_flag_mask(ssl->flags, FLAG_E, NULL);
		else if (ssl->argv[*argv_i][argv_j] == 'i')
		{
			parsing_flag_i(ssl, argv_i, &argv_j, arg_len);
			return ;
		}
		else if (ssl->argv[*argv_i][argv_j] == 'o')
		{
			parsing_flag_o(ssl, argv_i, &argv_j, arg_len);
			return ;
		}
		else
			error_handler(ssl, ERR_INVALID_OPT, &ssl->argv[*argv_i][argv_j]);

		++argv_j;
	}
}
