#include <stdio.h>

#define BUCKET_SIZE 10 // in bytes
#define OUTGOING_RATE 1 // in bytes per second
#define PACKET_SIZE 4 // in bytes

int main() {
    int bucket_level = 0; // current level of the bucket
    int time = 1; // current time
    int packets[] = {1, 2, 3, 5, 6, 8, 11, 12, 15, 16, 19}; // arrival times of packets
    int num_packets = sizeof(packets) / sizeof(int); // number of packets
    int i;

    for (i = 0; i < num_packets; i++) {
        // wait until the next packet arrives
        while (time < packets[i]) {
            // check if there is any data in the bucket
            if (bucket_level > 0) {
                printf("No packets at time. Bucket level is %d bytes.\n",bucket_level);
                // send one byte out of the bucket
                bucket_level--;
            }
            time++;
        }

        // check if the packet can be accommodated in the bucket
        if (bucket_level + PACKET_SIZE <= BUCKET_SIZE) {
            // add the packet to the bucket
            bucket_level += PACKET_SIZE;
            printf("Packet %d conforms at time %d. Bucket level is now %d bytes.\n", i+1, time, bucket_level);
        } else {
            printf("Packet %d does not conform at time %d. Bucket level is %d bytes.\n", i+1, time, bucket_level);
        }

        // send one byte out of the bucket
        if (bucket_level > 0) {
            bucket_level--;
        }
        time++;
    }

    // empty the bucket
    while (bucket_level > 0) {
        printf("No packets at time. Bucket level is %d bytes.\n",bucket_level);
        bucket_level--;
        time++;
    }

    printf("All packets have been processed. Bucket level is now %d bytes.\n", bucket_level);

    return 0;
}
