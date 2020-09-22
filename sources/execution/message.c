/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:43:32 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:12:47 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	message_set_flag_s:
**		Sets the message from the string parameter linked to the 's' flag
**		This function do not return a value
*/

void			set_flag_s_message(t_ssl *ssl)
{
	/* The file name is set to be printed out with the digest */
	if (!(ssl->arg->file_name = ft_strdup(ssl->flags->s)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	/* The message will be iterated during the execution and not freed up */
	ssl->arg->msg = (unsigned char*)ssl->flags->s;
	ssl->arg->msg_total_len = ft_strlen((char*)ssl->arg->msg);
	ssl->arg->msg_len = ssl->arg->msg_total_len;
}


/*
** message_dump:
**		Frees up the portion of the message read
**			unless under an 's' flag as we iterate on the full message
**		Dumps the static padding buffer as the end is reached
**		Returns a positive value if the buffer is dumped, a nul value otherwise
*/

int				message_dump(t_ssl *ssl)
{
	/* Frees up the portion of the message read
		but not under an 's' flag as we iterate on the message */
	if (!(ssl->flags->masks_sum & FLAG_S))
		ft_strdel((char**)&ssl->arg->msg);

	/* Dumps the static string */
	if (ssl->arg->msg_len < ssl->cmd->step - 9)
	{
		buffer_handler(ssl, 1);
		return (1);
	}

	return (0);
}


/*
**	message_increment:
**		Increments on the existing message for a given command step
**		Reduces the length of the message until nul
**		This function do not return a value
*/

static void		message_increment(t_ssl *ssl)
{
	if (ssl->arg->msg_len > ssl->cmd->step)
	{
		ssl->arg->msg += ssl->cmd->step;
		ssl->arg->msg_len -= ssl->cmd->step;
	}
	else
		ssl->arg->msg_len = 0;
}


/*
**	message_obtention:
**		Sets the portion of the message required for the command algorithm
**			computations
**		Increments on the existing message or sets it up if not present
**			in case of an 's' flag
**		Reads on the file
**		Pads the end of the message in regards of the command
**		Returns zero for on success or a positive value for a failed file access
*/

int 			message_obtention(t_ssl *ssl)
{
	/* Iterates on the message or reads on the file descriptor */
	if (ssl->flags->masks_sum & FLAG_S && ssl->arg->msg)
		message_increment(ssl);
	else if (ssl->flags->masks_sum & FLAG_S)
		set_flag_s_message(ssl);
	else if (file_reading(ssl))
		return (1);

	/* Specific 'p' flag logic */
	if (ssl->flags->masks_sum & FLAG_P)
		write(1, ssl->arg->msg, ssl->arg->msg_len);

	/* Pads the message and handles the buffer until the next rotation */
	if (ssl->arg->msg_len < ssl->cmd->step)
		buffer_handler(ssl, 0);

	return (0);
}
