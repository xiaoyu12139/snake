#include "map.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void Map::PrintInitmap()//���Ƴ�ʼ��ͼ
{
    for (auto& point : initmap)
    {
        point.Print();
        #ifdef _WIN32
            Sleep(10);//����Sleep������Ӫ�춯��Ч��
        #else
            usleep(10 * 1000);
        #endif
    }
}
