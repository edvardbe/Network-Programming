#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>

using namespace std;
using namespace chrono;

mutex primes_mutex;

static bool is_prime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

static int find_prime(int start, int end, vector<vector<int>>& primes, int id){
    if (start < 0) throw invalid_argument("Start-value needs to be larger than or equal to 0");
    
    vector<int> local_primes;

    // Ensure start is odd (since all even numbers are not prime)
    if (!(start & 1)) start++;

    for (int i = start; i <= end; i += (i < 3) ? 1 : 2) { // If i is less than 3 increment by 1, else increment by 2
        if (is_prime(i)) {
            local_primes.push_back(i);
        }
    }
    lock_guard<mutex> lock(primes_mutex);
    primes[id] = local_primes;
    
    return 0;
}

void print_concur_primes(vector<vector<int>>& primes, int num_threads, int start_range, int end_range){

    int total_range = end_range - start_range;
    int range_per_thread = total_range / num_threads;
    int remainder =  total_range % num_threads;
    
    for (int i = 0; i < num_threads; i++){
        int start = start_range + i * range_per_thread;
        int end = (i == num_threads - 1) ? start + range_per_thread + remainder : start + range_per_thread - 1;

        vector<int> local_primes = primes[i];
        cout << "Primes: [";
        for (int j = 0; j < local_primes.size(); j++){
            int prime = local_primes[j];
            cout << prime;
            if(j < local_primes.size() - 1){
                cout << ", ";
            }
        }
        cout << "], in range: (" << start << " - " << end << ")" << endl;
    }
    

}

void print_seq_primes(vector<int>& primes_seq){
    cout << "[";
    for(int i = 0; i < primes_seq.size(); i++){
        cout << primes_seq[i];
        if(i < primes_seq.size() - 1){
            cout << ", ";
        } 
    }
    cout << "]\n" << endl;
}

int run_concurrent(int num_threads, int start_range, int end_range, vector<vector<int>>& primes){
    vector<thread> threads;

    int total_range = end_range - start_range;
    int range_per_thread = total_range / num_threads;
    int remainder =  total_range % num_threads;
    for (int i = 0; i < num_threads; i++){
        int start = start_range + i * range_per_thread;
        int end = (i == num_threads - 1) ? start + range_per_thread + remainder : start + range_per_thread - 1;
        try{
            threads.emplace_back(find_prime, start, end, ref(primes), i);
        } catch(invalid_argument& e){
            cerr << e.what() << endl;
            return 1;
        }
    }

    for (auto& thread : threads){
        thread.join();
    }
    return 0;
}

int run_sequential(int start_range, int end_range, vector<int>& primes_seq){
    if (!(start_range & 1)) start_range++;
    for (int i = start_range; i <= end_range; i += (i < 3) ? 1 : 2){
        if(is_prime(i)) {
            primes_seq.push_back(i);
        }
    }
    return 0;
}

int main(){
    
    const int start_range = 0;
    const int end_range = 1e2;
    const int total_range = end_range - start_range;
    const int num_threads = 13;//(total_range > 1000) ? 40 : (end_range / 10) + 1;

    vector<vector<int>> primes(num_threads);

    vector<int> primes_seq;

    auto beg = chrono::high_resolution_clock::now();    
    
    run_concurrent(num_threads, start_range, end_range, ref(primes));

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - beg);

    cout << "Time taken to find primes in range, [" << start_range << ", " << end_range << "], concurrently: \n" << duration.count() << " microseconds\n" << endl;

    print_concur_primes(primes, num_threads, start_range, end_range);

    int num_primes = 0;
    for (auto vec : primes){
        num_primes += vec.size();
    }
    cout << "Number of primes (concurrent): " << num_primes << endl << endl;
    
    beg = high_resolution_clock::now();
    
    run_sequential(start_range, end_range, ref(primes_seq));
    
    end = high_resolution_clock::now();


    duration = duration_cast<microseconds>(end - beg);
    cout << "Time taken to find primes in range, [" << start_range << ", " << end_range << "], sequentially: \n" << duration.count() << " microseconds\n" << endl; 

    print_seq_primes(primes_seq);

    num_primes = primes_seq.size();
    cout << "Number of primes (sequential): " << num_primes << endl << endl;
}