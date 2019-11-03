#include <iostream>
#include "random.h"
#include <algorithm>

RandomNumbers::RandomNumbers(unsigned long int seed) : mean(0), sd(1), nsample(1), isnormal(true) {
    if (seed == 0) {
        std::random_device rd;
        seed = rd();
    }
    rng = std::mt19937(seed);
}

void RandomNumbers::initialize(double m, double s, int ns, bool norm) {
    mean = m;
    sd = s;
    nsample = ns;
    isnormal = norm;
    if (sd <= 0) throw(std::runtime_error("SDEV"));
    if (nsample <= 0) throw(std::runtime_error("NSMP"));
}

std::vector<double> RandomNumbers::generate_numbers()  {
    std::vector<double> result(nsample);
    if (isnormal) normal(result) ;
    else uniform_double(result);
    return result;
}

double RandomNumbers::uniform_double(double lower, double upper) {
	std::uniform_real_distribution<> unif(lower, upper);
	return unif(rng); 
}

void RandomNumbers::uniform_double(std::vector<double>& res, double lower, double upper) {
	
	std::uniform_real_distribution<> unif(lower, upper);  
    for (size_t i(0); i < res.size(); ++i)  
		{  
			res[i] = uniform_double(lower, upper); 
		}  
} 

void RandomNumbers::normal(std::vector<double> &res, double mean, double sd) {
    std::normal_distribution<> norm(mean, sd);
    for (size_t i(0); i < res.size(); ++i) 
		{ 
			res[i] = normal(mean,sd);
		}
}

double RandomNumbers::normal(double mean, double sd) {
	std::normal_distribution<> norm(mean, sd);
	return norm(rng);
}

void RandomNumbers::poisson(std::vector<int>&pois, double mean) {
  std::poisson_distribution<> d(mean); 
  for (size_t i(0); i < pois.size(); ++i) 
		{ 
			pois[i] = poisson(mean);
		}
}

int RandomNumbers::poisson(double mean) {

	 std::poisson_distribution<> d(mean);
	 return d(rng); 
} 

