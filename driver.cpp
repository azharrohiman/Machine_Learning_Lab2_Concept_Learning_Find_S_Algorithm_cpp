#include <stdio.h> // pre-processor directives
#include <string>      // insert the header files
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <array>

using namespace std;

struct EnjoySport {
	vector<string> dataset;

	EnjoySport(string sky, string air_temp, string humidity, string wind, string water, string forecast, string enjoy) {
		this->dataset.push_back(sky);
		this->dataset.push_back(air_temp);
		this->dataset.push_back(humidity);
		this->dataset.push_back(wind);
		this->dataset.push_back(water);
		this->dataset.push_back(forecast);
		this->dataset.push_back(enjoy);
	}
	
};

void findS(vector<EnjoySport> training_examples) {
	string hypothesis[] = {"0", "0", "0", "0", "0", "0", "0"};
	int trace_count = 0;

	ofstream output_file;
	output_file.open("output.txt");

	for (int i = 0; i < training_examples.size(); i++) {
		vector<string> example = training_examples.at(i).dataset;

		output_file << "Trace: " << ++trace_count << endl;

		if (example.at(example.size() - 1) == "1") {

			for (int j = 0; j < (sizeof(hypothesis)/sizeof(hypothesis[0])) - 1; j++) {
				if (hypothesis[j] == "0") {
					if (i == 0) {
						hypothesis[j] = example.at(j);
					}
				}

				else {
					if (hypothesis[j] != example.at(j)) {
						hypothesis[j] = "?";
					}
				}
			}
		}

		output_file << "<";

		for (int k = 0; k < (sizeof(hypothesis)/sizeof(hypothesis[0])) - 1; k++) {
			if (k != (sizeof(hypothesis)/sizeof(hypothesis[0])) - 2) {
				output_file << hypothesis[k] << ", ";
			}

			else {
				output_file << hypothesis[k] << ">" << endl;
			}
		}

		if (i != training_examples.size() - 1) {
			output_file << endl;
		}
	}
}

int main(int argc, char* argv[]) {

	
	vector<EnjoySport> training_examples;
	training_examples.push_back(EnjoySport("Sunny", "Warm", "Normal", "Strong", "Warm", "Same", "1"));
	training_examples.push_back(EnjoySport("Sunny", "Warm", "High", "Strong", "Warm", "Same", "1"));
	training_examples.push_back(EnjoySport("Rainy", "Cold", "High", "Strong", "Warm", "Change", "0"));
	training_examples.push_back(EnjoySport("Sunny", "Warm", "High", "Strong", "Cool", "Change", "1"));

	findS(training_examples);
	cout << "Find-S algorithm running on training examples" << endl;

	return 0;
}
