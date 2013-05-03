/*
** retr_opt.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<strings.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	"client.h"

int		init_download(client_ftp_t *client_ftp, char *cmd)
{
  char		buff[1024];
  int		i;

  bzero(buff, 1024);
  xsend(client_ftp->s, "TYPE I\n", 7, 0);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
  bzero(buff, 1024);
  open_new_data_connection(client_ftp);
  open_data_connection(client_ftp);
  bzero(buff, 1024);
  for (i = 4; cmd[i] == ' ' && cmd[i] != '\0'; i++)
    ;
  sprintf(buff, "RETR %s\n", cmd + i);
  xsend(client_ftp->s, buff, strlen(buff), 0);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
  if (strncmp(buff, "550", 3) == 0)
    {
      close(client_ftp->s_data);
      return (1);
    }
  return (0);
}

void		retr_opt(client_ftp_t *client_ftp, char *cmd)
{
  FILE		*fs;
  char		buff[1024];
  char		put[1024];
  int		nb;
  int		i;
  int		j;

  if ((i = init_download(client_ftp, cmd)) == 1)
    return;
  if ((fs = fopen(cmd + 4, "w+")) == NULL)
    {
      printf("Failed to open file\n");
      close(client_ftp->s_data);
      return;
    }
  bzero(buff, 1024);
  while ((nb = xread(client_ftp->s_data, buff, 1024)))
    {
      bzero(put, 1024);
      for (i = 0, j = 0; i != nb; i++, j++)
	put[j] = buff[i];
      fwrite(put, 1, j, fs);
      bzero(buff, 1024);
    }
  fclose(fs);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
  close(client_ftp->s_data);
}
