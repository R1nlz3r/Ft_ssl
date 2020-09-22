/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:38:05 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 21:01:18 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


/*
**	fatal_errors:
**		Displays the appropriate error message corresponding to the given
**			error code constant who should have a fatal error type
**		This message could be completed with a char* justification
**		Frees up memory allocated structures and exits the program as a failure
*/

void			fatal_errors(t_ssl *ssl, int error_code, char *justification)
{
	if (error_code == ERR_NO_ARG)
		display_ft_ssl_usage();
	else if (error_code == ERR_INVALID_CMD_NAME)
		display_invalid_cmd(justification);
	else if (error_code == ERR_OPT_WITHOUT_ARG)
		display_opt_without_arg(ssl, justification);
	else if (error_code == ERR_INVALID_OPT)
		display_invalid_opt(ssl, justification);
	else if (error_code == ERR_MEM_ALLOCATION
		|| error_code == ERR_UNDEFINED)
		display_undefined_error();
	else
		return ;

	exit_failure(ssl);
}


/*
**	non_blockant_errors:
**		Displays the appropriate error message corresponding to the given
**			error code constant who should have a non blockant error type
**		This message could be completed with a char* justification
**		This function do not return a value but sets the return value of
**			the program to a positive value
*/

static void		non_blockant_errors(t_ssl *ssl, int error_code)
{
	if (error_code == ERR_FILE_ACCESS)
		display_file_inaccessible(ssl);

	ssl->return_value = 1;
}


/*
**	filter_error_type:
**		Returns the error type corresponding to the given error code constant
**		This filter divide fatal errors from non-blockant errors,
**			fatal errors should free memory space and exit right away
**			while the program is allowed to continue after a non-blockant error
*/

static int		filter_error_type(int error_code)
{
	if (error_code == ERR_UNDEFINED
		|| error_code == ERR_MEM_ALLOCATION
		|| error_code == ERR_NO_ARG
		|| error_code == ERR_INVALID_CMD_NAME
		|| error_code == ERR_OPT_WITHOUT_ARG
		|| error_code == ERR_INVALID_OPT)
		return (ERR_FATAL);
	else if (error_code == ERR_FILE_ACCESS)
		return (ERR_NON_BLOCKANT);

	return (-1);
}


/*
**	error_handler:
**		Displays the appropriate error message corresponding to the given
**			error code constant
**		This message could be completed with a char* justification
**		Frees up memory allocated structures and exits the program as a failure
**			if the error is considered fatal
**		This function do not return a value otherwise
*/

void			error_handler(t_ssl *ssl, int error_code, char *justification)
{
	if (filter_error_type(error_code) == ERR_NON_BLOCKANT)
		non_blockant_errors(ssl, error_code);
	else
		fatal_errors(ssl, error_code, justification);
}
