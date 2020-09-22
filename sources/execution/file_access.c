/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 15:14:36 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:13:15 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	file_closing:
**		Closes the stored file descriptor
**		Returns zero for on success or a positive value for a failed file access
*/

void	file_closing(t_ssl *ssl)
{
	if (!(ssl->flags->masks_sum & FLAG_S)
		&& !(ssl->flags->masks_sum & FLAG_P)
		&& !(ssl->flags->masks_sum & FLAG_NO_ARGUMENT) && close(ssl->arg->fd))
		error_handler(ssl, ERR_FILE_ACCESS, NULL);
}


/*
**	file_reading:
**		Reads data for a size_t length from the stored file descriptor
**		The length is defined regarding the command algorithm requirement
**		Returns zero for on success or a positive value for a failed file access
*/

int		file_reading(t_ssl *ssl)
{
	ssl->arg->msg_len = 0;
	ssl->arg->msg = get_file_segment(ssl->arg->fd, ssl->cmd->step,
		(ssize_t*)&ssl->arg->msg_len);
	ssl->arg->msg_total_len += ssl->arg->msg_len;

	if ((ssize_t)ssl->arg->msg_len == -1)
	{
		error_handler(ssl, ERR_FILE_ACCESS, NULL);
		return (1);
	}

	if (!ssl->arg->msg_len)
		ft_strdel((char**)&ssl->arg->msg);

	return (0);
}


/*
**	file_opening:
**		Stores the char* file name to the argument structure
**		Opens the file and initializes the file descriptor variable
**		Returns zero for on success or a positive value for a failed file access
*/

int		file_opening(t_ssl *ssl, char *file_name)
{
	/* File name initialization */
	if (file_name && !(ssl->arg->file_name = ft_strdup(file_name)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	/* File descriptor initialization */
	if ((ssl->flags->masks_sum & FLAG_S)
		|| (ssl->flags->masks_sum & FLAG_P)
		|| (ssl->flags->masks_sum & FLAG_NO_ARGUMENT))
		ssl->arg->fd = 0;
	else if ((ssl->arg->fd = open(ssl->arg->file_name, O_RDONLY)) < 0)
	{
		error_handler(ssl, ERR_FILE_ACCESS, NULL);
		return (1);
	}

	return (0);
}
