#include <stdio.h> // pre-processor directives
#include <string>      // insert the header files
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct EnjoySport {
	string sky, air_temp, humidity, wind, water, forecast;
	int enjoy;

	EnjoySport() : sky ("0"), air_temp ("0"), humidity ("0"), wind ("0"), water ("0"), forecast ("0") {
		
	}

	EnjoySport(string sky, string air_temp, string humidity, string wind, string water, string forecast, int enjoy) {
		this->sky = sky;
		this->air_temp = air_temp;
		this->humidity = humidity;
		this->wind = wind;
		this->water = water;
		this->forecast = forecast;
		this->enjoy = enjoy;
	}
	
};

int main(int argc, char* argv[]) {

	vector<EnjoySport> training_examples;
	training_examples.push_back(EnjoySport("Sunny", "Warm", "Normal", "Strong", "Warm", "Same", 1));
	training_examples.push_back(EnjoySport("Sunny", "Warm", "High", "Strong", "Warm", "Same", 1));
	training_examples.push_back(EnjoySport("Rainy", "Cold", "High", "Strong", "Warm", "Change", 0));
	training_examples.push_back(EnjoySport("Sunny", "Warm", "High", "Strong", "Cool", "Change", 1));

	EnjoySport hypothesis;

	cout << hypothesis.sky << " " << hypothesis.air_temp << endl;

	cout << training_examples.at(0).sky << " " << training_examples.at(0).air_temp << endl;

	return 0;
}
