/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 02:14:07 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/09 01:55:29 by mapandel         ###   ########.fr       */
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
	size_t		pad_len;
	size_t		bit_len;

	// Number of characters to pad
	pad_len = 64 - ((input->msg_len + 9) % 64);
	if (pad_len == 64)
		pad_len = 0;

	// Copy of the message
	if (!(new_msg = ft_strnew(input->msg_len + 9 + pad_len)))
		return (-1);
	ft_memcpy(new_msg, input->msg, input->msg_len);

	// Adding the bias character
	new_msg[input->msg_len] = -128;

	// Adding the message length in bits
	bit_len = input->msg_len * 8;
	ft_memcpy(new_msg + input->msg_len + 1 + pad_len, &bit_len, 8);

	// Set the prepared message
	ft_strdel((char**)&input->msg);
	input->msg = (unsigned char*)new_msg;
	input->msg_len += 9 + pad_len;

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
	{
		if (!(input->msg = (unsigned char*)ft_strdup(input->input)))
			return (-1);
		input->msg_len = ft_strlen((char*)input->msg);
		return (0);
	}

	// Opening
	if ((fd = open(input->input, O_RDONLY | O_SYMLINK)) < 0)
	{
		ssl->return_value = 1;
		ft_puterror(ssl->argv[0], input->input);
		return (1);
	}

	// Replace the input by the content of the file
	input->msg = (unsigned char*)get_file(fd, (ssize_t*)&input->msg_len);
	if (!input->msg || (ssize_t)input->msg_len == -1)
	{
		ssl->return_value = 1;
		ft_puterror(ssl->argv[0], input->input);
		if (!input->msg)
			return (-1);
		return (1);
	}
	return (0);
}


/*
**	execution:
**		Transforms the current input to the final digest
**		Starts by opening the specified file
**		Prepare the message to a 512 bits mod input
**		Computes and produces the choosen algorithm digest
**		..
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

	// Implement rotations and produce the digest
	if (ft_strequ(ssl->command_name, "md5") && (ret_val = md5(input)))
		return (ret_val);

	// Display
	ft_putendl(input->digest);

	return (0);
}
