//
//  external.c
//  temp
//
//  Created by Stephen Merritt  on 11/1/23.
//
// External Sensor Process

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>

struct message_format {
       long msg_priority;
       int temperature;
       int process_id;
       int is_stable;
} external_msg, central_msg;

const int central_msg_queue_key = 1000;
   
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Expected 2 arguments, but got %d.\n", argc - 1);
        return 0;
    } else {
        int central_msg_queue_id, external_msg_queue_id, msg_status;
        int sensor_temp = atoi(argv[1]);
        int sensor_id = atoi(argv[2]);
        
        external_msg.msg_priority = 2;
        external_msg.temperature = sensor_temp;
        external_msg.process_id = sensor_id;
        external_msg.is_stable = 0;
        
        int message_queue_number = central_msg_queue_key + sensor_id;
        
        central_msg_queue_id = msgget(central_msg_queue_key, 0600 | IPC_CREAT);
        external_msg_queue_id = msgget(message_queue_number, 0600 | IPC_CREAT);
        printf("Sensor %d Starting with Initial Temperature: %d\n", sensor_id, sensor_temp);
        
        while (!central_msg.is_stable) {
            msg_status = msgsnd(central_msg_queue_id, &external_msg, sizeof(external_msg) - sizeof(long), 0);}}}
