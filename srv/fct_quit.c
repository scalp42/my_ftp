/*
** fct_quit.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<string.h>
#include	<stdio.h>
#include	"ftp.h"

void		fct_quit(char __UNUSED__ *cmd, client_ftp_t *client_ftp, ftp_t __UNUSED__ *ftp)
{
  xsend(client_ftp->cs, QUIT, strlen(QUIT), 0);
}
