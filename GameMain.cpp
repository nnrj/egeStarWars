//思路：用线性表记录当前所有food的位置 清除屏幕 根据键盘动作刷新player位置 
//随着玩家变大而变大 超出屏幕区域则消失 玩家移动到屏幕边缘 背景后退 相对玩家移动 
//两个玩家 被吃后自动复活 复活后一定时间内不被吃 //特殊食物 迅速变大
//单人游戏、双人游戏 
//分屏显示 
//单人游戏 分身大于某个值时失去控制 攻击玩家
//双人游戏 互相攻击 

#include "Game.h"
#include <graphics.h>

#define GAME_WIDTH 1000 //窗口高度 
#define GAME_HEIGHT 600 //窗口宽度 
#define DEFAULT_R 5 //小圆点的默认大小 
#define MY_R 12 //玩家角色的默认大小 
#define MY_STEP 10 //玩家的默认步伐 
#define MAX_NUM 100 //最大食物数量 
#define MIN_NUM MAX_NUM*0.3 //最小食物数量 
#define DEFAULT_ID 0 //小圆点的默认ID 
#define MAX_TIME 500; //初始时间 
#define PI 3.14 //圆周率 
#define FPS  8 //刷新率 
#define CH_NUM 4 //开始界面选项个数 
#define BRICK_NUM 10 //默认砖块数量 
#define BRICK_DEPTH 0 //砖块深度 
#define BR_R (sqrt(40*40+25*25))/2 //砖块外接圆半径大小 
#define BULLET_NUM 50 //默认子弹最大数量 
#define BULLET_R 3 //子弹半径 
#define BULLET_STEP MY_STEP*2 //子弹射速 
#define MATURE_R MY_R*1.5 //发育成熟半径 

typedef int Status;

int foodNum = 0;
int gameTime = MAX_TIME;
int randomX = 0;
int temp = 0;
int bullseye = -1;

void gameHelp();
int gameStart();
//void startRefresh(int ch);
int createPoint(Point *point);
int XYCheck(Point *player,Brick *brick);
void startRefresh(SqStack &S);
//int startControl();
int startControl(SqStack &S);
void createBrick(Brick *brick);
void createBullet(Bullet *bullet,Point *player,int dir);
void AIPlayerControl(Point *player,Point *player2,Bullet *bullet,LinkList &food_L);
int playerRefresh(Point *player,int ch);
int gameMain();
int visitPlayer(Point *player);
int createFood(LinkList &food_L);
int newPlayer(Point *player);
int gameControl(Point *player,Brick *brick,Bullet *bullet,int ch);
//int gameRefresh(Point *player,LinkList &food_L);
int gameRefresh(Point *player,LinkList &food_L,Brick *brick,Bullet *bullet);
void gameEnd();
void gameOver(Point *player,Point *player2,int ch);
int gameSave();
//int gameControl(BiTree &player_T,LinkList &food_L);
//void gameControl(Point *player);
//int gameRefresh(BiTree player_T);
//int playerRefresh(Point *player,LinkList &food_L);
//int gameRefresh(BiTree player_T,LinkList &food_L);


//int main(int argc, char** argv) {
int main(void) {
	int wl = 0,hl = 0,sum = 0;
	setinitmode(INIT_DEFAULT|INIT_NOFORCEEXIT);
	initgraph(GAME_WIDTH,GAME_HEIGHT);
	setcaption("星球大战1.0");
	randomize();
	setrendermode(RENDER_MANUAL);
	setbkcolor(EGERGB(15, 30, 15));
	/*while(sum <= GAME_WIDTH){
		sum = sum + GAME_WIDTH/10; 
		line(sum,0,sum,GAME_HEIGHT);
	}*/
	gameMain();

	closegraph();
	return 0;
}

int gameMain(){
	int ran = 0;
	int gameCh = 0,flag = 1;
	int maxTime = MAX_TIME;
	LinkList food_L;
	BiTree player_T;
	SqStack S;
	InitStack(S);
	Point *player,*player2;
	Brick brick[BRICK_NUM];
	Bullet bullet[BULLET_NUM];
	createBrick(brick);
	player = (Point *)malloc(POINT_SIZE);
	player2 = (Point *)malloc(POINT_SIZE);
	/*for(ch = CH_NUM;ch < 0;ch--){
		Push(S,ch);
	}*/
	for(int i = 0;i < BULLET_NUM;i++){
		bullet[i].bullet.live = FALSE;
	}
	InitList(food_L);
	//InitTree(player_T);
	
	newPlayer(player);
	newPlayer(player2);
	player->ID = -1;
	player2->ID = -2;
	//InsBiTree(player_T,player);
	//InsBiTree(player_T);
	//newPlayer(player_T->data);
	createFood(food_L);
	
	//player_T->data = player;
	//newPlayer(player_T->data);
	//newPlayer(player);
	
	//player = player_T->data;
	//newPlayer(player_T->data);
	//player_T.data = player;
	//*(player_T->data) = *player;
	//gameCh = gameStart();
	player2->coor.X = player2->coor.X + 50;
	gameCh = startControl(S);
	if(gameCh == 1){	
		//for(;is_run();delay_fps(FPS*1.5)){
		for(;is_run();delay_fps(FPS*1.5)){			
			if(gameTime > 0){
				//flag = 1;
				//if(flag == 1){
					gameControl(player,brick,bullet,1);
					//randomize(); ran = random(31);
					//if(ran <= 13){
						AIPlayerControl(player,player2,bullet,food_L);
					//}
				//}	
				//gameControl(player,2);
				cleardevice();									
				gameTime = maxTime - (int)fclock();	
				//gameRefresh(player,food_L);
				gameRefresh(player,food_L,brick,bullet);
				gameRefresh(player2,food_L,brick,bullet);
				//gameRefresh(player2,food_L,brick,bullet);
				playerRefresh(player,1);
				playerRefresh(player2,2);
				//playerRefresh(player,brick,1);
			}
			else{
				gameOver(player,player2,1);
			}		
		}
		return 0;	
	}
	else if(gameCh == 2){
		//Point *player2;
		//newPlayer(player2);
		int distance = -1;
		//player2->ID = -1;
		for(;is_run();delay_fps(FPS*2)){			
			distance = sqrt(((player->coor.X - player2->coor.X)*(player->coor.X - player2->coor.X)) + ((player->coor.Y - player2->coor.Y)*(player->coor.Y - player2->coor.Y)));			
			if(gameTime > 5){
				if(distance != -1 && distance <= fabs(player->R - player2->R)){
					if(player->R > player2->R && player2->R > MY_R){
						player->R = sqrt((player->R) * (player->R) + (player2->R) * (player2->R)/3);
						if(player->step > 5){
							player->step = player->step - (player->R / 12)/3*0.1;		
						}
						player2->live = FALSE;
						newPlayer(player2);
					}
					if(player->R < player2->R && player->R > MY_R){
						player2->R = sqrt((player2->R) * (player2->R) + (player->R) * (player->R)/3);
						if(player2->step > 5){
							player2->step = player2->step - (player2->R / 12)/3*0.1;		
						}
						player->live = FALSE;
						newPlayer(player);						
					}
					distance = -1;						
				}				
			}
			if(gameTime > 0){
				cleardevice();
				//setfillstyle(RED);				
				gameControl(player,brick,bullet,1);
				gameControl(player2,brick,bullet,2);
				gameTime = maxTime - (int)fclock();	
				//gameRefresh(player,food_L);
				//gameRefresh(player2,food_L);
				gameRefresh(player,food_L,brick,bullet);
				gameRefresh(player2,food_L,brick,bullet);
				playerRefresh(player,1);
				playerRefresh(player2,2);
				//playerRefresh(player,brick,1);
				//playerRefresh(player2,brick,2);
			}
			else{
				gameOver(player,player2,2);
			}		
		}			
	}
	else if(gameCh == 3){
		gameHelp();
	}
	else if(gameCh == 4){
		gameEnd();
	}
	return TRUE;
}

int createPoint(Point *point){
	//point = (Point *)malloc(POINT_SIZE);
	randomize();point->color.LINE_R = random(255);
	randomize();point->color.LINE_G = random(255);
	randomize();point->color.LINE_B = random(255);
	randomize();point->color.FILL_R = random(255);
	randomize();point->color.FILL_G = random(255);
	randomize();point->color.FILL_B = random(255);
	randomize();point->coor.X = random(GAME_WIDTH);
	randomize();point->coor.Y = random(GAME_HEIGHT);
	point->R = DEFAULT_R;point->ID = DEFAULT_ID;
	point->live = TRUE;point->step = MY_STEP;
	return TRUE;
}

int createFood(LinkList &food_L){
	int num = 0;
	Point point;
	for(;num < MAX_NUM;num++){
		//if(num > MAX_NUM){
		//	break;
	//	}
	//	else{
		createPoint(&point);
		point.ID = num+1;
		point.R = DEFAULT_R;
		setcolor(EGERGB(point.color.LINE_R,point.color.LINE_G,point.color.LINE_B));
		setfillcolor(EGERGB(point.color.FILL_R,point.color.FILL_G,point.color.FILL_B));
		fillellipse(point.coor.X,point.coor.Y,point.R,point.R);	
		InsAfter(food_L,point);				
	//	}		
	}
	foodNum = MAX_NUM;
	return TRUE;
}

int newPlayer(Point *player){
	createPoint(player);
	player->coor.X = GAME_WIDTH/2;
	player->coor.Y = GAME_HEIGHT/2;
	player->R = MY_R;
	player->ID = 0;
	
	setcolor(EGERGB(player->color.LINE_R,player->color.LINE_G,player->color.LINE_B));
	setfillcolor(EGERGB(player->color.FILL_R,player->color.FILL_G,player->color.FILL_B));
	fillellipse(player->coor.X,player->coor.Y,player->R,player->R);
	return TRUE;
}

//int gameControl(Point *player){
//int gameControl(BiTree &player_T){
int gameControl(Point *player,Brick *brick,Bullet *bullet,int ch){
	int flag = 1,distance = -1,dir = 0;
	for(int i = 0;i < BRICK_NUM;i++){
		flag = 0;
		//distance = sqrt((brick[i].lift - brick[i].right)*(brick[i].lift - brick[i].right) + (brick[i].top - brick[i].bottom)*(brick[i].top - brick[i].bottom));
		//distance = distance/2;
		
		//distance = sqrt( (player->coor.X - (brick[i].lift+brick[i].width/2)) * (player->coor.X - (brick[i].lift+brick[i].width/2)) +  (player->coor.Y - (brick[i].top+brick[i].height/2)) * (player->coor.Y - (brick[i].top+brick[i].height/2)));
		distance = sqrt( (player->coor.X - brick[i].X) *  (player->coor.X - brick[i].X) + (player->coor.Y - brick[i].Y) * (player->coor.Y - brick[i].Y));
		if(distance != -1 && distance <= (brick[i].br_r)){
			if((player->coor.Y + 2*player->R) >= brick[i].top){
				player->coor.Y = player->coor.Y - MY_STEP;
			}
			else if((player->coor.Y - 2*player->R) <= brick[i].bottom){
				player->coor.Y = player->coor.Y + MY_STEP;
				//reSet = 1;
			}
			if((player->coor.X + 2*player->R) >= brick[i].lift){
				player->coor.X= player->coor.X - MY_STEP;
			}
			else if((player->coor.X - 2*player->R) <= brick[i].right){
				player->coor.X = player->coor.X + MY_STEP;
			}
			
			//if((player->X+player>R))
			//distance = -1;
			break;
		}
		else{
			flag = 1;
		}
	}	
	//Point player;
	//player = player_T.data; 
	//int mouseX,mouseY;
	//mousepos(&mouseX,&mouseY);
	//if(mouseX)
	//mousepos(&(player->coor.X),&(player->coor.Y));
		//distance = (player->coor.X - )
		//if((player->coor.X - MY_R) > brick[i].right || (player->coor.X + MY_R) < brick[i].lift || (player->coor.Y - MY_R) > brick[i].bottom || (player->coor.Y +MY_R) < brick[i].top){
		//if( (player->coor.X < brick[i].right) && (player->coor.X > brick[i].lift) && (player->coor.Y < brick[i].bottom) && (player->coor.Y > brick[i].top)){
//		if((player->coor.X - MY_R) <= brick[i].right && (player->coor.X + MY_R) >= brick[i].lift && (player->coor.Y - MY_R) <= brick[i].bottom && (player->coor.Y +MY_R) >= brick[i].top){
//			flag = 0;
//			if((player->coor.X - MY_R) <= brick[i].right){
//				player->coor.X+2;
//			}
//			if((player->coor.X + MY_R) >= brick[i].lift){
//				player->coor.X-2;
//			}
//			if((player->coor.Y - MY_R) <= brick[i].bottom){
//				player->coor.Y+2;
//			}
//			if((player->coor.Y +MY_R) >= brick[i].top){
//				player->coor.Y-2;
//			} 			
//			break;
//		}
//		else{
//			flag = 1;
			/*if((player->coor.X - MY_R) <= brick[i].right){
				player->coor.X+2;
			}
			if((player->coor.X + MY_R) >= brick[i].lift){
				player->coor.X-2;
			}
			if((player->coor.Y - MY_R) <= brick[i].bottom){
				player->coor.Y+2;
			}
			if((player->coor.Y +MY_R) >= brick[i].top){
				player->coor.Y-2;
			} 
			break;*/ 
//		}	 
//	}	
	if(ch == 1 && flag == 1){
	//if(ch == 1){
		if(!player){
			return FALSE;
		}
		else{
//			if(keystate(VK_SPACE)){//按下空格键 
//				createBullet(bullet,1);
				//player->R = 1;//测试 
				//gameRefresh(player_T.data,food_L);
//			}
			if(keystate(VK_ESCAPE)){
				gameMain();
			}
			if(keystate('W') || keystate('w') != FALSE){
				if(player->coor.Y != 0){
					player->coor.Y = player->coor.Y - player->step;
				}
				else{
					player->coor.Y = GAME_HEIGHT; 
				}
				dir = 1;
				//if(keystate(VK_SPACE)){//按下空格键 
					//exit(0);
				//	createBullet(bullet,player,1);
				//}
				//gameRefresh(player,food_L);
			}
			if(keystate('S') || keystate('s') != FALSE){
				if(player->coor.Y != GAME_HEIGHT){
					player->coor.Y = player->coor.Y + player->step;
				}
				else{
					player->coor.Y = 0;
				}
				dir = 2;
				/*if(keystate(VK_SPACE)){//按下空格键 
					createBullet(bullet,player,2);
				}*/				
				//gameRefresh(player,food_L);
			}
			if(keystate('A') || keystate('a') != FALSE){
				if(player->coor.X != 0){
					player->coor.X = player->coor.X - player->step;
				}
				else{
					player->coor.X = GAME_WIDTH;
				}
				dir = 3;
				/*if(keystate(VK_SPACE)){//按下空格键 
					createBullet(bullet,player,3);
				}*/				
				//gameRefresh(player,food_L);
			}
			if(keystate('D') || keystate('d') !=FALSE){
				if(player->coor.X != GAME_WIDTH){
					player->coor.X = player->coor.X + player->step;
				}
				else{
					player->coor.X = 0;
				}
				dir = 4;
				/*if(keystate(VK_SPACE)){//按下空格键 
					createBullet(bullet,player,4);
				}*/				
				//gameRefresh(player,food_L);
			}
			if(keystate(VK_SPACE)  && player->R >= MATURE_R && dir != 0){//按下空格键 
				createBullet(bullet,player,dir);
				dir = 0;
			}	
			if(player->coor.X == 0){
				player->coor.X = GAME_WIDTH;
			}
			else if(player->coor.X == GAME_WIDTH){
				player->coor.X = 0;
			}
			if(player->coor.Y == 0){
				player->coor.Y = GAME_HEIGHT;
			}
			if(player->coor.Y == GAME_HEIGHT){
				player->coor.Y = 0;
			}	
			//gameRefresh(player);		
		}
		//randomize();randomX = random(31);
		//if(randomX >= 13){
			randomX = player->coor.X - player->coor.Y;
			//randomX = player->coor.X - random(31);
		//} 
		//else{
		//	randomX = player->coor.Y - player->coor.X;
		//}
	}
	if(ch == 2 && flag == 1){
	//if(ch == 2){
		if(!player){
			return FALSE;
		}
		else{
			//if(keystate(VK_SPACE)){//按下空格键 
			//}
			if(keystate(VK_ESCAPE)){
				gameMain();
			}
			if(keystate(VK_UP) != FALSE){
				if(player->coor.Y != 0){
					player->coor.Y = player->coor.Y - player->step;
				}
				else{
					player->coor.Y = GAME_HEIGHT; 
				}
				dir = 1;
				/*if(keystate(VK_RETURN)){//按下空格键 
					createBullet(bullet,player,1);
				}*/				
			}
			if(keystate(VK_DOWN) != FALSE){
				if(player->coor.Y != GAME_HEIGHT){
					player->coor.Y = player->coor.Y + player->step;
				}
				else{
					player->coor.Y = 0;
				}
				dir = 2;
				/*if(keystate(VK_RETURN)){//按下空格键 
					createBullet(bullet,player,2);
				}*/				
			}
			if(keystate(VK_LEFT) != FALSE){
				if(player->coor.X != 0){
					player->coor.X = player->coor.X - player->step;
				}
				else{
					player->coor.X = GAME_WIDTH;
				}
				dir = 3;
				/*if(keystate(VK_RETURN)){//按下空格键 
					createBullet(bullet,player,3);
				}*/				
			}
			if(keystate(VK_RIGHT) !=FALSE){
				if(player->coor.X != GAME_WIDTH){
					player->coor.X = player->coor.X + player->step;
				}
				else{
					player->coor.X = 0;
				}
				dir = 4;
				/*if(keystate(VK_RETURN)){//按下空格键 
					createBullet(bullet,player,4);
				}*/				
			}
			//if((keystate(VK_RETURN) || keystate(VK_SEPARATOR)) && player->R >= MATURE_R && dir != 0){//按下空格键 
			if( (keystate(VK_RETURN) && player->R >= MATURE_R && dir != 0) || (keystate(VK_SEPARATOR) && player->R >= MATURE_R && dir != 0)){//按下空格键 
				createBullet(bullet,player,dir);
				dir = 0;
			}				
			if(player->coor.X == 0){
				player->coor.X = GAME_WIDTH;
			}
			else if(player->coor.X == GAME_WIDTH){
				player->coor.X = 0;
			}
			if(player->coor.Y == 0){
				player->coor.Y = GAME_HEIGHT;
			}
			else if(player->coor.Y == GAME_HEIGHT){
				player->coor.Y = 0;
			}		
		}		
	} 	
	return OK;
}

//int gameRefresh(BiTree player_T,LinkList &food_L){
//int gameRefresh(Point *player,LinkList &food_L){
int gameRefresh(Point *player,LinkList &food_L,Brick *brick,Bullet *bullet){
	//Point *player;
	//double timeNow = 0;
	Point point,addPoint;
	LinkList p;
	p = food_L->next;
	float distance = -1;
	cleardevice();
	while(p->next != NULL){
		point = p->data;
		distance = sqrt(((player->coor.X - point.coor.X)*(player->coor.X - point.coor.X)) + ((player->coor.Y - point.coor.Y)*(player->coor.Y - point.coor.Y)));
		if(distance != -1 && distance <= fabs(player->R - point.R)){
			player->R = sqrt((player->R) * (player->R) + (point.R) * (point.R)/3);
			if(player->step > 5){
				player->step = player->step - (point.R / 12)/3*0.1;		
			}
			point.live = FALSE;
			foodNum--;
			DelElem(food_L,point);
			distance = -1;	
		}
		if(point.live == TRUE){
			setcolor(EGERGB(point.color.LINE_R,point.color.LINE_G,point.color.LINE_B));
			setfillcolor(EGERGB(point.color.FILL_R,point.color.FILL_G,point.color.FILL_B));
			fillellipse(point.coor.X,point.coor.Y,point.R,point.R);			
		}	
		if(foodNum < MIN_NUM){
			for(int i = 1;i <= MAX_NUM - foodNum;i++){
				createPoint(&addPoint);
				addPoint.ID = point.ID + i;
				InsAfter(food_L,addPoint);
				foodNum++;
			}
		}
		p = p->next;	
	}	
	for(int i = 0;i < BRICK_NUM;i++){
		//setfillcolor(RED);
		//bar3d(100, 100, 150, 150, 20, 1);
		//setfillcolor(EGERGB(brick[i].color.FILL_R,brick[i].color.FILL_G,brick[i].color.FILL_B));
		setfillcolor(EGERGB(255,0,0));
		setcolor(EGERGB(96,96,96));
		//bar3d(brick[i].X[0],brick[i].Y[0],brick[i].X[1],brick[i].Y[1],brick[i].depth,TRUE);
		bar3d(brick[i].lift,brick[i].top,brick[i].right,brick[i].bottom,brick[i].depth,0);
		//bar3d(100,70,140,90,1,0);
	}
	for(int i = 0;i < BULLET_NUM;i++){
		if(bullet[i].bullet.live == TRUE){
			if(bullet[i].dir == 1){			
				//bullet[i].bullet.coor.Y = bullet[i].bullet.coor.Y - BULLET_STEP;
				bullet[i].bullet.coor.Y = bullet[i].bullet.coor.Y - BULLET_STEP;
			}
			else if(bullet[i].dir == 2){
				bullet[i].bullet.coor.Y = bullet[i].bullet.coor.Y + BULLET_STEP;
			}
			else if(bullet[i].dir == 3){
				bullet[i].bullet.coor.X = bullet[i].bullet.coor.X - BULLET_STEP;
			}
			else if(bullet[i].dir == 4){
				bullet[i].bullet.coor.X = bullet[i].bullet.coor.X + BULLET_STEP;
			}				
			distance = sqrt( (player->coor.X - bullet[i].bullet.coor.X) * (player->coor.X - bullet[i].bullet.coor.X) + (player->coor.Y - bullet[i].bullet.coor.Y) * (player->coor.Y - bullet[i].bullet.coor.Y) );		
			if(distance <= (player->R + bullet[i].bullet.R)){
				if(player->R >= MATURE_R){
					player->R = player->R - (bullet[i].bullet.R*1.5)/3;
				}
				bullet[i].bullet.live = FALSE;
			}
			for(int j = 0;j < BRICK_NUM;j++){
				distance =sqrt((brick[j].X - bullet[i].bullet.coor.X) * (brick[j].X - bullet[i].bullet.coor.X) + (brick[j].Y - bullet[i].bullet.coor.Y) * (brick[j].Y - bullet[i].bullet.coor.Y)); 
				if(distance <= brick[j].br_r){
					bullet[i].bullet.live = FALSE;
				}
			}	
			//if()
			/*if(distance <= (player->R + bullet[i].bullet.R) && bullet[i].belong != player->ID && player->R >= MY_R*2){
				player->R = player->R - bullet[i].bullet.R*3;
				bullet[i].bullet.live = FALSE;
			}*/
			/*if(distance <= (player->R - bullet[i].bullet.R) && bullet[i].belong == player->ID){
				player->R = player->R + bullet[i].bullet.R*0.4;
				bullet[i].bullet.live = FALSE;
			}*/			
			if(bullet[i].bullet.coor.X <= 0 || bullet[i].bullet.coor.X >= GAME_WIDTH || bullet[i].bullet.coor.Y <= 0 || bullet[i].bullet.coor.Y >= GAME_HEIGHT){
				bullet[i].bullet.live = FALSE;
			}
			setcolor(EGERGB(bullet[i].bullet.color.LINE_R,bullet[i].bullet.color.LINE_G,bullet[i].bullet.color.LINE_B));
			setfillcolor(EGERGB(bullet[i].bullet.color.FILL_R,bullet[i].bullet.color.FILL_G,bullet[i].bullet.color.FILL_B));
			fillellipse(bullet[i].bullet.coor.X,bullet[i].bullet.coor.Y,bullet[i].bullet.R,bullet[i].bullet.R);									
		}		
	}
	if(player->R < MY_R){
		player->live = FALSE;
		newPlayer(player);
	}
	LOGFONTA f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 10;                      // 设置字体高度为 48（包含行距）
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
	setcolor(EGERGB(73, 178, 33));
	return OK;
}

int visitPlayer(Point *player){
	//gameControl(player,1);
	//gameRefresh(&player,food_L);//food_L怎么传过来--------------------------断点 
}

int startControl(SqStack &S){
	int ch = 1;
	//SqStack S;
	cleardevice();
	setbkcolor(EGERGB(15, 30, 40));
	for(ch = CH_NUM;ch > 0;ch--){
		Push(S,ch);
	}		
	//InitStack(S);
	startRefresh(S);
	for(;is_run();delay_fps(10)){
		GetTop(S,ch);			
		if(keystate(VK_UP) != FALSE || keystate(VK_LEFT) != FALSE ||  keystate('W') != FALSE || keystate('w') != FALSE || keystate('A') != FALSE || keystate('a') != FALSE){		
			/*Push(S,ch-1);			
			if (StackLength(S) >= CH_NUM){
				ClearStack(S);
				Push(S,CH_NUM);			
			}*/
			if (StackLength(S) < CH_NUM){
				Push(S,ch-1);		
			}
			else{
				ClearStack(S);
				Push(S,CH_NUM);				
			}
			startRefresh(S);
		}
		else if(keystate(VK_DOWN) != FALSE || keystate(VK_RIGHT) != FALSE || keystate('S') != FALSE || keystate('s') != FALSE || keystate('D') != FALSE || keystate('d') != FALSE){
			Pop(S,ch);
			if(StackEmpty(S)){
				for(ch = CH_NUM;ch > 0;ch--){
					Push(S,ch);
				}
			}

			/*if(!StackEmpty(S)){
				Pop(S,ch);
			}
			else{
				for(ch = CH_NUM;ch > 0;ch--){
					Push(S,ch);
				}				
			}*/
			startRefresh(S);
		}
		startRefresh(S);
		if(keystate(VK_RETURN) != FALSE || keystate(VK_SEPARATOR) != FALSE || keystate(VK_SPACE) != FALSE){
			GetTop(S,ch);
			setbkcolor(EGERGB(15, 30, 15));
			return ch;
		}		
	}	
	return OK;
}

/*int startControl(){
	int ch = 1;
	cleardevice();
	setbkcolor(EGERGB(15, 30, 40));

	for(;is_run();delay_fps(10)){
		startRefresh(ch);			
		if(keystate(VK_UP) != FALSE || keystate(VK_LEFT) != FALSE ||  keystate('W') != FALSE || keystate('w') != FALSE || keystate('A') != FALSE || keystate('a') != FALSE){
			if(ch > 1 && ch <= 4){
				ch--;
			}
			else{
				ch = 4;
			}
			startRefresh(ch);
		}
		else if(keystate(VK_DOWN) != FALSE || keystate(VK_RIGHT) != FALSE || keystate('S') != FALSE || keystate('s') != FALSE || keystate('D') != FALSE || keystate('d') != FALSE){
			if(ch >= 1 && ch < 4){
				ch++;
			}
			else{
				ch = 1;
			}
			startRefresh(ch);
		}
		if(keystate(VK_RETURN) != FALSE || keystate(VK_SEPARATOR) != FALSE || keystate(VK_SPACE) != FALSE){
			switch(ch){
				case 1:return 1;break;
				case 2:return 2;break;
				case 3:return 3;break;
				case 4:return 4;break;
			}
		}		
	}	
	setbkcolor(EGERGB(15, 30, 15));
	return OK;
}*/

/*int gameStart(){
	cleardevice();
	setbkcolor(EGERGB(15, 30, 40));
	char ch = '0';
	LOGFONTA f;
	getfont(&f);                          // 获取当前字体设置
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	f.lfHeight = 72;                           // 设置字体样式
	setfont(&f); 
	setcolor(EGERGB(200, 220, 120));
	xyprintf(GAME_WIDTH/2-80,GAME_HEIGHT/2-200,"星  球  大  战  1.0");
	setcolor(EGERGB(255, 0, 0));
	f.lfHeight = 36; 
	strcpy(f.lfFaceName, "幼圆"); 
	setfont(&f); 
	//outtextxy(0,50,"抗锯齿效果");
	xyprintf(GAME_WIDTH/2-50,GAME_HEIGHT/2-100,"<1>单 人 游 戏");
	xyprintf(GAME_WIDTH/2-50,GAME_HEIGHT/2-60,"<2>双 人 游 戏");
	xyprintf(GAME_WIDTH/2-50,GAME_HEIGHT/2-20,"<3>游 戏 帮 助");
	xyprintf(GAME_WIDTH/2-50,GAME_HEIGHT/2+20,"<4>退 出 游 戏");
	while(1){
		ch = getch();
		switch(ch){
			case '1':return 1;break;
			case '2':return 2;break;
			case '3':gameHelp();return 3;break;
			case '4':gameEnd();return 4;break;
		}
		if(keystate(VK_ESCAPE)){
			gameEnd();
		}
	}
	setbkcolor(EGERGB(15, 30, 15));
	return OK;
}*/

void gameOver(Point *player,Point *player2,int ch){//游戏结束，输赢判定 
	cleardevice();
	float body1 = 0,body2 = 0;
	LOGFONTA f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 50;                      // 设置字体高度为 48（包含行距）
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
	xyprintf(GAME_WIDTH/2-75,GAME_HEIGHT/2-125,"--游 戏 结 束--");
	setcolor(EGERGB(73, 178, 33));
	f.lfHeight = 25;                      // 设置字体高度为 48（包含行距）
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体” 
	setfont(&f);                          // 设置字体样式	
	if(ch == 1){
		body1 = 3.14*player->R*player->R;
		if(player->R < 50){
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2-25,"闯关失败！");
		}
		else{
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2,"闯关成功！");
		}
		xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2+25,"您的最终大小：%.2f",body1);
	}
	if(ch == 2){
		body1 = 3.14*player->R*player->R;
		body2 = 3.14*player2->R*player2->R;
		if(player->R > player2->R){
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2-50,"玩家A胜利！");
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2-25,"玩家A大小：%.2f",body1);
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2,"玩家B大小：%.2f",body2);
		}
		else{
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2-50,"玩家B胜利！");
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2-25,"玩家A大小：%.2f",body1);
			xyprintf(GAME_WIDTH/2-70,GAME_HEIGHT/2,"玩家B大小：%.2f",body2);			
		}
	}
	f.lfHeight = 25;                      // 设置字体高度为 48（包含行距）
	setfont(&f); 
	xyprintf(GAME_WIDTH/2-75,GAME_HEIGHT/2+75,"--按ESC键退出--");	
	if(keystate(VK_ESCAPE)){
		gameEnd();
	}
}

void gameHelp(){
	for(;is_run();delay_fps(10)){
		cleardevice();
		float body1 = 0,body2 = 0;
		LOGFONTA f;
		getfont(&f);                          // 获取当前字体设置
		f.lfHeight = 50;                      // 设置字体高度为 48（包含行距）
		strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
		f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
		setfont(&f);                          // 设置字体样式
		xyprintf(GAME_WIDTH/2-175,GAME_HEIGHT/2-150,"---使用帮助---");
		f.lfHeight = 25;                      // 设置字体高度为 48（包含行距）
		strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
		setcolor(EGERGB(73, 178, 33));
		setfont(&f);                          // 设置字体样式
		xyprintf(GAME_WIDTH/2-170,GAME_HEIGHT/2-75,"1.玩家A使用W、S、A、D控制上下左右移动;");
		xyprintf(GAME_WIDTH/2-170,GAME_HEIGHT/2-50,"2.玩家B使用↑、↓、←、→控制上下左右移动;");
		xyprintf(GAME_WIDTH/2-170,GAME_HEIGHT/2-25,"3.单人游戏时，在规定时间内，玩家半径大于50时胜利，否则失败;");
		xyprintf(GAME_WIDTH/2-170,GAME_HEIGHT/2,"4.双人游戏时，在规定时间内，体积大者胜出;");
		xyprintf(GAME_WIDTH/2-170,GAME_HEIGHT/2+25,"5.当食物数量小于一定数目时，会随机补充食物;");
		xyprintf(GAME_WIDTH/2-170,GAME_HEIGHT/2+50,"6.玩家半径大小大于18时将可以发射炮弹。");
		f.lfHeight = 50;                      // 设置字体高度为 48（包含行距）
		xyprintf(GAME_WIDTH/2-175,GAME_HEIGHT/2+100,"---按ESC键返回主界面---");
		if(keystate(VK_ESCAPE) != FALSE){
			gameMain();
			break;
		}	
	}
}

int playerRefresh(Point *player,int ch){
	//int flag = 1;
//	if(flag == 1){
	setcolor(EGERGB(player->color.LINE_R,player->color.LINE_G,player->color.LINE_B));
	setfillcolor(EGERGB(player->color.LINE_R,player->color.LINE_G,player->color.LINE_B));
	fillellipse(player->coor.X,player->coor.Y,player->R,player->R);
	//setcolor(EGERGB(player->color.LINE_R,player->color.LINE_G,player->color.LINE_B));				
//	}
	if(ch == 1){
		xyprintf(20,10,"[玩家A状态]");
		xyprintf(20,25,"剩余时间:%d",gameTime);
		xyprintf(20,35,"当前大小:%.2f",player->R);
		xyprintf(20,45,"食物数量:%d",foodNum);					
	}
	if(ch == 2){
		xyprintf(GAME_WIDTH-120,10,"[玩家B状态]");
		xyprintf(GAME_WIDTH-120,25,"剩余时间:%d",gameTime);
		xyprintf(GAME_WIDTH-120,35,"当前大小:%.2f",player->R);
		xyprintf(GAME_WIDTH-120,45,"食物数量:%d",foodNum);								
	}
	return OK;	
}

void gameEnd(){
	exit(0);
}

//void startRefresh(int ch){
void startRefresh(SqStack &S){
	int ch = 0;
	GetTop(S,ch);
	LOGFONTA f;
	getfont(&f);                          // 获取当前字体设置
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	cleardevice();
	f.lfHeight = 72;                           // 设置字体样式
	setbkcolor(EGERGB(15, 30, 40));
	setcolor(EGERGB(200, 220, 120));
	setfont(&f); 
	xyprintf(GAME_WIDTH/2-80,GAME_HEIGHT/2-200,"星  球  大  战  1.0");		
	if(ch == 1){
		setcolor(EGERGB(255, 0, 0));
		f.lfHeight = 36; 
		strcpy(f.lfFaceName, "幼圆"); 
		setfont(&f); 			
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-100,"--单 人 游 戏--");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-60,"  双 人 游 戏");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-20,"  游 戏 帮 助");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2+20,"  退 出 游 戏");
	//	xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-100,"  双 人 游 戏"); //此处可用入栈出栈改为齿轮操作，初始化 入栈四个数字 检测栈顶 加一减一 入栈出栈 
	//	xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-60,"--单 人 游 戏--");
	//	xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-20,"  游 戏 帮 助");
	//	xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2+20,"  退 出 游 戏");			
	}
	else if(ch == 2){
		setcolor(EGERGB(255, 0, 0));
		f.lfHeight = 36; 
		strcpy(f.lfFaceName, "幼圆"); 
		setfont(&f); 			
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-100,"  单 人 游 戏");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-60,"--双 人 游 戏-- ");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-20,"  游 戏 帮 助");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2+20,"  退 出 游 戏");					
	}
	else if(ch == 3){
		setcolor(EGERGB(255, 0, 0));
		f.lfHeight = 36; 
		strcpy(f.lfFaceName, "幼圆"); 
		setfont(&f); 
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-100,"  单 人 游 戏");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-60,"  双 人 游 戏");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-20,"--游 戏 帮 助--");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2+20,"  退 出 游 戏");			
	}
	else if(ch == 4){
		setcolor(EGERGB(255, 0, 0));
		f.lfHeight = 36; 
		strcpy(f.lfFaceName, "幼圆"); 
		setfont(&f); 
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-100,"  单 人 游 戏");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-60,"  双 人 游 戏 ");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2-20,"  游 戏 帮 助");
		xyprintf(GAME_WIDTH/2-60,GAME_HEIGHT/2+20,"--退 出 游 戏--");			
	}
}

void createBrick(Brick *brick){
	for(int i = 0;i < BRICK_NUM;i++){
		brick[i].width = 40;
		brick[i].height = 25;
		randomize();brick[i].lift = random(GAME_WIDTH);
		brick[i].right = brick[i].lift + brick[i].width;
		randomize();brick[i].top = random(GAME_HEIGHT);
		brick[i].bottom = brick[i].top + brick[i].height;
		randomize();brick[i].color.FILL_R = 255;
		randomize();brick[i].color.FILL_G = 0;
		randomize();brick[i].color.FILL_B = 0;
		randomize();brick[i].color.LINE_R = 96;
		randomize();brick[i].color.LINE_G = 96;
		randomize();brick[i].color.LINE_B = 96;
		brick[i].depth = BRICK_DEPTH;
		brick[i].br_r = (sqrt(40*40+25*25))/2;
		brick[i].X = (brick[i].lift + brick[i].right)/2;
		brick[i].Y = (brick[i].top + brick[i].bottom)/2;
		if(brick[i].lift > (GAME_WIDTH/2-MY_R) && brick[i].lift < (GAME_WIDTH/2+MY_R) && brick[i].top > (GAME_HEIGHT/2-MY_R) && brick[i].top < (GAME_HEIGHT/2+MY_R)){
			i--;
		}
		if( (brick[i].lift <= 20 && brick[i].top <=50) || (brick[i].right > GAME_WIDTH-120 && brick[i].top <=50)){
			i--;
		}
	}
}

void createBullet(Bullet *bullet,Point *player,int dir){
	for(int i = 0;i < BULLET_NUM;i++){
		if(bullet[i].bullet.live == FALSE){
			createPoint(&bullet[i].bullet);
			//bullet[i].belong = belong;
			bullet[i].belong = player->ID;
			bullet[i].bullet.R = BULLET_R;
			if(dir == 1){
				bullet[i].bullet.coor.X = player->coor.X;
				bullet[i].bullet.coor.Y = player->coor.Y - player->R;				
			}
			else if(dir == 2){
				bullet[i].bullet.coor.X = player->coor.X;
				bullet[i].bullet.coor.Y = player->coor.Y + player->R;				
			}	
			else if(dir == 3){
				bullet[i].bullet.coor.X = player->coor.X - player->R;
				bullet[i].bullet.coor.Y = player->coor.Y;				
			}
			else if(dir == 4){
				bullet[i].bullet.coor.X = player->coor.X + player->R;
				bullet[i].bullet.coor.Y = player->coor.Y;				
			}								
			bullet[i].bullet.color.FILL_R = player->color.LINE_R;
			bullet[i].bullet.color.FILL_G = player->color.LINE_G;
			bullet[i].bullet.color.FILL_B = player->color.LINE_B;
			bullet[i].bullet.color.LINE_R = player->color.LINE_R;
			bullet[i].bullet.color.LINE_R = player->color.LINE_R;
			bullet[i].bullet.color.LINE_B = player->color.LINE_B;
			bullet[i].bullet.step = BULLET_STEP;
			bullet[i].bullet.live = TRUE;
			bullet[i].dir = dir;
			bullet[i].bullet.ID = MAX_NUM+i;
			player->R = player->R - (BULLET_R*0.1)/3;
			player->step = player->step + (BULLET_R / 12)/3*0.1;
			/*bullet[i].bullet.coor.X = bullet[i].bullet.coor.X + 50;
			setcolor(EGERGB(bullet[i].bullet.color.LINE_R,bullet[i].bullet.color.LINE_G,bullet[i].bullet.color.LINE_B));
			setfillcolor(EGERGB(bullet[i].bullet.color.FILL_R,bullet[i].bullet.color.FILL_G,bullet[i].bullet.color.FILL_B));
			fillellipse(bullet[i].bullet.coor.X,bullet[i].bullet.coor.Y,bullet[i].bullet.R,bullet[i].bullet.R);
			while(1){
				getchar();	
			}*/
			break;
		}
	}
	
}

void AIPlayerControl(Point *player,Point *player2,Bullet *bullet,LinkList &food_L){
	int dir = 0,Xvary = 0,Yvary = 0,gun = 0,n = 0,distance = 0,disMin = 0;
	LinkList p;
	Point point;
	p = food_L->next;
	//randomize(2);
	n = (int)fclock() + randomX + random(randomX);
	//randomX = (int)fclock();
	//n = (n*(n%2)+n)*31;
	n = n*31;
	if(player2->R >= MATURE_R){
		randomize();dir = random(4);
		randomize();gun = random(randomX)%2;
		//for(int i = 0;i < n;i++){
			randomize();Xvary = (random(3) - 2)*(-1*gun);		
		//}
		n = (int)fclock() + randomX;
		randomize();gun = random(randomX)%2;
		//for(int i = 0;i < n;i++){
			randomize();Yvary = (random(3) - 2)*(-1*gun);
		//}
	}
	else{
		while(p->next != NULL && bullseye == -1){
			point = p->data;
			distance = sqrt(((player2->coor.X - point.coor.X)*(player2->coor.X - point.coor.X)) + ((player2->coor.Y - point.coor.Y)*(player2->coor.Y - point.coor.Y)));
			if(distance < disMin){
				disMin = distance;
				bullseye = point.ID;
				break;
			}
			p++;
		}
		if(point.live = TRUE){
			Xvary = (point.coor.X - player2->coor.X)%2;
			Yvary = (point.coor.Y - player2->coor.Y)%2;
		}
		else{
			bullseye = -1;
		}
	}	
	//if(player2->R < MATURE_R){
	//if(player2->live == TRUE){
		//player2->coor.X = player2->coor.X + Xvary*MY_STEP*0.8;
		//player2->coor.Y = player2->coor.Y + Yvary*MY_STEP*0.8;
		player2->coor.X = player2->coor.X + Xvary*MY_STEP;
		player2->coor.Y = player2->coor.Y + Yvary*MY_STEP;				
	//}
		if(player2->coor.X > GAME_WIDTH){
			player2->coor.X = 0; 
		} 
		else if(player2->coor.X < 0){
			//player2->coor.X = player2->coor.X + MY_STEP;
			player2->coor.X = GAME_WIDTH;
		}
		else if(player2->coor.Y > GAME_HEIGHT){
			//player2->coor.X = player2->coor.X - MY_STEP;
			player2->coor.Y = 0;
		}
		else if(player2->coor.Y < 0){
			//player2->coor.X = player2->coor.X + MY_STEP;
			player2->coor.Y = GAME_HEIGHT;
		}	 
	//}
	if(player2->R >= MATURE_R && gun == 1){
		createBullet(bullet,player2,dir);
	}
}
	/*int dir = 0,Xvary = 0,Yvary = 0;
	if(player->R < MATURE_R){
		randomize();dir = random(4);
		randomize();Xvary = random(GAME_WIDTH);
		randomize();Yvary = random(GAME_HEIGHT);
		if(dir == 1){
			for(int i = 0;i < Xvary;i++){
				randomize();dir = random(3);
				if()
				player->X
			}
		}
	}*/


/*void AIPlayerControl(Point *player,Point *player2){
	int dir = 0,Xvary = 0,Yvary = 0;
	if(player->R < MATURE_R){
		randomize();dir = random(4);
		randomize();Xvary = random(GAME_WIDTH);
		randomize();Yvary = random(GAME_HEIGHT);
		if(dir == 1){
			for(int i = 0;i < Xvary;i++){
				randomize();dir = random(3);
				if()
				player->X
			}
		}
	}
}*/

//int XYCheck(Point *player,Brick *brick){
//	for(int i = 0;i < BRICK_NUM;i++){
//		if(player->coor.X > [i].lift)
//	}
	
		/*if((player->coor.X - MY_R) <= brick[i].right && (player->coor.X + MY_R) >= brick[i].lift && (player->coor.Y - MY_R) <= brick[i].bottom && (player->coor.Y +MY_R) >= brick[i].top){
			flag = 0;
			if((player->coor.X - MY_R) <= brick[i].right){
				player->coor.X+2;
			}
			if((player->coor.X + MY_R) >= brick[i].lift){
				player->coor.X-2;
			}
			if((player->coor.Y - MY_R) <= brick[i].bottom){
				player->coor.Y+2;
			}
			if((player->coor.Y +MY_R) >= brick[i].top){
				player->coor.Y-2;
			} 			
			break;
		}
		else{
			flag = 1;
		}*/	 
//	}	
//}

/*int playerRefresh(Point *player){
	
}*/
