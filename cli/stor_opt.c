/*
** stor_opt.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<string.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	"client.h"

#ifdef	sun4
int		fileno(FILE *stream);
#endif

FILE		*init_transfert(char *cmd)
{
  FILE		*file;

  if ((file = fopen(cmd + 4, "r")) == NULL)
    {
      printf("Failed to open file.\n");
      return (NULL);
    }
  return (file);
}

void		stor_opt(client_ftp_t *client_ftp, char *cmd)
{
  FILE		*file;
  int		fd;
  int		nb_read;
  char		buff[1024];
  int		i;

  if ((file = init_transfert(cmd)) == NULL)
    return;
    bzero(buff, 1024);
  xsend(client_ftp->s, "TYPE I\n", 7, 0);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
  open_new_data_connection(client_ftp);
  open_data_connection(client_ftp);
 bzero(buff, 1024);
  for (i = 4; cmd[i] == ' ' && cmd[i] != '\0'; i++)
    ;
  sprintf(buff, "STOR %s\n", cmd + i);
  xsend(client_ftp->s, buff, strlen(buff), 0);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
  bzero(buff, 1024);
  fd = fileno(file);
  do
    {
       nb_read = xread(fd, buff, 1024);
      xsend(client_ftp->s_data, buff, nb_read, 0);
    }
  while (nb_read > 0);
  close(client_ftp->s_data);
  fclose(file);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
}
