/*
 * Server program settings
 * You need to specify the port 
 * on which the server will run
 */


#ifndef CONFIG_H
#define CONFIG_H

#pragma optimize("gsy", on)
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

static const char* IP = "127.0.0.1";
static const int   PORT = 3389;

#endif
