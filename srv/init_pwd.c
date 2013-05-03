/*
** init_pwd.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<string.h>
#include	<strings.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	"ftp.h"

#ifdef sun4
char		*strdup(const char *s1);
#endif

void		init_pwd(client_ftp_t *client_ftp)
{
  char		buff[MAXPATHLEN];

  bzero(buff, MAXPATHLEN);
  getcwd(buff, MAXPATHLEN - 1);
  buff[strlen(buff)] = '/';
  client_ftp->pwd = strdup(buff);
  client_ftp->pwd_init = strdup(buff);
}
