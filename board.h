//board.h

#define BOARDSTATUS_OK    1
#define BOARDSTATUS_NOK   0

int board_initBoard(void); //���� �ʱ�ȭ 
int board_getBoardStatus(int pos); // Ư�� ĭ�� �ļտ��� ��� 
int board_getBoardCoin(int); // ���� ���� ��� 
int board_printBoardStatus(void); //��ü ���� ���� ��� 

//int board_getSharkPosition(void); // ����� ��ġ ��� 
//int board_stepShark(void); //��� ���� ��� 


