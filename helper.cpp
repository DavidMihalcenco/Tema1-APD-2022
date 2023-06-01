#include "helper.hpp"

double getNPower(int power, int number) {
    double low = 1;
    double high = number;
    double eps = 1e-7; 
    
    while((high - low) > eps) {
        double mid = (low + high) / 2.0; 
        if(pow(mid, power) < number) {
            low = mid; 
        }
        else {
            high = mid; 
        }
    }
  return low; 
}