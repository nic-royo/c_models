#include <iostream>
#include <vector>
#include <algorithm>

// Define a simple structure for our data point
struct DataPoint {
    std::vector<float> features;
    int label; // Assuming binary classification (-1 or 1)
};

// Decision Stump as a Weak Classifier
class DecisionStump {
public:
    int featureIndex;
    float threshold;
    int polarity;

    DecisionStump() : featureIndex(0), threshold(0.0), polarity(1) {}

    // Predict function for a decision stump
    int predict(const std::vector<float>& features) {
        float featureValue = features[featureIndex];
        return (featureValue < threshold) ? -polarity : polarity;
    }
};

// AdaBoost Classifier
class AdaBoost {
private:
    std::vector<DecisionStump> stumps;
    std::vector<float> alphas;

public:
    // Function to train AdaBoost on the given dataset
    void train(const std::vector<DataPoint>& dataset, int numIterations) {
        int n = dataset.size();
        std::vector<float> weights(n, 1.0 / n);

        for (int i = 0; i < numIterations; ++i) {
            DecisionStump stump;
            float minError = std::numeric_limits<float>::max();

            // Iterate over each feature and threshold to find the best stump
            for (size_t j = 0; j < dataset[0].features.size(); ++j) {
                float threshold, error;
                int polarity;
                std::tie(threshold, error, polarity) = findBestThreshold(dataset, weights, j);

                if (error < minError) {
                    minError = error;
                    stump.featureIndex = j;
                    stump.threshold = threshold;
                    stump.polarity = polarity;
                }
            }

            // Calculate alpha
            float alpha = 0.5 * log((1.0 - minError) / (minError + std::numeric_limits<float>::epsilon()));
            stumps.push_back(stump);
            alphas.push_back(alpha);

            // Update weights
            for (size_t k = 0; k < n; ++k) {
                int prediction = stump.predict(dataset[k].features);
                if (prediction == dataset[k].label) {
                    weights[k] *= exp(-alpha);
                } else {
                    weights[k] *= exp(alpha);
                }
            }

            // Normalize weights
            float sumWeights = std::accumulate(weights.begin(), weights.end(), 0.0f);
            for (float &weight : weights) {
                weight /= sumWeights;
            }
        }
    }

    // Prediction function for AdaBoost
    int predict(const std::vector<float>& features) {
        float finalScore = 0.0;
        for (size_t i = 0; i < stumps.size(); ++i) {
            finalScore += alphas[i] * stumps[i].predict(features);
        }
        return finalScore >= 0 ? 1 : -1;
    }

private:
// 
std::tuple<float, float, int> findBestThreshold(const std::vector<DataPoint>& dataset, const std::vector<float>& weights, int featureIndex) {
    std::vector<std::pair<float, int>> featureValues;
    for (const auto& data : dataset) {
        featureValues.emplace_back(data.features[featureIndex], data.label);
    }

    sort(featureValues.begin(), featureValues.end());

    float bestThreshold = 0;
    float bestError = std::numeric_limits<float>::max();
    int bestPolarity = 1;

    for (size_t i = 0; i < featureValues.size(); ++i) {
        float threshold = featureValues[i].first;
        int polarity = 1;
        float error = 0;

        for (size_t j = 0; j < featureValues.size(); ++j) {
            int prediction = (featureValues[j].first < threshold) ? 1 : -1;
            if (prediction != featureValues[j].second) {
                error += weights[j];
            }
        }

        if (error > 0.5) {
            error = 1 - error;
            polarity = -1;
        }

        if (error < bestError) {
            bestError = error;
            bestThreshold = threshold;
            bestPolarity = polarity;
        }
    }

    return std::make_tuple(bestThreshold, bestError, bestPolarity);
}

// Main function to test our AdaBoost Classifier
int main() {
    // Load dataset
    // ...

    // Create an AdaBoost instance and train it
    AdaBoost classifier;
    classifier.train(dataset, 10); // Number of iterations

    // Test the classifier
    // ...

    return 0;
}
// mlpack_adaboost --training_file /home/nicolas/Desktop/c_models/data/c_files/training_data.csv --labels_file /home/nicolas/Desktop/c_models/data/c_files/labels_training_data.csv --output_model_file ab_model.bin --weak_learner perceptron

// mlpack_adaboost --input_model_file ab_model.bin --test_file /home/nicolas/Desktop/c_models/data/c_files/labels_testing_data.csv --predictions_file predictions_ab.csv
