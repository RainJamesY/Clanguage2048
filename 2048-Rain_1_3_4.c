//Rain的2048小游戏1.3.4版本
//独立出game_winning函数模块
#include <Stdio.h>
#include <stdlib.h> // for rand() and srand() and exit()
#include <time.h>   // for time()
#include <conio.h> //为了读取方向键
#include <windows.h>    // for system()

//------------------全局变量-------------------------------
// 游戏主界面是一个 4*4 的 16 宫格，使用二维数组进行表示，用 0 表示空格
int a[4][4];

// 16 宫格中空格的个数
int empty;
// 用户名
int name[30];
// 分数统计
int score = 0;

//游戏结束判定
int gameover = 0;
int gamewinning = 0;

void init(void);      // 初始化数组跟赋值第一个随机二维数组元素 
void draw(void);      // 绘制4 * 4方格图 
void play(void);      // 控制移动方向
void to_up(void);     // 向上移动 
void to_down(void);   // 向下移动 
void to_left(void);   // 向左移动 
void to_right(void);  // 向右移动 
void add_number(void);  // 加新的数
void game_winning(void); //游戏获胜判定
void game_over(void);  //结束游戏判定
void rank(void);      //跟据最终游戏分数来给出评级

int main()
{
    system("color f9");
    printf("****************************************\n"); 
    printf("     2048(by RainJamesY)(4*4)     \n\n"); 
    printf("           Control by:\n"
           "w/s/a/d or W/S/A/D or up/down/left/right \n"); 
    printf("      press q or Q quit game!\n");
    printf("****************************************\n"); 
    printf("  Please enter the name of player\n");
    scanf("%s", name);
    printf("           Hello %s\n", name);
    printf("  Press any key to continue . . .\n"); 
    getch();
    system("cls"); 
    
    init();
    draw();
    while(1)
        play();
    

    return 0;
} 


void init(void)
{
    //开始时显示方格中字符下标位置
    int x, y;

    for(x=0; x<4; x++)
        for(y=0; y<4; y++)
            a[x][y] = 0;
    srand(time(0));
    x = rand() % 4;
    y = rand() % 4;
    a[x][y] = 2;
    empty = 15;
}

void draw(void)              //画出4*4方格 每一格其实由三行组成 空格-数组数字空格
{
    int i, j;                      

    for(i=0; i<4; i++) 
    {                              // 一个方格由三根竖线组成 
        for(j=0; j<4; j++)     // 第一排竖线 每个竖线之间占5个格 
            printf("|    ");       //打印四个竖线后最后一个跟随一个\n转行符进入下一行
        printf("|\n");
        
        for(j=0; j<4; j++) {   // 第二排竖线与数字 (所有的数字都在每个格子的第二排出现)
            if(a[i][j] == 0)
                printf("|    ");
            else
                printf("|%4d", a[i][j]);
        } 
        printf("|\n"); 
        
        for(j=0; j<4; j++)     // 第三排竖线加底线 
            printf("|____");
        printf("|\n");
    }

    printf("Current Score: %d", score);  //最后一排显示实时分数值
} //draw函数结束

void play(void)
{
    int ch;
    ch = getch();//<conio.h>头文件中用getch()输入一个按键， 其返回值为ACII码
    //方向键的读取--case后只能为数值
    switch (ch)
    {
    case 72:     //up键和大小写的Ww都可作为向上指令
    case 'w':
    case 'W':
        to_up();
        system("cls");   //清屏指令
        add_number();
        draw();     
        break;
    case 80:     
    case 's':
    case 'S':
        to_down();
        system("cls");
        add_number(); 
        draw(); 
        break;
    case 75:     
    case 'a':
    case 'A':
        to_left();
        system("cls");
        add_number(); 
        draw(); 
        break;
    case 77:     
    case 'd':
    case 'D':
        to_right();
        system("cls");
        add_number(); 
        draw(); 
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 0:
    case 224:
        break;
    default:
        printf("\nWRONG INPUT!!!\n\n");
        printf("Please type:\nw/s/a/d or W/S/A/D or up/down/left/right \n");
        break;
    }
    

    game_winning(); //用game_winning()函数判定是否生成2048从而判定游戏获胜
    if(gamewinning == 1){
        printf("\nCONGRATES!!!\n\n  %s\n", name);
                printf("YOU WIN!!!\n\n");
                printf("Your final score is %d\n", score);
                rank();
                system("PAUSE");
                printf("\nInput 'q' or 'Q' to quit\n");
                switch (ch){
                case 'q':
                case 'Q':
                exit(0);
                break;
                }
    }

     
    game_over();     //用game_over()函数判定是否满足运行条件，不满足则带回gameover变量的值为1
    
    if(gameover == 1){       
        printf("\nGAME OVER!\n");
        printf("Your final score is %d\n", score);
        rank();
        system("PAUSE");
        printf("\nInput 'q' or 'Q' to quit\n");
        switch (ch){
        case 'q':
        case 'Q':
        exit(0);
        break;
        }    
    }    


} //play函数完


void rank(void)
{
    if(score<100){
        printf("Rank F\n");
    } else if((score>100)&&(score<1000)){
        printf("Rank E\n");
    } else if((score>1000)&&(score<2500)){
        printf("Rank D\n");
    } else if((score>2500)&&(score<5000)){
        printf("Rank C\n");
    } else if((score>5000)&&(score<7500)){
        printf("Rank B\n");
    } else if((score>7500)&&(score<10000)){
        printf("Rank A\n");
    } else if((score>10000)&&(score<12500)){
        printf("Rank S\n");
    } else if((score>12500)&&(score<15000)){
        printf("Rank SS\n");
    } else if((score>15000)&&(score<17500)){
        printf("Rank SSS\n");
    } else if(score>17500){
        printf("Rank LEGENDARY!!!\n");
    }
}

void game_winning(void)
{
    
    int j, k;
    for(j=0; j<4; j++){
        for(k=0; k<4; k++){
            if(a[j][k] == 2048){
                gamewinning = 1;     
            } 
        }
    }
}

void game_over(void)
{
    //判断失败条件
    //for循环遍历数组 让横纵都不相等时且empty为0时跳出(x)
    //新思路:for循环遍历数组用||进行判定，若横纵方向任一一方或都可合并，则跳出函数体(return)，给gameover赋值0
    //但k的值要在0-2之间（为了避免k=4的时侯强行与没有任何赋值的a[x][4]/a[4][y]进行比较）
    int j, k;
    for(j=0; j<4; j++){
        for(k=0; k<3; k++){
            if(a[j][k]==a[j][k+1]||a[k][j]==a[k+1][j]){    //相邻的数有相同的时候可以运行
                gameover = 0;                              //且必须在遍历完整个数组后才能对gameover进行判定赋值
                return;             //满足运行条件时直接return返回继续运行
            }
        }
    }
    //如果遍历完整个数组前后左右都无相邻的两个相同的数，则让gameover值为1
    if(empty == 0){
        gameover = 1;
    }
}



void add_number(void)
{
    int temp, number;
    int x, y;

    if(empty > 0) {      // 找出空格 
        srand(time(0));   //srand()用来设置rand()产生随机数时的随机数种子，参数seed必须是整数
        do {                //通常可以用time(0)的返回值作为seed.如果每次seed都设置相同的值，rand()产生的随机数值每次都一样。
            x = rand() % 4;    //%4后只会余下0、1、2、3，恰好满足格数需求
            y = rand() % 4;
        } while(a[x][y] != 0);
        
        number = rand();
        temp = number % 2; //因为只能生成2或4 则采用%2的形式
                            //再用两个if语句进行2选1
    
        if(temp == 1) {  // 判断是生成数字2，还是数字4
            a[x][y] = 2;
            empty--;    //随机生成2或4后，空格数减一
        } 
        if(temp == 0) {
            a[x][y] = 4;
            empty--;
        }
    }
}





void to_up(void)
{
    int x, y, i;    //x-行数  y-列数

    for(y=0; y<4; y++){            //竖直方向上做行（row）--x的运算，则先遍历每一列--y
        for(x=0; x<4; x++){       // 从下向上合并相同的方块 
            if(a[x][y] != 0){   
                for(i=x+1; i<4; i++){
                    if(a[i][y] != 0){
                        if(a[x][y] == a[i][y]){       
                        a[x][y] += a[i][y];  //如果上下两个数相同就叠加并将上一个数变为0
                        a[i][y] = 0;
                        empty++;             //将0视为空格 故合并后空格数应该加一
                        score += a[x][y];
                        x = i;
                        break;
                        } else{
                            break;
                        }  
                    }  
                }
            }    
        }
    }   //第一圈for循环一定要包含后面所有的操作！！！！！！！

    for(y=0; y<4; y++){
        for(x=0; x<4; x++){
            if(a[x][y] != 0){
                for(i=x;(i>0)&&(a[i-1][y]==0);i--){
                    a[i-1][y] = a[i][y];
                    a[i][y] = 0;
                }
            }
        }
    }

}

void to_down(void)
{
    int x, y, i;

    for(y=0; y<4; y++){
        for(x=3; x>=0; x--){
            if(a[x][y]!=0){         //如果该位不为零则向上扫描所有行
                for(i=x-1; i>=0; i--){
                    if(a[i][y] != 0){
                        if(a[i][y] == a[x][y]){
                            a[x][y] += a[i][y];    //向下合并相同的两个数
                            a[i][y] = 0;
                            empty++;
                            score += a[x][y];
                            x = i;        //跳过向上1格的扫描，进入向上2格的扫描（因为有合并的数导致有空格）
                            break;
                        } else{
                            break;
                            }
                    }
                }     
            }
        }
    }

    for(y=0; y<4; y++){
        for(x=3; x>=0; x--){
            if(a[x][y] != 0){       //如果检测到本位不为0
                for(i=x;(i<3)&&(a[i+1][y]==0);i++){   //且向下一位也为0时(可以向下移动)
                    a[i+1][y] = a[i][y];        //将不为0的那一位赋值给下一位
                    a[i][y] = 0;                //原位赋值为0
                }
            }
        }
    }

}

void to_left(void) 
{
    int x, y, i;
        //左右移动，做同一行上每一列的运算则先遍历行数--x
    for(x=0; x<4; x++){       //从右往左合并相同方块
        for(y=0; y<4; y++){
            if(a[x][y] != 0){
                for(i=y+1; i<4; i++)     //扫描该位右侧的所有数
                    if(a[x][i] != 0){
                        if(a[x][i] == a[x][y]){
                            a[x][y] += a[x][i];   //如果该位右侧的数等于该位则将其合并
                            a[x][i] = 0;
                            empty++;
                            score += a[x][y];
                            y = i;
                            break;
                        }else {
                            break;
                        }
                    }
            }
        }
    }

    for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            if(a[x][y] != 0){
                for(i=y;(i>0)&&(a[x][i-1]==0);i--){    //像左移动空格 只要左侧为0就可以移动
                    a[x][i-1] = a[x][i];
                    a[x][i] = 0;
                }
            }
        }
    }


}

void to_right(void)
{
    int x, y, i;

    for(x=0; x<4; x++){
        for(y=3; y>=0; y--){
            if(a[x][y] != 0){         //如果该位不为零则向左扫描所有行
                for(i=y-1; i>=0; i--){
                    if(a[x][i] != 0){
                        if(a[x][i] == a[x][y]){
                            a[x][y] += a[x][i];    //向右合并相同的两个数
                            a[x][i] = 0;
                            empty++;
                            score += a[x][y];
                            y = i;        //跳过向右1格的扫描，进入向右2格的扫描（因为有合并的数导致有空格）
                            break;
                        } else{
                            break;
                            }
                    }
                }     
            }
        }
    }

    for(x=0; x<4; x++){
        for(y=3; y>=0; y--){
            if(a[x][y] != 0){       //如果检测到本位不为0
                for(i=y;(i<3)&&(a[x][i+1]==0);i++){   //且向右一位也为0时(可以向右动)
                    a[x][i+1] = a[x][i];        //将不为0的那一位赋值给右一位
                    a[x][i] = 0;                //原位赋值为0
                }
            }
        }
    }

}