#include <iostream>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include "conio_linux.h"
#endif
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "food.h"

void Controller::Start()//��ʼ����
{
    SetWindowSize(41, 32);//���ô��ڴ�С
    SetColor(2);//���ÿ�ʼ������ɫ
    StartInterface *start = new StartInterface();//��̬����һ��StartInterface��start
    start->Action();//��ʼ����
    delete start;//�ͷ��ڴ�ռ�

    /*���ùر�λ�ã��������ʾ��ȴ�������������*/
    SetCursorPosition(13, 26);
    std::cout << "Press any key to start... " ;
    SetCursorPosition(13, 27);
    #ifdef _WIN32
    system("pause");
    #else
    getch();
    #endif

}

void Controller::Select()//ѡ�����
{
    /*��ʼ������ѡ��*/
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          " ;
    SetCursorPosition(13, 27);
    std::cout << "                          " ;
    SetCursorPosition(6, 21);
    std::cout << STR("��ѡ����Ϸ�Ѷȣ�") ;
    SetCursorPosition(6, 22);
    std::cout << STR("(���¼�ѡ��,�س�ȷ��)") ;
    SetCursorPosition(27, 22);
    SetBackColor();//��һ��ѡ�����ñ���ɫ�Ա�ʾ��ǰѡ��
    std::cout << STR("��ģʽ") ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << STR("��ͨģʽ") ;
    SetCursorPosition(27, 26);
    std::cout << STR("����ģʽ") ;
    SetCursorPosition(27, 28);
    std::cout << STR("����ģʽ") ;
    SetCursorPosition(0, 31);
    score = 0;

    /*���·����ѡ��ģ��*/
    int ch;//��¼����ֵ
    key = 1;//��¼ѡ�����ʼѡ���һ��
    bool flag = false;//��¼�Ƿ����Enter����ǣ���ʼ��Ϊ��
    while ((ch = getKeyCode()))
    {
        switch (ch)//��������
        {
        case KEY_UP://UP�Ϸ����
            if (key > 1)//����ʱѡ����Ϊ��һ��ʱ��UP�Ϸ������Ч
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);//����ѡ�������ñ���ɫ
                    SetBackColor();
                    std::cout << STR("��ģʽ") ;

                    SetCursorPosition(27, 24);//����ѡ����ȡ���ұ���ɫ
                    SetColor(3);
                    std::cout << STR("��ͨģʽ") ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << STR("��ͨģʽ") ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << STR("����ģʽ") ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << STR("����ģʽ") ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << STR("����ģʽ") ;

                    --key;
                    break;
                }
            }
            break;

        case KEY_DOWN://DOWN�·����
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << STR("��ͨģʽ") ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << STR("��ģʽ") ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << STR("����ģʽ") ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << STR("��ͨģʽ") ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << STR("����ģʽ") ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << STR("����ģʽ") ;

                    ++key;
                    break;
                }
            }
            break;

        case KEY_ENTER://Enter�س���
            flag = true;
            break;
        default://��Ч����
            break;
        }
        if (flag) break;//����Enter�س���ȷ�ϣ��˳��������ѭ��

        SetCursorPosition(0, 31);//������������½ǣ�����ر���˸Ӱ����Ϸ����
    }

    switch (key)//������ѡѡ�������ߵ��ƶ��ٶȣ�speedֵԽС���ٶ�Խ��
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
}

void Controller::DrawGame()//������Ϸ����
{
    clearScreen();//����

    /*���Ƶ�ͼ*/
    SetColor(3);
    Map *init_map = new Map();
    init_map->PrintInitmap();
    delete init_map;

    /*���Ʋ����*/
    SetColor(3);
    SetCursorPosition(33, 1);
    std::cout << "Greedy Snake" ;
    SetCursorPosition(34, 2);
    std::cout << STR("̰����") ;
    SetCursorPosition(31, 4);
    std::cout << STR("�Ѷȣ�") ;
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        std::cout << STR("��ģʽ") ;
        break;
    case 2:
        std::cout << STR("��ͨģʽ") ;
        break;
    case 3:
        std::cout << STR("����ģʽ") ;
        break;
    case 4:
        std::cout << STR("����ģʽ") ;
        break;
    default:
        break;
    }
    SetCursorPosition(31, 7);
    std::cout << STR("�÷֣�") ;
    SetCursorPosition(37, 8);
    std::cout << "     0" ;
    SetCursorPosition(33, 13);
    std::cout << STR(" ������ƶ�") ;
    SetCursorPosition(33, 15);
    std::cout << STR(" ESC����ͣ") ;
}

int Controller::PlayGame()//��Ϸ����ѭ��
{
    /*��ʼ���ߺ�ʳ��*/
    Snake *csnake = new Snake();
    Food *cfood = new Food();
    SetColor(6);
    csnake->InitSnake();
    srand((unsigned)time(NULL));//������������ӣ����û�� ʳ��ĳ���λ�ý���̶�
    cfood->DrawFood(*csnake);

    /*��Ϸѭ��*/
    while (csnake->OverEdge() && csnake->HitItself()) //�ж��Ƿ�ײǽ��ײ���������Ƿ�������
    {
        /*����ѡ��˵�*/
        if (!csnake->ChangeDirection()) //��Esc��ʱ
        {
            int tmp = Menu();//���Ʋ˵������õ�����ֵ
            switch (tmp)
            {
            case 1://������Ϸ
                break;

            case 2://���¿�ʼ
                delete csnake;
                delete cfood;
                return 1;//��1��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ���¿�ʼ

            case 3://�˳���Ϸ
                delete csnake;
                delete cfood;
                return 2;//��2��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ�˳���Ϸ

            default:
                break;
            }
        }
        //clear map
        for(int x = 2; x < 30; x ++){
            for (int y = 2; y < 30; y ++){
                Point p(x,y);
                bool flag = false;
                for (auto& point : csnake->snake)
                {
                    if(p == point){
                        flag = true;
                    }
                }
                if(p.GetX() == cfood->x && p.GetY() == cfood->y){
                    flag = true;
                }
                if(!flag){
                    SetCursorPosition(x,y);
                    std::cout << " ";
                }
            }
        }
        if (csnake->GetFood(*cfood)) //�Ե�ʳ��
        {
            csnake->Move();//������
            UpdateScore(1);//���·�����1Ϊ����Ȩ��
            RewriteScore();//���»��Ʒ���
            cfood->DrawFood(*csnake);//������ʳ��
        }
        else
        {
            csnake->NormalMove();//�������ƶ�
        }

        if (csnake->GetBigFood(*cfood)) //�Ե���ʱʳ��
        {
            csnake->Move();
            UpdateScore(cfood->GetProgressBar()/5);//����������ʱʳ�������ȷ��
            RewriteScore();
        }

        if (cfood->GetBigFlag()) //�����ʱ����ʱʳ���˸��
        {
            cfood->FlashBigFood();
        }
        sleep(speed);
    }

    /*������*/
    delete csnake;//�ͷŷ�����ڴ�ռ�
    delete cfood;
    int tmp = GameOver();//������Ϸ�������棬��������ѡ��
    switch (tmp)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 2;
    }
}

void Controller::UpdateScore(const int& tmp)//���·���
{
    score += key * 10 * tmp;//���÷���������Ϸ�Ѷȼ����˵Ĳ���tmpȷ��
}

void Controller::RewriteScore()//�ػ����
{
    /*Ϊ���ַ���β�����룬������������Ϊ6λ�����㵱ǰ����λ������ʣ��λ���ÿո�ȫ�����������*/
    SetCursorPosition(37, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " " ;
    }
    std::cout << score ;
}

int Controller::Menu()//ѡ��˵�
{
    /*���Ʋ˵�*/
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << STR("�˵���") ;
    #ifdef _WIN32
        Sleep(100);
    #else
        usleep(100 * 1000);
    #endif
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << STR("������Ϸ") ;
    #ifdef _WIN32
        Sleep(100);
    #else
        usleep(100 * 1000);
    #endif
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << STR("���¿�ʼ") ;
    #ifdef _WIN32
        Sleep(100);
    #else
        usleep(100 * 1000);
    #endif
    SetCursorPosition(34, 25);
    std::cout << STR("�˳���Ϸ") ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getKeyCode()))
    {
        switch (ch)
        {
        case KEY_UP://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    std::cout << STR("������Ϸ") ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << STR("���¿�ʼ") ;

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << STR("���¿�ʼ") ;
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << STR("�˳���Ϸ") ;

                    --tmp_key;
                    break;
                }
            }
            break;

        case KEY_DOWN://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << STR("���¿�ʼ") ;
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << STR("������Ϸ") ;

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << STR("�˳���Ϸ") ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << STR("���¿�ʼ") ;

                    ++tmp_key;
                    break;
                }
            }
            break;

        case KEY_ENTER://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //ѡ�������Ϸ���򽫲˵�����
    {
        SetCursorPosition(32, 19);
        std::cout << "      " ;
        SetCursorPosition(34, 21);
        std::cout << "        ";
        SetCursorPosition(34, 23);
        std::cout << "        ";
        SetCursorPosition(34, 25);
        std::cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//��Ϸһ��ѭ��
{
    Start();//��ʼ����
    while (true)//��Ϸ����Ϊһ����ѭ����ֱ���˳���Ϸʱѭ������
    {
        Select();//ѡ�����
        DrawGame();//������Ϸ����
        int tmp = PlayGame();//������Ϸѭ���������¿�ʼ���˳���Ϸʱ������ѭ��������ֵ��tmp
        if (tmp == 1) //����ֵΪ1ʱ���¿�ʼ��Ϸ
        {
            clearScreen();
            continue;
        }
        else if (tmp == 2) //����ֵΪ2ʱ�˳���Ϸ
        {
            break;
        }
        else
        {
            break;
        }
    }
}

int Controller::GameOver()//��Ϸ��������
{
    /*������Ϸ��������*/
    sleep(500);
    SetColor(11);
    SetCursorPosition(10, 8);
    std::cout << "��������������������������������������������" ;
    sleep(30);
    SetCursorPosition(9, 9);
    std::cout << " ��               Game Over !!!              ��" ;
    sleep(30);
    SetCursorPosition(9, 10);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(9, 11);
    std::cout << STR(" ��              ���ź��������              ��") ;
    sleep(30);
    SetCursorPosition(9, 12);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(9, 13);
    std::cout << STR(" ��             ��ķ���Ϊ��                 ��") ;
    SetCursorPosition(24, 13);
    std::cout << score ;
    sleep(30);
    SetCursorPosition(9, 14);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(9, 15);
    std::cout << STR(" ��   �Ƿ�����һ�֣�                         ��") ;
    sleep(30);
    SetCursorPosition(9, 16);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(9, 17);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(9, 18);
    std::cout << STR(" ��    �ţ��õ�        ���ˣ�����ѧϰ����˼  ��") ;
    sleep(30);
    SetCursorPosition(9, 19);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(9, 20);
    std::cout << " ��                                          ��" ;
    sleep(30);
    SetCursorPosition(10, 21);
    std::cout << "��������������������������������������������" ;
    sleep(100);
    SetCursorPosition(12, 18);
    SetBackColor();
    std::cout << STR("�ţ��õ�") ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getKeyCode()))
    {
        switch (ch)
        {
        case KEY_LEFT://LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(12, 18);
                SetBackColor();
                std::cout << STR("�ţ��õ�") ;
                SetCursorPosition(20, 18);
                SetColor(11);
                std::cout << STR("���ˣ�����ѧϰ����˼") ;
                --tmp_key;
            }
            break;

        case KEY_RIGHT://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(20, 18);
                SetBackColor();
                std::cout << STR("���ˣ�����ѧϰ����˼") ;
                SetCursorPosition(12, 18);
                SetColor(11);
                std::cout << STR("�ţ��õ�") ;
                ++tmp_key;
            }
            break;

        case KEY_ENTER://Enter
            flag = true;
            break;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 1;
    }
}
