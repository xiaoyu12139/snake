#include "startinterface.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "tools.h"


void StartInterface::PrintFirst()//�ߴ���߳��ֵ���ȫ���ֵĹ���
{
    for (auto& point : startsnake)
    {
        point.Print();
        sleep(speed);
    }
}

void StartInterface::PrintSecond()//�ߴ��������ƶ��Ĺ���
{
    for (int i = 10; i != 40; ++i) //��ͷ��Ҫ��10�ƶ���40
    {
        /*������ͷ����һ��λ�ã�������ѹ��startsnake�У����Ƴ���������βȥ��*/
        int j = ( ((i-2)%8) < 4 )?( 15 + (i-2)%8 ) : ( 21 - (i-2)%8 );
        startsnake.emplace_back( Point(i, j) );
        startsnake.back().Print();
        startsnake.front().Clear();
        startsnake.pop_front();
        sleep(speed);
    }
}

void StartInterface::PrintThird()//�ߴӽӴ��ұߵ���ʧ�Ĺ���
{
    while ( !startsnake.empty() || textsnake.back().GetX() < 33 ) //���߻�û��ʧ������û�ƶ���ָ��λ��
    {
        if ( !startsnake.empty() ) //����߻�û��ʧ�������ƶ�
        {
            startsnake.front().Clear();
            startsnake.pop_front();
        }
        ClearText();//�����������
        PrintText();//���Ƹ���λ�ú������
        #ifdef _WIN32
            Sleep(speed);
        #else
            usleep(speed * 1000);
        #endif
    }
}

void StartInterface::PrintText()
{
    for (auto& point : textsnake)
    {
        if (point.GetX() >= 0)
            point.Print();
    }
}

void StartInterface::ClearText()
{
    for (auto& point : textsnake) //�����ͬʱ���������������ƶ�һ��
    {
        if (point.GetX() >= 0)
            point.Clear();
        point.ChangePosition(point.GetX() + 1, point.GetY());
    }
}

void StartInterface::Action()
{
    PrintFirst();
    PrintSecond();
    PrintThird();
}

