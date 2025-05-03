#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define EASY 10
#define MIDDLE 20
#define DIFFICULT 30
#define CROSS 10 
//本项目只是完成了基础的扫雷，但是不能够连续的将没有地雷的位点进行消除，以及排除坐标重复输入的功能，该部分在后续的学习中完成，同时，在后续修改中，还会美化界面，加入计时器等功能
typedef struct checkerboard{
	int game_choice;
	//此处使用二维指针，指向一维指针，最终指向棋盘上的每一个元素
	char **board;
	char **display_board;
	int *record_x;
	int *record_y;
	int record_count;
}checkerboard;
//地雷判断函数 
bool mine_judge(int x_axis,int y_axis,checkerboard *game){
	x_axis = x_axis - 1;
	y_axis = y_axis - 1;
	if (game->board[x_axis][y_axis] == 'x'){
		return true;
	} else {
		return false;
	}
}
//棋盘生成函数 
void background(int model,checkerboard *game){ 
	//使用结构体将定义的棋盘储存起来
	game->game_choice = model; 
	//为行分配内存 
	game->board = (char**)malloc(CROSS * sizeof(char*));
	int index,line;
	for (index = 0 ; index < CROSS ; index++){
		//为每一行当中的元素分配内存 
		game->board[index] = (char*)malloc(model * sizeof(char));
		for (line = 0 ; line < model ; line++){
			//使用 'x'表示空白棋盘，这是在将棋盘初始化，并未放上地雷 ,将棋盘存入结构体中 
			game->board[index][line] = 'x';
		}
	}
}
//地雷放置函数 
void mine_put(int model,checkerboard *game){
	int tmp_index,tmp_line,number_mine;
	for (number_mine = 0 ; number_mine < model ; number_mine++){
		//使用随机数，为某一个坐标上放置地雷做准备
		//注意此处范围不需要加1，因为对于数组而言是从第0个数组到第99个数组 
		tmp_index =rand() %  CROSS;
		tmp_line =rand() % model;
		if (game->board[tmp_index][tmp_line] == 'x'){
			game->board[tmp_index][tmp_line] = '*';
		}
	}
}
//棋盘框架打印 
void origin_game(int model,checkerboard *game){ 
	int index,line;
	//头部框架
	printf("\n+");
	for (line = 0 ; line < model ; line ++){
		printf("-"); 
	}
	printf("+\n");
	//中间部分
	game->display_board = (char**)malloc(CROSS * sizeof(char*));
	for (index = 0 ; index < CROSS ; index++){
		//为每一行当中的元素分配内存 
		game->display_board[index] = (char*)malloc(model * sizeof(char));
		for (line = 0 ; line < model ; line++){
			//使用 'x'表示空白棋盘，这是在将显示棋盘初始化，不显示地雷 ,将棋盘存入结构体中 
			game->display_board[index][line] = 'x';
		}
	}
	for (index = 0 ; index < CROSS; index++) {
		printf("|");
		for (line = 0 ; line < model ; line++){
			//打印显示的棋盘
			//此处打印的单个字符串，因此使用c%
			printf("%c",game->display_board[index][line]);
		} 
		printf("|\n");
	}
	//底部部分
	printf("+");
	for (line = 0 ; line < model ; line ++){
		printf("-"); 
	}
	printf("+\n");
}
//打印游戏进行时的棋盘
void new_game(int model,checkerboard *game){ 
	int index,line;
	//头部框架
	printf("\n\n+");
	for (line = 0 ; line < model ; line ++){
		printf("-"); 
	}
	printf("+\n");
	for (index = 0 ; index < CROSS; index++) {
		printf("|");
		for (line = 0 ; line < model ; line++){
			//打印显示的棋盘
			//此处打印的单个字符串，因此使用c%
			printf("%c",game->display_board[index][line]);
		} 
		printf("|\n");
	}
	//底部部分
	printf("+");
	for (line = 0 ; line < model ; line ++){
		printf("-"); 
	}
	printf("+\n");
}
//该点位棋子检验
int real_game(int model,int x_axis,int y_axis,checkerboard *game,int mine_record){
	printf("\n当前进行步数：%d",mine_record);
	int number = 0;
	int index = 0;
	int line = 0;
	//此处不需要考虑坐标位置，因为只需要参考该点位的四周是否有'*'即可
	for (index = -1 ; index < 2 ; index++){
		for (line = -1 ; line < 2; line++){
			if (index == 0 && line == 0){
				continue;
			}
			//此处需检查是否越界
			if (x_axis + index - 1 >= 0 && x_axis + index - 1 < CROSS && y_axis + line -1 >= 0 && y_axis + line -1 < CROSS){
				if (game->board[x_axis + index - 1][y_axis + line -1] == '*'){
					number++;
				}
			}
		}
	}
	//此处需要将数字转换成字符才能够正常打印
	game->display_board[x_axis-1][y_axis-1] = '0' + number;
	mine_record++;
	return mine_record;
}
//询问部分
int ask_question_x(int model){
	int x;
	printf("请输入选择的行坐标，范围1-%d\n",model);
	scanf("%d",&x);
	return x;
} 
int ask_question_y(int model){
	int y;
	printf("请输入选择的列坐标，范围1-%d\n",CROSS);
	scanf("%d",&y);
	return y;
} 
//游戏主体部分 
void game_body(int model,checkerboard *game){
	origin_game(model,game);	
	int x_axis,y_axis,mine_record;
	//mine_record为进行步数的确定
	mine_record = 1;
	char result = true;
	x_axis = ask_question_x(model);
	y_axis = ask_question_y(model);
	while (result){
		mine_record = real_game(model,x_axis,y_axis,game,mine_record);
		result = mine_judge(x_axis,y_axis,game);
		//此处打印两个棋盘是因为在下一次询问之前，需确认棋盘的样式，此处只需要打印，并不需要赋值
		new_game(model,game);
		x_axis = ask_question_x(model);
		y_axis = ask_question_y(model);
		if (mine_record == 0){
			result = true;
		}
		if (mine_record == model*CROSS-model){
			break;
		}
	}
	if (result){
		printf("您赢得了本场游戏");
	} else {
		printf("您触发了地雷，游戏结束，已经进行了%d步",mine_record );
	}
}
int model_select(){
	printf("+-----------------------+\n");
	printf("|欢迎进入游戏!\t\t|\n");
	printf("|请选择游戏难度:\t|\n|	1.简单模式\t|\n|	2.一般模式\t|\n|	3.困难模式\t|\n");
	printf("+-----------------------+\n");
	
	printf("\n\n");
	
	int choice;
	scanf("%d",&choice);
	
	return choice;
}
//释放分配过的内存，提高内存利用率 ，避免内存泄漏 
void fr_checker_board(checkerboard *game){
	int index;
	for(index = 0 ; index < CROSS ; index++){
		free(game->board[index]);
		free(game->display_board[index]);
	}
	free(game->board);
	free(game->display_board);
}
int main(){
	srand(time(NULL)); 
	//先制作一个简单版的扫雷游戏
	//第一部分：开始菜单，选择游戏模式
	int choice = model_select();
	checkerboard game;
	//第二部分：进行模式判断,这里选用swith进入各个游戏难度 
	switch(choice){
		case 1:
			//此处放入简单游戏模式
			background(EASY,&game);
			mine_put(EASY,&game);
			game_body(EASY,&game);
			break;
		case 2:
		 	//此处放入一般游戏模式
		 	background(MIDDLE,&game);
			mine_put(MIDDLE,&game);
			game_body(MIDDLE,&game);
			break;
		case 3:
			//此处放入困难游戏模式
			background(DIFFICULT,&game);
			mine_put(DIFFICULT,&game);
			game_body(DIFFICULT,&game);
			break;
		default:
			printf("您的选择无效:请输入1或2或3选择游戏模式"); 
	}
	fr_checker_board(&game);
	return 0 ;
}
 
