#include "client.h"

int tcp_socket = 0;
struct sockaddr_in addr;
struct LcdDevice *lcd = NULL;
font *f = NULL;

int main(int argc,char *argv[])
{
        if(argc != 2)
        {
                printf("./client username\n");
                return -1;
        }

        //初始化Lcd
       lcd = init_lcd("/dev/fb0");
       //打开字体
       f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

       ShowMain();

        TCP_Chat(argv[1]);

        //关闭字库
        fontUnload(f);

        return 0;
}
