/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:51:18 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/10 18:14:04 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// verifie que le fichier en argumenet se termine bien par l extension .ber
int	check_args(int argc, char **argv)
{
	int		len;
	char	*ext;

	if (argc != 2)
	{
		print_error("Number of arguments\n");
		return (0);
	}
	len = strlen(argv[1]);
	if (len < 5)
	{
		print_error("File name too short");
		return (0);
	}
	ext = argv[1] + len - 4;
	if (strcmp(ext, ".ber"))
	{
		print_error("File extension\n");
		return (0);
	}
	return (1);
}

void	print_error(const char *message)
{
	ft_printf("%s\n", message);
}
