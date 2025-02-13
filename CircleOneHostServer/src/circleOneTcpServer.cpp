#include <iostream>
#include <string>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include "circleOneTcpServer.h"
#include "circleOneConnectionInfoList.h"
#include "circleOneMessage.h"
#include "circleOneMessageQueues.h"

using namespace std;
using namespace CircleOne;

#define PORT      11223
#define LISTENQ   1024
#define MAX_PACKET_SIZE 1024

TcpServer* TcpServer::mp_PtrInstance = NULL;

// Constructor
TcpServer::TcpServer()
{
   m_ServerSocket          = -1;
   m_ClientSocket          = -1;
   m_SocketReUse           = 1;
   m_LengthOfReceivedMsg   = 0;
   m_ServerAddrLen         = sizeof(m_ServerAddrLen);
   m_ClientAddrLen         = sizeof(m_ClientAddrLen);
   
   memset((char *) &m_ServerAddr, 0, sizeof(m_ServerAddr));
   memset((char *) &m_RecvBuf, 0, sizeof(m_RecvBuf));

   m_ServerAddr.sin_family = AF_INET;
   m_ServerAddr.sin_port = htons(PORT);
   m_ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

// getInstance function
TcpServer* TcpServer::getInstance()
{
   if(NULL == mp_PtrInstance)
   {
      mp_PtrInstance = new TcpServer;
   }
   return mp_PtrInstance;
}

// Initialize TCP Server
bool TcpServer::openTcpServer()
{
   // Open Socket
   if((m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
   {
      return false;
   }

   // Set the socket option to reuse it immediately
   if ((setsockopt(m_ServerSocket, SOL_SOCKET, SO_REUSEADDR, &m_SocketReUse, sizeof(m_SocketReUse))) != 0)
   {
      return false;
   }

   // Bind the server
   if(bind(m_ServerSocket, (struct sockaddr*)&m_ServerAddr, sizeof(m_ServerAddr)) != 0)
   {
      return false;
   }

   // Start server in listen mode
   listen(m_ServerSocket, LISTENQ);

   return true;
}

void* runWokerThread(void* pArg)
{
   cout << "Worker thread created !!" << endl;
   fd_set readFd;
   int fd;
   int selectResult = -1;
   
   while(1)
   {
      FD_ZERO(&readFd);
      fd = ConnInfoList::getInstance()->getFdFromTheList();
      FD_SET(fd, &readFd);
      
      struct timeval tv;              //Time value struct declaration
      tv.tv_sec = 10;                 //The second portion of the struct
      tv.tv_usec = 500000;            //The microsecond portion of the struct

      selectResult = select(fd + 1, &readFd, NULL, NULL, &tv);

      cout << "Value of select: " << selectResult << endl;

      if(selectResult <= -1)
      {
         cout << "Select returns -1" << endl;
         continue;
      }
      else if(selectResult == 0)
      {
         cout << "Select returns 0 i.e Timeout case" << endl;
         continue;
      }
      else
      {
         // some socket event was triggered, check which one
         if (FD_ISSET(fd, &readFd))
         {
            //if(readFd)
            //{
              // FD_CLR(fd, &readFd);
               // it was a read event on our socket, so call recv
               char buffer[MAX_PACKET_SIZE];
               memset(buffer, 0, MAX_PACKET_SIZE);
               int totalBytesReceived = read(fd, &buffer, MAX_PACKET_SIZE);
               //recv(fd, buffer, MAX_PACKET_SIZE, 0);
               cout << "Total Bytes Received" << totalBytesReceived << endl;
               // Parse the message
               
               char msgType = buffer[0];
               char frameTerminatingPattern[3] = "\n\r";
               char *token;
               token = strtok(&buffer[1], frameTerminatingPattern);
               string messageString;
               messageString.assign(token, strlen(token));
               
               cout << "Complete Message received: " << messageString << endl;
               
               switch(msgType)
               {
                  case 'R':
                  case 'r':
                     {
                        cout << "Registration Message Received !!" << endl;
                        // push registration message into the queue
                        Message* ptrMsg = new RegistrationMessage(fd, messageString);
                        RegistrationQueue::getInstance()->pushMessageIntoQueue(ptrMsg);
                     }
                     break;
                     
                  case 'L':
                  case 'l':
                     {
                        cout << "Location Message Received !!" << endl;
                        // push location message into the queue
                        Message* ptrMsg = new LocationMessage(messageString);
                        LocationQueue::getInstance()->pushMessageIntoQueue(ptrMsg);
                     }
                     break;
                     
                  case 'C':
                  case 'c':
                     {
                        cout << "Chat Message Received !!" << endl;
                        // push location message into the queue
                        Message* ptrMsg = new ChatMessage(messageString);
                        ChatQueue::getInstance()->pushMessageIntoQueue(ptrMsg);
                     }
                     break;
                     
                  default:
                     {
                        char notValidMsg[] = "Message is not valid";
                        int bytesSent = write(fd , notValidMsg , strlen(notValidMsg));
                        if(bytesSent > 0)
                        {
                           cout << "Error Message Successfully sent. Bytes Sent: " << bytesSent << endl;
                        }
                        else
                        {
                           cout << "Error Message does not sent" << endl;
                        }
                        break;
                     } 
                  }    
              // }
         }
      }
   }
}

void TcpServer::createWorkerThread()
{
   int ret = -1;
   pthread_t workerThreadId = 0;
   ret = pthread_create(&workerThreadId, 0, runWokerThread, (void*)this);
   if(ret != 0)
   {
      cout << "Unable to create worker thread !!";
   }
}

void* runRegistrationThread(void* pArg)
{
   cout << "Registration thread created !!" << endl;
   RegistrationQueue* msg = NULL;
   while(1)
   {
      msg = NULL;
      if(RegistrationQueue::getInstance()->sizeOfTheTheQueue() > 0)
      {
         //msg = (RegistrationMessage*)((RegistrationQueue::getInstance())->getFirstMessageFromTheQueue()); 
         //msg->updateMapOfEmpIdAndFd();
         //msg->generateAndUpdateEmailCode();
         //if()
      }
   }
}

void TcpServer::createRegistrationThread()
{
   int ret = -1;
   pthread_t workerThreadId = 0;
   ret = pthread_create(&workerThreadId, 0, runRegistrationThread, (void*)this);
   if(ret != 0)
   {
      cout << "Unable to create registration thread !!";
   }
}

void* runLocationThread(void* pArg)
{
   cout << "Location thread created !!" << endl;
}

void TcpServer::createLocationThread()
{
   int ret = -1;
   pthread_t workerThreadId = 0;
   ret = pthread_create(&workerThreadId, 0, runLocationThread, (void*)this);
   if(ret != 0)
   {
      cout << "Unable to create location thread !!";
   }
}

void* runChatThread(void* pArg)
{
   cout << "Chat thread created !!" << endl;
}

void TcpServer::createChatThread()
{
   int ret = -1;
   pthread_t workerThreadId = 0;
   ret = pthread_create(&workerThreadId, 0, runChatThread, (void*)this);
   if(ret != 0)
   {
      cout << "Unable to create chat thread !!";
   }
}

void TcpServer::runTcpServer()
{
   createWorkerThread();
   while(1)
   {
      m_ClientSocket = accept(m_ServerSocket, (sockaddr*)&m_ClientAddr, &m_ClientAddrLen);
      
      if(m_ClientSocket < 0)
      {
         cout << "Client Socket is zero !!" << endl;
      }
      else
      {
         cout << "Connection accepted !!" << endl;
         // make connection in nonblocking mode
         fcntl(m_ClientSocket, F_SETFL, O_NONBLOCK);
         // Push client fd into the fd list
         ConnInfoList::getInstance()->pushIntoInfoList(m_ClientSocket);
      }
      
   }
}

