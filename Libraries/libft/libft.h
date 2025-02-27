/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:36:55 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/18 04:18:54 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../gnl/get_next_line.h"
# include "../ft_printf/ft_printf.h"

void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
void	*ft_memset(void *s, int c, size_t n);

#endif
