#include <stdio.h>
#include "./includes/libft.h"

int main(void)
{
	char *file = " blal    lefjljsf kwehjfkhwafk       iowfjoijf jfkfljefwlw n       ijfsf      wioj     wlfjwjef           ljflwjs  wefj  hfhfhfhf d    w    qw	weqweqew werawed qWEEWef   wfwefwfss  wesfsrgwsfgsrghsagsgf wghergsgedxvjsdhzfaghdzgfja jwrhgajsgjz awhefuwaefhuawufrahuwf shdwEHFUFHWRFSCJSFJFS  IQWEHUHUIRWEHRHWIRUHIFHS   WFIUEHFIUHSFIUHSFIUHSUIGHFGIHASGFHSKX";
	char **tab = ft_strsplit(file, ' ');
	int i = 0;
	while (tab[i])
	{
		printf ("%s\n", tab[i]);
		i++;
	}
	free(tab);
	return (0);
}