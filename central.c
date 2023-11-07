//
//  central.c
//  temp
//
//  Created by Stephen Merritt  on 11/1/23.
//
// Main Control Program

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
} ext_message, central_message;

const int central_msg_queue_key = 1000;

int main(int argc, char *argv[]) {
    if (argc != 2) {
           printf("Expected 1 argument, but got %d.\n", argc - 1);
           return 0;
    } else {
           int central_msg_queue_id, external_msg_queue_ids[4], msg_status;
           central_message.temperature = atoi(argv[1]);
           central_message.msg_priority = 2;
           central_message.process_id = 0;
           central_message.is_stable = 0;

           central_msg_queue_id = msgget(central_msg_queue_key, 0600 | IPC_CREAT);

           for (int i = 0; i < 4; i++) {
               external_msg_queue_ids[i] = msgget((central_msg_queue_key + i + 1), 0600 | IPC_CREAT);
           }

           printf("Central Control Started with Initial Temperature: %d\n", central_message.temperature);

           int completion_count = 0;
          while (!central_message.is_stable) {
               int match_count = 0, total_temp = 0;

               for (int j = 0; j < 4; j++) {
                   msg_status = msgrcv(central_msg_queue_id, &ext_message, sizeof(ext_message) - sizeof(long), 2, 0);
                   total_temp += ext_message.temperature;
                   if (central_message.temperature == ext_message.temperature) {
                       match_count++;
                   }
               }

               if (match_count == 4) {
                   completion_count++;
               }

               if (completion_count == 2) {
                   central_message.is_stable = 1;
                   printf("System Stabilized.\n");
                   for (int l = 0; l < 4; l++) {
                       msg_status = msgsnd(external_msg_queue_ids[l], &central_message, sizeof(central_message) - sizeof(long), 0);
                   }
               } else {
                   central_message.temperature = (2 * central_message.temperature + total_temp) / 6;
                   for (int k = 0; k < 4; k++) {
                       msg_status = msgsnd(external_msg_queue_ids[k], &central_message, sizeof(central_message) - sizeof(long), 0);
                   }
               }
           }

           printf("Final Central Temperature: %d\n", central_message.temperature);
        msg_status = msgctl(central_msg_queue_id, IPC_RMID, 0);
           printf("Central Control Process Ending.\n");
    }
       return 0;
}
