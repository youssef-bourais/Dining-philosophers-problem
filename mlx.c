
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void ft_execut()
{
	char command[] = "pmset displaysleepnow";

    int result = system(command);
	exit(0);
}

int handler(int keycode)
{
	if (keycode == 232 || keycode == 233)
	{
		printf("hello\n");
	}
	else
		printf("aaaa\n");
	// ft_execut();
	// printf("%D\n", keycode);
	return 0;
}

int handler2(int button, int x, int y, void *param) // 259
{
	// ft_execut();
	if (button == 232 || button == 233)
	{
		printf("hello\n");
	}
	else
		printf("bbbb\n");
    return 0;
}

int main()
{
	void *ptr;
	void *win;
	struct timeval  *pst;
	int     tz_minuteswest;

	ptr = mlx_init();

	
	win = mlx_new_window(ptr, 51, 28, "hello");

	mlx_key_hook(win, &handler, 0);
	// mlx_mouse_hook(win, &handler2, 0);
	mlx_hook(win, 6, 0, &handler2, 0);

	// gettimeofday(struct timeval *restrict tp, void *restrict tzp);
	// gettimeofday(pst->tv_sec, 0);
	// printf("%ld\n", tv_sec);
	
	mlx_loop(ptr);
}
