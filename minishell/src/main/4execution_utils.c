/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4execution_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:39:55 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/27 09:45:22 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	safe_close_fd(int fd, int fd2)
{
	if (!isatty(fd))
		close(fd);
	if (!isatty(fd2))
		close(fd2);
}

void	check_dup2(int in, int out)
{
	if (!isatty(in))
	{
		dup2(in, STDIN_FILENO);
	}
	if (!isatty(out))
		dup2(out, STDOUT_FILENO);
}

void	cut_wait(void)
{
	write(1, "\n", 1);
}
