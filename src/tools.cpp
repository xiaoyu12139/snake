#include "tools.h"
#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#else
#include "conio_linux.h"
#endif

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void sleep(int speed){
    #ifdef _WIN32
        Sleep(speed);//�����ߵ��ƶ�Ч��
    #else
        usleep(speed * 1000);
    #endif
}


void SetWindowSize(int cols, int lines)//���ô��ڴ�С
{
    #ifdef _WIN32
        system("title ̰����");//���ô��ڱ���
        char cmd[30];
        sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);//һ��ͼ�Ρ�ռ�����ַ����ʿ�ȳ���2
        system(cmd);//system(mode con cols=88 lines=88)���ô��ڿ�Ⱥ͸߶�
    #else
        std::string title = STR("̰����");
        std::string cmd = 
        "bash -c '"\
        "ps1_clean=\"$PS1\";"\
        "ps1_clean=\"${ps1_clean#\\\\[\\\\e]0;}\";"\
        "ps1_clean=\"${ps1_clean#*\\a\\\\]}\";"\
        "export PS1=\"$ps1_clean\";"\
        "echo -ne \"\\033]0;" + title + std::string("\\007\";") +
        "'";
        std::cout << cmd << std::endl;
        system(cmd.c_str());
        system("clear");
        std::cout << "\033[8;" << lines << ";" << cols * 2 << "t" << std::flush;
    #endif
}

void SetCursorPosition(const int x, const int y)//���ù��λ��
{
    #ifdef _WIN32
        COORD position;
        position.X = x * 2;
        position.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    #else
        printf("\033[%d;%dH", y + 1, x * 2 + 1); // Linux�ն������Ǵ�(1,1)��ʼ��
        fflush(stdout);
    #endif
}

void SetColor(int colorID)//�����ı���ɫ
{
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
    #else
        // Linux: colorID 0-7 ��ʾ��׼��ɫ
        // 0-��ɫ��1-��ɫ��2-��ɫ��3-��ɫ��4-��ɫ��5-Ʒ�죬6-��ɫ��7-��ɫ
        int linuxColor = 30 + (colorID % 8); // ��ֹ������Χ
        printf("\033[%dm", linuxColor);
        fflush(stdout);
    #endif
}

void SetBackColor()//�����ı�����ɫ
{
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_BLUE |
        BACKGROUND_BLUE |
        BACKGROUND_GREEN |
        BACKGROUND_RED );
    #else
        // ���ñ���ɫΪ��ɫ��ͬʱ��ǰ��ɫ�����ɫ
        printf("\033[44;37m"); 
        fflush(stdout);
    #endif
}

int getKeyCode(){
    int ch0 = getch();
    #ifdef _WIN32
        if(ch0 == 224){//����
            int ch1 = getch();
            switch (ch1) {
                case 72: return KEY_UP;
                case 80: return KEY_DOWN;
                case 77: return KEY_RIGHT;
                case 75: return KEY_LEFT;
                default: return KEY_ERROR;
            }
        }else if(ch0 == 13){
            return KEY_ENTER;
        }
        else if (ch0 == 27) {
            return KEY_ESC;
        }
        else {
            return KEY_ERROR;
        }
        return getch();
    #else
        switch (ch0) {
            case 27: return KEY_ESC;
            case 10: return KEY_ENTER;
            case 87: return KEY_UP;
            case 119: return KEY_UP;
            case 115: return KEY_DOWN;
            case 83: return KEY_DOWN;
            case 100: return KEY_RIGHT;
            case 68: return KEY_RIGHT;
            case 97: return KEY_LEFT;
            case 65: return KEY_LEFT;
            default: return KEY_ERROR;
        }
    #endif
}
