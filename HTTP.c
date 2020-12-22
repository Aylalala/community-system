#include "client.h"

int GetNetInf(char cmd[100])
{
        //创建 TCP  socket
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
        	if(tcp_socket < 0)
        	{
        		perror("socket");
        		return -1;
        	}
                else
                {
                        printf("socket ok\n");
                }

        //获取服务器IP
        char server_ip[100] = {0};
        struct hostent *getip = gethostbyname("api.qingyunke.com");
                if(getip == NULL)
                {
                        perror("gethostbyname");
                        return -1;
                }
                else
                {
                        strcpy(server_ip,inet_ntoa(*((struct in_addr*)getip->h_addr_list[0])));
                        printf("server_ip = %s\n",server_ip);
                }

        //设置服务器的IP地址信息
        struct sockaddr_in  addr;
        addr.sin_family   = AF_INET; //IPV4 协议
        addr.sin_port     = htons(80); //端口 80  ,所有的HTTP 服务器端口都是  80
        addr.sin_addr.s_addr = inet_addr(server_ip); //服务器的IP 地址信息
        int ret = connect(tcp_socket,(struct sockaddr *)&addr,sizeof(addr));
                if(ret < 0)
                {
                        perror("connect");
                        return -1;
                }
                else
                {
                        printf("connect ok\n");
                }

        //重点！！定制HTTP 请求协议
        //https://    cloud.qqshabi.cn    /api/hitokoto/hitokoto.php
        char http[1024] = {0};
        sprintf(http,"GET /api.php?key=free&appid=0&msg=%s HTTP/1.1\r\nHost:api.qingyunke.com\r\n\r\n",cmd);

        //发送数据给服务器
        write(tcp_socket,http,strlen(http));

	//跳过头
	char  buf[4096] = {0};
	char *buf_p = NULL;
	int buf_size = read(tcp_socket,buf,4096);

	buf_p = strstr(buf,"广州天气");
	int size = buf_size - (int)(buf_p - buf);
	char msg[4096] = {0};
	strcpy(msg,strtok(buf_p,"{br}"));
        printf("size = %d  msg = %s\n",size,msg);

	write(tcp_socket,http,strlen(http));
	char  buf1[4096] = {0};
	char *buf_p1 = NULL;
	int buf_size1 = read(tcp_socket,buf1,4096);

	buf_p1 = strstr(buf1,"[");
	int size1 = buf_size1 - (int)(buf_p1 - buf1);
	char msg1[4096] = {0};
	strcpy(msg1,strtok(buf_p1,"{br}"));
        printf("size1 = %d  msg1 = %s\n",size1,msg1);

        fontSetSize(f,25);
	bitmap *bm9 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        // fontPrint(f,bm9,70,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,600,280,bm9);
        destroyBitmap(bm9);
        bitmap *bm = createBitmapWithInit(200,110,4,getColor(0,255,239,191));
        fontPrint(f,bm,10,10,msg,getColor(0,139,123,96),190);
        show_font_to_lcd(lcd->mp,600,280,bm);
	destroyBitmap(bm);
	bitmap *bm1 = createBitmapWithInit(200,90,4,getColor(0,255,239,191));
	fontPrint(f,bm1,10,10,msg1,getColor(0,139,123,96),190);
        show_font_to_lcd(lcd->mp,600,390,bm1);
        destroyBitmap(bm1);

	return 0;
}
