/*
** fct_retr.c for ftp in /Users/scalp/projs/my_ftp
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
#include	<sys/stat.h>
#include	<unistd.h>
#include	"ftp.h"

#ifdef sun4
int fileno(FILE *stream);
#endif

int		  size_file(FILE *fs)
{
  struct stat	size;

  fstat(fileno(fs), &size);
  return ((int) size.st_size);
}

void		fct_retr(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp)
{
  FILE		*file;
  int		fd;
  int		nb_read;
  char		buff[1024];
  char		unit;

  if ((file = init_transfert(cmd, client_ftp)) == NULL)
    return;
  bzero(buff, 1024);
  if (client_ftp->type == 0)
    {
      fd = fileno(file);
      do
	{
	  nb_read = xread(fd, buff, 1024);
	  xsend(client_ftp->cs_data, buff, nb_read, 0);
	}
      while (nb_read > 0);
    }
  else
    {
      while ((unit = fgetc(file)) != EOF)
	{
	  if (unit == '\n')
	    xsend(client_ftp->cs_data, "\r", 1, 0);
	  xsend(client_ftp->cs_data, &unit, 1, 0);
	}
    }

  fclose(file);
  xsend(client_ftp->cs, ENVIAR, strlen(ENVIAR), 0);
  close(client_ftp->cs_data);
  close(ftp->s_data);
}
