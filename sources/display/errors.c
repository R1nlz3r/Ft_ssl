/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:41:26 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 01:09:41 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	display_undefined_error:
**		Displays the error message relative to errno
**		This function do not return a value
*/

void	display_undefined_error()
{
	ft_puterror("ft_ssl: ", NULL);
}


/*
**	display_file_inaccessible:
**		Displays the appropriate error message relative to an inaccessible file
**		This function do not return a value
*/

void	display_file_inaccessible(t_ssl *ssl)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_puterror(ssl->cmd->name, ssl->arg->file_name);
}


/*
**	display_invalid_opt:
**		Displays the appropriate error message relative to an invalid option
**		This message should be completed with a char* justification
**			for the invalid option
**		This function do not return a value
*/

void	display_invalid_opt(t_ssl *ssl, char *justification)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(ssl->cmd->name, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(justification[0], 2);

	if (ssl->cmd->type == CMD_MESSAGE_DIGEST)
		display_md_algorithm_usage();
}


/*
**	display_opt_without_arg:
**		Displays the appropriate error message relative to an option
**			without argument
**		This message should be completed with a char* justification
**			for the blocking option
**		This function do not return a value
*/

void	display_opt_without_arg(t_ssl *ssl, char *justification)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(ssl->cmd->name, 2);
	ft_putstr_fd(": option requires an argument -- ", 2);
	ft_putchar_fd(justification[0], 2);

	if (ssl->cmd->type == CMD_MESSAGE_DIGEST)
		display_md_algorithm_usage();
}


/*
**	display_invalid_cmd:
**		Displays the appropriate error message relative to an invalid command
**		This message should be completed with a char* justification
**			for the wrong command passed
**		This function do not return a value
*/

void	display_invalid_cmd(char *justification)
{
	ft_putstr_fd("ft_ssl: Error: '", 2);
	ft_putstr_fd(justification, 2);
	ft_putendl_fd("' is an invalid command.\n\nStandard commands:\n\n\
Message Digest commands:\nmd5\nsha256\nsha512\n\nCipher commands:", 2);
}
