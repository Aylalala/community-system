#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <linux/input.h>   //声明输入模型
#include "font.h"

/*服务器地址信息*/
#define PORT 8080
#define IP "192.168.22.23"

/*消息类型*/
#define BOARDCAST 0x00 //广播                             BOARDCAST@bc_msg
#define CHAT 0x01 //服务器消息                               CHAT@c_msg
#define THRANSPOND 0x02 //需要转发的消息      THRANSPOND@destname@t_msg
#define GET 0x03 //获取列表                                     GET@list
#define SYN 0x04 //请求同步                                     SYN@destname@filename#filesize
#define FILEE 0x05 //文件发送                                  FILEE@destname@file_data
#define RESPONSE 0x06 // 回应                                RESPONSE@destname@r_msg

#define RESET 0x00 //重置
#define ACCEPT 0x01 //接收                                      RESPONSE@destname@ACCEPT
#define REFUSE 0x02 //拒收                                      RESPONSE@destname@REFUSE

/*外部变量声明*/
extern int tcp_socket;//TCP通信socket
extern struct sockaddr_in addr;//服务器地址信息
extern struct LcdDevice *lcd;//LCD
extern font *f;//字库

/*函数声明*/
int TCP_Chat(char username[50]);//TCP通信

struct LcdDevice *init_lcd(const char *device);//初始化LCD
void ShowMain();//显示界面
void ShowBoard(char buf[1024]);//显示公告消息
void ShowSrv(char buf[1024]);//显示服务器信息
void ShowList(char buf[1024]);//显示好友列表
void ShowTalk(char buf[1024]);//显示聊天消息

int GetNetInf(char cmd[100]);//获取网络信息

char *mystrcat(char *dest,const char *scr,int num);//拼接文件信息
int RcvFile(char buf[1024]);//接收文件
int SndFile();//发送文件

#endif
