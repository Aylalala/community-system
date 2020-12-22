#include "client.h"

char *mystrcat(char *dest,const char *src,int num)
{
        while(*dest != '\0')
        {
                dest++;
        }

        while(num != 0)
        {
                *dest = *src;
                dest++;
                src++;
                num--;
        }

        return dest;
}

int SndFile()
{
        printf("请输入发送好友名字\n");
        char name[100] = {0};
        scanf("%s",name);
        printf("请输入发送文件名\n");
        char filename[1024] = {0};
        scanf("%s",filename);

        //打开源文件
	int fd = open(filename,O_RDWR);
		if(fd < 0)
		{
			perror("open source file");
			return -1;
		}
                else
                {
                        printf("open source file ok\n");
                }

	//获取发送文件的大小
	int  filesize = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

        //发送请求给服务器
        char send[2048] = {0};
        sprintf(send,"%d@%s@%s#%d\n",SYN,name,filename,filesize);
        write(tcp_socket,send,strlen(send));

	//等待对方回应
        char respon[1024] = {0};
	read(tcp_socket,respon,1024);

        fontSetSize(f,25);
        bitmap *bm11 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
        // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,200,380,bm11);
        destroyBitmap(bm11);
        bitmap *bm = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
        fontPrint(f,bm,10,5,"等待回应",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,200,380,bm);
        destroyBitmap(bm);

        char *t_p = strrchr(respon,'@');
        t_p += 1;
        char res_ty[300] = {0};
        strcpy(res_ty,strtok(t_p,"#"));
        int res_type = atoi(res_ty);
	if(res_type == ACCEPT)  //对方成功接收到 文件大小
	{
		int  send_size = 0;
		while(1)
		{
			//读取文件中的数据
			char send[4096] = {0};
			int size = read(fd,send,4096);

			printf("发送的大小 %d 总大小 %d\n",size,send_size);
                        char sendfile[4500] = {0};
                        sprintf(sendfile,"%d@%s@",FILEE,name);
                        mystrcat(sendfile,send,size);

			//发送网络中
			int  s_size = write(tcp_socket,sendfile,size);
			send_size += s_size;
        			if(send_size == filesize)
        			{
        				// printf("发送完毕等待对方接收完毕\n");
                                        //
                                        // bitmap *bm11 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                                        // // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
                                        // show_font_to_lcd(lcd->mp,200,380,bm11);
                                        // destroyBitmap(bm11);
                                        // bitmap *bm = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                                        // fontPrint(f,bm,10,5,"等待接收完毕",getColor(0,225,228,255),0);
                                        // show_font_to_lcd(lcd->mp,200,380,bm);
                                        // destroyBitmap(bm);
                                        //
        				// bzero(respon,1024);
        				// read(tcp_socket,respon,1024);
        				// if(strstr(respon,"END"))
        				// {
        					printf("文件传输完毕\n");

                                                bitmap *bm11 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                                                // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
                                                show_font_to_lcd(lcd->mp,200,380,bm11);
                                                destroyBitmap(bm11);
                                                bitmap *bm = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                                                fontPrint(f,bm,10,5,"发送完毕",getColor(0,225,228,255),0);
                                                show_font_to_lcd(lcd->mp,200,380,bm);
                                                destroyBitmap(bm);

        					break;
        				// }
        			}

                                res_type = RESET;
                                while(res_type != ACCEPT);
		}
	}
        // else if(res_type == REFUSE)
        // {
        //         printf("%s 拒收 %s\n",name,filename);
        //         close(fd);
        // }
        else
        {
                return ;
        }
}


int RcvFile(char buf[1024])
{
        char *s_p = strstr(buf,"@");
        s_p += 1;
        char sendname[300] = {0};
        strcpy(sendname,strtok(s_p,"@"));

        char *n_p = strrchr(buf,'@');
        n_p += 1;
        char filename[300] = {0};
        strcpy(filename,strtok(n_p,"#"));

        char *f_p = strstr(buf,"#");
        f_p += 1;
        char filesize[100] = {0};
        strcpy(filesize,strtok(f_p,"****"));
        int file_size = atoi(filesize);

        printf("sendname = %s,filename = %s,file_size = %d\n",sendname,filename,file_size);

        printf("%s 发来 %s,大小为 %d,请问是否接收?[y/n]\n",sendname,filename,filesize);
        char c;
        scanf("%c",&c);
        if(c == 'y')
        {
                //应答对方
                char respon[1024] = {0};
                sprintf(respon,"%d@%s@%d\n",RESPONSE,sendname,ACCEPT);
                write(tcp_socket,respon,strlen(respon));

                fontSetSize(f,25);
                bitmap *bm13 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
                show_font_to_lcd(lcd->mp,400,380,bm13);
                destroyBitmap(bm13);
                bitmap *bm = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                char note[100] = {0};
                sprintf(note,"正在接收 %s\n",filename);
                fontPrint(f,bm,10,5,note,getColor(0,225,228,255),90);
                show_font_to_lcd(lcd->mp,400,380,bm);
                destroyBitmap(bm);

                //创建新文件
                int fd = open(filename,O_RDWR|O_CREAT|O_TRUNC,0777);
                        if(fd < 0)
                        {
                                perror("open new file");
                                return -1;
                        }
                        else
                        {
                                printf("open new file ok\n");
                        }

                //接收网络数据写入到本地文件中
                int  recv_size = 0;
                while(1)
                {
                        char recv[4096] = {0};
                        int size = read(tcp_socket,recv,4096); //读取网络数据
                        recv_size += size;
                        printf("当前接收的大小 %d ,总大小 %d\n",size,recv_size);
                        write(fd,recv,size); //写入到本地文件中

                        //应答对方
                        char respon[1024] = {0};
                        sprintf(respon,"%d@%s@%d\n",RESPONSE,sendname,ACCEPT);
                        write(tcp_socket,respon,strlen(respon));

                        if(recv_size == file_size)
                        {
                                printf("接收完毕\n");

                                fontSetSize(f,30);
                                bitmap *bm13 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                                // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
                                show_font_to_lcd(lcd->mp,400,380,bm13);
                                destroyBitmap(bm13);
                                bitmap *bm = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
                                char notes[100] = {0};
                                sprintf(notes,"接收 %s 完毕\n",filename);
                                fontPrint(f,bm,10,5,notes,getColor(0,225,228,255),90);
                                show_font_to_lcd(lcd->mp,400,380,bm);
                                destroyBitmap(bm);

                                //应答对方
                                //write(tcp_socket,"END",strlen("END"));
                                close(fd);
                                break;
                        }
                }
        }
        else if(c == 'n')
        {
                //应答对方
                char respon[1024] = {0};
                sprintf(respon,"%d@%s@%d\n",RESPONSE,sendname,REFUSE);
                write(tcp_socket,respon,strlen(respon));

                return ;
        }
        else
        {
                printf("输入错误\n");
                return ;
        }


}
