#include "client.h"

int TCP_Chat(char username[50])
{
        //创建 TCP  socket
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
        	if(tcp_socket < 0)
        	{
        		perror("socket");
        		return -1;
        	}
                else
                {
                        printf("socket ok\n");
                }

	//连接服务器

	addr.sin_family = AF_INET;//IPV4
	addr.sin_port     = htons(PORT);//端口号
	addr.sin_addr.s_addr = inet_addr(IP);//服务器IP地址

        int  ret = connect(tcp_socket,(struct sockaddr *)&addr,sizeof(addr));
                if(ret < 0)
                {
                        perror("connect");
                        return  -1;
                }
                else
                {
                        printf("connect ok\n");
                }

	char msg[100] = {0};
	sprintf(msg,"login %s",username);
	write(tcp_socket,msg,strlen(msg));

	//设计多路复用的框架
	while(1)
	{
		printf("1.查看好友列表 2.指定好友聊天 3.获取天气 4.发送文件给好友\n");

                fd_set set;
                FD_ZERO(&set);//清空文件描述集合

                FD_SET(tcp_socket,&set);
                FD_SET(0,&set);

                //开始监听
                int ret = select(tcp_socket+1,&set,NULL,NULL,NULL);
                        if(ret < 0)
                        {
                                perror("select");
                                return -1;
                        }
                        else
                        {
                                printf("select ok\n");
                        }

                //判断哪一个描述符活跃
                if(FD_ISSET(tcp_socket,&set))
                {
                        char buf[1024] = {0};
                        int size = read(tcp_socket,buf,1024);
				if(size <= 0)
				{
					printf("服务器已关闭\n");

                                        char notice[1200] = {0};
                                        sprintf(notice,"%d@%s\n",CHAT,"服务器已关闭");
                                        ShowSrv(notice);

                                        close(tcp_socket);
					return 0;
				}

                        int type = atoi(buf);
                                if(type == BOARDCAST)//广播消息
                                {
                                        ShowBoard(buf);
                                }
				else if(type == CHAT)//服务器消息
	                        {
                                        ShowSrv(buf);
	                        }
                                else if(type == GET)//获取列表
                                {
                                        ShowList(buf);
                                }
                                else if(type == THRANSPOND)//聊天消息
                                {
                                        ShowTalk(buf);
                                }
                                else if(type == SYN)//文件接收请求
	                        {
                                        RcvFile(buf);
	                        }
                }

                if(FD_ISSET(0,&set))
                {
                        char buf[4096] = {0};
                        read(0,buf,4096);
			if(atoi(buf) == 1)
                        {
                                char get_list[100] = {0};
                                sprintf(get_list,"%d@%s\n",GET,"list");
                                write(tcp_socket,get_list,strlen(get_list));
                        }
                        else if(atoi(buf) == 2)
			{
                                printf("请输入聊天好友名字\n");
                                char name[100] = {0};
                                scanf("%s",name);
                                printf("请输入聊天信息\n");
                                char text[1024] = {0};
                                scanf("%s",text);
                                char chat[2048] = {0};
                                sprintf(chat,"%d@%s@%s\n",THRANSPOND,name,text);
                                write(tcp_socket,chat,strlen(chat));

                                fontSetSize(f,30);
                                bitmap *bm7 = createBitmapWithInit(400,150,4,getColor(0,238,223,178));
                                // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
                                show_font_to_lcd(lcd->mp,200,190,bm7);
                                destroyBitmap(bm7);
                                bitmap *bm = createBitmapWithInit(400,150,4,getColor(0,238,223,178));
                                fontPrint(f,bm,10,10,text,getColor(0,139,123,96),390);
                                show_font_to_lcd(lcd->mp,200,190,bm);
                                destroyBitmap(bm);
			}
                        else if(atoi(buf) == 3)
			{
				GetNetInf("广州天气");
			}
                        else if(atoi(buf) == 4)
                        {
                                SndFile();
                        }

                }
        }
}
