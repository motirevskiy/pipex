/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgretche <cgretche@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:37:32 by cgretche          #+#    #+#             */
/*   Updated: 2022/04/05 12:12:38 by cgretche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_do_cmd(char *av, t_struct *s)
{
	int	i;

	i = -1;
	execve(ft_split(av, ' ')[0], ft_split(av, ' '), s->env);
	while (ft_split(s->env[s->n] + 5, ':')[++i])
		execve(ft_strjoin(ft_strjoin(ft_split(s->env[s->n] + 5, ':')[i], "/"),
				ft_split(av, ' ')[0]), ft_split(av, ' '), s->env);
	exit(write(2, "error: bad path\n", 16));
}

void	main_proc(t_struct *s)
{
	int	fd;

	fd = open(s->av[4], O_WRONLY | O_TRUNC | O_CREAT, 422);
	if (fd == -1)
		exit(write(1, "error: open write file\n", 24));
	dup2(s->pipe[0], 0);
	dup2(fd, 1);
	close(fd);
	close(s->pipe[0]);
	close(s->pipe[1]);
	ft_do_cmd(s->av[s->ac - 2], s);
}

void	doch_proc(t_struct *s)
{
	int	fd;

	if (ft_strcmp(s->av[1], s->av[4]) == 0)
		fd = open(s->av[1], O_RDONLY | O_TRUNC);
	else
		fd = open(s->av[1], O_RDONLY);
	if (fd == -1)
		exit(write(1, "error: open read file\n", 23));
	dup2(fd, 0);
	dup2(s->pipe[1], 1);
	close(fd);
	close(s->pipe[0]);
	close(s->pipe[1]);
	ft_do_cmd(s->av[2], s);
}

int	main(int ac, char **av, char **env)
{
	t_struct	s;
	int			pid;

	if (ac != 5)
		return (write(1, "Agruments error\n", 17));
	s.ac = ac;
	s.av = av;
	s.env = env;
	while (ft_strnstr(env[s.n], "PATH=", 5) == NULL)
		if (env[++s.n] == NULL)
			exit(write(1, "error: unset path\n", 18));
	pipe(s.pipe);
	pid = fork();
	if (pid == 0)
		doch_proc(&s);
	main_proc(&s);
}
