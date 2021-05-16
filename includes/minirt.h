/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 00:27:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 04:17:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <strings.h>
# include <error.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"

# define W_WIDTH 800
# define W_HEIGHT 400
# define W_TITLE "minirt"

# define K_BUFF_SIZE 20

typedef struct	s_keys
{
	int			keycode;
}				t_keys;

typedef struct	s_img
{
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_vect3
{
	double		x;
	double		y;
	double		z;
}				t_vect3;

typedef struct s_ray
{
	t_vect3		ori;
	t_vect3		dir;
}				t_ray;


t_vect3 vect3_minus(t_vect3 vect);
double	vect3_squared_lenght(t_vect3 vect3);
double	vect3_lenght(t_vect3 vect3);
void	vect3_make_unit(t_vect3	*vect3);
t_vect3 vect3_add(t_vect3 r, t_vect3 l);
t_vect3 vect3_sub(t_vect3 r, t_vect3 l);
t_vect3 vect3_mult(t_vect3 r, t_vect3 l);
t_vect3 vect3_div(t_vect3 r, t_vect3 l);
t_vect3	vect3_mult_scalar(t_vect3 v, double s);
t_vect3	vect3_div_scalar(t_vect3 v, double s);
double	vect3_dot(t_vect3 r, t_vect3 l);
t_vect3	vect3_cross(t_vect3 r, t_vect3 l);
t_vect3	vect3_unit(t_vect3 v);

typedef struct	s_camera
{
	t_vect3		pos;
	int			fov;
}				t_camera;


typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_keys		keys[K_BUFF_SIZE + 1];
	int			redraw;
}				t_game;

void	refresh(t_game *game);
int		init_img(t_img *img_struct, void *mlx, int w, int h);
int		init_game(t_game *game, int w, int h);
int		destroy_game(t_game *game);
int		add_shade(double shade, int color);
int		rgb(unsigned char r, unsigned char g, unsigned char b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/*
** BACKEND
*/

t_keys	*key_chr(t_keys *arr, int keycode, size_t size);

/*
** EVENT HANDLERS
*/

int		keyboard_handler(t_game *vars);
void	hooks(t_game *vars);
int		loop_handler(t_game *vars);
int		key_handler(int keycode, t_game *vars);
int		release_handler(int keycode, t_game *vars);


# ifdef __linux__

#  define LINUX 1
#  define OSX 0
#  define MIXER_COMMAND "amixer set Master 50% > /dev/null 2>&1"
#  define PLAYER        "aplay"
#  define KILL_COMMAND  "killall"

#  define ESC_KEY			65307
#  define USE_KEY			102

#  define ARROW_UP_KEY		65362
#  define ARROW_DOWN_KEY	65364
#  define ARROW_LEFT_KEY	65361
#  define ARROW_RIGHT_KEY	65363
#  define SHOOT_KEY			65506

#  ifndef QWERTY
#   define FORWARD_KEY		122
#   define BACKWARD_KEY		115
#   define LEFT_KEY			113
#   define RIGHT_KEY		100
#   define CTRL_KEY			65507
#   define ALT_KEY			99
#   define C_KEY			99
#  endif

#  ifdef QWERTY
#   define FORWARD_KEY		119
#   define BACKWARD_KEY		115
#   define LEFT_KEY			97
#   define RIGHT_KEY		100
#   define CTRL_KEY			65507
#   define ALT_KEY			99
#   define C_KEY			99
#  endif

# endif

# ifdef __APPLE__

#  define OSX 1
#  define LINUX 0

#  define MIXER_COMMAND "echo NO MIXER"
#  define PLAYER        "afplay"
#  define KILL_COMMAND  "killall"

#  define ARROW_UP_KEY		126
#  define ARROW_DOWN_KEY	125
#  define ARROW_LEFT_KEY	123
#  define ARROW_RIGHT_KEY	124
#  define SHOOT_KEY			258

#  define FORWARD_KEY		13
#  define BACKWARD_KEY		1
#  define LEFT_KEY			0
#  define RIGHT_KEY			2
#  define CTRL_KEY			256
#  define ALT_KEY			8
#  define C_KEY				8
#  define ESC_KEY			53
#  define USE_KEY			3

# endif

# ifdef _WIN32

#  define OSX 0
#  define LINUX 1

#  define ARROW_UP_KEY		1073741906
#  define ARROW_DOWN_KEY	1073741905
#  define ARROW_LEFT_KEY	1073741904
#  define ARROW_RIGHT_KEY	1073741903
#  define SHOOT_KEY			1073742053

#  define FORWARD_KEY		122
#  define BACKWARD_KEY		115
#  define LEFT_KEY			113
#  define RIGHT_KEY			100
#  define CTRL_KEY			1073742048
#  define ALT_KEY			1073742050
#  define C_KEY				99
#  define ESC_KEY			27
#  define USE_KEY			102

# endif

/*
** EVENT DEFINITION
*/

# define NOEVENT_MASK				0L
# define KEYPRESS_MASK				1L
# define KEYRELEASE_MASK			2L
# define BUTTONPRESS_MASK			4L
# define BUTTONRELEASE_MASK			8L
# define ENTERWINDOW_MASK			16L
# define LEAVEWINDOW_MASK			32L
# define POINTERMOTION_MASK			64L
# define POINTERMOTIONHINT_MASK		128L
# define FOCUS_CHANGE_MASK			2097152L
# define STRUCTURE_NOTIFY_MASK		131072L

/*
** # define Button1MotionMask		(1L<<8)
** # define Button2MotionMask		(1L<<9)
** # define Button3MotionMask		(1L<<10)
** # define Button4MotionMask		(1L<<11)
** # define Button5MotionMask		(1L<<12)
** # define ButtonMotionMask		(1L<<13)
** # define KeymapStateMask			(1L<<14)
** # define ExposureMask			(1L<<15)
** # define VisibilityChangeMask	(1L<<16)
** # define StructureNotifyMask		(1L<<17)
** # define ResizeRedirectMask		(1L<<18)
** # define SubstructureNotifyMask	(1L<<19)
** # define SubstructureRedirectMask	(1L<<20)
** # define FocusChangeMask			(1L<<21)
** # define PropertyChangeMask		(1L<<22)
** # define ColormapChangeMask		(1L<<23)
** # define OwnerGrabButtonMask		(1L<<24)
*/

# define KEY_PRESS			2
# define KEY_RELEASE		3
# define BUTTON_PRESS		4
# define BUTTON_RELEASE		5
# define FOCUS_IN			9
# define FOCUS_OUT			10
# define DESTROY_NOTIFY		17

/*
** # define MotionNotify	    6
** # define EnterNotify		    7
** # define LeaveNotify		    8
** # define KeymapNotify	    11
** # define Expose			    12
** # define GraphicsExpose	    13
** # define NoExpose		    14
** # define VisibilityNotify    15
** # define CreateNotify		16
** # define DestroyNotify		17
** # define UnmapNotify		    18
** # define MapNotify		    19
** # define MapRequest		    20
** # define ReparentNotify		21
** # define ConfigureNotify		22
** # define ConfigureRequest	23
** # define GravityNotify		24
** # define ResizeRequest		25
** # define CirculateNotify		26
** # define CirculateRequest	27
** # define PropertyNotify		28
** # define SelectionClear		29
** # define SelectionRequest	30
** # define SelectionNotify		31
** # define ColormapNotify		32
** # define ClientMessage		33
** # define MappingNotify		34
** # define GenericEvent		35
** # define LASTEvent		    36
*/

#endif