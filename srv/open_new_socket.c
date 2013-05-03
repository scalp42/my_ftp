/*
** open_new_socket.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/socket.h>
#ifdef sun4
#include	<sys/types.h>
#endif
#include	<unistd.h>
#include	"ftp.h"

char		open_new_socket(client_ftp_t __UNUSED__ *client_ftp, ftp_t *ftp)
{
  int			option_value;
  struct sockaddr_in    sin;

  if ((ftp->s_data = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Problem in socket open\n");
      exit(1);
    }
  option_value = 1;
#ifndef sun4
  if (setsockopt(ftp->s_data, SOL_SOCKET, SO_REUSEPORT,
		 (char *)&option_value,
		 sizeof(option_value)) < 0)
    {
      perror("setsockopt");
      exit(0);
    }
#endif
  sin.sin_family = AF_INET;
  sin.sin_port = htons(ftp->port1 * 256 + ftp->port2);
  sin.sin_addr.s_addr = INADDR_ANY;
  if  (bind(ftp->s_data, (struct sockaddr *) &sin, sizeof(sin)) == -1)
    {
      close(ftp->s_data);
      exit(1);
    }
  if ((listen(ftp->s_data, 42)) == -1)
    exit(1);
  return (1);
}
