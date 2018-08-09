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

void findS(vector<EnjoySport> training_examples, ofstream &output_file) {
	string hypothesis[] = {"0", "0", "0", "0", "0", "0", "0"};
	int trace_count = 0;

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

bool create_example(string hypothesis[], string target_concept[], ofstream &output_file) {
	string attributes[][2] = { {"Sunny", "Rainy"}, {"Warm", "Cold"}, {"Normal", "High"}, {"Strong", "Weak"}, {"Warm", "Cool"}, {"Same", "Change"} };
	string example[] = {"0", "0", "0", "0", "0", "0", "1"};
	
	srand(time(NULL));
	
	for (int i = 0; i < sizeof(attributes)/sizeof(attributes[0]); i++) {
		string temp = attributes[i][rand()%2];

		if (target_concept[i] == "?") {
			example[i] = temp;
			continue;
		}

		else {
			if (target_concept[i] != temp) {
				return false;
			}

			else {
				example[i] = temp;
			}
		}
	}

	for (int j = 0; j < sizeof(attributes)/sizeof(attributes[0]); j++) {
		if (hypothesis[j] != example[j]) {
			hypothesis[j] = "?";
		}

		if (hypothesis[j] != target_concept[j]) {
			return false;
		}
	}

	output_file << "Example required to match target concept: " << endl << endl;
	output_file << "<";
	for (int i = 0; i < (sizeof(example)/sizeof(example[0]) - 1); i++) {
		if (i != (sizeof(example)/sizeof(example[0])) -2) {
			output_file << example[i] << ", ";
		}

		else {
			output_file << example[i] << ">" << endl << endl;
		}
	}

	return true;

}

void findMinimum(vector<EnjoySport> training_examples, ofstream &output_file) {
	string hypothesis[] = {"0", "0", "0", "0", "0", "0", "0"};
	string target_concept[] = {"Sunny", "Warm", "?", "?", "?", "?"};

	
	for (int i = 0; i < training_examples.size(); i++) {
		vector<string> example = training_examples.at(i).dataset;

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
	}
	

	bool flag = false;
	int count = 0;

	while (!flag) {
		++count;
		flag = create_example(hypothesis, target_concept, output_file);
	}

	output_file << "Amount of examples needed to match target concept: " << count << endl;
}

int main(int argc, char* argv[]) {

	vector<EnjoySport> training_examples;
	training_examples.push_back(EnjoySport("Sunny", "Warm", "Normal", "Strong", "Warm", "Same", "1"));
	training_examples.push_back(EnjoySport("Sunny", "Warm", "High", "Strong", "Warm", "Same", "1"));
	training_examples.push_back(EnjoySport("Rainy", "Cold", "High", "Strong", "Warm", "Change", "0"));
	training_examples.push_back(EnjoySport("Sunny", "Warm", "High", "Strong", "Cool", "Change", "1"));

	ofstream output_file;
	output_file.open("output.txt");

	findS(training_examples, output_file);
	cout << "Find-S algorithm running on training examples" << endl << endl;

	output_file << endl;

	cout << "Finding example to match target concept" << endl;
	findMinimum(training_examples, output_file);

	return 0;
}
