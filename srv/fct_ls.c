/*
** fct_ls.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	"ftp.h"

#ifdef sun4
FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);
#endif

void		fct_ls(char __UNUSED__ *cmd, client_ftp_t *client_ftp, ftp_t __UNUSED__ *ftp)
{
  FILE		*ls;
  char		freadbuff[1024];

  if ((ls = popen("ls -l", "r")) == NULL)
    {
      printf("Error in popen\n");
      exit(1);
    }
  xsend(client_ftp->cs, LIST, strlen(LIST), 0);
  while (fgets(freadbuff, 1024, ls) != NULL)
    {
      freadbuff[strlen(freadbuff) - 1] = '\0';
      xsend(client_ftp->cs_data, freadbuff, strlen(freadbuff), 0);
      xsend(client_ftp->cs_data, "\r\n", 2, 0);
    }
  close(client_ftp->cs_data);
  xsend(client_ftp->cs, END_LI, strlen(END_LI), 0);
  pclose(ls);
}
