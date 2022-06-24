#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#define MAP_HEIGHT 34           //整个界面高度（包含准备区域） 
#define MAP_WIDTH 25			// 整个界面宽度（包含准备区域）
#define BLOCK_HEIGHT 4          //方块高度 
#define BLOCK_WIDTH 4			//方块宽度 
#define BLANK_HEIGHT 4			//准备区域高度
#define BLANK_WIDTH 25			//准备区域宽度 
int map[MAP_HEIGHT][MAP_WIDTH]={0};//绘制全界面的二维数组 ->相当于棋盘  一个元素对应一个格子    1代表有方块，0代表没有方块 
bool changeallow[MAP_HEIGHT][MAP_WIDTH]={0};//界面二维数组无法全部初识化为一 ，需要预处理    1代表可以被改变，0代表不可以改变   边界和无法下落的都不可改变 
int mapcolor[MAP_HEIGHT][MAP_WIDTH]={0};//绘制全界面的颜色 
int blockcolor[MAP_HEIGHT][MAP_WIDTH]={0};//方块的颜色 
int score=0;					//得分
int X=6,Y=0;                    //方块为4*4数组 X，Y标记左上角起始位置 
int a,b,c,d;					//a，b可表示当前方块种类    c，d可表示下一个方块种类
int (*curblock)[4];				//当前方块
int (*nxtblock)[4];				//下一个方块
int curcolor;					//当前方块颜色 
void importcolor();				//导入方块颜色
void initial(); 				//初始化 
void setBlockData();			//方块种类数据 
using namespace std;
typedef struct BlockData  		 // 表示一个方块所有方向的数据
{
    int data[BLOCK_HEIGHT][BLOCK_WIDTH]; 
}BlockData;

typedef struct Block
{
    BlockData blockData[4]; 	// 最多4个方向数据
}Block;
Block arrBlock[6];
class Tetris{
	private:
		int rank;				//难度等级
	public:
		int interval();			//rank划分等级
		void drawBlock();		//呈现方块 
		void start();			//绘制开始界面 
		void createMap();		//创建游戏界面  
		void drawMap();			//绘制游戏界面 
		void createBlock();		//创建4*4方块 
		void drop();			//定时下落
		void clean();			//清除上一步痕迹 
		void transform(int);	//按键操作 
		void up();				//上键旋转 
		void down();			//下键加速 
		void left();			//左移 
		void right();			//右移 
		void pause();			//空格暂停 
		bool candrop();			//判断是否可以下落
		bool canleft();			//判断是否可以左移
		bool canright();		//判断是否可以右移 
		void newblock();		//下一轮函数
		void cleanrow();		//消除堆满的整行 
		void nextblock();		//呈现下一个函数 
		
};
void initial(){        			//初始化 
	for(int i=0;i<MAP_HEIGHT;i++){
		for(int j=0;j<MAP_WIDTH;j++){
			changeallow[i][j]=1;
		}
		cout<<endl;
	}

}
void setBlockData(){			// 方块种类数据 
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
    curblock=arrBlock[a].blockData[b].data;  //当前方块 
    importcolor();
    c=rand()%7;
    d=rand()%4;
    nxtblock=arrBlock[c].blockData[d].data; //下一个方块 
}
void pos(int x, int y) {        //表示坐标
	COORD pos;					 
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//偏移光标位置
}
void color(int colorNum){	    //设置颜色		
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
void Tetris::start(){			//绘制开始界面 得到等级rank 
	int x;
	while(1){
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "■              俄罗斯方块              ■" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "■              玩法规则：              ■" << endl;
		cout << "■              ↑ - 旋转               ■" << endl;
		cout << "■              ↓ - 加速下移           ■" << endl;
		cout << "■              ← - 左移               ■" << endl;
		cout << "■              → - 右移               ■" << endl;
		cout << "■              空格 - 暂停             ■" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl<<endl;
		cout << ">>按1—5选择难度:";
		x=getchar();
		if(x>'0'&&x<'6'){
			rank=x-'0';
			system("cls");
			break;
		}
	}
}
int Tetris::interval(){			//rank划分等级
	switch(rank){
		case 1:return 1250;
		case 2:return 500;
		case 3:return 300;
		case 4:return 120;
		case 5:return 70;
	}
}
void Tetris::transform(int key){//按键操作
	if(key==27)
		exit(0);
		else if(key==75) {//左
			left();
		}
		else if(key==77) {//右
			right(); 
		}
		else if(key==72) {//上 
			up();
		}
		else if(key==80) {//下
		if(candrop())
			down();
		}
		else if(key==32){
			getch();
		}
}
void Tetris::createMap(){ 		//创建不可变初始地图  
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
void Tetris::drawMap(){         //绘制地图   一个方块占两个空格所以要  ×2 
		for(int i=0;i<MAP_HEIGHT;i++){
			for(int j=0;j<MAP_WIDTH;j++){
				if(i>14&&i<MAP_HEIGHT-1&&j>16&&j<MAP_WIDTH-1){
					color(0);
					pos(17*2,5);
					cout<<"下一个方块为：";
					pos(17*2,20);
					cout<<"您当前得分为：";
					pos(19*2,22);
					cout<<score;
					pos(17*2,24);
					cout<<"再接再厉哦";
					pos(17*2,27);
					cout<<"(*~_~*)(*~_~*)";
				}
				else{
					if(map[i][j]==1){
					color(mapcolor[i][j]);
					pos(j*2,i);
					cout<<"■";
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
void importcolor(){				//导入方块颜色
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
void Tetris::drawBlock(){   	//绘制方块 
		for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(changeallow[Y+i][X+j]){
				map[Y+i][j+X]=curblock[i][j];
				mapcolor[Y+i][j+X]=blockcolor[i][j];
				if(map[Y+i][j+X]==1){
					color(mapcolor[Y+i][j+X]);
					pos((X+j)*2,(Y+i));
					cout<<"■";
				}
				
			}		
		}
	}	
}
void Tetris::clean(){           //清理方块痕迹 
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
bool Tetris::candrop(){         //是否可以下落 
	for(int i=BLOCK_WIDTH-1;i>=0;i--){
		for(int j=BLOCK_HEIGHT-1;j>=0;j--){
			if(Y+i+1==4){
				return 1;
			}
			if(curblock[i][j]==1&&map[Y+i+1][X+j]==1&&changeallow[Y+i+1][X+j]==0){
				for(int m=0;m<BLOCK_WIDTH;m++){//是无法下落的方块不能再移动 
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
void Tetris::newblock(){       	//下一轮掉落新方块 
	bool flag=1;
	for(int i=1;i<16;i++){
		if(map[5][i]==1&&changeallow[5][i]==0){
			flag=0;
			break;	
		}
	}
	if(!flag){                 //游戏失败 
		color(3);
		system("cls");
		cout<<"GAME OVER"<<endl<<"您的最终得分为："<<score;		
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
void Tetris::cleanrow(){     	//有一行满清除一行 
	bool canclean=0;
	int flag=0;
	bool canend=0;
	int cleanrownum=0;
	while(!canend){
		for(int i=MAP_HEIGHT-2;i>BLANK_HEIGHT+1;i--){//自下而上检查 
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
bool Tetris::canleft(){        //是否可以左移
	for(int i=BLOCK_WIDTH-1;i>=0;i--){
		for(int j=BLOCK_HEIGHT-1;j>=0;j--){
			if(curblock[i][j]==1&&map[Y+i][X+j-1]==1&&changeallow[Y+i][X+j-1]==0){
				return 0;
			}
		}
	}
	return 1;
}
bool Tetris::canright(){       //是否可以右移 
	for(int i=BLOCK_WIDTH-1;i>=0;i--){
		for(int j=BLOCK_HEIGHT-1;j>=0;j--){
			if(curblock[i][j]==1&&map[Y+i][X+j+1]==1&&changeallow[Y+i][X+j+1]==0){
				return 0;
			}
		}
	}
	return 1;
}
void Tetris::drop(){           //下落函数 
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
void Tetris::up(){             //上键旋转切换 
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
void Tetris::nextblock(){      //呈现下一个方块 
	color(0);
	for(int i=0;i<BLOCK_WIDTH;i++){
		for(int j=0;j<BLOCK_HEIGHT;j++){
			if(changeallow[7+i][19+j]){//Y=7,x18
				map[7+i][j+19]=nxtblock[i][j];
				if(map[7+i][j+19]==1){
					pos((19+j)*2,(7+i));
					cout<<"■";
				}
				if(map[7+i][j+19]==0){
					pos((19+j)*2,(7+i));
					cout<<"  ";
				}
			}		
		}
	}	
} 
void Tetris::down(){			//下键加速 
	clean();
	Y++;
	drawBlock();
}
void Tetris::left(){           //左移
	if(canleft()){
		clean();
		X--;
		drawBlock();
	}
}
void Tetris::right(){		   // 右移 
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

