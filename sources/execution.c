/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 02:14:07 by mapandel          #+#    #+#             */
/*   Updated: 2020/01/17 01:35:09 by mapandel         ###   ########.fr       */
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

static int		execution_message_preparation(t_ssl *ssl, t_input *input)
{
	char		*new_msg;
	size_t		pad_len;
	size_t		bit_len;
	size_t		i;

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
	if (ft_strequ(ssl->command_name, "sha256"))
	{
		// Little-endian addition of the message length
		i = 0;
		while (i < 8)
		{
			new_msg[input->msg_len + 8 + pad_len - i] = (char)
				(bit_len >> (i * 8));
			++i;
		}
	}
	else
		// Big-endian addition of the message length
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
	if (input->flags & FLAG_S)
	{
		if (!(input->msg = (unsigned char*)ft_strdup(input->input)))
			return (-1);
		input->msg_len = ft_strlen((char*)input->msg);
		return (0);
	}
	else if (input->flags & FLAG_P || input->flags & FLAG_NO_ARGUMENT)
	{
		if (!(input->msg = ft_memalloc(input->input_len)))
			return (-1);
		ft_memcpy(input->msg, input->input, input->input_len);
		input->msg_len = input->input_len;
		return (0);
	}

	// Opening
	if ((fd = open(input->input, O_RDONLY)) < 0)
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

	// Open the file to store the initial message
	if ((ret_val = execution_open_file(ssl, ssl->input)))
		return (ret_val);

	// Prepare the message
	if ((ret_val = execution_message_preparation(ssl, ssl->input)))
		return (ret_val);

	// Implement rotations and produce the digest
	if (ft_strequ(ssl->command_name, "md5") && (ret_val = md5(ssl->input)))
		return (ret_val);
	else if (ft_strequ(ssl->command_name, "sha256")
		&& (ret_val = sha256(ssl->input)))
		return (ret_val);

	// Display
	display_hash(ssl->command_name, ssl->input);

	return (0);
}
