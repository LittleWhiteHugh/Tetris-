#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#define MAP_HEIGHT 34           //��������߶ȣ�����׼������ 
#define MAP_WIDTH 25			// ���������ȣ�����׼������
#define BLOCK_HEIGHT 4          //����߶� 
#define BLOCK_WIDTH 4			//������ 
#define BLANK_HEIGHT 4			//׼������߶�
#define BLANK_WIDTH 25			//׼�������� 
int map[MAP_HEIGHT][MAP_WIDTH]={0};//����ȫ����Ķ�ά���� ->�൱������  һ��Ԫ�ض�Ӧһ������    1�����з��飬0����û�з��� 
bool changeallow[MAP_HEIGHT][MAP_WIDTH]={0};//�����ά�����޷�ȫ����ʶ��Ϊһ ����ҪԤ����    1������Ա��ı䣬0�������Ըı�   �߽���޷�����Ķ����ɸı� 
int mapcolor[MAP_HEIGHT][MAP_WIDTH]={0};//����ȫ�������ɫ 
int blockcolor[MAP_HEIGHT][MAP_WIDTH]={0};//�������ɫ 
int score=0;					//�÷�
int X=6,Y=0;                    //����Ϊ4*4���� X��Y������Ͻ���ʼλ�� 
int a,b,c,d;					//a��b�ɱ�ʾ��ǰ��������    c��d�ɱ�ʾ��һ����������
int (*curblock)[4];				//��ǰ����
int (*nxtblock)[4];				//��һ������
int curcolor;					//��ǰ������ɫ 
void importcolor();				//���뷽����ɫ
void initial(); 				//��ʼ�� 
void setBlockData();			//������������ 
using namespace std;
typedef struct BlockData  		 // ��ʾһ���������з��������
{
    int data[BLOCK_HEIGHT][BLOCK_WIDTH]; 
}BlockData;

typedef struct Block
{
    BlockData blockData[4]; 	// ���4����������
}Block;
Block arrBlock[6];
class Tetris{
	private:
		int rank;				//�Ѷȵȼ�
	public:
		int interval();			//rank���ֵȼ�
		void drawBlock();		//���ַ��� 
		void start();			//���ƿ�ʼ���� 
		void createMap();		//������Ϸ����  
		void drawMap();			//������Ϸ���� 
		void createBlock();		//����4*4���� 
		void drop();			//��ʱ����
		void clean();			//�����һ���ۼ� 
		void transform(int);	//�������� 
		void up();				//�ϼ���ת 
		void down();			//�¼����� 
		void left();			//���� 
		void right();			//���� 
		void pause();			//�ո���ͣ 
		bool candrop();			//�ж��Ƿ��������
		bool canleft();			//�ж��Ƿ��������
		bool canright();		//�ж��Ƿ�������� 
		void newblock();		//��һ�ֺ���
		void cleanrow();		//�������������� 
		void nextblock();		//������һ������ 
		
};
void initial(){        			//��ʼ�� 
	for(int i=0;i<MAP_HEIGHT;i++){
		for(int j=0;j<MAP_WIDTH;j++){
			changeallow[i][j]=1;
		}
		cout<<endl;
	}

}
void setBlockData(){			// ������������ 
	arrBlock[0].blockData[0]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
    };
    arrBlock[0].blockData[1]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
    };
    arrBlock[0].blockData[2]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
    };
    arrBlock[0].blockData[3]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
    };
	arrBlock[1].blockData[0]=
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
    };
    arrBlock[1].blockData[1]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
    };
    arrBlock[1].blockData[2]=
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
    };
    arrBlock[1].blockData[3]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
    };
    arrBlock[2].blockData[0]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
    };
    arrBlock[2].blockData[1]=
    {
        0, 0, 0, 0,
        1, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
    };
    arrBlock[2].blockData[2]=
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0,
    };
    arrBlock[2].blockData[3]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
    };
    arrBlock[3].blockData[0]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 1, 0,
    };
    arrBlock[3].blockData[1]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0,
        1, 0, 0, 0,
    };
    arrBlock[3].blockData[2]=
    {
        0, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
    };
    arrBlock[3].blockData[3]=
    {
        0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
    };
    arrBlock[4].blockData[0]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
    };
    arrBlock[4].blockData[1]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 0,
        1, 0, 0, 0,
    };
    arrBlock[4].blockData[2]=
    {
        0, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
    };
    arrBlock[4].blockData[3]=
    {
        0, 0, 0, 0,
        0, 0, 1, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    };
    arrBlock[5].blockData[0]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    };
    arrBlock[5].blockData[1]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
    };
    arrBlock[5].blockData[2]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 1, 0, 0,
    };
    arrBlock[5].blockData[3]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
    };
    arrBlock[6].blockData[0]=
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0,
    };
    arrBlock[6].blockData[1]=
    {
        0, 0, 0, 0,
        1, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    };
    arrBlock[6].blockData[2]=
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
    };
    arrBlock[6].blockData[3]=
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 1, 0,
    };
	srand ( time(NULL) );
    a=c;
    b=d;
    curcolor=rand()%4+1;
    curblock=arrBlock[a].blockData[b].data;  //��ǰ���� 
    importcolor();
    c=rand()%7;
    d=rand()%4;
    nxtblock=arrBlock[c].blockData[d].data; //��һ������ 
}
void pos(int x, int y) {        //��ʾ����
	COORD pos;					 
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//ƫ�ƹ��λ��
}
void color(int colorNum){	    //������ɫ		
	int n;						
	switch (colorNum)
	{
		case 0: n = 0x07; break;
		case 1: n = 0x0C; break;
		case 2: n = 0x04; break;
		case 3: n = 0x0E; break;
		case 4: n = 0x0A; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
void Tetris::start(){			//���ƿ�ʼ���� �õ��ȼ�rank 
	int x;
	while(1){
		system("cls");
		cout << "������������������������������������������" << endl;
		cout << "��              ����˹����              ��" << endl;
		cout << "������������������������������������������" << endl;
		cout << "��              �淨����              ��" << endl;
		cout << "��              �� - ��ת               ��" << endl;
		cout << "��              �� - ��������           ��" << endl;
		cout << "��              �� - ����               ��" << endl;
		cout << "��              �� - ����               ��" << endl;
		cout << "��              �ո� - ��ͣ             ��" << endl;
		cout << "������������������������������������������" << endl<<endl;
		cout << ">>��1��5ѡ���Ѷ�:";
		x=getchar();
		if(x>'0'&&x<'6'){
			rank=x-'0';
			system("cls");
			break;
		}
	}
}
int Tetris::interval(){			//rank���ֵȼ�
	switch(rank){
		case 1:return 1250;
		case 2:return 500;
		case 3:return 300;
		case 4:return 120;
		case 5:return 70;
	}
}
void Tetris::transform(int key){//��������
	if(key==27)
		exit(0);
		else if(key==75) {//��
			left();
		}
		else if(key==77) {//��
			right(); 
		}
		else if(key==72) {//�� 
			up();
		}
		else if(key==80) {//��
		if(candrop())
			down();
		}
		else if(key==32){
			getch();
		}
}
void Tetris::createMap(){ 		//�������ɱ��ʼ��ͼ  
	for(int i=0;i<MAP_WIDTH;i++){
		map[BLANK_HEIGHT][i]=1;
		map[MAP_HEIGHT-1][i]=1;
		changeallow[BLANK_HEIGHT][i]=0;
		changeallow[MAP_HEIGHT-1][i]=0;
		mapcolor[BLANK_HEIGHT][i]=0;
		mapcolor[MAP_HEIGHT-1][i]=0;
		if(i>=16){
			map[14][i]=1;
			changeallow[14][i]=0;
			mapcolor[14][i]=0;
		}
		
	}
	
	for(int i=BLANK_HEIGHT+1;i<MAP_HEIGHT;i++){
		map[i][0]=1;
		changeallow[i][0]=0;
		mapcolor[i][0]=0;
		map[i][MAP_WIDTH-1]=1;
		changeallow[i][MAP_WIDTH-1]=0;
		mapcolor[i][MAP_WIDTH-1]=0;
		map[i][16]=1;
		changeallow[i][16]=0;
		mapcolor[i][16]=0;	
	}
	for(int i=0;i<BLANK_HEIGHT;i++){
		for(int j=0;j<BLANK_WIDTH;j++){
			changeallow[i][j]=0;
		}
	}
}
void Tetris::drawMap(){         //���Ƶ�ͼ   һ������ռ�����ո�����Ҫ  ��2 
		for(int i=0;i<MAP_HEIGHT;i++){
			for(int j=0;j<MAP_WIDTH;j++){
				if(i>14&&i<MAP_HEIGHT-1&&j>16&&j<MAP_WIDTH-1){
					color(0);
					pos(17*2,5);
					cout<<"��һ������Ϊ��";
					pos(17*2,20);
					cout<<"����ǰ�÷�Ϊ��";
					pos(19*2,22);
					cout<<score;
					pos(17*2,24);
					cout<<"�ٽ�����Ŷ";
					pos(17*2,27);
					cout<<"(*~_~*)(*~_~*)";
				}
				else{
					if(map[i][j]==1){
					color(mapcolor[i][j]);
					pos(j*2,i);
					cout<<"��";
				}
				if(map[i][j]==0){
					color(mapcolor[i][j]);
					pos(j*2,i);
					cout<<"  ";
				}
				}
			}
		}
	}
void importcolor(){				//���뷽����ɫ
	for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(curblock[i][j]==1){
				blockcolor[i][j]=curcolor;
			}
			else 
			blockcolor[i][j]=0;	
		}
	}	
}
void Tetris::drawBlock(){   	//���Ʒ��� 
		for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(changeallow[Y+i][X+j]){
				map[Y+i][j+X]=curblock[i][j];
				mapcolor[Y+i][j+X]=blockcolor[i][j];
				if(map[Y+i][j+X]==1){
					color(mapcolor[Y+i][j+X]);
					pos((X+j)*2,(Y+i));
					cout<<"��";
				}
				
			}		
		}
	}	
}
void Tetris::clean(){           //������ۼ� 
		for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(changeallow[Y+i][X+j]){
				map[Y+i][j+X]=0;
				changeallow[Y+i][j+X]=1;
				pos((X+j)*2,(Y+i));
				cout<<"  ";				
			}
		}
	}
}
bool Tetris::candrop(){         //�Ƿ�������� 
	for(int i=BLOCK_WIDTH-1;i>=0;i--){
		for(int j=BLOCK_HEIGHT-1;j>=0;j--){
			if(Y+i+1==4){
				return 1;
			}
			if(curblock[i][j]==1&&map[Y+i+1][X+j]==1&&changeallow[Y+i+1][X+j]==0){
				for(int m=0;m<BLOCK_WIDTH;m++){//���޷�����ķ��鲻�����ƶ� 
					for(int n=0;n<BLOCK_HEIGHT;n++){
						if(map[Y+m][n+X]==1) changeallow[Y+m][n+X]=0;
					}
				}
				newblock();	
				return 0;
			}
		}
	}
	return 1;
}
void Tetris::newblock(){       	//��һ�ֵ����·��� 
	bool flag=1;
	for(int i=1;i<16;i++){
		if(map[5][i]==1&&changeallow[5][i]==0){
			flag=0;
			break;	
		}
	}
	if(!flag){                 //��Ϸʧ�� 
		color(3);
		system("cls");
		cout<<"GAME OVER"<<endl<<"�������յ÷�Ϊ��"<<score;		
			exit(0);
		
	}
	else{
		setBlockData();
		nextblock();
		cleanrow();
		X=6;
		Y=0;
		drop();
	}
}
void Tetris::cleanrow(){     	//��һ�������һ�� 
	bool canclean=0;
	int flag=0;
	bool canend=0;
	int cleanrownum=0;
	while(!canend){
		for(int i=MAP_HEIGHT-2;i>BLANK_HEIGHT+1;i--){//���¶��ϼ�� 
			for(int j=1;j<16;j++){
				if(map[i][j]==1){
					flag++;
				}
			}
			if(flag==15){
				cleanrownum=i;
				canclean=1;
				score+=10;
				break;
			}
			if(i==BLANK_HEIGHT+2) canend=1;
			flag=0;
		}
		if(canclean){
			for(int i=cleanrownum;i>BLANK_HEIGHT+1;i--){
				for(int j=1;j<16;j++){
					map[i][j]=map[i-1][j];
					changeallow[i][j]=changeallow[i-1][j];
					mapcolor[i][j]=mapcolor[i-1][j];
				}
			}
			drawMap();
		}
		flag=0;
		canclean=0;
	}
}
bool Tetris::canleft(){        //�Ƿ��������
	for(int i=BLOCK_WIDTH-1;i>=0;i--){
		for(int j=BLOCK_HEIGHT-1;j>=0;j--){
			if(curblock[i][j]==1&&map[Y+i][X+j-1]==1&&changeallow[Y+i][X+j-1]==0){
				return 0;
			}
		}
	}
	return 1;
}
bool Tetris::canright(){       //�Ƿ�������� 
	for(int i=BLOCK_WIDTH-1;i>=0;i--){
		for(int j=BLOCK_HEIGHT-1;j>=0;j--){
			if(curblock[i][j]==1&&map[Y+i][X+j+1]==1&&changeallow[Y+i][X+j+1]==0){
				return 0;
			}
		}
	}
	return 1;
}
void Tetris::drop(){           //���亯�� 
	int key=0;
	clock_t last,next;
	next = last = clock();
	while(1){
		next = clock();
			if(_kbhit()){
			key=getch();
			transform(key);
			continue;
		}
		if(! kbhit()){
			if((double)(next-last) >= interval()&&candrop()){
				next = last = clock();
			clean();
			Y++;
			drawBlock();
			}
		}
		
	}
}
void Tetris::up(){             //�ϼ���ת�л� 
	int b0=b;
	if(b==3) b=0;
	else b++;
	curblock=arrBlock[a].blockData[b].data;
	for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(curblock[i][j]==1&&map[Y+i][j+X]==1&&changeallow[Y+i][j+X]==0){
				b=b0;
				break;
			}
		}
	}	
	curblock=arrBlock[a].blockData[b].data;
	importcolor();
}
void Tetris::nextblock(){      //������һ������ 
	color(0);
	for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(changeallow[7+i][19+j]){//Y=7,x18
				map[7+i][j+19]=nxtblock[i][j];
				if(map[7+i][j+19]==1){
					pos((19+j)*2,(7+i));
					cout<<"��";
				}
				if(map[7+i][j+19]==0){
					pos((19+j)*2,(7+i));
					cout<<"  ";
				}
			}		
		}
	}	
} 
void Tetris::down(){			//�¼����� 
	clean();
	Y++;
	drawBlock();
}
void Tetris::left(){           //����
	if(canleft()){
		clean();
		X--;
		drawBlock();
	}
}
void Tetris::right(){		   // ���� 
	if(canright()){
		clean();
		X++;
		drawBlock();
	}
}
int main()
{
	Tetris game;
	game.start();
	initial();
	game.createMap();
	game.drawMap();
	srand ( time(NULL)-10 );
	c=rand()%7;
    d=rand()%4;
	setBlockData();
	game.nextblock();
	game.drop();
	return 0;
}

