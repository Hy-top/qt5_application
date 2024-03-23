/******************************************************************************
  文 件 名   : can_drv.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "can_drv.h"
#include <qdebug.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <QProcess>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <termios.h>

static void closeSocket(const int sockfd);
static int socketCanListen(const int port);

CAN_Drv::CAN_Drv(QObject *parent) :
    QObject(parent)
{
    can_send_socket_fd = -1;
    can_recv_socket_fd = -1;
}

CAN_Drv::CAN_Drv(QObject *parent, int port, int bitrate) :
    QObject(parent),can_send_socket_fd(-1)
{
    bitrate = bitrate;

    if(port == 0)
    {
        /*** 权限限制，故把以下语句屏蔽掉，功能实现在rootfs的脚本中 ***/
        /*
        this->closeCan(0);
        this->setCanBitrate(0, bitrate);
        this->openCan(0);
        */

        can_send_socket_fd = this->socketCanConnect(0);
        can_recv_socket_fd = this->socketCanConnect(0);
        if (can_send_socket_fd < 0 || can_send_socket_fd < 0)
        {
            this->canDisconnect(&can_send_socket_fd);
            this->canDisconnect(&can_recv_socket_fd);
        }
        this->setCanFilter(can_send_socket_fd);
        this->setCanLoopback(can_send_socket_fd, false);   //  fase : 本地环回关闭; true : 本地环回使能
    }
    else
    {
        /*** 权限限制，故把以下语句屏蔽掉，功能实现在rootfs的脚本中 ***/
        /*
        this->closeCan(1);
        this->setCanBitrate(1, bitrate);
        this->openCan(1);
        */

        can_send_socket_fd = this->socketCanConnect(1);
        can_recv_socket_fd = this->socketCanConnect(1);
        if (can_send_socket_fd < 0 || can_send_socket_fd < 0)
        {
            this->canDisconnect(&can_send_socket_fd);
            this->canDisconnect(&can_recv_socket_fd);
        }
        this->setCanFilter(can_send_socket_fd);
        this->setCanLoopback(can_send_socket_fd, false);   //  fase : 本地环回关闭; true : 本地环回使能
    }
}

static void panic(const char *msg)
{
    printf(msg);
    exit(1);
}

bool CAN_Drv::closeCan(const int port)
{
    char	l_c8Command[64] = {0};
    sprintf(l_c8Command, "ifconfig can%d down", port);
    system(l_c8Command);

    return true;
}

/*
 * port: 0, 1
 *	bitrate: 250000 or 125000
 */
bool CAN_Drv::setCanBitrate(const int port, const int bitrate)
{
    #define TX_QUEUE_LEN		4096 // 使用足够多的发送缓存

    char	l_c8Command[128] = {0};

    //sprintf(l_c8Command, "echo %d > /sys/class/net/can%d/can_bittiming/bitrate", bitrate, port);
    sprintf(l_c8Command, "ifconfig can%d down", port);
    system(l_c8Command);
    //sprintf(l_c8Command, "ip link set can%d up type can bitrate %d restart-ms 3000", port, bitrate);
    sprintf(l_c8Command, "ip link set can%d up type can bitrate %d restart-ms 100", port, bitrate);
    system(l_c8Command);
    sprintf(l_c8Command, "ifconfig can%d up", port);
    system(l_c8Command);
    sprintf(l_c8Command,"ifconfig can%d txqueuelen 1000",port);
    system(l_c8Command);

    // 设置tx_queue_len
//    memset(l_c8Command, 0, sizeof(l_c8Command));
//    sprintf(l_c8Command, "echo %d > /sys/class/net/can%d/tx_queue_len", TX_QUEUE_LEN, port);
//    system(l_c8Command);

    return true;
}

bool CAN_Drv::openCan(const int port)
{
    char	l_c8Command[64] = {0};

    sprintf(l_c8Command, "ifconfig can%d up", port);
    system(l_c8Command);

    return true;
}


void closeSocket(const int sockfd)
{
    if (sockfd != -1)
    {
        close(sockfd);
    }
}

bool CAN_Drv::canDisconnect(int *sockfd)
{
    if (!sockfd || *sockfd == -1)
    {
        return false;
    }

    closeSocket(*sockfd);
    *sockfd = -1;

    return true;
}

int CAN_Drv::setCanFilter(int send_socket_fd)
{
    /**
    * struct can_filter - CAN ID based filter in can_register().
    * @can_id:   relevant bits of CAN ID which are not masked out.
    * @can_mask: CAN mask (see description)
    *
    * Description:
    * A filter matches, when
    *
    *          <received_can_id> & mask == can_id & mask
    *
    */
    const int n = 1;
    struct can_filter rfilter[n];

    // 过滤规则：当<received_can_id> & mask == can_id & mask时，接收报文，否则过滤掉.
    // 可以同时添加多条过滤规则

    // 在用来发送CAN帧的CAN_RAW套接字上不接收任何CAN帧
    rfilter[0].can_id  = 0x00000000;
    rfilter[0].can_mask = CAN_EFF_MASK;
    (void)setsockopt(send_socket_fd, SOL_CAN_RAW, CAN_RAW_FILTER, rfilter, n * sizeof(struct can_filter));

    // 在用来接收CAN帧的CAN_RAW套接字上禁用接收过滤规则
    //(void)setsockopt(recv_socket_fd, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

    return  0;
}

int CAN_Drv::setCanLoopback(const int sockfd, const bool lp)
{
    // 在默认情况下，本地回环功能是开启的，可以使用下面的方法关闭回环/开启功能：
    int loopback = lp;  // 0表示关闭, 1表示开启(默认)
    (void)setsockopt(sockfd, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback));

    #if 0
    // 在本地回环功能开启的情况下，所有的发送帧都会被回环到与CAN总线接口对应的套接字上。
    // 默认情况下，发送CAN报文的套接字不想接收自己发送的报文，因此发送套接字上的回环功能是关闭的。
    // 可以在需要的时候改变这一默认行为：
    int ro = 1; // 0表示关闭(默认), 1表示开启
    (void)setsockopt(sockfd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &ro, sizeof(ro));
    #endif

    return  0;
}

int CAN_Drv::can_send_frame(unsigned char *data, const int count, const int timeout_ms)
{
    int ret = timeout_ms;   // timeout_ms 赋值只是为了不报编译警告，没有实际含义
    ret = write(this->can_send_socket_fd, (char*)data, count);
    if (ret > 0)
    {
        tcdrain(this->can_send_socket_fd);//不做出错处理，因为网络不支持tcdrain
    }
    return  ret;
}

int CAN_Drv::can_recv_frame(unsigned char *buf, const int count, const int timeout_ms)
{
    struct timeval tv_timeout;
    tv_timeout.tv_sec  = timeout_ms  / 1000;
    tv_timeout.tv_usec = (timeout_ms % 1000) * 1000;
    fd_set fs_read;

    FD_ZERO(&fs_read);
    FD_SET(this->can_recv_socket_fd, &fs_read);	//if fd == -1, FD_SET will block here

    int ret = select((int)this->can_recv_socket_fd + 1, &fs_read, NULL, NULL, &tv_timeout);
    if (ret == 0) // recv timeout
    {
        return  0;
    }
    if (ret < 0) // select error
    {
        return  ret;
    }

    ret = read(this->can_recv_socket_fd, (char*)buf, count);

    if (ret <= 0)
    {
        return  -1;
    }
    return  ret;
}

int CAN_Drv::socketCanConnect(const int port)
{
    int tmpVal = 0;
    tmpVal = socketCanListen(port);

    return tmpVal;
}

// 绑定sock，然后监听端口
// 返回监听 套接字 文件描述符
int socketCanListen(const int port)
{
    int sockfd = -1;

    struct sockaddr_can _addr;
    struct ifreq _ifreq;
    char buf[256];
    int ret = 0;

    /* 建立套接字，设置为原始套接字，原始CAN协议 */
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sockfd < 0)
    {
        sprintf(buf, "\n\topen socket can%d fail\n\n", port + 1);
        panic(buf);
        return  -1;
    }

    /* 以下是对CAN接口进行初始化，如设置CAN接口名，即当我们用ifconfig命令时显示的名字 */
    sprintf(buf, "can%d", port);
    strcpy(_ifreq.ifr_name, buf);
    ret = ioctl(sockfd, SIOCGIFINDEX, &_ifreq);
    if (ret < 0)
    {
        sprintf(buf, "\n\tcan not match socket can%d \n\n", port + 1);
        panic(buf);
        return  -1;
    }

    /* 设置CAN协议 */
    _addr.can_family = AF_CAN;
    _addr.can_ifindex = _ifreq.ifr_ifindex;


    /* disable default receive filter on this RAW socket */
    /* This is obsolete as we do not read from the socket at all, but for */
    /* this reason we can remove the receive list in the Kernel to save a */
    /* little (really a very little!) CPU usage.                          */
    //	setsockopt(sockfd, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

    /* 将刚生成的套接字与CAN套接字地址进行绑定 */
    ret = bind(sockfd, (struct sockaddr *)&_addr, sizeof(_addr));
    if ( ret < 0)
    {
        closeSocket(sockfd);
        sprintf(buf, "\n\t绑定 socket can%d 错误\n\n", port + 1);
        panic(buf);
        return  -1;
    }

    return  sockfd;
}

