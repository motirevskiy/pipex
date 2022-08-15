/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgretche <cgretche@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:37:30 by cgretche          #+#    #+#             */
/*   Updated: 2022/03/29 15:36:54 by cgretche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_struct
{
	int		n;
	int		pipe[2];
	int		ac;
	char	**av;
	char	**env;
}	t_struct;

int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strnstr(const char *h, const char *n, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
#endif