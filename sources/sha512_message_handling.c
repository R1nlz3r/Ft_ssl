/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_message_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:22:39 by mapandel          #+#    #+#             */
/*   Updated: 2020/07/17 12:44:25 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	sha512_message_buffer_preparation:
**
*/

static unsigned char		*sha512_message_buffer_preparation(t_input *input,
	unsigned char *static_buffer)
{
	size_t					pad_len;
	size_t					bit_len;
	size_t					i;

	pad_len = 128 - ((input->msg_len + 9) % 128);
	if (pad_len == 128)
		pad_len = 0;

	if (!(static_buffer = (unsigned char*)ft_strnew(input->msg_len
		+ (size_t)9 + pad_len)))
		return (NULL);
	ft_memcpy(static_buffer, input->msg, input->msg_len);

	((char*)static_buffer)[input->msg_len] = -128;

	bit_len = input->msg_total_len * 8;
	i = 0;
	while (i < 8)
	{
		static_buffer[input->msg_len + 8 + pad_len - i] =
			(unsigned char)(bit_len >> (i * 8));
		++i;
	}

	return (static_buffer);
}


/*
**	sha512_message_buffer_handling:
**
*/

static int		sha512_message_buffer_handling(t_input *input, int bool_dump)
{
	static unsigned char	*static_buffer = NULL;

	if (bool_dump)
	{
		ft_strdel((char**)&static_buffer);
		static_buffer = NULL;
	}
	else if (!static_buffer)
	{
		static_buffer = sha512_message_buffer_preparation(input, static_buffer);
		if (!(input->flags & FLAG_S))
			ft_strdel((char**)&input->msg);
		input->msg = ft_memdup(static_buffer, 128);
	}
	else
	{
		if (input->msg_len < 119)
			input->msg_len = 0;
		else
			input->msg_len -= 119;
		ft_strdel((char**)&input->msg);
		input->msg = ft_memdup(static_buffer + 128, 128);
	}

	return (0);
}


/*
**	sha512_message_obtaining:
**
*/

int 			sha512_message_obtaining(t_input *input)
{
	if ((input->flags & FLAG_S))
	{
		if (!(input->msg))
		{
			input->msg_len = input->msg_total_len;
			input->msg = (unsigned char*)input->input;
		}
		else
		{
			if (input->msg_len > 128 && (input->msg_len -= 128))
				input->msg += 128;
			else
				input->msg_len = 0;
		}
	}
	else
	{
		input->msg_len = 0;
		input->msg = get_file_segment(input->fd, 128,
			(ssize_t*)&input->msg_len);
		input->msg_total_len += input->msg_len;
		if ((ssize_t)input->msg_len == -1)
			return (1);
		else if (!input->msg_len)
			ft_strdel((char**)&input->msg);
	}

	if (input->flags & FLAG_P)
		write(1, input->msg, input->msg_len);

	if (input->msg_len < 128)
		return (sha512_message_buffer_handling(input, 0));

	return (0);
}


/*
**	sha512_message_dumping:
**
*/

int				sha512_message_dumping(t_input *input)
{
	if (!(input->flags & FLAG_S))
		ft_strdel((char**)&input->msg);

	// Dumps the static string
	if (input->msg_len < 119)
	{
		sha512_message_buffer_handling(input, 1);
		return (1);
	}

	return (0);
}