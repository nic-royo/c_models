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
    data::Load("/home/nicolas/Desktop/c_models/data/c_files/training_data.csv", trainingData, true);

    arma::Row<size_t> labels;
    data::Load("/home/nicolas/Desktop/c_models/data/c_files/labels_training_data.csv", labels, true);

    // Create and train RandomForest.
    RandomForest<> rf(trainingData, labels, 10); // 10 trees

    // Save the trained model
    {
        std::ofstream os("rf_model.bin");
        cereal::BinaryOutputArchive archive(os);
        archive(rf);
    }

    // Load the testing data and labels
    arma::mat testingData;
    data::Load("/home/nicolas/Desktop/c_models/data/c_files/testing_data.csv", testingData, true);

    // Load the trained model
    RandomForest<> loadedRf;
    {
        std::ifstream is("rf_model.bin");
        cereal::BinaryInputArchive archive(is);
        archive(loadedRf);
    }

    // Predict the labels for the testing data
    arma::Row<size_t> predictions;
    loadedRf.Classify(testingData, predictions);

    // Calculate accuracy
    const double accuracy = arma::accu(predictions == labels) / double(labels.n_elem);

    // Print the accuracy
    std::cout << "Accuracy: " << accuracy << std::endl;

    return 0;
}