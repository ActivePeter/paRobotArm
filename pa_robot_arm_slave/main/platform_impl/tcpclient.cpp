#include "tcpclient.h"
#include "paLibSubs/paCoreInc/all"
#include "communication.h"
#include "lwip/sockets.h"

#define TcpLib_Arduino
// #define TcpLib_Idf
namespace tcpclient
{
    void recv_loop(void *_client)
    {

        // TcpClient&client=*((TcpClient*)_client);
        // while(client.client.connected()){
        //     if(client.client.available())
        //     {
        //         static char buf[1000];
        //         auto len=client.client.readBytes(buf,1000);
        //         communication::handle_data(buf,len);
        //     }
        //     _G_paBase.delayMs(10);
        // }
        // client.client.stop();
    }

    bool connect(TcpClient &client)
    {
        char host_ip[] =
                // "192.168.43.8"
                "192.168.31.249";
        uint16_t port = 12398;

        #ifdef TcpLib_Arduino
        {
            if(client.client.connect(host_ip,port)){
                client.connected=true;
            } 
            return client.connected;
        }
        #endif
        #ifdef TcpLib_Idf
        { // char rx_buffer[128];
            

            int addr_family = 0;
            int ip_protocol = 0;

            // while (1)
            {
                // #if defined(CONFIG_EXAMPLE_IPV4)

                //  ipv4
                struct sockaddr_in dest_addr;
                dest_addr.sin_addr.s_addr = inet_addr(host_ip);
                dest_addr.sin_family = AF_INET;
                dest_addr.sin_port = htons(port);
                addr_family = AF_INET;
                ip_protocol = IPPROTO_IP;
                // #elif defined(CONFIG_EXAMPLE_IPV6)
                //             struct sockaddr_in6 dest_addr = {0};
                //             inet6_aton(host_ip, &dest_addr.sin6_addr);
                //             dest_addr.sin6_family = AF_INET6;
                //             dest_addr.sin6_port = htons(PORT);
                //             dest_addr.sin6_scope_id = esp_netif_get_netif_impl_index(EXAMPLE_INTERFACE);
                //             addr_family = AF_INET6;
                //             ip_protocol = IPPROTO_IPV6;
                // #elif defined(CONFIG_EXAMPLE_SOCKET_IP_INPUT_STDIN)
                //             struct sockaddr_storage dest_addr = {0};
                //             ESP_ERROR_CHECK(get_addr_from_stdin(PORT, SOCK_STREAM, &ip_protocol, &addr_family, &dest_addr));
                // #endif
                client.sock = socket(addr_family, SOCK_STREAM, ip_protocol);
                if (client.sock < 0)
                {
                    // ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
                    // break;
                    return false;
                }
                // ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

                int err = connect(client.sock, (struct sockaddr *)&dest_addr, sizeof(sockaddr_in6));
                if (err != 0)
                {
                    // ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
                    // break;
                    return false;
                }

                client.connected = true;
                // ESP_LOGI(TAG, "Successfully connected");

                // while (1)
                // {

                //     int len =
                //     // Error occurred during receiving
                //     if (len < 0)
                //     {
                //         ESP_LOGE(TAG, "recv failed: errno %d", errno);
                //         break;
                //     }
                //     // Data received
                //     else
                //     {
                //         rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                //         ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
                //         ESP_LOGI(TAG, "%s", rx_buffer);
                //     }

                //     vTaskDelay(2000 / portTICK_PERIOD_MS);
                // }
            }
            // // auto ok=client.client.connect("192.168.31.249", 12398);
            // if (ok)
            // {
            //     client.connected = true;
            //     // xTaskCreate(
            //     // recv_loop,   /* Task function. */
            //     // "recv_loop", /* String with name of task. */
            //     // 10000,     /* Stack size in bytes. */
            //     // (void*)&client,      /* Parameter passed as input of the task */
            //     // 1,         /* Priority of the task. */
            //     // NULL);     /* Task handle. */
            // }
            // else
            // {
            //     client.connected = false;
            // }

            return true;
        }
        #endif
    }
}
int TcpClient::send_(char *data, int len)
{
    #ifdef TcpLib_Arduino
    {
        return client.write(data,len);//client.read(data,len);
    }
    #endif
    #ifdef TcpLib_Idf
        return send(sock, data, len, 0);
    #endif
}

void TcpClient::close_()
{
    if (sock != -1)
    {
        // ESP_LOGE(TAG, "Shutting down socket and restarting...");
        shutdown(sock, 0);
        close(sock);
    }
    connected = false;
}

int TcpClient::recv_(char *data, int len)
{
    #ifdef TcpLib_Arduino
    {
        return client.read((uint8_t*)data,len);//client.read(data,len);
    }
    #endif
    #ifdef TcpLib_Idf
        return recv(sock, data, len, 0);
    #endif
}
