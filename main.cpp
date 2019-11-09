#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

#include "json.h"
#include "udp.h"

const char kConfigFile[] = "config.json";

void SendUdp(std::string ip, uint16_t port){
    UdpSocket udp;
    if(udp.Init()){
        printf("[Error] Cannot init socket\n");
        return;
    }
    udp.SetSendIp(ip.c_str(), port);
    char buff[512];
    for(;;){
        if(udp.Send(buff, sizeof(buff))<=0){
            printf("[Error] Send error\n");
            return ;
        }
    }
}

int main(){
    Json::Value root;
    std::ifstream fd(kConfigFile);
    if(!fd){
        printf("[Error] Cannot open config file\n");
        return -1;
    }
    fd >> root;
    fd.close();
    std::string ip = root["ip"].asString();
    uint16_t port = root["port"].asUInt();
    printf("Start test\n");
    printf("[IP] %s\n", ip.c_str());
    printf("[Port] %u\n", port);
    SendUdp(ip, port);
    return 0;
}