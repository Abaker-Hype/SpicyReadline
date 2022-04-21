#include "spicyreadline.h"
#include <stdio.h>
#include <sys/time.h>

int	main(void)
{
	char *line;

	while (true)
	{
		line = spicy_readline("FUCK>", "hi", "there", true);
		printf("Returned Line = %s", line);
		fflush(NULL);
		if (line)
		{
			if (!ft_strncmp("exit", line, 5))
				break ;
			free(line);
		}
	}
	free(line);
}
/*
typedef struct RGB{
	int	r;
	int	g;
	int	b;
}	RGB;

static double	gettime(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

bool	fpsupdate(int fps)
{
	static double	last = 0;
	double			now;

	now = gettime();
	if (now - last < 1000 / fps)
		return (false);
	last = now;
	return (true);
}


RGB	invert(RGB rgb)
{
	RGB	invert;

	invert.r = 255 - rgb.r;
	invert.g = 255 - rgb.g;
	invert.b = 255 - rgb.b;
	return (invert);
}

void	updatecol(int *a, int *b, int *c)
{
	if (*b < 255 && *c == 0)
		(*b)++;
	else if (*c > 0 && *b == 0)
		(*c)--;
	else
		(*a)--;
}

RGB	updatergb(RGB rgb)
{
	if (rgb.r == 255)
		updatecol(&rgb.r, &rgb.g, &rgb.b);
	else if (rgb.g == 255)
		updatecol(&rgb.g, &rgb.b, &rgb.r);
	else if (rgb.b == 255)
		updatecol(&rgb.b, &rgb.r, &rgb.g);
	return (rgb);
}

int	main(void)
{
	RGB	rgb = {255, 0, 0};
	RGB	irgb;
	RGB	tmp;
	int	i;

	while (true)
	{
		if (fpsupdate(360))
		{
			i = 0;
			tmp = rgb;
			irgb = invert(rgb);
			printf("\r");
			while (i++ < 100)
			{
				printf("\e[38;2;%i;%i;%im", rgb.r, rgb.g, rgb.b);
				printf("\e[48;2;%i;%i;%im", irgb.r, irgb.g, irgb.b);
				printf("E");
				for (int j = 0; j < 20; j++)
					rgb = updatergb(rgb);
				irgb = invert(rgb);
			}
			printf("\e[0m");
			fflush(NULL);
			rgb = updatergb(tmp);
		}
	}
}
*/