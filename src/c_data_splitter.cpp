// code to split the files into labels and feature data, bc thats how MLPack processes it,
// for both training and testing

#include <mlpack/core.hpp>
#include <mlpack/core/data/split_data.hpp>
#include <fstream>
#include <iostream>

int main() {
    // load datasets 
    const std::string training_file_name = "/home/nicolas/Desktop/c_models/data/train_tv_activity.csv";
    const std::string testing_file_name = "/home/nicolas/Desktop/c_models/data/test_tv_activity.csv";
    
    arma::mat data_training;
    arma::mat data_testing;
    mlpack::data::Load(training_file_name, data_training, true);
    mlpack::data::Load(testing_file_name, data_testing, true);

    // split datasets into features and labels
    arma::mat labels_training = data_training.row(data_training.n_rows - 1);
    data_training.shed_row(data_training.n_rows - 1);

    arma::mat labels_testing = data_testing.row(data_testing.n_rows - 1);
    data_testing.shed_row(data_testing.n_rows - 1);

    // file paths for saving
    const std::string training_data_file = "/home/nicolas/Desktop/c_models/data/c_files/training_data.csv";
    const std::string labels_training_file = "/home/nicolas/Desktop/c_models/data/c_files/labels_training_data.csv";
    const std::string testing_data_file = "/home/nicolas/Desktop/c_models/data/c_files/testing_data.csv";
    const std::string labels_testing_file = "/home/nicolas/Desktop/c_models/data/c_files/labels_testing_data.csv";

    // save the new datasets IF they don't exist, oterwise do nothing
    auto save_if_not_exists = [](const arma::mat& data, const std::string& file_path) {
        std::ifstream ifile(file_path);
        if (!ifile) {
            mlpack::data::Save(file_path, data, true); // true for no transpose
            std::cout << "File saved: '" << file_path << "'" << std::endl;
        } else {
            std::cout << "File already exists: '" << file_path << "'" << std::endl;
        }
    };

    save_if_not_exists(data_training, training_data_file);
    save_if_not_exists(labels_training, labels_training_file);
    save_if_not_exists(data_testing, testing_data_file);
    save_if_not_exists(labels_testing, labels_testing_file);

    return 0;
}
