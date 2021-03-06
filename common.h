#ifndef _COMMON_H
#define _COMMON_H

#include <openssl/rsa.h>
#include <stdint.h>
#include <sys/socket.h>
#include "audio.h"
#include "mdns.h"

// struct sockaddr_in6 is bigger than struct sockaddr. derp
#ifdef AF_INET6
    #define SOCKADDR struct sockaddr_storage
    #define SAFAMILY ss_family
#else
    #define SOCKADDR struct sockaddr
    #define SAFAMILY sa_family
#endif


typedef struct {
    char *password;
    char *apname;
    uint8_t hw_addr[6];
    int port;
    char *output_name;
    audio_output *output;
    char *mdns_name;
    mdns_backend *mdns;
    int buffer_start_fill;
    uint32_t latency;
    uint32_t userSuppliedLatency; // overrides all other latencies -- use with caution
    uint32_t iTunesLatency; // supplied with --iTunesLatency option
    uint32_t AirPlayLatency; //supplied with --AirPlayLatency option
    int daemonise;
    char *cmd_start, *cmd_stop;
    char *pidfile;
    char *logfile;
    char *errfile;
} shairport_cfg;

extern int debuglev;
void die(char *format, ...);
void warn(char *format, ...);
void debug(int level, char *format, ...);

uint8_t *base64_dec(char *input, int *outlen);
char *base64_enc(uint8_t *input, int length);

#define RSA_MODE_AUTH (0)
#define RSA_MODE_KEY  (1)
uint8_t *rsa_apply(uint8_t *input, int inlen, int *outlen, int mode);

// given a volume (0 to -30) and high and low attenuations in dB*100 (e.g. 0 to -6000 for 0 to -60 dB), return an attenuation depending on the transfer function
double vol2attn(double vol, long max_db, long min_db);

extern shairport_cfg config;

void shairport_shutdown();
// void shairport_startup_complete(void);

#endif // _COMMON_H
