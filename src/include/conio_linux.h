#ifndef CONIO_LINUX_H
#define CONIO_LINUX_H
#include <iostream>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// 1. Linux��getch()
inline int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);           // ��ȡ�ɵ��ն�����
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);          // ȡ������+������
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);   // Ӧ��������
    // system("stty -echo");
    ch = getchar();                            // ��һ���ַ�
    // system("stty echo");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);   // �ָ�������
    return ch;
}

// 2. Linux��kbhit()
inline int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin); // �Ѷ�ȡ�����ַ��Ż�������
        return 1;
    }

    return 0;
}
#endif
#endif // CONIO_LINUX_H
