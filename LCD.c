#include "client.h"

//初始化Lcd
struct LcdDevice *init_lcd(const char *device)
{
	//申请空间
	struct LcdDevice* lcd = malloc(sizeof(struct LcdDevice));
	if(lcd == NULL)
	{
		return NULL;
	}

	//1打开设备
	lcd->fd = open(device, O_RDWR);
	if(lcd->fd < 0)
	{
		perror("open lcd fail");
		free(lcd);
		return NULL;
	}

	//映射
	lcd->mp = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd->fd,0);

	return lcd;
}

//显示界面
void ShowMain()
{
	fontSetSize(f,30);

        bitmap *bm = createBitmapWithInit(200,40,4,getColor(0,238,211,164));
        fontPrint(f,bm,70,5,"公告",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,0,0,bm);
        destroyBitmap(bm);
        bitmap *bm1 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        // fontPrint(f,bm1,70,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,0,40,bm1);
        destroyBitmap(bm1);

        bitmap *bm2 = createBitmapWithInit(200,40,4,getColor(0,238,211,164));
        fontPrint(f,bm2,55,5,"服务器",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,0,240,bm2);
        destroyBitmap(bm2);
        bitmap *bm3 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        // fontPrint(f,bm3,55,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,0,280,bm3);
        destroyBitmap(bm3);

        bitmap *bm4 = createBitmapWithInit(200,40,4,getColor(0,238,211,164));
        fontPrint(f,bm4,40,5,"好友列表",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,600,0,bm4);
        destroyBitmap(bm4);
        bitmap *bm5 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        // fontPrint(f,bm5,10,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,600,40,bm5);
        destroyBitmap(bm5);

        bitmap *bm6 = createBitmapWithInit(400,40,4,getColor(0,205,182,141));
        fontPrint(f,bm6,140,5,"聊天消息",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,200,0,bm6);
        destroyBitmap(bm6);
        bitmap *bm7 = createBitmapWithInit(400,300,4,getColor(0,238,223,178));
        // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,200,40,bm7);
        destroyBitmap(bm7);

        bitmap *bm8 = createBitmapWithInit(200,40,4,getColor(0,238,211,164));
        fontPrint(f,bm8,70,5,"天气",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,600,240,bm8);
        destroyBitmap(bm8);
        bitmap *bm9 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        // fontPrint(f,bm9,70,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,600,280,bm9);
        destroyBitmap(bm9);

        bitmap *bm10 = createBitmapWithInit(200,40,4,getColor(0,205,182,141));
        fontPrint(f,bm10,40,5,"发送文件",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,200,340,bm10);
        destroyBitmap(bm10);
        bitmap *bm11 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
        // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,200,380,bm11);
        destroyBitmap(bm11);

        bitmap *bm12 = createBitmapWithInit(200,40,4,getColor(0,205,182,141));
        fontPrint(f,bm12,40,5,"接收文件",getColor(0,139,112,74),0);
        show_font_to_lcd(lcd->mp,400,340,bm12);
        destroyBitmap(bm12);
        bitmap *bm13 = createBitmapWithInit(200,100,4,getColor(0,238,223,178));
        // fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
        show_font_to_lcd(lcd->mp,400,380,bm13);
        destroyBitmap(bm13);
}

//显示公告内容
void ShowBoard(char buf[1024])
{
        char *p = strstr(buf,"@");
        p += 1;
        char board[1024] = {0};
        strcpy(board,strtok(p,"****"));

        printf("board:\n\t%s\n",board);

        fontSetSize(f,30);
        bitmap *bm1 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        // fontPrint(f,bm1,10,10," ",getColor(0,225,228,255),190);
        show_font_to_lcd(lcd->mp,0,40,bm1);
        destroyBitmap(bm1);
        bitmap *bm = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
        fontPrint(f,bm,10,10,board,getColor(0,139,123,96),190);
        show_font_to_lcd(lcd->mp,0,40,bm);
        destroyBitmap(bm);

	return ;
}

//显示服务器信息
void ShowSrv(char buf[1024])
{
	char *p = strstr(buf,"@");
	p += 1;
	char ser[1024] = {0};
	strcpy(ser,strtok(p,"****"));

	printf("ser:\n\t%s\n",ser);

	fontSetSize(f,30);
	bitmap *bm1 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
	//fontPrint(f,bm1,10,10,ser,getColor(0,139,123,96),190);
	show_font_to_lcd(lcd->mp,0,280,bm1);
	destroyBitmap(bm1);
	bitmap *bm = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
	fontPrint(f,bm,10,10,ser,getColor(0,139,123,96),190);
	show_font_to_lcd(lcd->mp,0,280,bm);
	destroyBitmap(bm);
}

//显示好友列表
void ShowList(char buf[1024])
{
	char *p = strstr(buf,"@");
	p += 1;
	char list[1024] = {0};
	strcpy(list,strtok(p,"****"));
	printf("好友列表\n");
	printf("%s\n",list);

	fontSetSize(f,30);
	bitmap *bm5 = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
	// fontPrint(f,bm5,10,5," ",getColor(0,225,228,255),0);
	show_font_to_lcd(lcd->mp,600,40,bm5);
	destroyBitmap(bm5);
	bitmap *bm = createBitmapWithInit(200,200,4,getColor(0,255,239,191));
	fontPrint(f,bm,10,10,list,getColor(0,139,123,96),190);
	show_font_to_lcd(lcd->mp,600,40,bm);
	destroyBitmap(bm);
}

//显示聊天消息
void ShowTalk(char buf[1024])
{
	char *p = strstr(buf,"@");
	p += 1;
	char chat[2048] = {0};
	strcpy(chat,strtok(p,"****"));
	printf("%s\n",chat);

	fontSetSize(f,30);
	bitmap *bm7 = createBitmapWithInit(400,150,4,getColor(0,238,223,178));
	// fontPrint(f,bm7,10,5," ",getColor(0,225,228,255),0);
	show_font_to_lcd(lcd->mp,200,40,bm7);
	destroyBitmap(bm7);
	bitmap *bm = createBitmapWithInit(400,150,4,getColor(0,238,223,178));
	fontPrint(f,bm,10,10,chat,getColor(0,139,123,96),390);
	show_font_to_lcd(lcd->mp,200,40,bm);
	destroyBitmap(bm);
}
