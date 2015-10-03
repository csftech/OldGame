#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

const int Amap=5;
const int Bmap=5;
const int maplimitL=22;
const int maplimitW=22;
const int packlimit=10;

void SetColor(int f=7,int b=0)
{
    unsigned short ForeColor = f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

void gotoxy(int x, int y)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = x;
    scrn.Y = y;
    SetConsoleCursorPosition(hOuput,scrn);
}

void F1()
{
    SetColor();
    system("CLS");
    gotoxy(0,5);
    SetColor();
    cout<<"這是一座荒島，"<<endl;
    cout<<"主角因著空難，"<<endl;
    cout<<"順著洋流來到了這片蠻荒之地。"<<endl;
    cout<<"這裡似是一片荒蕪，"<<endl;
    cout<<"但卻生機盎然......"<<endl<<endl;
    system("pause");

    SetColor();
    system("CLS");
    gotoxy(0,5);
    SetColor();
    cout<<">>基本操作"<<endl;
    cout<<"控制方向：上下左右"<<endl;
    cout<<"Function:"<<endl;
    cout<<"      攻擊    ：A"<<endl;
    cout<<"使用手中工具  ：S"<<endl;
    cout<<"丟棄手中物品  ：D"<<endl;
    cout<<"撿起面前物品  ：F"<<endl;
    cout<<"食用手中食物  ：E"<<endl;
    cout<<"裝取飲水或放火：W"<<endl;
    cout<<"    儲存紀錄  ：Q"<<endl;
    cout<<"    查看說明  ：F1"<<endl;
    cout<<"選擇物品欄位  ：數字鍵 (不可使用數字盤)"<<endl<<endl;
    system("pause");

    SetColor();
    system("CLS");
    gotoxy(0,5);
    SetColor();
    cout<<">>基本規則"<<endl;
    cout<<"Health是主角的生命狀況，歸零時死亡，"<<endl;
    cout<<"死亡後會失去手中所有物品並回到原點復活。"<<endl<<endl;
    cout<<"Power是主角進行攻擊、使用工具時必須消耗的精力。"<<endl<<endl;
    cout<<"Hunger與Water將隨時間漸減，若歸零將損耗Health，"<<endl;
    cout<<"樹、稻、莓、菇皆可採取並食用以補充Hunger。"<<endl;
    cout<<"而Water可由淡水補充。"<<endl<<endl;
    system("pause");

    SetColor();
    system("CLS");
    gotoxy(0,5);
    SetColor();
    cout<<">>基本規則2"<<endl;
    cout<<"底色："<<endl;
    cout<<"灰色 - 岩石地"<<endl;
    cout<<"棕色 - 土壤"<<endl;
    cout<<"深藍 - 鹹水"<<endl;
    cout<<"淺藍 - 淡水"<<endl;
    cout<<"紅色 - 火焰"<<endl<<endl;
    cout<<"鋤頭可自岩石地鋤出石塊，"<<endl;
    cout<<"斧頭可將樹伐為木材，"<<endl;
    cout<<"刀為攻擊時使用。"<<endl<<endl;
    cout<<">>小技巧"<<endl;
    cout<<"可藉由放置物品躲避野獸的攻擊。"<<endl<<endl;
    system("pause");
    SetColor();
    system("CLS");
}

void showframe()
{
    int i;
    for(i=1; i<=23; i++)
    {
        gotoxy(2*i,0);
        cout<<"--";
        gotoxy(0,i);
        cout<<"｜";
        gotoxy(2*i,23);
        cout<<"--";
        gotoxy(46,i);
        cout<<"｜";
    }
    gotoxy(0,0);
    cout<<"┌";
    gotoxy(46,0);
    cout<<"┐";
    gotoxy(46,23);
    cout<<"┘";
    gotoxy(0,23);
    cout<<"└";
    gotoxy(48,23);
    cout<<"--------------------------------";
}

int blood(int aaa)
{
    switch(aaa)
    {
    case 101:
    case 105:
    {
        return 10;
        break;
    }
    case 103:
    case 104:
    {
        return 30;
        break;
    }
    case 102:
    {
        return 50;
        break;
    }
    case 210:
    {
        return 60;
        break;
    }
    case 211:
    {
        return 10;
        break;
    }
    case 220:
    case 221:
    case 222:
    case 224:
    case 225:
    {
        return 80;
        break;
    }
    case 223:
    {
        return 70;
        break;
    }
    case 230:
    case 231:
    case 232:
    {
        return 100;
        break;
    }
    case 233:
    {
        return 150;
        break;
    }
    }
}

int BackgroundColor(int aaa)
{
    switch(aaa)
    {
    case 0:
    {
        return 4;
        break;
    }
    case -1:
    {
        return 8;
        break;
    }
    case -2:
    {
        return 1;
        break;
    }
    case -3:
    {
        return 3;
        break;
    }
    default:
    {
        return 12;
        break;
    }
    }
}

int ObjectColor(int aaa)
{
    switch(aaa/100)
    {
    case 0:
    {
        return 0;
        break;
    }
    case 1:
    {
        return 11;
        break;
    }
    case 2:
    {
        return 13;
        break;
    }
    case 5:
    {
        return 14;
        break;
    }
    default:
    {
        if (aaa==301 || aaa==302)
        {
            return 10;
            break;
        }
        else if (aaa==303 || aaa==304)
        {
            return 14;
            break;
        }
        else if (aaa==310)
        {
            return 6;
            break;
        }
        else if (aaa==311)
        {
            return 15;
            break;
        }
        else if (aaa==411 || aaa==412)
        {
            return 13;
            break;
        }
        else if (aaa==421 || aaa==422)
        {
            return 10;
            break;
        }
        else if (aaa==423 || aaa==424)
        {
            return 13;
            break;
        }
    }
    }
}

void NameObject(int a)
{
    switch(a)
    {
    case 0:
    {
        cout<<"　";
        break;
    }
    case 101:
    {
        cout<<"兔";
        break;
    }
    case 102:
    {
        cout<<"鹿";
        break;
    }
    case 103:
    {
        cout<<"羊";
        break;
    }
    case 104:
    {
        cout<<"豬";
        break;
    }
    case 105:
    {
        cout<<"狗";
        break;
    }
    case 210:
    {
        cout<<"蟑";
        break;
    }
    case 211:
    {
        cout<<"蜂";
        break;
    }
    case 220:
    {
        cout<<"狼";
        break;
    }
    case 221:
    {
        cout<<"熊";
        break;
    }
    case 222:
    {
        cout<<"羆";
        break;
    }
    case 223:
    {
        cout<<"蛇";
        break;
    }
    case 224:
    {
        cout<<"虎";
        break;
    }
    case 225:
    {
        cout<<"獅";
        break;
    }
    case 230:
    {
        cout<<"半";
        break;
    }
    case 231:
    {
        cout<<"妖";
        break;
    }
    case 232:
    {
        cout<<"魔";
        break;
    }
    case 233:
    {
        cout<<"王";
        break;
    }
    case 301:
    {
        cout<<"樹";
        break;
    }
    case 302:
    {
        cout<<"稻";
        break;
    }
    case 303:
    {
        cout<<"莓";
        break;
    }
    case 304:
    {
        cout<<"菇";
        break;
    }
    case 310:
    {
        cout<<"木";
        break;
    }
    case 311:
    {
        cout<<"石";
        break;
    }
    case 411:
    {
        cout<<"肉";
        break;
    }
    case 412:
    {
        cout<<"屍";
        break;
    }
    case 421:
    {
        cout<<"果";
        break;
    }
    case 422:
    {
        cout<<"米";
        break;
    }
    case 423:
    {
        cout<<"莓";
        break;
    }
    case 424:
    {
        cout<<"菇";
        break;
    }
    case 501:
    {
        cout<<"鋤";
        break;
    }
    case 502:
    {
        cout<<"斧";
        break;
    }
    case 503:
    {
        cout<<"刀";
        break;
    }
    }
}
int random(int percent)
{
    int num;
    num = rand()%1001;
    if (percent>1000 || percent<0)
        return -1;
    if (num>=0 && num<=percent)
        return 1;
    if (num>percent && percent<=1000)
        return 0;
}

int main()
{
    SetConsoleTitleA("《荒島餘生I-適者生存》");
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = 25;
    SetConsoleCursorInfo(hcon, &cci);
    srand(int(time(0)));
    clock_t start, stop;
    start = clock();
    int x=10,y=10,map1=0,map2=0,face=0;  //face:0->up 1->down 2->left 3->right
    int mapE[Amap][Bmap][maplimitL][maplimitW],mapOA[Amap][Bmap][maplimitL][maplimitW],mapOB[Amap][Bmap][maplimitL][maplimitW];
    int health=100,power=100,hunger=100,bottle=100;
    int packA[packlimit],packB[packlimit],inhand=0;
    int a,b,c,d,i=0,j=0;
    bool update=1;
    char name[20];

    for(a=0; a<20; a++)
    {
        name[a]=0;
    }

    packA[0]=501;
    packA[1]=502;
    packA[2]=503;
    packB[0]=1;
    packB[1]=2;
    packB[2]=3;

    gotoxy(20,15);
    SetColor();
    cout<<"開新紀錄 (A)";
    gotoxy(20,16);
    SetColor();
    cout<<"繼續遊戲 (S)";

    while(i==0)
    {
        if (GetAsyncKeyState(0x41)&0x8000)
        {
            i=1;
            F1();
        }
        if (GetAsyncKeyState(0x53)&0x8000)
        {
            i=-1;
        }
    }

    if (i==1)
    {
        gotoxy(20,17);
        SetColor();
        cout<<"請輸入您的新紀錄名稱:";
        cin>>name;
        system("CLS");
        gotoxy(20,17);
        SetColor();
        cout<<"Loading...                          ";

        fstream filein("map.map",ios::in);
        if (!filein)
        {
            gotoxy(20,17);
            cout<<"資料庫已損毀，請聯絡開發者!   ";
            Sleep(3000);
            return 0;
        }
        for(a=0; a<Amap; a++)
            for(b=0; b<Bmap; b++)
                for(c=0; c<maplimitL; c++)
                    for(d=0; d<maplimitW; d++)
                        filein>>mapE[a][b][c][d];
        for(a=0; a<Amap; a++)
            for(b=0; b<Bmap; b++)
                for(c=0; c<maplimitL; c++)
                    for(d=0; d<maplimitW; d++)
                        filein>>mapOA[a][b][c][d];
        for(a=0; a<Amap; a++)
            for(b=0; b<Bmap; b++)
                for(c=0; c<maplimitL; c++)
                    for(d=0; d<maplimitW; d++)
                        filein>>mapOB[a][b][c][d];

        update=1;
        gotoxy(1,24);
        cout<<"讀取完畢                            ";
        filein.close();

        Sleep(1000);
        system("CLS");
    }

    if (i==-1)
    {
        system("CLS");
        FlushConsoleInputBuffer(hstdin);
        gotoxy(20,17);
        SetColor();
        cout<<"請輸入您的舊紀錄名稱:";
        cin>>name;
        system("CLS");
        gotoxy(20,17);
        SetColor();
        cout<<"Loading...                          ";
        fstream filein2(name,ios::in);
        if (!filein2)
        {
            gotoxy(20,17);
            cout<<"查無此記錄!                  ";
            Sleep(3000);
            return 0;
        }
        for(a=0; a<Amap; a++)
            for(b=0; b<Bmap; b++)
                for(c=0; c<maplimitL; c++)
                    for(d=0; d<maplimitW; d++)
                        filein2>>mapE[a][b][c][d];
        for(a=0; a<Amap; a++)
            for(b=0; b<Bmap; b++)
                for(c=0; c<maplimitL; c++)
                    for(d=0; d<maplimitW; d++)
                        filein2>>mapOA[a][b][c][d];
        for(a=0; a<Amap; a++)
            for(b=0; b<Bmap; b++)
                for(c=0; c<maplimitL; c++)
                    for(d=0; d<maplimitW; d++)
                        filein2>>mapOB[a][b][c][d];
        for(a=0; a<packlimit; a++)
            filein2>>packA[a];
        for(a=0; a<packlimit; a++)
            filein2>>packB[a];
        filein2>>inhand;
        filein2>>x>>y>>map1>>map2>>face>>health>>power>>hunger>>bottle;

        update=1;
        gotoxy(1,24);
        cout<<"讀取完畢                              ";
        filein2.close();

        Sleep(1000);
        system("CLS");
    }

    while(1)
    {
        if (update==1)
        {
            showframe();
            //------------------------->small map
            for(i=0; i<Amap; i++)
                for(j=0; j<Bmap; j++)
                {
                    gotoxy(50+2*j,6+i);
                    if (i==map1 && j==map2)
                        SetColor(14,14);
                    else
                        SetColor(15,15);
                    cout<<"　";
                }
            //------------------------->show object information
            if (mapOA[map1][map2][y][x]/10==30)
            {
                gotoxy(50,12);
                SetColor();
                NameObject(mapOA[map1][map2][y][x]);
                cout<<"尚可採集"<<mapOB[map1][map2][y][x]/2<<"次";
            }
            else
            {
                gotoxy(50,12);
                SetColor();
                cout<<"                              ";
            }
            //------------------------->INFORMATION
            SetColor();
            a=15;
            b=15;
            c=15;
            d=15;
            if (health<30)
                a=12;
            if (power<30)
                b=12;
            if (hunger<30)
                c=12;
            if (bottle<30)
                d=12;
            gotoxy(50,1);
            SetColor(15,0);
            cout<<"Health:                      ";
            gotoxy(58,1);
            SetColor(a,0);
            for(i=health; i>0; i-=5)
                cout<<"|";
            gotoxy(50,2);
            SetColor(15,0);
            cout<<"Power :                      ";
            gotoxy(58,2);
            SetColor(b,0);
            for(i=power; i>0; i-=5)
                cout<<"|";
            gotoxy(50,3);
            SetColor(15,0);
            cout<<"Hunger:                      ";
            gotoxy(58,3);
            SetColor(c,0);
            for(i=hunger; i>0; i-=5)
                cout<<"|";
            gotoxy(50,4);
            SetColor(15,0);
            cout<<"Water :                      ";
            gotoxy(58,4);
            SetColor(d,0);
            for(i=bottle; i>0; i-=5)
                cout<<"|";
            //------------------------------>PACK
            for(a=0; a<packlimit; a++)
            {
                j=0;
                gotoxy(50+2*a,21);
                i=ObjectColor(packA[a]);
                if (a==inhand)
                    j=8;
                SetColor(i,j);
                NameObject(packA[a]);
                gotoxy(50+2*a,22);
                SetColor(15,j);
                cout<<a+1<<" ";
            }
            //------------------------------>MAP
            for(c=0; c<22; c++)
                for(d=0; d<22; d++)
                {
                    gotoxy(2*(c+1),d+1);
                    //>>>>decide background
                    i=BackgroundColor(mapE[map1][map2][d][c]);
                    //>>>>decide object
                    j=ObjectColor(mapOA[map1][map2][d][c]);
                    //>>>>word
                    SetColor(j,i);
                    NameObject(mapOA[map1][map2][d][c]);
                }
            SetColor(15,BackgroundColor(mapE[map1][map2][y][x]));
            gotoxy(2*(x+1),y+1);
            switch(face)
            {
            case 0:
            {
                cout<<"↑";
                break;
            }
            case 1:
            {
                cout<<"↓";
                break;
            }
            case 2:
            {
                cout<<"←";
                break;
            }
            case 3:
            {
                cout<<"→";
                break;
            }
            }
            update=0;
        }
        if (GetAsyncKeyState(0x51)&0x8000)
        {
            fstream fileout(name,ios::out);
            for(a=0; a<Amap; a++)
                for(b=0; b<Bmap; b++)
                    for(c=0; c<maplimitL; c++)
                        for(d=0; d<maplimitW; d++)
                            fileout<<mapE[a][b][c][d]<<" ";
            for(a=0; a<Amap; a++)
                for(b=0; b<Bmap; b++)
                    for(c=0; c<maplimitL; c++)
                        for(d=0; d<maplimitW; d++)
                            fileout<<mapOA[a][b][c][d]<<" ";
            for(a=0; a<Amap; a++)
                for(b=0; b<Bmap; b++)
                    for(c=0; c<maplimitL; c++)
                        for(d=0; d<maplimitW; d++)
                            fileout<<mapOB[a][b][c][d]<<" ";
            for(a=0; a<packlimit; a++)
                fileout<<packA[a]<<" ";
            for(a=0; a<packlimit; a++)
                fileout<<packB[a]<<" ";
            fileout<<inhand<<" ";
            fileout<<x<<" "<<y<<" "<<map1<<" "<<map2<<" "<<face<<" "<<health<<" "<<power<<" "<<hunger<<" "<<bottle<<" ";
            fileout.close();
            gotoxy(1,24);
            SetColor(14,0);
            cout<<"存檔完畢                              ";
        }
        if (GetAsyncKeyState(VK_UP)&0x8000)
        {
            update=1;
            face=0;
            if (y-1>-1 && mapE[map1][map2][y-1][x]>=-1)
            {
                y--;
            }
            else if (y-1<=-1 && map1!=0 && mapE[map1-1][map2][maplimitL-1][x]>=-1)
            {
                y=maplimitL-1;
                map1--;
            }
        }
        if (GetAsyncKeyState(VK_DOWN)&0x8000)
        {
            update=1;
            face=1;
            if (y+1<22 && mapE[map1][map2][y+1][x]>=-1)
            {
                y++;
            }
            else if (y+1>=22 && map1<Amap-1 && mapE[map1+1][map2][0][x]>=-1)
            {
                y=0;
                map1++;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)&0x8000)
        {
            update=1;
            face=3;
            if (x+1<22 && mapE[map1][map2][y][x+1]>=-1)
            {
                x++;
            }
            else if (x+1>=22 && map2<Bmap-1 && mapE[map1][map2+1][y][0]>=-1)
            {
                x=0;
                map2++;
            }
        }
        if (GetAsyncKeyState(VK_LEFT)&0x8000)
        {
            update=1;
            face=2;
            if (x-1>-1 && mapE[map1][map2][y][x-1]>=-1)
            {
                x--;
            }
            else if (x-1<=-1 && map2!=0 && mapE[map1][map2-1][y][maplimitW-1]>=-1)
            {
                x=maplimitW-1;
                map2--;
            }
        }
        if (GetAsyncKeyState(0x45)&0x8000)
        {
            update=1;
            if (packA[inhand]/100==4)
            {
                Beep(900,100);
                switch(packA[inhand])
                {
                case 411:
                {
                    hunger=hunger+30;
                    gotoxy(1,24);
                    SetColor(14,0);
                    cout<<"你吃了";
                    NameObject(packA[inhand]);
                    cout<<"                                ";
                    break;
                }
                case 412:
                {
                    hunger=hunger+10;
                    gotoxy(1,24);
                    SetColor(14,0);
                    cout<<"你吃了";
                    NameObject(packA[inhand]);
                    cout<<"                                ";
                    break;
                }
                case 421:
                {
                    hunger=hunger+10;
                    gotoxy(1,24);
                    SetColor(14,0);
                    cout<<"你吃了";
                    NameObject(packA[inhand]);
                    cout<<"                                ";
                    break;
                }
                case 422:
                {
                    hunger=hunger+10;
                    gotoxy(1,24);
                    SetColor(14,0);
                    cout<<"你吃了";
                    NameObject(packA[inhand]);
                    cout<<"                                ";
                    break;
                }
                case 423:
                {
                    power=power+20;
                    gotoxy(1,24);
                    SetColor(14,0);
                    cout<<"你吃了";
                    NameObject(packA[inhand]);
                    cout<<"                                ";
                    break;
                }
                case 424:
                {
                    power=power+20;
                    gotoxy(1,24);
                    SetColor(14,0);
                    cout<<"你吃了";
                    NameObject(packA[inhand]);
                    cout<<"                                ";
                    break;
                }
                }
                if (hunger>100)
                    hunger=100;
                if (power>100)
                    power=100;
                packA[inhand]=0;
                packB[inhand]=0;
            }
            else
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"請選擇食物以食用!           ";
            }
        }
        if (GetAsyncKeyState(0x46)&0x8000)
        {
            update=1;
            j=-1;
            for(i=3; i<packlimit; i++)
            {
                if (packA[i]==0)
                {
                    j=i;
                    break;
                }
            }
            if (j==-1)
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"包包已滿!                           ";
            }
            else
            {
                Beep(1000,100);
                if (face==0 && y!=0 && (mapOA[map1][map2][y-1][x]/100==3 || mapOA[map1][map2][y-1][x]/100==4))
                {
                    if (mapOA[map1][map2][y-1][x]/10==30 && mapOB[map1][map2][y-1][x]>0)
                    {
                        mapOB[map1][map2][y-1][x]-=2;
                        packA[j]=mapOA[map1][map2][y-1][x]+120;
                        packB[j]=1000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y-1][x]+120);
                        cout<<"!                           ";
                    }
                    if (mapOA[map1][map2][y-1][x]/10==31 || mapOA[map1][map2][y-1][x]/100==4)
                    {
                        packA[j]=mapOA[map1][map2][y-1][x];
                        packB[j]=5000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y-1][x]);
                        cout<<"!                           ";
                        mapOA[map1][map2][y-1][x]=0;
                        mapOB[map1][map2][y-1][x]=0;
                    }
                }
                if (face==1 && y!=21 && (mapOA[map1][map2][y+1][x]/100==3 || mapOA[map1][map2][y+1][x]/100==4))
                {
                    if (mapOA[map1][map2][y+1][x]/10==30 && mapOB[map1][map2][y+1][x]>0)
                    {
                        mapOB[map1][map2][y+1][x]-=2;
                        packA[j]=mapOA[map1][map2][y+1][x]+120;
                        packB[j]=1000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y+1][x]+120);
                        cout<<"!                           ";
                    }
                    if (mapOA[map1][map2][y+1][x]/10==31 || mapOA[map1][map2][y+1][x]/100==4)
                    {
                        packA[j]=mapOA[map1][map2][y+1][x];
                        packB[j]=5000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y+1][x]);
                        cout<<"!                           ";
                        mapOA[map1][map2][y+1][x]=0;
                        mapOB[map1][map2][y+1][x]=0;
                    }
                }
                if (face==2 && x!=0 && (mapOA[map1][map2][y][x-1]/100==3 || mapOA[map1][map2][y][x-1]/100==4))
                {
                    if (mapOA[map1][map2][y][x-1]/10==30 && mapOB[map1][map2][y][x-1]>0)
                    {
                        mapOB[map1][map2][y][x-1]-=2;
                        packA[j]=mapOA[map1][map2][y][x-1]+120;
                        packB[j]=1000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y][x-1]+120);
                        cout<<"!                           ";
                    }
                    if (mapOA[map1][map2][y][x-1]/10==31 || mapOA[map1][map2][y][x-1]/100==4)
                    {
                        packA[j]=mapOA[map1][map2][y][x-1];
                        packB[j]=5000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y][x-1]);
                        cout<<"!                           ";
                        mapOA[map1][map2][y][x-1]=0;
                        mapOB[map1][map2][y][x-1]=0;
                    }
                }
                if (face==3 && x!=21 && (mapOA[map1][map2][y][x+1]/100==3 || mapOA[map1][map2][y][x+1]/100==4))
                {
                    if (mapOA[map1][map2][y][x+1]/10==30 && mapOB[map1][map2][y][x+1]>0)
                    {
                        mapOB[map1][map2][y][x+1]-=2;
                        packA[j]=mapOA[map1][map2][y][x+1]+120;
                        packB[j]=1000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y][x+1]+120);
                        cout<<"!                           ";
                    }
                    if (mapOA[map1][map2][y][x+1]/10==31 || mapOA[map1][map2][y][x+1]/100==4)
                    {
                        packA[j]=mapOA[map1][map2][y][x+1];
                        packB[j]=5000;
                        gotoxy(1,24);
                        SetColor(10,0);
                        cout<<"獲得";
                        NameObject(mapOA[map1][map2][y][x+1]);
                        cout<<"!                           ";
                        mapOA[map1][map2][y][x+1]=0;
                        mapOB[map1][map2][y][x+1]=0;
                    }
                }
            }
        }
        if (GetAsyncKeyState(0x31)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=0;
        }
        if (GetAsyncKeyState(0x32)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=1;
        }
        if (GetAsyncKeyState(0x33)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=2;
        }
        if (GetAsyncKeyState(0x34)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=3;
        }
        if (GetAsyncKeyState(0x35)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=4;
        }
        if (GetAsyncKeyState(0x36)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=5;
        }
        if (GetAsyncKeyState(0x37)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=6;
        }
        if (GetAsyncKeyState(0x38)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=7;
        }
        if (GetAsyncKeyState(0x39)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=8;
        }
        if (GetAsyncKeyState(0x30)&0x8000)
        {
            update=1;
            Beep(400,100);
            inhand=9;
        }
        if (GetAsyncKeyState(VK_F1)&0x8000)
        {
            F1();
            update=1;
        }
        if (GetAsyncKeyState(0x41)&0x8000)
        {
            update=1;
            if (power<=0)
            {
                power=0;
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"Power已用完                               ";
            }
            else if (packA[inhand]==503)
            {
                Beep(5000,100);
                power-=2;
                if (face==0 && y!=0 && (mapOA[map1][map2][y-1][x]/100==1 || mapOA[map1][map2][y-1][x]/100==2))
                {
                    mapOB[map1][map2][y-1][x]-=20;
                    gotoxy(1,24);
                    SetColor();
                    NameObject(mapOA[map1][map2][y-1][x]);
                    cout<<"遭受攻擊 (血量剩下:"<<mapOB[map1][map2][y-1][x]<<")             ";
                }
                if (face==1 && y!=21 && (mapOA[map1][map2][y+1][x]/100==1 || mapOA[map1][map2][y+1][x]/100==2))
                {
                    mapOB[map1][map2][y+1][x]-=20;
                    gotoxy(1,24);
                    SetColor();
                    NameObject(mapOA[map1][map2][y+1][x]);
                    cout<<"遭受攻擊 (血量剩下:"<<mapOB[map1][map2][y+1][x]<<")             ";
                }
                if (face==2 && x!=0 && (mapOA[map1][map2][y][x-1]/100==1 || mapOA[map1][map2][y][x-1]/100==2))
                {
                    mapOB[map1][map2][y][x-1]-=20;
                    gotoxy(1,24);
                    SetColor();
                    NameObject(mapOA[map1][map2][y][x-1]);
                    cout<<"遭受攻擊 (血量剩下:"<<mapOB[map1][map2][y][x-1]<<")             ";
                }
                if (face==3 && x!=21 && (mapOA[map1][map2][y][x+1]/100==1 || mapOA[map1][map2][y][x+1]/100==2))
                {
                    mapOB[map1][map2][y][x+1]-=20;
                    gotoxy(1,24);
                    SetColor();
                    NameObject(mapOA[map1][map2][y][x+1]);
                    cout<<"遭受攻擊 (血量剩下:"<<mapOB[map1][map2][y][x+1]<<")             ";
                }
            }
            else
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"請選擇刀以進行攻擊！           ";
            }
        }
        if (GetAsyncKeyState(0x53)&0x8000)
        {
            update=1;
            if (power<=15)
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"Power不足使用!                               ";
            }
            else if (packA[inhand]==501)
            {
                Beep(3000,100);
                power-=15;
                if (face==0 && y!=0 && mapE[map1][map2][y-1][x]==-1 && mapOA[map1][map2][y-1][x]==0)
                {
                    mapOA[map1][map2][y-1][x]=311;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"鋤出了石                                  ";
                }
                if (face==1 && y!=21 && mapE[map1][map2][y+1][x]==-1 && mapOA[map1][map2][y+1][x]==0)
                {
                    mapOA[map1][map2][y+1][x]=311;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"鋤出了石                                  ";
                }
                if (face==2 && x!=0 && mapE[map1][map2][y][x-1]==-1 && mapOA[map1][map2][y][x-1]==0)
                {
                    mapOA[map1][map2][y][x-1]=311;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"鋤出了石                                  ";
                }
                if (face==3 && x!=21 && mapE[map1][map2][y][x+1]==-1 && mapOA[map1][map2][y][x+1]==0)
                {
                    mapOA[map1][map2][y][x+1]=311;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"鋤出了石                                  ";
                }
            }
            else if (packA[inhand]==502)
            {
                Beep(3000,100);
                power-=15;
                if (face==0 && y!=0 && mapOA[map1][map2][y-1][x]==301)
                {
                    mapOA[map1][map2][y-1][x]=310;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"砍下了木                                  ";
                }
                if (face==1 && y!=21 && mapOA[map1][map2][y+1][x]==301)
                {
                    mapOA[map1][map2][y+1][x]=310;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"砍下了木                                  ";
                }
                if (face==2 && x!=0 && mapOA[map1][map2][y][x-1]==301)
                {
                    mapOA[map1][map2][y][x-1]=310;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"砍下了木                                  ";
                }
                if (face==3 && x!=21 && mapOA[map1][map2][y][x+1]==301)
                {
                    mapOA[map1][map2][y][x+1]=310;
                    gotoxy(1,24);
                    SetColor();
                    cout<<"砍下了木                                  ";
                }
            }
            else
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"請選擇正確工具!           ";
            }
        }
        if (GetAsyncKeyState(0x44)&0x8000)
        {
            update=1;
            if (packA[inhand]/100!=5 && mapOA[map1][map2][y][x]==0)
            {
                Beep(1000,100);
                mapOA[map1][map2][y][x]=packA[inhand];
                mapOB[map1][map2][y][x]=packB[inhand];
                packA[inhand]=0;
                packB[inhand]=0;
                gotoxy(1,24);
                SetColor();
                cout<<"您放下了";
                NameObject(mapOA[map1][map2][y][x]);
                cout<<"                           ";
            }
            else
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"無法放下!                      ";
            }
        }
        if (GetAsyncKeyState(0x57)&0x8000)
        {
            Beep(1000,100);
            update=1;
            if (face==0 && y!=0 && mapE[map1][map2][y-1][x]==-3)
            {
                bottle=100;
                gotoxy(1,24);
                SetColor();
                cout<<"水瓶已裝滿                      ";
            }
            else if (face==1 && y!=21 && mapE[map1][map2][y+1][x]==-3)
            {
                bottle=100;
                gotoxy(1,24);
                SetColor();
                cout<<"水瓶已裝滿                      ";
            }
            else if (face==2 && x!=0 && mapE[map1][map2][y][x-1]==-3)
            {
                bottle=100;
                gotoxy(1,24);
                SetColor();
                cout<<"水瓶已裝滿                      ";
            }
            else if (face==3 && x!=21 && mapE[map1][map2][y][x+1]==-3)
            {
                bottle=100;
                gotoxy(1,24);
                SetColor();
                cout<<"水瓶已裝滿                      ";
            }
            else if (face==0 && y!=0 && mapOA[map1][map2][y-1][x]/100==3)
            {
                mapE[map1][map2][y-1][x]=1000;
                mapOA[map1][map2][y-1][x]=0;
                mapOB[map1][map2][y-1][x]=0;
                gotoxy(1,24);
                SetColor();
                cout<<"燒毀!                      ";
            }
            else if (face==1 && y!=21 && mapOA[map1][map2][y+1][x]/100==3)
            {
                mapE[map1][map2][y+1][x]=1000;
                mapOA[map1][map2][y+1][x]=0;
                mapOB[map1][map2][y+1][x]=0;
                gotoxy(1,24);
                SetColor();
                cout<<"燒毀!                      ";
            }
            else if (face==2 && x!=0 && mapOA[map1][map2][y][x-1]/100==3)
            {
                mapE[map1][map2][y][x-1]=1000;
                mapOA[map1][map2][y][x-1]=0;
                mapOB[map1][map2][y][x-1]=0;
                gotoxy(1,24);
                SetColor();
                cout<<"燒毀!                      ";
            }
            else if (face==3&&x!=21 && mapOA[map1][map2][y][x+1]/100==3)
            {
                mapE[map1][map2][y][x+1]=1000;
                mapOA[map1][map2][y][x+1]=0;
                mapOB[map1][map2][y][x+1]=0;
                gotoxy(1,24);
                SetColor();
                cout<<"燒毀!                      ";
            }
            else
            {
                gotoxy(1,24);
                SetColor(12,0);
                cout<<"無法執行此動作!                      ";
            }
        }
        //==================================================>auto
        stop = clock();
        i=int ( double(stop - start) / CLOCKS_PER_SEC );
        if (i%20==0)
        {
            hunger--;
            bottle--;
            if (power<100)
                power++;
            if (health<100)
                health++;
            if (hunger<=0)
            {
                hunger=0;
                health-=5;
                Beep(6000,100);
            }
            if (bottle<=0)
            {
                bottle=0;
                health-=5;
                Beep(6000,100);
            }
        }
        if (health<=0)
        {
            gotoxy(30,10);
            SetColor(15,12);
            cout<<"==!您已死亡!==";
            Beep(7000,1000);
            Sleep(3000);
            for(a=3; a<packlimit; a++)
            {
                packA[a]=0;
                packB[a]=0;
            }
            map1=0;
            map2=0;
            y=10;
            x=10;
            health=50;
            power=50;
            hunger=50;
            bottle=50;
            update=1;
        }
        if (mapE[map1][map2][y][x]>0)
        {
            health-=3;
            gotoxy(1,24);
            SetColor(12,0);
            cout<<"您著火了!                      ";
            Beep(7000,100);
        }
        //plant grow
        if (random(1))
        {
            i=rand()%maplimitL;
            j=rand()%maplimitW;
            if (mapOA[map1][map2][i][j]==0 && mapE[map1][map2][i][j]==0)
            {
                mapOA[map1][map2][i][j]=301+rand()%4;
                mapOB[map1][map2][i][j]=10;
            }
        }
        for(a=0; a<maplimitL; a++)
            for(b=0; b<maplimitW; b++)
            {
                if (mapOA[map1][map2][b][a]/100==4)
                {
                    mapOB[map1][map2][b][a]--;
                }
                if (mapOB[map1][map2][b][a]<=0)
                {
                    update=1;
                    gotoxy(1,24);
                    SetColor();
                    switch(mapOA[map1][map2][b][a]/100)
                    {
                    case 1:
                    {
                        NameObject(mapOA[map1][map2][b][a]);
                        mapOA[map1][map2][b][a]=411;
                        mapOB[map1][map2][b][a]=600;
                        cout<<"死亡了!                         ";
                        break;
                    }
                    case 2:
                    {
                        NameObject(mapOA[map1][map2][b][a]);
                        mapOA[map1][map2][b][a]=412;
                        mapOB[map1][map2][b][a]=600;
                        cout<<"死亡了!                         ";
                        break;
                    }
                    case 4:
                    {
                        NameObject(mapOA[map1][map2][b][a]);
                        mapOA[map1][map2][b][a]=0;
                        mapOB[map1][map2][b][a]=0;
                        cout<<"消失了                           ";
                        break;
                    }
                    }
                }
                //fire
                if (mapE[map1][map2][b][a]>0)
                    mapE[map1][map2][b][a]-=8;
                //animal move and breed
                i=rand()%30;
                if ((mapOA[map1][map2][b][a]/100==1 || mapOA[map1][map2][b][a]/100==2) && i<=4)
                {
                    update=1;
                    switch(i)
                    {
                    case 1:
                    {
                        if (b-1>-1 && mapOA[map1][map2][b-1][a]==0 && (mapE[map1][map2][b-1][a]==-1 || mapE[map1][map2][b-1][a]==0))
                        {
                            mapOA[map1][map2][b-1][a]=mapOA[map1][map2][b][a];
                            mapOB[map1][map2][b-1][a]=mapOB[map1][map2][b][a];
                            if (random(3))
                            {
                                mapOB[map1][map2][b][a]=blood(mapOA[map1][map2][b][a]);
                            }
                            else
                            {
                                mapOA[map1][map2][b][a]=0;
                                mapOB[map1][map2][b][a]=0;
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        if (b+1<22 && mapOA[map1][map2][b+1][a]==0 && (mapE[map1][map2][b+1][a]==-1 || mapE[map1][map2][b+1][a]==0))
                        {
                            mapOA[map1][map2][b+1][a]=mapOA[map1][map2][b][a];
                            mapOB[map1][map2][b+1][a]=mapOB[map1][map2][b][a];
                            if (random(3))
                            {
                                mapOB[map1][map2][b][a]=blood(mapOA[map1][map2][b][a]);
                            }
                            else
                            {
                                mapOA[map1][map2][b][a]=0;
                                mapOB[map1][map2][b][a]=0;
                            }
                        }
                        break;
                    }
                    case 3:
                    {
                        if (a-1>-1 && mapOA[map1][map2][b][a-1]==0 && (mapE[map1][map2][b][a-1]==-1 || mapE[map1][map2][b][a-1]==0))
                        {
                            mapOA[map1][map2][b][a-1]=mapOA[map1][map2][b][a];
                            mapOB[map1][map2][b][a-1]=mapOB[map1][map2][b][a];
                            if (random(3))
                            {
                                mapOB[map1][map2][b][a]=blood(mapOA[map1][map2][b][a]);
                            }
                            else
                            {
                                mapOA[map1][map2][b][a]=0;
                                mapOB[map1][map2][b][a]=0;
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        if (a+1<22 && mapOA[map1][map2][b][a+1]==0 && (mapE[map1][map2][b][a+1]==-1 || mapE[map1][map2][b][a+1]==0))
                        {
                            mapOA[map1][map2][b][a+1]=mapOA[map1][map2][b][a];
                            mapOB[map1][map2][b][a+1]=mapOB[map1][map2][b][a];
                            if (random(3))
                            {
                                mapOB[map1][map2][b][a]=blood(mapOA[map1][map2][b][a]);
                            }
                            else
                            {
                                mapOA[map1][map2][b][a]=0;
                                mapOB[map1][map2][b][a]=0;
                            }
                        }
                        break;
                    }
                    }
                }
                if (mapOA[map1][map2][b][a]/100==2 && b==y && a==x)
                {
                    Beep(7000,100);
                    switch(mapOA[map1][map2][b][a])
                    {
                    case 210:
                    case 211:
                    {
                        health-=1;
                        break;
                    }
                    case 220:
                    case 221:
                    case 222:
                    case 223:
                    case 224:
                    case 225:
                    {
                        health-=5;
                        break;
                    }
                    case 230:
                    {
                        health-=8;
                        break;
                    }
                    case 231:
                    {
                        health-=10;
                        break;
                    }
                    case 232:
                    {
                        health-=20;
                        break;
                    }
                    case 233:
                    {
                        health-=100;
                        break;
                    }
                    }
                }
            }
        Sleep(50);
    }
}
