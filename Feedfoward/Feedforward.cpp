#include <iostream>
#include <stdio.h>
#include <string>

#include "NeuralNet_Layer.h"
#define LIMIT 0.001
using namespace std;

int main(int argc, char* argv)
{
	srand((unsigned int)time(NULL));
	int num_input_node = 4;
	int num_input_weight_row = 3;
	int num_input_weight_col = num_input_node;
	
	double Err = 0;
	double inputs[] = { 1.0, 1.0, 0.0, 0.0 };
	Input_Layer *il = new Input_Layer(inputs, num_input_node, num_input_weight_row, num_input_weight_col);

	
	il->init_weight();
	il->feedfoward();
	
	cout << "network_spec :";
	il->print_layer_spec();
	cout << endl;
	cout << "==============================================================" << endl;

	int num_outnode = num_input_weight_row;
	Input_Layer *ml = new Input_Layer(il->outnode, 3, 4, 3);
	ml->init_weight();

	Err = 100;
	int iter = 0;
	while (Err > LIMIT){
		iter++;
		Err = 0.0;
		ml->feedfoward();
		ml->weight_update(inputs);
		
		for (int i = 0; i < num_input_node; i++){

			Err += (0.5)*(ml->outnode[i] - inputs[i])*(ml->outnode[i] - inputs[i]);
		}
		cout <<iter<< ". error : " << Err<< endl;
	}


	cout << "\nnetwork_spec :";
	ml->print_layer_spec();
	cout << endl;
	cout << "==============================================================" << endl;
	return 0;

}
