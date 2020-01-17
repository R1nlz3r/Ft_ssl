/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:59:47 by mapandel          #+#    #+#             */
/*   Updated: 2020/01/17 02:01:12 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_file:
**		Initializes and sets up a new t_input
**		Handles 'ps' specific flags
**		Associates the argument and flags parsed to this new input
**		Launches the choosen algorithm afterwards for it
**		Returns a negative value for a failed allocation
*/

int				parsing_file(t_ssl *ssl, char *input_string, int flag)
{
	t_input		*new_input;

	// Init t_input
	if (!(new_input = init_t_input()))
		return (-1);
	ssl->input = new_input;

	// Set the input argument according to the right flags
	if (!flag || flag == FLAG_S)
	{
		if (!(new_input->input = ft_strdup(input_string)))
			return (-1);
	}
	else if (flag == FLAG_P || flag == FLAG_NO_ARGUMENT)
	{
		if (!(new_input->input = get_stdin((ssize_t*)&new_input->input_len)))
			return (-1);
	}
	new_input->flags += flag + ssl->flags;

	// Algorithm execution based on the argument
	if (execution(ssl) == -1)
	{
		del_t_input(&ssl->input);
		return (-1);
	}
	del_t_input(&ssl->input);

	return (0);
}
