#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DIE		6

void opening(void){
	printf("=================================\n");
	printf("============SHARK GAME ==========\n");
	printf("=================================\n");
	printf("============S=T=A=R=T==!=========\n");
	printf("================================>>>>>>>>>\n");
}
int rolldie(void)
{
	return rand()%MAX_DIE+1;
}
int main(int argc, char *argv[]) {
	int pos=0;
	srand((unsigned)time(NULL));
	
	//0. opening
	opening();
	
	//1. 초기화 & 플레이어 이름 결정
	board_initBoard();
	//2. 반복문 (플레이어 턴)
	do{
		int step = rolldie();
		int coinResult;
		char c;
		
		board_printBoardStatus();
		
		pos += step;
		coinResult = board_getBoardCoin(pos);
		
		printf("press any key to continue : ");
		scanf("%d", &c);
		fflush(stdin);
		
		//2-1. 플레이어이 상태 출력
		//2-2. 주사위 던지기
		//2-3. 이동
		//2-4. 코인 얻기
		//2-5. 다음 턴 
		//2-6. 상어 동작 (조건 : 모든 플레이어가 한번씩 돈다.)- if문 사용 
	 		//상어동작
	}while(1);
	//3. 정리 (승자 계산, 출력)
	
	 
	return 0;
}
