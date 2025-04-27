#include <stdio.h>
#include <stdbool.h>
#define LINE 1024
#define N 10

//����Ϊ[1,1]�ĵ�Ϊ��ɫ���������ڵ�Ϊ��ɫ,���ʾΪ����Һڣ���֮Ϊ����Һ� 
bool is_red(char tree[N][LINE],int x,int y){
	//ʹ�ò��������жϸ������λ����ɫ 
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
		//�˴��������ж�����Ϊ�Ѿ�������һ��Ϊ��ɫ,����ֻ��Ҫ�жϵڶ��㵽��ʮ�㼴�� 
		while (k <= i){
			current_line = current_line * 2;
			k++;
		}
		//ԭʼ���Ĺ��ɣ����ӽڵ��븸�ӽڵ�ʼ����ͬ�����ӽڵ�ʼ���븸�ӽڵ��෴ 
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
	printf("�����ĸ߶�Ŀǰֻ��ʮ��!\n");
	char tree[N][LINE];
	//�˴��Դ��ڲ���֮��������������N*LINE��������ʮ����ÿһ�л��˷Ѳ����ڴ棬���ں�����ϰ�н�������� 
	tree[0][0] = 'r';
	//�����������ṹ���뺯�������и�ֵ 
	real_tree(tree);
	printf("��������һ����Ҫ��ѯ����������(n <= 10):\n");
	scanf("%d",&number);
	int coordinates[number][2];
	printf("�������������(ʹ�ÿո����������:1 1):\n");
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
