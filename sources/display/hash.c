/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:37:01 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 20:44:26 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	display_flag_r_file:
**		Displays the file / string for the 'r' flag case after the digest
**		This function do no return a value
*/

static void		display_flag_r_file(t_ssl *ssl)
{
	if (ssl->flags->masks_sum & FLAG_R && !(ssl->flags->masks_sum & FLAG_P
		|| ssl->flags->masks_sum & FLAG_NO_ARGUMENT
		|| ssl->flags->masks_sum & FLAG_Q))
	{
		if (ssl->flags->masks_sum & FLAG_S)
			ft_printf(" \"%s\"", ssl->arg->file_name);
		else
			ft_printf(" %s", ssl->arg->file_name);
	}
}


/*
**	display_command_and_file:
**		Displays the command name and file / string
**			according to the right combination of options
**		This function do no return a value
*/

static void		display_command_and_file(t_ssl *ssl, char *cmd_uppercase)
{
	if (!(ssl->flags->masks_sum & FLAG_P
		|| ssl->flags->masks_sum & FLAG_NO_ARGUMENT
		|| ssl->flags->masks_sum & FLAG_Q
		|| ssl->flags->masks_sum & FLAG_R))
	{
		if (ssl->flags->masks_sum & FLAG_S)
			ft_printf("%s (\"%s\") = ", cmd_uppercase, ssl->arg->file_name);
		else
			ft_printf("%s (%s) = ", cmd_uppercase, ssl->arg->file_name);
	}
}


/*
**	display_hash:
**		Displays the computed digest of an argument
**			according to the right combination of options
**		This function do no return a value
*/

void			display_hash(t_ssl *ssl)
{
	char	*cmd_uppercase;

	if (!(cmd_uppercase = ft_strtoupper(ssl->cmd->name)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	display_command_and_file(ssl, cmd_uppercase);
	ft_putstr(ssl->arg->digest);
	display_flag_r_file(ssl);
	ft_putchar('\n');

	ft_strdel(&cmd_uppercase);
}
