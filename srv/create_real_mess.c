/*
** create_real_mess.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	"ftp.h"

char		*create_real_mess(char *ipaddr)
{
  char		*mess;

  mess = xmalloc(128 * sizeof(*mess));
  sprintf(mess, PASV, ipaddr);
  free(ipaddr);
  return (mess);
}
