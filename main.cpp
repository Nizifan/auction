//
//  main.cpp
//  auction
//
//  Created by zifan on 2016/11/29.
//  Copyright © 2016年 zifan. All rights reserved.
//


#include <stdio.h>
#include <winsock2.h>//winsocket2 的头文件
#include <iostream>
#include <vector>
#include <string.h>
#pragma comment(lib, "WS2_32.lib")//winsocket2需要的库文件

using namespace std;

string INSTR[20];
int INSTR_NUM = 20;

class AuctionRoom{
public:
    AuctionRoom(){
        roomNumber =ROOMS.createRoomNumber();
        price = -1;
        lastBidder = -1;
        auctionName = string();
    }
    int getRoomNumber(){
        return roomNumber;
    }
    void printMember(){
        cout<<"member in the room "<<getRoomNumber()<<endl;
		for (int i = 0; i < member.size(); i++) {
			cout << member[i] << endl;
		}
        cout<<"================"<<endl;
    }
private:
    vector<int> member;
    int roomNumber;
    int price;
    int lastBidder;
    string auctionName;
};

class AuctionRooms{
public:
    AuctionRooms(){
        lastRoom = 0;
    }
    int createRoomNumber(){
        lastRoom += 1;
        return lastRoom;
    }
    int newroom(string auctionName,int _price){
        rooms.push(AuctionRoom(auctionName,_price));
        return rooms[rooms.size()-1].getRoomNumber();
    }
    int getLastRoom(){
        return lastRoom;
    }
    int getInRoom(){
        return inRoom;
    }
    void listBidder(){
        if (self.getRoomByNumber(inRoom))
                self.getRoomByNumber(inRoom).printMember();
        else cout<<"In no Rooms"<<endl;
    }
    void listRoom(){
        cout<<"========Auction========"<<endl;
        for(int i = 0; i < rooms.size; i++){
            cout<<rooms[i].getRoomNumber()<<endl;
        }
        cout<<"=========end==========="<<endl;
    }
private:
    vector<AuctionRoom> rooms;
    int lastRoom;
    int inRoom;
    AuctionRoom getRoomByNumber(int roomNumber){
        for(int i = 0; i< rooms.size; i++){
            if (rooms[i].getRoomNumber == inRoom)
                return rooms[i];
        }
        return;
    }
};

AuctionRooms ROOMS = new AuctionRooms();

int getid(string input){
    for(int i = 0; i < INSTR_NUM ; i++ ){
        if(input.substr(INSTR[i]) != -1){
            return i;
        }
    }
    return -1;
}

int msg(string instr){
}

int list(){
    ROOMS.listBidder();
    return 1;
}

int auctions(){
    ROOMS.listRoom();
    return 1;
}

int process(int i,	string instr){
    int result = 1;
    switch (i) {
        case 1:
            msg(instr);
            break;
            
        default:
            break;
    }
    return result;
}

int main()
{
    //main logic
    
    string input = string();
    while(true){
        cin>>input;
        if(input[0] != '/'){
            continue;
        }
        process(getid(input));
    }
    
    //第一步：初始化网络
    WSADATA     wsaData;
    WORD     wVersion = MAKEWORD(2,2);
    WSAStartup(wVersion, &wsaData);
    
    //第二步：建立一个socket
    SOCKET     sServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    //第三步：填充sockaddr_in结构
    sockaddr_in    sin;
    sin.sin_family     = AF_INET;
    sin.sin_port     = htons(16568);
    sin.sin_addr.S_un.S_addr  = INADDR_ANY;
    
    //第四步：绑定这个套接字到一个本地地址
    if ( ::bind( sServer, (LPSOCKADDR)&sin, sizeof(sin) ) == SOCKET_ERROR )
    {
        return 0;
    }
    
    //第五步：接收数据
    char     szBuf[1024];
    sockaddr_in    addr;
    int      nLen = sizeof(addr);
    while (true)
    {
        int nRecv     = recvfrom(sServer, szBuf, 1024, 0, (sockaddr*)&addr, &nLen);
        if ( nRecv > 0 )
        {
            szBuf[nRecv] = '\0';
            cout << "接收到数据：" << szBuf << endl;
            if ( strcmp(szBuf, "exit") == 0 )
            {
                break;
            } if ( strcmp(szBuf, ""))
        }
    }
    
    //第六步：关闭socket，释放网络
    closesocket(sServer);
    WSACleanup();
    return 0;
}
