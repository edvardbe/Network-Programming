#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;

class Prime{
public:

    static bool is_prime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
    }

    static int find_prime(int start, int end, vector<int>& primes){
        if (start < 0) throw invalid_argument("Start-value needs to be larger than or equal to 0");
        cout << "start: " << start << endl;
        cout << "end: " << end << endl;
        while (start < 3){
            bool prime = is_prime(start);
            if(prime) primes.push_back(start);
            start++;
        }
        for(int i = start; i < end; i = i + 2){
            bool prime = is_prime(i);
            if(prime) primes.push_back(i);
        }
        return 0;
    }
};

int main(){
    vector<thread> threads;
    const int num_threads = 4;
    const int start_range = 0;
    const int end_range = 100;
    vector<int> primes;
    
    int range_per_thread = (end_range - start_range) / num_threads;

    cout << "Range per thread: " << range_per_thread << endl;

    for (int i = 0; i < num_threads; i++){
        int start = i * range_per_thread;
        int end = range_per_thread * (i + 1);
        try{
            Prime::find_prime(start, end, primes);
        } catch(invalid_argument& e){
            cerr << e.what() << endl;
            return 1;
        }
    } 

    for(int i : primes){
        cout << "prime: " << i << endl;
    }

}