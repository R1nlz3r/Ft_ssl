/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:24:03 by mapandel          #+#    #+#             */
/*   Updated: 2020/01/08 13:45:29 by mapandel         ###   ########.fr       */
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
		ft_printf("%s: Error: '%s' is an invalid command.\n\n\
Standard commands:\n\n\
Message Digest commands:\n\
md5\n\
sha256\n\n\
Cipher commands:\n", ssl->argv[0], justification);
	}
	else if (error_code == ERR_OPT_WITHOUT_ARG)
	{
		ft_printf("%s: %s: option requires an argument -- %c\n\
usage: ft_ssl command [-pqr] [-s string] [files ...]\n",
			ssl->argv[0], ssl->command_name, justification[0]);
	}
	else if (error_code == ERR_INVALID_OPT)
	{
		ft_printf("%s: %s: illegal option -- %c\n\
usage: ft_ssl command [-pqr] [-s string] [files ...]\n",
			ssl->argv[0], ssl->command_name, justification[0]);
	}

	return (-1);
}


/*
**	display_hash:
**		Outputs a computed digest of an input
**			according to the right combination of options
**		This function do no return a value
*/

void	display_hash(char *command_name, t_input *input)
{
	char	*cmd_uppercase;

	cmd_uppercase = ft_strtoupper(command_name);

	if (input->flags & FLAG_P)
		write(1, input->input, input->input_len);
	if (!(input->flags & FLAG_P) && !(input->flags & FLAG_Q)
		&& !(input->flags & FLAG_R))
	{
		if (input->flags & FLAG_S)
			ft_printf("%s (\"%s\") = ", cmd_uppercase, input->input);
		else
			ft_printf("%s (%s) = ", cmd_uppercase, input->input);
	}
	ft_putstr(input->digest);
	if (input->flags & FLAG_R && !(input->flags & FLAG_Q))
	{
		if (input->flags & FLAG_S)
			ft_printf(" \"%s\"", input->input);
		else
			ft_printf(" %s", input->input);
	}
	ft_putchar('\n');

	ft_strdel(&cmd_uppercase);
}
