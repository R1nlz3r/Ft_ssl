/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 02:22:20 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/09 23:50:13 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	infinite_loop:
**		Endless loop with no return value
**			to perform the `leaks` command in parallel
*/

void	infinite_loop(t_ssl **ssl)
{
	if (!ssl)
		return ;
	*ssl = NULL;
	while (1) {}
}


/*
**	display_t_input:
**		Displays all the values of a t_input
*/

void	display_t_input(t_input *input)
{
	ft_printf("Flags: %3d \033[34m|\033[0m\
 Message Length: %5d \033[34m|\033[0m\
 Input: %20s \033[34m|\033[0m\
 Digest: %20s\n",
		input->flags, input->msg_len, input->input, input->digest);
}


/*
**	display_t_ssl:
**		Displays all the values for the data container of this project
*/

void	display_t_ssl(t_ssl *ssl)
{
	ft_putendl("Ssl:");
	ft_printf("Command name: %8s \033[34m|\033[0m\
 Flags: %2d\n\
Return value: %8d \033[34m|\033[0m\
 Argc: %3d",
		ssl->command_name, ssl->flags, ssl->return_value, ssl->argc);
	// ft_putendl("\n\nInputs:");
	// display_input(ssl->input);
}
