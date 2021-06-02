#include <stdio.h>
#include <math.h>

int main() {
    double n = 5; 

    int dns_one_rtt = 3; 
    int dns_two_rtt = 20; 
    int dns_three_rtt = 26; 

    int sumBaseRTT = dns_one_rtt + dns_two_rtt + dns_three_rtt; 
    
    int rtt_http = 47; 
    
    int client_click_to_receipt = sumBaseRTT + 2 * rtt_http; 
    int client_receive_six_objects = client_click_to_receipt + 6 * 2 * rtt_http; 
    int n_parallel_persistent = client_click_to_receipt + ceil(6 / n) * rtt_http; 
    int n_parallel_nonpersistent = client_click_to_receipt + ceil(6 / n) * 2 * rtt_http;

    printf("Client click to receipt of one object: %d ms, Six objects: %d ms, N parallel connections, persistent: %d ms, Non-Persistent: %d ms\n", client_click_to_receipt, client_receive_six_objects, n_parallel_persistent, n_parallel_nonpersistent);
}