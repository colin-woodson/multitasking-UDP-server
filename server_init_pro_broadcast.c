#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "common.h"

udp_node_t *udp_list_head = NULL;
udp_node_t *udp_list_tail = NULL;
pthread_mutex_t mutex_lock;
pthread_cond_t cond;

device_info_t *device_info_header = NULL;
//read from DB.
uint16_t registed_device_number = 3;
int init()
{
	//read the exist devices' number from DB.
	if (registed_device_number == 0) {
		//do nothing.
	} else {
		//device_info_header = malloc(registed_device_number * sizeof(device_info_t));
		device_info_header = calloc(registed_device_number, sizeof(device_info_t));
		if (device_info_header == NULL) {
			perror("malloc()");
		}
	}
	//read the exist device' info from DB.
	uint16_t i = 0;
	for (i=0; i<registed_device_number; i++) {
		(device_info_header + i)->id = i;
		(device_info_header + i)->fault_code = 0;
		memcpy((device_info_header + i)->name, "1234567890", strlen("1234567890"));
		//memcpy(((device_info_t *)device_info_header)->name, "1234567890", strlen("1234567890"));
		//(device_info_header + i)->latest_unix_second = 9999999;
		(device_info_header + i)->latest_unix_second = get_unix_time();

	}
	for (i=0; i<registed_device_number; i++) {
		printf("id: %d\n", (device_info_header + i)->id);
		printf("fault_code: %d\n", (device_info_header + i)->fault_code);
		printf("name: %s\n", (device_info_header + i)->name);
		printf("latest_unix_second: %ld\n", (device_info_header + i)->latest_unix_second);
	}

	return 0;
}

int init_pro()
{
	//read the exist devices' number from DB.
	//device_info_header = malloc(registed_device_number * sizeof(device_info_t));
	device_info_header = calloc(MAX_DEVICE_NUMBER, sizeof(device_info_t));
	if (device_info_header == NULL) {
		perror("malloc()");
	}
	//read the exist device' info from DB.
//	uint16_t i = 0;
//	for (i=0; i<registed_device_number; i++) {
//		(device_info_header + i)->id = i;
//		(device_info_header + i)->fault_code = 0;
//		memcpy((device_info_header + i)->name, "1234567890", strlen("1234567890"));
//		//memcpy(((device_info_t *)device_info_header)->name, "1234567890", strlen("1234567890"));
//		(device_info_header + i)->latest_unix_second = 9999999;
//		//(device_info_header + i)->latest_unix_second = get_unix_time();
//
//		
//	}
//	for (i=0; i<registed_device_number; i++) {
//		printf("id: %d\n", (device_info_header + i)->id);
//		printf("fault_code: %d\n", (device_info_header + i)->fault_code);
//		printf("name: %s\n", (device_info_header + i)->name);
//		printf("latest_unix_second: %ld\n", (device_info_header + i)->latest_unix_second);
//	}


	return 0;
}



int destroy()
{
	return 0;
}

int create_server_sock(int ip, int port)//创建server端socket
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in server;//创建server端网络地址信息
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = ip;

    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)//绑定
    {
        perror("bind");
        exit(2);
    }

    return sock;
}

int decrypte_udp_data(char *data) 
{

	return 0;
}

int check_udp_data(char *data){
	//culture the data 

	return 0;
}


void *work_thread_function(void *arg)
{
	while (1) {
		char data[1024];

		pthread_mutex_lock(&mutex_lock);
		pthread_cond_wait(&cond, &mutex_lock);
//		printf("|--------------------------------------\n");
//		printf("In process: %d, tid: %lu\n", getpid(), pthread_self());
	
		if (udp_list_head == NULL && udp_list_tail == NULL) {
			//do nothing.
			//printf("This a big issue, udp_list_head is NULL.\n");
			//exit(1);	

		//	pthread_mutex_unlock(&mutex_lock);
		//	continue;

		} else {
			udp_node_t *toBeFreed = udp_list_head;
			memcpy(data, toBeFreed->udp_data, 1024);
			if ( udp_list_head == udp_list_tail) {
				//printf("1\n");
//				printf("udp_data: %s\n", data);
				udp_list_head = udp_list_tail = NULL;
			} else { // udp_list_head != udp_list_tail
				//printf("2\n");
//				printf("udp_data: %s\n", data);
				udp_list_head = udp_list_head->next;
			}
			free(toBeFreed);
	
	
		}

//		printf("--------------------------------------|\n");
		pthread_mutex_unlock(&mutex_lock);


		/*decript data*/
		if (decrypte_udp_data(data) == 0) {


		} else {


		}

		/*Judge the data real or virual */
		if (check_udp_data(data) == 0) {


		} else {


		}

		/*Save the real data to device_info array */
#if 0
		device_info_t a_device_info;
		memset(&a_device_info, '\0', sizeof(device_info_t));
		memcpy(&a_device_info, (device_info_t *)data, sizeof(device_info_t));


		printf("----Size of device_info_t: %d----\n", sizeof(device_info_t));
		printf("----Size of int: %d----\n", sizeof(int));
		printf("data's address = 0x%lx\n", data);
		printf("a_device_info's address = 0x%lx\n", &a_device_info);

		printf("a_device_info.id = %u\n", a_device_info.id);
		printf("a_device_info.id's address = 0x%lx\n", &(a_device_info.id));

		printf("a_device_info.fault_code = %u\n", a_device_info.fault_code);
		printf("a_device_info.fault_code's address = 0x%lx\n", &(a_device_info.fault_code));

		printf("a_device_info.name = %s\n", a_device_info.name);
		printf("data->name = %s\n", data+4);
		printf("    a_device_info.name's address = 0x%lx\n", a_device_info.name);


		printf("a_device_info.latest_unix_second = %lu\n", (unsigned long int)a_device_info.latest_unix_second);
		printf("a_device_info.latest_unix_second = 0x%lx\n", &(a_device_info.latest_unix_second));

		printf("        data->latest_unix_second = %lu\n", *(unsigned long int *)(data+68));
		printf("        data->latest_unix_second = 0x%lx\n", (unsigned long int *)(data+68));

#else
		uint16_t device_id;
		uint16_t fault_code;
		char name[64] = {'\0'};
		uint64_t latest_unix_second;

		memcpy(&device_id, data, 2);
		memcpy(&fault_code, data+2, 2);
		memcpy(name, data+4, 64);
		memcpy(&latest_unix_second, data+68, 8);

	//	printf("  device_id = %u\n", device_id);
	//	printf("  fault_code = %u\n", fault_code);
	//	printf("  name = %s\n", name);
	//	printf("  latest_unix_second = %ld\n", latest_unix_second);

		(device_info_header + device_id)->id = device_id;
		(device_info_header + device_id)->fault_code = fault_code;
		memcpy((device_info_header + device_id)->name, name, 64);
		//(device_info_header + device_id)->latest_unix_second = current_unix_second;
		(device_info_header + device_id)->latest_unix_second = latest_unix_second;

	//	printf("# device_id : %d\n", (device_info_header + device_id)->id);
	//	printf("# fault_code : %d\n", (device_info_header + device_id)->fault_code);
	//	printf("# name : %s\n", (device_info_header + device_id)->name);
	//	printf("# latest_unix_second : %ld\n", (device_info_header + device_id)->latest_unix_second);
#endif
	
	}

	return NULL;
}

int main(void)
{
	//init();
	init_pro();

	//int threads.

#if 0
	pthread_t tid;
	if (pthread_create(&tid, NULL, work_thread_function, NULL)) {
		perror("pthread_create()");
		exit(1);
	}
	pthread_t tid2;
	if (pthread_create(&tid2, NULL, work_thread_function, NULL)) {
		perror("pthread_create()");
		exit(1);
	}
#else
	pthread_t tid_array[NUMBER_OF_WORKERS];
	int new_a_thread = 0;
	while (new_a_thread < NUMBER_OF_WORKERS) {
		if (pthread_create(&tid_array[new_a_thread], NULL, work_thread_function, NULL)) {
			perror("pthread_create()");
			exit(1);
		}
		new_a_thread++;
	}
	printf("new_a_thread: %d\n", new_a_thread);
#endif



	int port = atoi("6666");
	int ip = inet_addr("192.168.1.77");

	int server_sock = create_server_sock(ip, port);

	char buf[1024];
	struct sockaddr_in client;
	socklen_t len = sizeof(client);


	//#Debug
//	int i = 0;
//	uint64_t start_unix_second = get_unix_time();
	//#Debug

	//loop();
	//int j = 0;
	while (1) {

		memset(buf, '\0', sizeof(buf));
		uint64_t size = recvfrom(server_sock, buf, sizeof(buf)-1, 0, (struct sockaddr *)&client, &len);
		if (size < 0) {
			perror("recvfrom()");
		}
		//printf("j = %d\n", j++);
//	}
///*
		//////////////////////////////////////////////////////////////////
		pthread_mutex_lock(&mutex_lock);
		udp_node_t *a_udp_node = (udp_node_t *)malloc(sizeof(udp_node_t));

		memcpy(a_udp_node->udp_data, buf, sizeof(buf));
		a_udp_node->next = NULL;

		if (udp_list_tail == NULL) {
			udp_list_head = udp_list_tail = a_udp_node;
		} else {
			udp_list_tail->next = a_udp_node;
			udp_list_tail = a_udp_node;
		}


		//pthread_cond_signal(&cond);
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex_lock);
		//////////////////////////////////////////////////////////////////

//		int x=0;
//		pthread_mutex_lock(&mutex_lock);
//		udp_node_t *tmp = udp_list_head;
//		while(tmp != NULL){
//			tmp = tmp->next;
//			x++;
//		}
//		pthread_mutex_unlock(&mutex_lock);



	//	uint16_t device_id = recvfrom();
		uint16_t device_id = 0;
		memcpy(&device_id, buf, 2);
		uint16_t fault_code = 0;
		memcpy(&fault_code, buf+2, 2);
		uint64_t current_unix_second = get_unix_time();


		//#Debug
//		if (current_unix_second == start_unix_second) {
//			i++;
//		} else {
//			//printf("Unix time:%ld, count: %d\n", start_unix_second, i);
//			printf("i = %d\n", i);
//			start_unix_second = current_unix_second;
//			i = 0;
//printf("x=%d\n", x);
//		}
		//#Debug
	
	//	lock(device_info_array[device_id]);

		//####
		//lock(device_info_header);
		(device_info_header + device_id)->id = device_id;
		(device_info_header + device_id)->fault_code = fault_code;
		(device_info_header + device_id)->latest_unix_second = current_unix_second;
		//unlock(device_info_header);
		//####

	//	unlock(device_info_array[device_id]);
	//
	//	sendto("CMD"); //Such as, reboot device and so on.


	//	printf("id: %d\n", (device_info_header + device_id)->id);
	//	printf("fault_code: %d\n", (device_info_header + device_id)->fault_code);
	//	printf("name: %s\n", (device_info_header + device_id)->name);
	//	printf("latest_unix_second: %ld\n", (device_info_header + device_id)->latest_unix_second);


	}

//*/

	destroy();
}

