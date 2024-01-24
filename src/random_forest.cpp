#include <iostream>

//  mlpack_random_forest --training_file /home/nicolas/Desktop/c_models/data/c_files/training_data.csv --labels_file /home/nicolas/Desktop/c_models/data/c_files/labels_training_data.csv --minimum_leaf_size 20 --num_trees 10 --output_model_file rf_model.bin --print_training_accuracy

// mlpack_random_forest --input_model_file rf_model.bin --test_file /home/nicolas/Desktop/c_models/data/c_files/testing_data.csv --test_labels_file /home/nicolas/Desktop/c_models/data/c_files/labels_testing_data.csv --predictions_file predictions_rf.csv


#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <mlpack/core/data/split_data.hpp>

using namespace mlpack;
using namespace mlpack::tree;

int main()
{
    // Load the training data and labels
    arma::mat trainingData;
    data::Load("training_data.csv", trainingData, true);

    arma::Row<size_t> trainingLabels;
    data::Load("labels_training_data.csv", trainingLabels, true);

    // Load the testing data and labels
    arma::mat testingData;
    data::Load("testing_data.csv", testingData, true);

    arma::Row<size_t> testingLabels;
    data::Load("labels_testing_data.csv", testingLabels, true);

    // Train the Random Forest model
    RandomForest<> rfModel;
    rfModel.Train(trainingData, trainingLabels);

    // Predict the labels of the test data
    arma::Row<size_t> predictions;
    rfModel.Classify(testingData, predictions);

    // Calculate and print the accuracy
    double accuracy = arma::accu(predictions == testingLabels) / double(testingLabels.n_elem);
    std::cout << "Accuracy: " << accuracy << std::endl;

    return 0;
}


