/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 02:14:07 by mapandel          #+#    #+#             */
/*   Updated: 2020/02/21 04:47:34 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	execution_open_file:
**		Open files by their specified path
**		Replace the input by the content of the file
**		Returns zero for a success,
**			a positive value for a failed opening
**			and a negative value for a failed allocation
*/

static int		execution_open_file(t_ssl *ssl, t_input *input)
{
	if ((input->flags & FLAG_S)
		|| (input->flags & FLAG_P) || (input->flags & FLAG_NO_ARGUMENT))
		input->fd = 0;
	else if ((input->fd = open(input->input, O_RDONLY)) < 0)
	{
		ssl->return_value = 1;
		ft_putstr_fd("ft_ssl: ", 2);
		ft_puterror(ssl->command_name, input->input);
		return (1);
	}

	return (0);
}


/*
**	execution:
**		Transforms the current input agument to the final hash
**		Starts by opening the specified file
**		Prepare the message to a 512 bits mod input
**		Computes and produces the choosen algorithm digest
**		Displays it according to the right combination of flags
**		Returns zero for a successfull conversion,
**			a positive value for a failed one (non blocking)
**			and a negative value for a failed allocation
*/

int				execution(t_ssl *ssl)
{
	int			ret_val;

	// Initialize the file descriptor variable
	if ((ret_val = execution_open_file(ssl, ssl->input)))
		return (ret_val);

	// Message Implement rotations and produce the digest
	if ((ft_strequ(ssl->command_name, "md5") && (ret_val = md5(ssl->input)))
		|| (ft_strequ(ssl->command_name, "sha256")
		&& (ret_val = sha256(ssl->input))))
	{
		ssl->return_value = 1;
		ft_putstr_fd("ft_ssl: ", 2);
		ft_puterror(ssl->command_name, ssl->input->input);
		return (ret_val);
	}

	// Display
	display_hash(ssl->command_name, ssl->input);

	return (0);
}
