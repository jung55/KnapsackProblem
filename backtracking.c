#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int n = 4; //������ ����
int W = 16; //�賶�� �뷮
int w[5] = { 0,2,5,10,5 };  //0�� �ǹ� ���� ����
int p[5] = { 0,40,30,50,10 }; //0�� �ǹ� ���� ����
int numbest = 0; //������� ã�� ������
int maxprofit = 0; //������� ã�� �ִ� ����
char include[5] = { 0 }; //������� ���� �����۵�
char bestset[5] = { 0 }; //�ִ� ������ ��� ���� �����;� �ϴ� ������ ���

bool promising(int i, int profit, int weight) {
	int j = 0;
	int k = 0;
	int totweight = 0;
	float bound = 0;

	if (weight >= W) {
		return false;
	} //�賶�� �� ���� ������ ������ �������� �ʴ�.
	else {
		j = i + 1;
		bound = (float)profit;
		totweight = weight;

		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			++j;
		} 
		k = j; 
		if (k <= n) {
			bound = bound + (W - totweight) * (p[k] / w[k]);
		} //������ ���� �� �ִ� �ִ� ����
		return(bound > maxprofit); 
	} //��������� �ִ� ������ ������ ���� �� �ִ� �ִ����ͺ��� ������ �����ϰ�, �׷��� ������ �������� �ʴ�.
}


void knapsack(int i, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		for (int i = 0; i < n + 1; i++) {
			bestset[i] = include[i];
		}
	} //������� ã�� �ִ� ������ ���
	if (promising(i, profit, weight)) {
		include[i + 1] = 't'; //w[i+1]�� �����ϴ� ���
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = 'f'; //w[i+1]�� �������� �ʴ� ���
		knapsack(i + 1, profit, weight);
	}
}

int main() {
	knapsack(0,0,0);
	for (int i = 1; i < n + 1; i++) {
		printf("w%d: %c ", i, bestset[i]);
	}//�ִ� ������ ��� ���� �����;� �ϴ� ������ ���
	printf("\n");
	printf("answer: %d", maxprofit);
	//�ִ� ���� ���.
	return 0;
}
