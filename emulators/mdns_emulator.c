#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <err.h>

int handle_datagram(char buffer[], int count){
    if (strstr(buffer,"\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x09\x5F\x73\x65\x72\x76\x69\x63\x65\x73\x07\x5F\x64\x6E\x73\x2D\x73\x64\x04\x5F\x75\x64\x70\x05\x6C\x6F\x63\x61\x6C\x00\x00\x0C\x00\x01")!=NULL){
        //printf("Message received!\n");
        return 1;
    }
    else{
        return -1;
    }
}

int main(){
    //Create child(deamon) process
    pid_t process_id = fork();
    if (process_id<0){
        printf("Fork failure!\n");
        exit(1);
    }
    else if (process_id>0){
        //printf("Deamon process initialized!\n");
        //printf("Terminating parent process...\n");
        exit(0);
    }
    
    //IP address and port converted from string to struct sockaddr_in
    const char* hostname="0.0.0.0"; /* wildcard */
    const char* portname="1900";
   	struct addrinfo hints;
    
    //Content to reflect back
   	char content[]={0xa1,0x3c,0x83,0x80,0x00,0x01,0x00,0x15,0x00,0x00,0x00,0x01,0x04,0x63,0x70,0x73,0x63,0x03,0x67,0x6f,0x76,0x00,0x00,0xff,0x00,0x01,0xc0,0x0c,0x00,0x02,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x12,0x06,0x61,0x75,0x74,0x68,0x30,0x30,0x02,0x6e,0x73,0x02,0x75,0x75,0x03,0x6e,0x65,0x74,0x00,0xc0,0x0c,0x00,0x02,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x09,0x06,0x61,0x75,0x74,0x68,0x36,0x31,0xc0,0x2d,0xc0,0x0c,0x00,0x0f,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x0b,0x00,0x05,0x06,0x68,0x6f,0x72,0x6d,0x65,0x6c,0xc0,0x0c,0xc0,0x0c,0x00,0x0f,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x0a,0x00,0x05,0x05,0x73,0x74,0x61,0x67,0x67,0xc0,0x0c,0xc0,0x0c,0x00,0x10,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x51,0x50,0x76,0x3d,0x73,0x70,0x66,0x31,0x20,0x69,0x70,0x34,0x3a,0x36,0x33,0x2e,0x37,0x34,0x2e,0x31,0x30,0x39,0x2e,0x36,0x20,0x69,0x70,0x34,0x3a,0x36,0x33,0x2e,0x37,0x34,0x2e,0x31,0x30,0x39,0x2e,0x31,0x30,0x20,0x69,0x70,0x34,0x3a,0x36,0x33,0x2e,0x37,0x34,0x2e,0x31,0x30,0x39,0x2e,0x32,0x30,0x20,0x6d,0x78,0x20,0x61,0x3a,0x6c,0x69,0x73,0x74,0x2e,0x63,0x70,0x73,0x63,0x2e,0x67,0x6f,0x76,0x20,0x2d,0x61,0x6c,0x6c,0xc0,0x0c,0x00,0x01,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x04,0x3f,0x4a,0x6d,0x02,0xc0,0x0c,0x00,0x1c,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x10,0x26,0x00,0x08,0x03,0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xc0,0x0c,0x00,0x30,0x00,0x01,0x00,0x00,0x0c,0x88,0x01,0x08,0x01,0x01,0x03,0x07,0x03,0x01,0x00,0x01,0x75,0x6d,0xf8,0xba,0xba,0x07,0x40,0xd5,0xc0,0x00,0x0c,0x2e,0x46,0xfd,0x92,0x59,0xac,0xfb,0xa8,0xb6,0x96,0x4d,0xe8,0xad,0x54,0x01,0x19,0x3c,0x34,0x0d,0x7b,0x11,0xc3,0x56,0xf5,0x3f,0x55,0x7d,0x01,0xeb,0x85,0xfd,0x17,0xca,0x5a,0xb7,0x5d,0xde,0x01,0x65,0x3d,0x72,0x44,0x1a,0x0b,0x60,0x84,0xce,0xca,0xe9,0x82,0xb8,0x5d,0x71,0x53,0xd7,0x75,0x19,0x49,0x6c,0x63,0x2e,0x50,0x6d,0xa2,0x45,0x0f,0x42,0x41,0x73,0xcf,0xae,0x8a,0x98,0x21,0xb4,0xe8,0x38,0xf9,0xe5,0xf6,0x0b,0xd8,0x77,0x7a,0x6b,0x00,0xe9,0xdd,0x8d,0x48,0xbc,0x43,0x40,0xcb,0x87,0x1e,0x73,0xff,0x62,0x6d,0x6f,0x0c,0x43,0x46,0x2e,0x8f,0x34,0xf0,0xce,0xfa,0x6b,0xce,0xc7,0x5b,0x23,0x35,0x49,0xf1,0x3a,0x4b,0xfe,0x4c,0x88,0x59,0xc4,0x83,0x94,0xb6,0xfd,0x3a,0xcf,0xb7,0x58,0x17,0x0f,0x1d,0xa2,0x9a,0x16,0x2b,0xe1,0x0c,0x77,0xeb,0x6d,0xf6,0x22,0x2f,0x1b,0x82,0x19,0x48,0xac,0xde,0x4a,0xf0,0x13,0x92,0xe1,0x8d,0xa6,0x31,0x49,0xa4,0x29,0x9d,0xa9,0x6a,0x62,0x9b,0x0d,0x40,0x2e,0xd5,0xd8,0x4d,0x6c,0x78,0x74,0xa7,0x8c,0xb8,0x3c,0x70,0xee,0x49,0x74,0xe0,0xf8,0xab,0x73,0x2d,0x9c,0xbd,0x9d,0x60,0xfd,0x8e,0xa0,0x4a,0x19,0xf8,0xf8,0xfb,0x17,0x5a,0x5f,0x18,0x1d,0x0e,0xf4,0x93,0xd6,0x96,0x89,0xeb,0x89,0x24,0xbb,0xeb,0x1c,0x4e,0xb7,0x0a,0xd8,0xd5,0x00,0xb2,0xb1,0x9b,0xbd,0x0c,0x91,0x10,0x5a,0x05,0x61,0x12,0x08,0x0d,0x74,0xec,0x07,0x64,0x89,0xc0,0x0c,0x00,0x30,0x00,0x01,0x00,0x00,0x0c,0x88,0x01,0x08,0x01,0x01,0x03,0x07,0x03,0x01,0x00,0x01,0x92,0x58,0xe5,0xd2,0x00,0x9b,0xc4,0x2c,0x33,0x6b,0x01,0x06,0xc3,0xa8,0x62,0x47,0x8c,0x86,0x4d,0x6c,0x50,0x70,0x6a,0x30,0xe0,0x25,0xc5,0x0f,0x15,0x06,0x1a,0x15,0x36,0x80,0xcd,0xd2,0xf5,0x73,0x3a,0x92,0xc0,0x19,0x54,0xc4,0x4e,0x1c,0xef,0x3a,0x59,0x4b,0x5f,0x65,0xb1,0x0a,0x99,0x14,0xf0,0x02,0xa2,0xa0,0xee,0x25,0xd7,0xcf,0x11,0x8c,0x17,0xf9,0xc2,0x3b,0x3f,0x02,0x3d,0xa2,0xd6,0xe2,0x3c,0x40,0x8c,0xa1,0x68,0xcc,0x59,0x4b,0xf8,0x9f,0x5a,0x04,0x78,0x6c,0x10,0x38,0x77,0x83,0x60,0x18,0x3a,0x47,0x64,0x49,0x6b,0xd0,0x29,0xf6,0x3a,0x50,0xc9,0xc2,0x11,0x84,0x34,0xea,0xfd,0x93,0x18,0x60,0x0d,0x74,0xfd,0xed,0x45,0x67,0x23,0x61,0x7b,0x26,0x9b,0x50,0x66,0x07,0x80,0x22,0x51,0xa8,0xc1,0x53,0xcc,0x52,0x94,0xb3,0xe2,0xfe,0xb5,0xd2,0xe7,0xb2,0x3a,0x06,0x16,0x35,0x83,0x74,0xdf,0xe2,0x22,0xb5,0x83,0x96,0x1c,0xc0,0xc1,0x9b,0x8b,0x77,0xa1,0x88,0x6b,0x08,0xa9,0xea,0x3e,0xe6,0xae,0x1b,0x5a,0x2e,0x95,0x64,0xbd,0xcb,0x97,0x9a,0x60,0xd4,0x7c,0xda,0x3f,0xd6,0x9c,0x2c,0xc0,0x2b,0xf8,0x1b,0xe5,0x74,0xdc,0x1e,0x2d,0x36,0x24,0x1f,0x7c,0x3e,0x20,0x17,0x50,0xee,0xfe,0x08,0xd8,0xe2,0xf5,0x94,0x6d,0xff,0x21,0x43,0xaa,0x9a,0x20,0xa0,0xa8,0x77,0xa2,0xab,0xc4,0x0b,0xe9,0x4f,0x34,0x03,0xfd,0x09,0x9f,0xc3,0xb9,0x4a,0x7e,0x44,0x32,0xf8,0xd6,0x69,0xb9,0xbc,0xab,0xe9,0x17,0xd8,0x1e,0x22,0xae,0x57,0x18,0x51,0xc0,0x0c,0x00,0x30,0x00,0x01,0x00,0x00,0x0c,0x88,0x01,0x08,0x01,0x00,0x03,0x07,0x03,0x01,0x00,0x01,0x76,0xfa,0xe3,0xea,0x5f,0x03,0x74,0x35,0x93,0x79,0xe9,0x1c,0xae,0x90,0xe0,0x34,0x4f,0x72,0x8f,0x5d,0x3e,0x92,0xd6,0x72,0x56,0xa6,0x1e,0x45,0xb9,0x81,0x78,0x28,0x91,0x93,0x43,0x86,0xb3,0x53,0x1c,0xbc,0x01,0x07,0x43,0xd8,0xec,0x29,0x36,0xe6,0x22,0xff,0xca,0xab,0x29,0x82,0x8c,0x5f,0xcd,0xe6,0x02,0xfe,0x9c,0x02,0x67,0xeb,0x1b,0x49,0x84,0x0d,0x97,0x50,0x01,0x4b,0x94,0x18,0x54,0x77,0x23,0x3f,0x77,0x03,0x32,0xb0,0x71,0x56,0x33,0x16,0xbf,0xfa,0x89,0x16,0x7b,0x2a,0x36,0x3d,0x33,0x6c,0xfe,0xad,0xa9,0x37,0x13,0xb6,0xca,0x28,0x28,0x14,0xd5,0x63,0x22,0x8a,0xac,0xe1,0x59,0xd5,0x26,0x60,0x6b,0xb7,0x08,0x1e,0x4e,0x67,0x29,0xda,0x93,0x15,0x9d,0xe4,0xd4,0x64,0x9d,0xca,0x5f,0x9d,0x26,0xdb,0x2d,0xe0,0x86,0x54,0x3d,0xc2,0x3d,0x84,0xfe,0x32,0x49,0xb7,0x89,0x2c,0x1a,0x0a,0x12,0xff,0xe5,0xb4,0xd8,0x7d,0xf2,0x0c,0x8d,0xee,0x45,0x7d,0x68,0xf1,0x97,0x67,0x8f,0xd7,0xd3,0x01,0xf2,0x7b,0x0e,0xf7,0xa4,0x34,0x15,0xcc,0xe5,0x97,0x4d,0x20,0xc4,0x47,0x2c,0x12,0xc1,0xcd,0x37,0x8c,0xb8,0x6c,0xec,0xa1,0x85,0x17,0xfb,0x0f,0xf2,0x61,0xec,0x29,0x77,0xf8,0x0f,0x68,0x5a,0xcb,0x18,0xfc,0x9c,0x6c,0xa9,0x64,0x7d,0x73,0xd9,0xb6,0xf7,0x2e,0x5e,0x20,0xd7,0xa8,0x6f,0xe8,0x1a,0x22,0x90,0x19,0xf2,0x43,0xcc,0x64,0x3a,0x44,0xde,0xd2,0xa3,0xf4,0x50,0xd2,0xda,0x93,0xe7,0xc0,0xe2,0x45,0xb6,0x41,0xf4,0x45,0x01,0x55,0xc0,0x0c,0x00,0x30,0x00,0x01,0x00,0x00,0x0c,0x88,0x01,0x08,0x01,0x00,0x03,0x07,0x03,0x01,0x00,0x01,0x9e,0xbf,0x4f,0x35,0xad,0x4b,0x5b,0xc6,0x75,0xee,0x63,0x9a,0xf6,0xdc,0x1b,0x61,0x15,0xe3,0x52,0x3a,0xc5,0xca,0x98,0xcc,0xa7,0xc9,0xdb,0x4c,0x31,0xee,0x24,0x1a,0x0a,0xee,0x71,0x39,0xf4,0xdc,0x10,0xea,0x4e,0x57,0x06,0x16,0x79,0xeb,0xaf,0x60,0x8b,0x83,0xbe,0xc9,0x6a,0x1f,0xfc,0x0e,0xd5,0x03,0x0e,0xd4,0xb1,0x46,0xab,0xcc,0x98,0x20,0x52,0x4d,0x35,0xf2,0x89,0x8f,0xa9,0xaf,0x6d,0xa8,0x35,0x18,0xa6,0x05,0xd5,0x8c,0xe6,0xab,0xf2,0x05,0x6a,0x47,0x86,0xd9,0x52,0xcc,0xdb,0x54,0x68,0x37,0xcd,0x39,0x83,0xb8,0x49,0x30,0x23,0x96,0x45,0x84,0x18,0x14,0xb2,0x7d,0xf7,0x0b,0xda,0x7e,0x06,0xbf,0xa6,0x3f,0xe4,0x19,0x6c,0xf2,0xdd,0xd5,0xd3,0xe6,0x99,0x8b,0xd3,0x3c,0xde,0x86,0xc7,0x3b,0xc8,0xa1,0xf9,0xa9,0x61,0x11,0x39,0x52,0xdb,0x27,0x73,0x69,0xd8,0x6a,0xea,0xd4,0x6b,0x83,0x02,0x24,0x3c,0xfe,0x23,0x6d,0x23,0x93,0x91,0x65,0x1b,0x1b,0x96,0xae,0x36,0xc4,0xf9,0xa9,0x63,0x35,0xb5,0x77,0xcd,0x84,0x2f,0xdd,0x01,0x70,0xa8,0x97,0xf4,0x02,0x8a,0x25,0x92,0x77,0xf0,0x5c,0xc0,0xd0,0xea,0x60,0x37,0xb4,0xdd,0xa4,0x35,0xd2,0x2e,0xe8,0x84,0xe0,0xd9,0xca,0x62,0x8f,0xcf,0xaf,0x63,0xbd,0x5b,0x8f,0xb2,0x89,0x92,0x3f,0xa0,0x67,0x51,0xc7,0xb3,0x38,0x93,0x71,0x2c,0xcc,0x39,0xec,0xf0,0x7d,0xe2,0x8b,0x62,0x3c,0x1b,0x04,0xcc,0x46,0x4f,0x16,0x63,0x3a,0x5b,0x4f,0x63,0x64,0x9a,0x99,0x7e,0x8a,0x59,0x9e,0x33,0x8b,0xc0,0x0c,0x00,0x33,0x00,0x01,0x00,0x00,0x0c,0x88,0x00,0x09,0x01,0x00,0x00,0x0c,0x04,0xaa,0xbb,0xcc,0xdd,0xc0,0x0c,0x00,0x2e,0x00,0x01,0x00,0x00,0x0c,0x88,0x01,0x1c,0x00,0x02,0x07,0x02,0x00,0x00,0x54,0x60,0x56,0x3d,0x6a,0x14,0x56,0x34,0x21,0x84,0xd1,0x15,0x04,0x63,0x70,0x73,0x63,0x03,0x67,0x6f,0x76,0x00,0x41,0x1f,0x32,0x79,0x99,0xff,0x53,0xd1,0x40,0x4a,0x87,0x6f,0x34,0x1f,0xdd,0x88,0x03,0xd3,0x4a,0x55,0x13,0xc5,0xb6,0x34,0x88,0xa7,0x07,0x88,0x74,0xbb,0xab,0x9c,0xf0,0xc2,0x00,0x00,0x00,0x00,0x00,0x00};
    while(1){
        memset(&hints,0,sizeof(hints));
        hints.ai_family=AF_INET;
        hints.ai_socktype=SOCK_DGRAM;
        hints.ai_protocol=0;
        hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
        
        struct addrinfo* res=0;
        int err = getaddrinfo(hostname,portname,&hints,&res);
        if (err!=0) {
            printf("ERROR");
        }
        //Create socket
        int fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
        if (fd==-1) {
            printf("ERROR: socket");
        }
        //Bind socket
        if (bind(fd,res->ai_addr,res->ai_addrlen)==-1) {
            printf("ERROR: bind");
        }
        //Receive and handle datagrams
        char buffer[1549];
        struct sockaddr_in src_addr;
        socklen_t src_addr_len;
        ssize_t count;
        
        count = recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len);
        if (count==-1) {
            printf("ERROR: count=-1");
        }
        else if (count==sizeof(buffer)) {
            warn("datagram too large for buffer: truncated");
        }
        else {//Sending response
            if (handle_datagram(buffer,count)==1){
                sendto(fd,content,sizeof(content),0,(struct sockaddr*)&src_addr,src_addr_len);
            }
        }
        memset(&buffer[0],0,sizeof(buffer));
        close(fd);
    }
    return 0;
}

