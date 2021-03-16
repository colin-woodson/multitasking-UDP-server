#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_DEVICE_NUMBER 20480 //102400
#define NUMBER_OF_WORKERS 6

typedef struct udp_node{
	char udp_data[1024];
	//udp_node_t *next;
	struct udp_node *next;
} udp_node_t;

typedef struct device_info {
	uint16_t id;
	uint16_t fault_code;
	char name[64];
	//uint8_t online_flag;
	uint64_t latest_unix_second;
} device_info_t;

typedef struct address_info {
	//uint64_t address;
	device_info_t *address;
} address_info_t;

int get_unix_time();

#endif
