/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 02:14:07 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/02 02:21:36 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	execution_message_preparation:
**		Prepares the input message before the computations
**		Adds a "1" bit bias to the message
**		Pads the message with zeros
**		Then adds the initial message length for a 64 bits length
**		The total message length should be 512 bits modulo
**		Returns a negative value for a failed allocation
*/

static int		execution_message_preparation(t_input *input)
{
	char		*new_msg;
	size_t		len;
	size_t		pad_len;
	size_t		bit_len;

	len = ft_strlen(input->input);

	// Number of characters to pad
	pad_len = 64 - ((len + 9) % 64);
	if (pad_len == 64)
		pad_len = 0;

	// Copy of the message
	if (!(new_msg = ft_strnew(len + 9 + pad_len)))
		return (-1);
	ft_strcpy(new_msg, input->input);

	// Adding the bias character
	new_msg[len] = -128;

	// Adding the message length in bits
	bit_len = len * 8;
	ft_memcpy(new_msg + len + 1 + pad_len, &bit_len, 8);

	// Replace input by the prepared message
	ft_strdel(&input->input);
	input->input = new_msg;

	return (0);
}


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
	int		fd;

	// Filter flags who do not require a file opening
	if (input->flags & FLAG_P || input->flags & FLAG_S)
		return (0);

	// Opening
	if ((fd = open(input->input, O_RDONLY | O_SYMLINK)) < 0)
	{
		ssl->return_value = 1;
		return (1);
	}

	// Replace the input by the content of the file
	ft_strdel(&input->input);
	if (!(input->input = get_file(fd)))
		return (-1);

	return (0);
}


/*
**	execution:
**		Transforms the current input to the final digest
**		Starts by opening the specified file
**		Prepare the message to a 512 bits mod input
**		...
**		Returns zero for a successfull conversion,
**			a positive value for a failed one
**			and a negative value for a failed allocation
*/

int				execution(t_ssl *ssl)
{
	t_input		*input;
	int			ret_val;

	input = ssl->inputs->content;

	// Open the file to store the initial message
	if ((ret_val = execution_open_file(ssl, input)))
		return (ret_val);

	// Prepare the message
	if ((ret_val = execution_message_preparation(input)))
		return (ret_val);

	// Implement rotations

	// Concatenate the digest

	// Display

	return (0);
}
