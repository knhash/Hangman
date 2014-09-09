#define _WIN32_WINNT 0x0500
#include <iostream>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#include<limits.h>

using namespace std;

int main();

string array,answer="                         ",input="                          ";
char Dict[][20]={"afghanistan","akrotiri","albania","algeria","andorra","angola","anguilla","antarctica","argentina","armenia","aruba","australia","austria","azerbaijan","bahrain","bangladesh","barbados","belarus","belgium","belize","benin","bermuda","bhutan","bolivia","botswana","brazil","brunei","bulgaria","burma","cambodia","cameroon","canada","chad","chile","china","colombia","comoros","congo","croatia","cuba","cyprus","denmark","dhekelia","djibouti","dominica","ecuador","egypt","eritrea","estonia","ethiopia","fiji","finland","france","germany","ghana","gibraltar","greece","greenland","guatemala","guernsey","guinea","guyana","haiti","hungary","iceland","india","indonesia","iran","iraq","ireland","israel","italy","jamaica","japan","jersey","jordan","kazakhstan","kenya","kiribati","kuwait","laos","latvia","lebanon","lesotho","liberia","libya","liechtenstein","lithuania","luxembourg","macau","macedonia","madagascar","malawi","malaysia","maldives","mali","mauritius","mayotte","mexico","moldova","monaco","mongolia","montserrat","morocco","mozambique","namibia","nepal","netherlands","niger","nigeria","niue","norway","oman","pakistan","palau","panama","paraguay","peru","philippines","poland","portugal","qatar","romania","russia","rwanda","samoa","senegal","singapore","slovakia","slovenia","somalia","spain","sudan","svalbard","swaziland","sweden","switzerland","syria","taiwan","tajikistan","tanzania","thailand","tonga","tunisia","turkey","turkmenistan","uganda","ukraine","uruguay","uzbekistan","venezuela","vietnam","yemen","zambia","zimbabwe"};
bool let[26];
char guess;
int size;
int inp;
int chance;
int index;
int hang;
int correct;
int mx,my;

void gotoxy(int x, int y)               //Changing cursor co-ordinates
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void border()                           //Custom Border
{
    int c,r;
    //HORIZONTAL
    for(c=0;c<80;c++)
    {
        gotoxy(c,0);
        cout<<'%';
        gotoxy(c,24);
        cout<<'%';
    }

    //VERTICAL
    for(r=0;r<24;r++)
    {
        gotoxy(0,r);
        cout<<'%';
        gotoxy(79,r);
        cout<<'%';
        gotoxy(61,r);
        cout<<'%';
    }
}

void clear(int a=0)                     //Custom Clear Screen
{
    if(a==0)
    {
        //CLEAR EVERYTHING EXCEPT BORDER
        for(int i=1;i<61;++i)
            for(int k=1;k<24;++k)
            {
                gotoxy(i,k);
                cout<<"K";
                Sleep(.5);
            }

        for(int i=1;i<61;++i)
            for(int k=1;k<24;++k)
            {
                gotoxy(i,k);
                cout<<" ";
                Sleep(.5);
            }
    }
    else if(a==1)
    {
        for(int k=1;k<24;++k)
            for(int i=62;i<80;++i)
            {
                gotoxy(i,k);
                cout<<"K";
                Sleep(0.5);
            }

        for(int k=1;k<24;++k)
            for(int i=62;i<80;++i)
            {
                gotoxy(i,k);
                cout<<" ";
                Sleep(0.5);
            }
    }
}

void gameover(int a=0)                  //Gameover
{
    clear();
    if(a==0)
    {
        gotoxy(25,15);
        cout<<"!GAME OVER!";
        gotoxy(18,18);
        cout<<"The country is : "<<array;
    }
    else if(a==1)
    {
        gotoxy(17,15);
        cout<<"!CONGRATULATIONS! YOU WON";
        gotoxy(18,18);
        cout<<"The country is : "<<array;
    }

    gotoxy(17,21);
    cout<<"Want to play again?...(y)";
    char ch;
    ch=getch();
    if(ch=='y')
    {
        clear();
        clear(1);
        main();
    }
    exit(0);
}

void man(int hang)
{
    switch(hang)
    {
    case 6:
        gotoxy(72,12);cout<<char(1);
    case 5:
        gotoxy(71,16);cout<<"/";gotoxy(73,16);cout<<"\\";
    case 4:
        gotoxy(71,14);cout<<"/";gotoxy(73,14);cout<<"\\";
    case 3:
        for(int i=13;i<16;++i)
        {
            gotoxy(72,i);
            cout<<'|';
        }
    case 2:
        for(int i=65;i<73;++i)
        {
            gotoxy(i,10);
            cout<<char(205);
        }
        gotoxy(72,11);
        cout<<'|';
    case 1:
        for(int i=10;i<20;++i)
        {
            gotoxy(66,i);
            cout<<char(186);
        }
        gotoxy(67,10);cout<<'/';
    case 0:
        for(int i=64;i<77;++i)
        {
            gotoxy(i,20);
            cout<<char(240);
        }

    }
    return;
}

void LLeft()
{
    for(int i=3;i<60;++i)
    {
        gotoxy(i,16);
        cout<<' ';
    }
    gotoxy(5,14);
    cout<<"Letters Left :";
    for(int i=0;i<26;++i)
    {
        if(let[i]==true)
        {
            gotoxy(2*i+5,16);
            cout<<char(65+i);
        }
    }
}

void check(char letter,int size)
{
    bool check=false;
    int i;
    for(i=0;i<size;++i)
    {
        if(letter==Dict[index][i])
        {
            int fin=letter;
            let[fin-97]=false;
            answer[i]=letter;
            check=true;
            correct++;
        }
    }
    if(check==false)
        hang++;
}

void board(int size)
{
    for(int i=0;i<size;++i)
    {
        gotoxy(i*4+5,5);
        cout<<"_";
        gotoxy(i*4+5,4);
        cout<<answer[i];
    }
}

void play()
{
    answer="                         ",input="                          ";
    srand(time(NULL));
    index=rand()%154;
    array=Dict[index];
    for(int i=0;array[i]!='\0';++i)
        size=i;size++;
    board(size);
    chance=size;
    hang=-1;
    inp=0;
    correct=0;

    while(chance)
    {
        gotoxy(30,20);cout<<"You have "<<chance<<" chances left";
        gotoxy(30,22);cout<<"Hanging in T-minus "<<6-hang<<" turns ";
        gotoxy(20,10);cout<<"                               ";
        gotoxy(20,10);cout<<"Your Guess...";

        guess=getch();

        if(GetKeyState('Q')<-100)
        {
            gotoxy(20,10);
            cout<<"                                        ";
            gotoxy(20,10);
            cout<<"Enter Answer...";
            string stuff;
            cin>>stuff;
            if(stuff.compare(array)==0)
            {
                cin.clear();
                gameover(1);
            }
        }

        cout<<guess;
        int in=guess;
        let[in-97]=false;
        check(guess,size);
        LLeft();
        board(size);
        man(hang);
        chance--;
        if(hang==7 || correct==size)
        {
            if(correct==size)
                gameover(1);
            else
                gameover(0);
        }
    }
    gameover();

    return;
}

int main()
{
    system("cls");
    cout << "Hello world!" << endl;

    border();
    gotoxy(67,5);
    cout<<"HANGMAN";
    for(int i=0;i<26;++i)
        let[i]=true;
    LLeft();
    play();

    gotoxy(0,24);
    //system("pause");
    return 0;
}
