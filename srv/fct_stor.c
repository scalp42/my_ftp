/*
** fct_stor.c for ftp in /Users/scalp/projs/my_ftp
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
#include	"ftp.h"

void		fct_stor(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp)
{
  FILE		*fs;
  char		buff[1024];
  char		put[1024];
  int		nb;
  int		i;
  int		j;

  fs = fopen(cmd + 5, "w");
  bzero(put, 1024);
  sprintf(put, PUT, cmd + 5);
  xsend(client_ftp->cs, put, strlen(put), 0);
  bzero(buff, 1024);
  while ((nb = xread(client_ftp->cs_data, buff, 1024)))
    {
      bzero(put, 1024);
      for (i = 0, j = 0; i != nb; i++, j++)
	{
	  if (client_ftp->type == 1 && buff[i] == '\r' && buff[i + 1] == '\n')
	    j--;
	  else
	    put[j] = buff[i];
	}
      fwrite(put, 1, j, fs);
      bzero(buff, 1024);
    }
  fclose(fs);
  xsend(client_ftp->cs, ENVIAR, strlen(ENVIAR), 0);
  close(client_ftp->cs_data);
  close(ftp->s_data);
}
