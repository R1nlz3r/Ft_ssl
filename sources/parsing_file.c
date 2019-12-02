/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:59:47 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/01 19:04:56 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_file:
**		Initializes and sets up a new t_input
**		Handles 'ps' flags
**		Associates flags parsed to this new input
**		Returns a negative value for a failed allocation
*/

int				parsing_file(t_ssl *ssl, char *input_string, int flag)
{
	t_input		*new_input;

	// Init t_input
	if (!(new_input = add_t_input_to_t_list(ssl)))
		return (-1);

	// Touch variables
	if (!flag)
	{
		if (!(new_input->input = ft_strdup(input_string)))
			return (-1);
	}
	else if (flag == FLAG_P)
	{
		if (!(new_input->input = get_stdin()))
			return (-1);
		new_input->flags += FLAG_P;
	}
	else if (flag == FLAG_S)
	{
		if (!(new_input->input = ft_strdup(input_string)))
			return (-1);
		new_input->flags += FLAG_S;
	}
	new_input->flags += ssl->flags;

	return (0);
}
