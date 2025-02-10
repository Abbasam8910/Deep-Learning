#include <iostream> 
#include <vector>   
#include <cmath>    

using namespace std; 

double dotProduct(const vector<double>& weights, const vector<double>& inputs) {
    double result = 0.0;     for (size_t i = 0; i < weights.size(); ++i) {
        result += weights[i] * inputs[i]; 
    }
    return result; 
}

void perceptronLearning(vector<vector<double>>& data, vector<int>& labels, double learningRate, int maxEpochs) {
    int numFeatures = data[0].size(); 

    vector<double> weights(numFeatures, 0.0);

    double bias = 0.0;

    int consistentPredictions = 0;

    for (int epoch = 0; epoch < maxEpochs; ++epoch) {
        cout << "Epoch " << epoch + 1 << ":\n"; 
        bool allCorrect = true; 

        for (size_t i = 0; i < data.size(); ++i) {
            double prediction = dotProduct(weights, data[i]) + bias;

            int output = (prediction >= 0) ? 1 : 0;

            cout << "  Data point " << i + 1 << ": Prediction = " << output << ", Actual = " << labels[i] << endl;

            if (output != labels[i]) {
                allCorrect = false; // Mark as incorrect if any prediction is wrong.

                for (size_t j = 0; j < weights.size(); ++j) {
                    weights[j] += learningRate * (labels[i] - output) * data[i][j];
                }
                bias += learningRate * (labels[i] - output);
                // Mathematical logic: 
                // weights[j] = weights[j] + learningRate * error * input[j]
                // bias = bias + learningRate * error
                // Where error = actual label - predicted output.
            }
        }

        if (allCorrect) {
            consistentPredictions++; 
            if (consistentPredictions > 1) { 
                cout << "Early stopping: Predictions are consistently correct.\n";
                break; 
            }
        } else {
            consistentPredictions = 0; 
        }

        cout << "  Updated Weights = [ ";
        for (double w : weights) cout << w << " ";
        cout << "], Bias = " << bias << endl;
    }
}

int main() {
    // Define the input data (AND logic gate truth table).
    vector<vector<double>> data = {
        {0.0, 0.0}, // Input: (0, 0)
        {0.0, 1.0}, // Input: (0, 1)
        {1.0, 0.0}, // Input: (1, 0)
        {1.0, 1.0}  // Input: (1, 1)
    };

    vector<int> labels = {0, 0, 0, 1}; // Output: [0 AND 0 = 0, 0 AND 1 = 0, etc.]

    double learningRate = 0.1;

    int maxEpochs = 10;

    perceptronLearning(data, labels, learningRate, maxEpochs);

    return 0; 
}
