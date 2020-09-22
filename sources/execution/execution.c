/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 02:14:07 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:13:32 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	command_launcher:
**		Launches the command matching the command identifier stored
**		Returns the value of the choosen algorithm
**			or a negative value if no algorithm matches the identifier
*/

static int		command_launcher(t_ssl *ssl)
{
	int		ret_val;

	if (ssl->cmd->id == CMD_MD5)
		ret_val = md5(ssl);
	else if (ssl->cmd->id == CMD_SHA256)
		ret_val = sha256(ssl);
	else if (ssl->cmd->id == CMD_SHA512)
		ret_val = sha512(ssl);
	else
		ret_val = -1;

	return (ret_val);
}


/*
**	command_preparation:
**		Initializes the t_arg structure values for the given file name
**		Wraps the command algorithm with opening and closing of the file stream
**		Launches the choosen command
**		This function do not return a value
*/

static void		command_preparation(t_ssl *ssl, char *file_name)
{
	if (file_opening(ssl, file_name))
		return ;

	if (command_launcher(ssl))
		return ;

	file_closing(ssl);
}


/*
**	execution:
**		Wraps a command execution by setting up data structures and file streams
**		Creates a new t_arg* structure to store the argument values
**		Removes the "one execution only" flags afterwards
**		This function do not return a value
*/

void			execution(t_ssl *ssl, char *file_name)
{
	t_arg		*arg;

	/* Allocates memory for a t_arg structure */
	if (!(arg = init_t_arg()))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);
	ssl->arg = arg;

	command_preparation(ssl, file_name);

	remove_one_shot_flags(ssl->flags);

	/* Frees up the t_arg strucutre */
	del_t_arg(&ssl->arg);
}
