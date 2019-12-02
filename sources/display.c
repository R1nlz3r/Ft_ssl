/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:24:03 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/01 03:06:10 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	display_parsing_error:
**		Displays the appropriate error message for an error code constant
**		This message could be completed with a char* justification
**		Sets up the return value for the command
**		Returns a negative value all the time
*/

int		display_parsing_error(t_ssl *ssl, int error_code, char *justification)
{
	if (error_code == ERR_NO_ARG)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (error_code == ERR_INVALID_CMD_NAME)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n\
Standard commands:\n\n\
Message Digest commands:\n\
md5\n\
sha256\n\n\
Cipher commands:\n", justification);
	}
	else if (error_code == ERR_OPT_WITHOUT_ARG)
	{
		ft_printf("ft_ssl: %s: option requires an argument -- %c\n\
usage: md5 [-pqr] [-s string] [files ...]\n",
			ssl->command_name, justification[0]);
	}
	else if (error_code == ERR_INVALID_OPT)
	{
		ft_printf("ft_ssl: %s: illegal option -- %c\n\
usage: ft_ssl [command] [-pqr] [-s string] [files ...]\n",
			ssl->command_name, justification[0]);
	}

	return (-1);
}
