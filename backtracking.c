#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int n = 4; //아이템 개수
int W = 16; //배낭의 용량
int w[5] = { 0,2,5,10,5 };  //0은 의미 없는 숫자
int p[5] = { 0,40,30,50,10 }; //0은 의미 없는 숫자
int numbest = 0; //현재까지 찾은 아이템
int maxprofit = 0; //현재까지 찾은 최대 이익
char include[5] = { 0 }; //현재까지 취한 아이템들
char bestset[5] = { 0 }; //최대 이익을 얻기 위해 가져와야 하는 아이템 출력

bool promising(int i, int profit, int weight) {
	int j = 0;
	int k = 0;
	int totweight = 0;
	float bound = 0;

	if (weight >= W) {
		return false;
	} //배낭에 더 넣을 공간이 없으면 유망하지 않다.
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
		} //앞으로 얻을 수 있는 최대 이익
		return(bound > maxprofit); 
	} //현재까지의 최대 이익이 앞으로 얻을 수 있는 최대이익보다 작으면 유먕하고, 그렇지 않으면 유망하지 않다.
}


void knapsack(int i, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		for (int i = 0; i < n + 1; i++) {
			bestset[i] = include[i];
		}
	} //현재까지 찾은 최대 이익의 경로
	if (promising(i, profit, weight)) {
		include[i + 1] = 't'; //w[i+1]를 포함하는 경우
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = 'f'; //w[i+1]를 포함하지 않는 경우
		knapsack(i + 1, profit, weight);
	}
}

int main() {
	knapsack(0,0,0);
	for (int i = 1; i < n + 1; i++) {
		printf("w%d: %c ", i, bestset[i]);
	}//최대 이익을 얻기 위해 가져와야 하는 아이템 출력
	printf("\n");
	printf("answer: %d", maxprofit);
	//최대 이익 출력.
	return 0;
}
