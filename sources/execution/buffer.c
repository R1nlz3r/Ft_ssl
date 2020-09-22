/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:35:06 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:15:37 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	buffer_increment:
**		Increments on the existing buffer for a given command step
**		Reduces the length of the message until nul
**		This function do not return a value
*/

static void				buffer_increment(t_ssl *ssl,
	unsigned char *static_buffer)
{
	if (ssl->arg->msg_len < ssl->cmd->step - 9)
		ssl->arg->msg_len = 0;
	else
		ssl->arg->msg_len -= ssl->cmd->step - 9;

	ft_strdel((char**)&ssl->arg->msg);

	if (!(ssl->arg->msg = ft_memdup(static_buffer + ssl->cmd->step,
		ssl->cmd->step)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);
}


/*
**	byte_length_addition:
**		Computes and adds the byte length to the buffer
**		This byte length is added as a little or big endian depending on
**			the command
**		This function do not return a value
*/

static void				byte_length_addition(t_ssl *ssl,
	unsigned char *static_buffer, size_t pad_len)
{
	size_t		bit_len;
	size_t		i;

	bit_len = ssl->arg->msg_total_len * 8;

	/* Little endian */
	if (ssl->cmd->id == CMD_MD5)
		ft_memcpy(static_buffer + ssl->arg->msg_len + 1 + pad_len,
			&bit_len, 8);
	/* Big endian */
	else
	{
		i = 0;
		while (i < 8)
		{
			static_buffer[ssl->arg->msg_len + 8 + pad_len - i] =
				(unsigned char)(bit_len >> (i * 8));
			++i;
		}
	}
}



/*
**	buffer_padding:
**		Pads the message with zeros
**		Adds a single bit to '1' and the byte length
**		Returns the buffer
*/

static unsigned char	*buffer_padding(t_ssl *ssl,
	unsigned char *static_buffer)
{
	size_t		pad_len;

	/* Computes the number of characters to pad */
	pad_len = ssl->cmd->step - ((ssl->arg->msg_len + 9) % ssl->cmd->step);
	if (pad_len == ssl->cmd->step)
		pad_len = 0;

	/* Allocates the needed memory space and copies the end of the message */
	if (!(static_buffer = (unsigned char*)ft_strnew(ssl->arg->msg_len +
		(size_t)9 + pad_len)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);
	ft_memcpy(static_buffer, ssl->arg->msg, ssl->arg->msg_len);

	/* Adds a single bit to '1' */
	((char*)static_buffer)[ssl->arg->msg_len] = -128;

	/* Adds the byte length to the buffer as little endian or big endian */
	byte_length_addition(ssl, static_buffer, pad_len);

	return (static_buffer);
}


/*
**	buffer_creation:
**		Creates the padding buffer to replace the message
**		This function do not return a value
*/

static void				buffer_creation(t_ssl *ssl,
	unsigned char **static_buffer)
{
	*static_buffer = buffer_padding(ssl, *static_buffer);

	if (!(ssl->flags->masks_sum & FLAG_S))
		ft_strdel((char**)&ssl->arg->msg);

	if (!(ssl->arg->msg = ft_memdup(*static_buffer, ssl->cmd->step)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);
}


/*
**	buffer_handler:
**		Handles the gestion of the padding buffer
**		Creates, increments or dumps it
**		This function do not return a value
*/

void					buffer_handler(t_ssl *ssl, int bool_dump)
{
	static unsigned char	*static_buffer = NULL;

	/* Destroy the buffer */
	if (bool_dump)
		ft_strdel((char**)&static_buffer);
	/* Creates the buffer */
	else if (!static_buffer)
		buffer_creation(ssl, &static_buffer);
	/* Iterates on the second part of the buffer */
	else
		buffer_increment(ssl, static_buffer);
}
