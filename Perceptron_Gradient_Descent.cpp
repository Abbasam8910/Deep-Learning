#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double dotProduct(const vector<double>& weights, const vector<double>& inputs) {
    double result = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        result += weights[i] * inputs[i];
    }
    return result;
}

// Gradient Descent for Perceptron Learning
void gradientDescentPerceptron(vector<vector<double>>& data, vector<int>& labels, 
                               vector<double>& weights, double learningRate, int maxEpochs) {
    int numFeatures = data[0].size();  // Number of features in the data

    int consistentPredictions = 0;  // Track consistent predictions for early stopping
    
    for (int epoch = 0; epoch < maxEpochs; ++epoch) {
        cout << "Epoch " << epoch + 1 << ":\n";
        
        double totalError = 0.0;  // Total error for the current epoch
        bool allCorrect = true;   // Flag to track if all predictions are correct

        for (size_t i = 0; i < data.size(); ++i) {
            double prediction = dotProduct(weights, data[i]);
            int output = prediction >= 0 ? 1 : -1;  // Output is +1 or -1 based on the sign of the prediction

            // Calculate the error
            double error = labels[i] - output;
            totalError += abs(error);

            cout << "  Data point " << i + 1 << ": Prediction = " << output 
                 << ", Actual = " << labels[i] << ", Error = " << error << endl;

            if (error != 0) {
                allCorrect = false;  // Mark as incorrect if there is an error
                // Update weights using gradient descent rule
                for (size_t j = 0; j < numFeatures; ++j) {
                    weights[j] += learningRate * error * data[i][j];
                }
            }
        }

        // Output the total error for this epoch
        cout << "  Total Error for Epoch " << epoch + 1 << " = " << totalError << endl;

        // Check if model converges (total error is zero) or if predictions are consistent
        if (allCorrect) {
            consistentPredictions++;
            if (consistentPredictions > 1) {
                cout << "Early stopping: Predictions are consistently correct.\n";
                break;
            }
        } else {
            consistentPredictions = 0;
        }

        // Output the updated weights at the end of the epoch
        cout << "  Updated Weights = [ ";
        for (double w : weights) cout << w << " ";
        cout << "]\n";
    }
}

int main() {
    // Define the training data (sample data with two features)
    vector<vector<double>> trainingData = {
        {3.0, 5.0},
        {1.0, 4.0},
        {2.5, 3.5},
        {-3.0, -4.0},
        {-2.5, -3.0},
        {-1.5, -2.5}
    };

    // Corresponding labels (1 for positive class, -1 for negative class)
    vector<int> labels = {1, 1, 1, -1, -1, -1};

    int numFeatures = trainingData[0].size();  // Number of features in the data

    // Initialize weights to zero
    vector<double> weights(numFeatures, 0.0);

    double learningRate = 0.1;  // Learning rate for weight updates
    int maxEpochs = 100;       // Maximum number of epochs

    // Start the perceptron learning process using gradient descent
    gradientDescentPerceptron(trainingData, labels, weights, learningRate, maxEpochs);

    return 0;
}
