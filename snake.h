#ifndef __SNAKE__H__
#define __SNAKE__H__


#define M 24
#define Col 62
#define SnakeLength 20
char background[M][Col] = {//62,Ä©Î²»¹ÓÐ¸ö¿Õ×Ö·û
	"¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö                                                        ¡ö\n",
	"¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö\n"
};

enum direction{ up = -1, down = 1, right = 2, left = -2 };
int SnakeBody[SnakeLength][3] = { 0 };
int SnakeDirection = left;

typedef int bool;
#define true 1
#define false 0

bool Food = true;
int g_x_food;
int g_y_food;
int g_snake_length = 2;
int g_sleep_time = 500;



#endif