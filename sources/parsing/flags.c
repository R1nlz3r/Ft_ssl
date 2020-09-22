/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:58:01 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/22 01:17:55 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


/*
**	end_of_parameters_check:
**		Handles single and double hyphen cases for the given argument
**		Single hypen argument is treated as a file name and stops
**			the flags parsing
**		Double hypen argument stops the flags parsing
**		Returns a positive value if one of this cases match the argument,
**			a nul value otherwise
*/

static int		end_of_parameters_check(t_ssl *ssl, size_t *argv_i,
	size_t arg_len)
{
	// Single hyphen argument
	if (arg_len == 1)
	{
		add_t_flag_mask(ssl->flags, FLAG_END_OF_PARAMETERS, NULL);
		ssl->bool_one_conversion_done = 1;
		execution(ssl, ssl->argv[*argv_i]);
		return (1);
	}
	// Double hyphen argument
	else if (ft_strequ(ssl->argv[*argv_i], "--"))
	{
		add_t_flag_mask(ssl->flags, FLAG_END_OF_PARAMETERS, NULL);
		if (*argv_i == 2)
			ssl->bool_one_conversion_done = 1;
		return (1);
	}

	return (0);
}


/*
**	parsing_flags:
**		Filters a directs a flag search for the given argument and command
**		Command types have different flags available to them
**		This function do not return a value
*/

static void		parsing_flags(t_ssl *ssl, size_t *argv_i, size_t arg_len)
{
	if (end_of_parameters_check(ssl, argv_i, arg_len))
		return ;

	// Filters flags relative to the command type
	if (ssl->cmd->type == CMD_MESSAGE_DIGEST)
		parsing_message_digest_flags(ssl, argv_i, arg_len);
	else if (ssl->cmd->type == CMD_CIPHER)
		parsing_cipher_flags(ssl, argv_i, arg_len);
}

/*
**	searching_flags:
**		Iterates on arguments containing potential flags
**		This function do not return a value
*/

void			searching_flags(t_ssl *ssl, size_t *argv_i)
{
	size_t		arg_len;

	while (*argv_i < ssl->argc
		&& !(ssl->flags->masks_sum & FLAG_END_OF_PARAMETERS)
		&& ssl->argv[*argv_i][0] == '-')
	{
		arg_len = ft_strlen(ssl->argv[*argv_i]);
		parsing_flags(ssl, argv_i, arg_len);

		++*argv_i;
	}
}
