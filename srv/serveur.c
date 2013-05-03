/*
** serveur.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<arpa/inet.h>
#include	<netinet/in.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	"ftp.h"


void	launch_client(client_ftp_t *client_ftp, ftp_t *ftp)
{
  char	*line;
  int	i;
  cmd_t			tab[] =
    {
      {"USER", 4, fct_user},
      {"PASS", 4, fct_pass},
      {"SYST", 4, fct_syst},
      {"FEAT", 4, fct_feat},
      {"PWD", 3, fct_pwd},
      {"EPSV", 4, fct_epsv},
      {"PASV", 4, fct_pasv},
      {"LIST", 4, fct_ls},
      {"CWD", 3, fct_cd},
      {"RETR", 4, fct_retr},
      {"STOR", 4, fct_stor},
      {"TYPE", 4, fct_type},
      {"QUIT", 4, fct_quit},
      {0, 0, 0}
    };

  xsend(client_ftp->cs, WELCOME, strlen(WELCOME), 0);
  init_pwd(client_ftp);
  while ((line = get_next_line(client_ftp->cs)) != 0)
    {
      if (line[strlen(line) - 1] == '\r')
	line[strlen(line) - 1] = '\0';
      printf("[%s]\n", line);
      for (i = 0; tab[i].cmd != 0; i++)
	{
	  if (strncmp(tab[i].cmd, line, tab[i].size) == 0)
	    {
	      tab[i].f(line, client_ftp, ftp);
	      break;
	    }
	}
      free(line);
    }
}

void	init_server(ftp_t *ftp, char *av)
{
  if ((ftp->s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Problem in socket open\n");
      exit(1);
    }
  ftp->sin.sin_family = AF_INET;
  ftp->sin.sin_port = htons(atoi(av));
  ftp->sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(ftp->s, (struct sockaddr *) &(ftp->sin), sizeof(ftp->sin)) == -1)
    {
      close(ftp->s_data);
      exit(1);
    }
  if ((listen(ftp->s, 42)) == -1)
    exit(1);
}

void	launch_nclient(ftp_t *ftp)
{
  int                   client_sin_len;
  pid_t			client;
  client_ftp_t		client_ftp;
  struct sockaddr_in    client_sin;

  client_sin_len = sizeof(client_sin);
  while (42)
    {
#ifndef alpha
      client_ftp.cs = accept(ftp->s, (struct sockaddr *)&client_sin, (socklen_t *) &client_sin_len);
#else
      client_ftp.cs = accept(ftp->s, (struct sockaddr *)&client_sin, &client_sin_len);
#endif
      if ((client = fork()) == -1)
	{
	  perror("fork");
	  exit(1);
	}
      else if (client)
	{
	printf("New Client connected %s:%d\n", inet_ntoa(client_sin.sin_addr), ntohs(client_sin.sin_port));
	close(client_ftp.cs);
	}
      else
	{
	  close(ftp->s);
	  launch_client(&client_ftp, ftp);
	  close(client_ftp.cs);
	  printf("Client exited\n");
	  exit(0);
	}
    }
}

int	main(int __UNUSED__ ac, char **av)
{
  ftp_t			ftp;

  if (av[1] == 0)
    {
      printf("Please precise a port\n");
      return (0);
    }
  init_server(&ftp, av[1]);
  launch_nclient(&ftp);
  return (0);
}
