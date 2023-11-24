#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME	200
#define N_PLAYER	3		
#define MAX_DIE		6
#define N_BOARD   		 15 

#define PLAYERSTATUS_LIVE	0
#define PLAYERSTATUS_DIE	1
#define PLAYERSTATUS_END	2


int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER]; 	//	0: LIVE, 1: DIE, 2: END  , if(player_status[0]==PLAYERSTATUS_LIVE)
char player_statusString[3][MAX_CHARNAME]={"LIVE","DIE","END"};

void opening(void){
	printf("=================================\n");
	printf("============SHARK=GAME===========\n");
	printf("=================================\n");
	printf("============S=T=A=R=T==!=========\n");
	printf("================================>>>>>>>>>\n");
}
int rolldie(void)
{
	return rand()%MAX_DIE+1;
}
void printPlayerPosition(int player)
{
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(player_position[player]==i)
			printf("%c", player_name[player][0]);
		else
		{
			if(board_getBoardStatus(i)==BOARDSTATUS_NOK)
				printf("X");
			else
				printf(" ");
		}
	}
	printf("|\n");
}
void printPlayerStatus(void)
{
	int i;
	printf("player status ---\n");
	for(i=0;i<N_PLAYER;i++)
	{
		printf("%s : pos %i, coin %i, status %s\n", player_name[i],player_position[i],player_coin[i],player_statusString[player_status[i]]);
		printPlayerPosition(i);
	}
	printf("-----------\n");
 } 
 
void checkDie(void)
{
	int i;
	for(i=0; i<N_PLAYER;i++)
		if(board_getBoardStatus(player_position[i])==BOARDSTATUS_NOK)
			player_status[i]=PLAYERSTATUS_DIE;
}
int game_end(void)
{
	int i;
	int flag_end =1;
	for(i=0; i<N_PLAYER;i++)
	{
		if(player_status[i]==PLAYERSTATUS_LIVE)
		{
			flag_end =0;
			break;
		}
	}
	return flag_end;
}
int getAlivePlayer(void)
{
	int i;
	int cnt=0;
	for(i=0; i<N_PLAYER; i++)
	{
		if(player_status[i]==PLAYERSTATUS_LIVE)
			cnt++;
	}
	return cnt;
}
int getWinner(void)
{
	int i;
	int winner=0;
	int max_coin=-1;
	for(i=0;i<N_PLAYER;i++)
	{
		if(player_coin[i]>max_coin)
		{
			max_coin = player_coin[i];
			winner=i;
		}
	}
	return winner;
}

int main(int argc, char *argv[]) {
	int pos=0;
	int i;
	int turn=0;
	srand((unsigned)time(NULL));
	
	//0. opening
	opening();
	
	//1. 초기화 & 플레이어 이름 결정
	board_initBoard();
	//1-2.
	for(i=0;i<N_PLAYER;i++)
	{
		player_position[i]=0;
		player_coin[i]=0;
		player_status[i]=PLAYERSTATUS_LIVE;
		printf("player %i's name : ",i);
		scanf("%s", player_name[i]);
	}
	//2. 반복문 (플레이어 턴)
	do{
		int step;
		int coinResult;
		char c;
		
		if(player_status[turn]!= PLAYERSTATUS_LIVE)
		{
			turn = (turn+1)%N_PLAYER;
			continue;
		}
		
		//2-1. 보드와 플레이어이 상태 출력
		board_printBoardStatus();
		for(i=0;i<N_PLAYER;i++)
			printPlayerPosition(i);	
		printPlayerStatus();
	
	
		//2-2. 주사위 던지기
		printf("%s turn!",player_name[turn]);
		printf("press any key to roll a die!\n");
		scanf("%d", &c);
		fflush(stdin);
		step = rolldie();
		
		//2-3. 이동
		player_position[turn] += step;
		if (player_position[turn]>= N_BOARD)
		{
			player_position[turn]=N_BOARD-1;
		}
		if(player_position[turn]==N_BOARD-1)
			player_status[turn]=PLAYERSTATUS_END;
		//printf();
				
		//2-4. 코인 얻기
		coinResult = board_getBoardCoin(pos);
		player_coin[turn]+= coinResult;
		//printf()
		
		//2-5. 다음 턴 
		turn=(turn+1)%N_PLAYER; //wrap around
		//2-6. 상어 동작 (조건 : 모든 플레이어가 한번씩 돈다.)- if문 사용 
		if(turn==0)
		{
			//상어동작
			int shar_pos = board_stepShark();
			//printf();
			checkDie();
		}	 		
	}while(game_end()==0);
	
	//3. 정리 (승자 계산, 출력)
	printf("생존 플레이어 수: %i\n",getAlivePlayer());
	printf("승자 플레이어는 %s\n", player_name[getWinner()]);
	return 0;
}
