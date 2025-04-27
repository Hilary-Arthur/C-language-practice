#include <stdio.h>
#include <stdbool.h>
#define LINE 1024
#define N 10

//坐标为[1,1]的点为红色，如果其根节点为红色,则表示为左红右黑，反之为左黑右红 
bool is_red(char tree[N][LINE],int x,int y){
	//使用布尔函数判断该坐标点位的颜色 
	if (tree[x - 1][y - 1] == 'r'){
		return true;
	} else {
		return false;
	}
}

void real_tree(char tree[N][LINE]){
	int i,j,k;
	k = 1;
	int current_line = 1;
	for (i = 1 ; i < N ; i++){
		//此处层数的判定，因为已经给定第一层为红色,所以只需要判断第二层到第十层即可 
		while (k <= i){
			current_line = current_line * 2;
			k++;
		}
		//原始树的构成，左子节点与父子节点始终相同，右子节点始终与父子节点相反 
		for (j = 0 ; j < current_line ;j++){
			if (j % 2 == 0){
				if (tree[i - 1][j / 2] == 'r'){
					tree[i][j] = tree[i - 1][j / 2];
				} else {
					tree[i][j] = 'b';
				}
			} else {
				if (tree[i - 1][(j - 1) / 2] == 'r'){
					tree[i][j] = 'b';
				} else {
					tree[i][j] = tree[i - 1][(j - 1) / 2];
				}
			}
		}
	}
}

int main(){
	int i,j,k,number;
	printf("该树的高度目前只有十行!\n");
	char tree[N][LINE];
	//此处仍存在不妥之处，即该数组是N*LINE，即除第十行外每一行会浪费部分内存，需在后续练习中解决该问题 
	tree[0][0] = 'r';
	//将定义的数组结构带入函数，进行赋值 
	real_tree(tree);
	printf("请输入你一共需要查询多少组坐标(n <= 10):\n");
	scanf("%d",&number);
	int coordinates[number][2];
	printf("请输入各组坐标(使用空格隔开，形如:1 1):\n");
	for (i = 0 ; i < number ;i++){
		scanf("%d%d",&coordinates[i][0],&coordinates[i][1]);
	}
	
	for (i = 0 ; i < number ; i++){
		if (is_red(tree,coordinates[i][0],coordinates[i][1])){
			printf("RED\n");
		} else {
			printf("BLACK\n");
		}
	}
	
	return 0;
}
