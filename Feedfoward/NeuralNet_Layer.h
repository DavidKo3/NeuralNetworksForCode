#include <iostream>
#include <math.h>
#include <time.h>
#define LEARNINGLATE 10
using namespace std;
class Layer{

	public:
    double *node = nullptr;
	double **weight= nullptr;
	double *outnode = nullptr;

};

class Input_Layer : Layer
{
	
public:
	double *node;
	double **weight;
	double *outnode;
	double Error = 0;
	int num_node; int num_weight_row; int num_weight_col;
	Input_Layer(double* inputs, int node_size, int weight_row, int weight_col){
		num_node = node_size;
		num_weight_row = weight_row;
		num_weight_col = weight_col;
		this->node = new double[num_node];
		
		for (int i = 0; i < num_node; i++){
			this->node[i] = 0.0;
			this->node[i] = inputs[i];
			
		}

		this->outnode = new double[num_weight_row];

		for (int i = 0; i < num_weight_row; i++){
			this->outnode[i] = 0.0;

		}
		this->weight = new double*[num_weight_col];
		for (int i = 0; i < weight_row; i++){
			weight[i] = new double[num_weight_col];
		}
	}
	void weight_update(double *inputNode){
		double *O = new double[num_weight_row]; 
		
	
		for (int i = 0; i < num_weight_row; i++){
			
			O[i] = this->outnode[i];
			this->Error += (O[i] - inputNode[i]);
			for (int j = 0; j < num_weight_col; j++){
				
				this->weight[i][j] = this->weight[i][j] + LEARNINGLATE*(this->Error)*O[i] * (1 - O[i])*(this->node[j]) - (LEARNINGLATE*(this->Error)*O[i] * (1 - O[i]));
			}
		}
	}
	~Input_Layer()
	{
		delete this->node;

		for (int i = 0; i < num_weight_row; i++){
			delete[] this->weight[i];

		}
		delete this->weight;

	}
	void feedfoward(){
		double output = 0;
		for (int i = 0; i < num_weight_row; i++){
			for (int j = 0; j < num_weight_col; j++){
				this->outnode[i] += node[j] *(this->weight[i][j]);

			}
			
			this->outnode[i] = sig_moid(this->outnode[i]);
		}



	}
	double Random_weights(){
		double result = 0;

		
		result = ((double)rand() / (RAND_MAX));
		result = result * 2 - 1;
		return result;
	}

	double sig_moid(double value){
		return ((double)1.0 / (1.0 + exp(-(value))));
	}

	void print_layer_spec(){
	
		cout << "num of node :" << num_node << endl;
		for (int i = 0; i < num_node; i++){
			cout.setf(ios::showpoint);
			cout.precision(6);
			cout << this->node[i] << "   ";
		}
		cout << "\n========================================" << endl;
		for (int i = 0; i < num_weight_row; i++){
			for (int j = 0; j < num_weight_col; j++){
			
				cout.setf(ios::showpoint);
				cout.precision(6);
				cout << weight[i][j] << "   ";
			}
			cout <<  endl;
		}
		cout << "======================================" << endl;
		for (int i = 0; i < num_weight_row; i++){

			
				cout.setf(ios::showpoint);
				cout.precision(6);
				cout << this->outnode[i] << "   ";
			
		}


	}

	void init_weight(){

		for (int i = 0; i < num_weight_row; i++){
			for (int j = 0; j < num_weight_col; j++){
				weight[i][j] = Random_weights();
			}
		}
	}

};