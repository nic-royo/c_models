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
//
//// FOllowing code for one hot encoding of the week day, comment for now
//    // Assuming 'Week_day' is in a specific column, e.g., the fourth column (index 4)
//    size_t week_day_index = 3;
//
//    // Identify unique days and map them to integers
//    std::unordered_map<int, int> day_mapping;
//    arma::rowvec week_days = data_training.row(week_day_index);
//    int counter = 0;
//    for (auto day : week_days) {
//        if (day_mapping.find(day) == day_mapping.end()) {
//            day_mapping[day] = counter++;
//        }
//    }
//
//    // Create matrices for one-hot encoding
//    arma::mat training_encoded = arma::zeros<arma::mat>(day_mapping.size(), data_training.n_cols);
//    arma::mat testing_encoded = arma::zeros<arma::mat>(day_mapping.size(), data_testing.n_cols);
//
//    // Apply one-hot encoding
//    for (size_t i = 0; i < data_training.n_cols; ++i) {
//        int day = data_training(week_day_index, i);
//        training_encoded(day_mapping[day], i) = 1;
//        }
//    for (size_t i = 0; i < data_testing.n_cols; ++i) {
//        int day = data_testing(week_day_index, i);
//        testing_encoded(day_mapping[day], i) = 1;
//        }
//    data_training.shed_row(week_day_index);
//    data_testing.shed_row(week_day_index);
//
//    data_training = arma::join_cols(data_training, training_encoded);
//    data_testing = arma::join_cols(data_testing, testing_encoded);
//
//

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

    // save the new datasets, replacing existing files if they exist
    mlpack::data::Save(training_data_file, data_training, true); // true for no transpose
    std::cout << "File saved: '" << training_data_file << "'" << std::endl;

    mlpack::data::Save(labels_training_file, labels_training, true);
    std::cout << "File saved: '" << labels_training_file << "'" << std::endl;

    mlpack::data::Save(testing_data_file, data_testing, true);
    std::cout << "File saved: '" << testing_data_file << "'" << std::endl;
    
    mlpack::data::Save(labels_testing_file, labels_testing, true);
    std::cout << "File saved: '" << labels_testing_file << "'" << std::endl;

    
    // save the new datasets IF they don't exist, instead of deleteing them
    //auto save_if_not_exists = [](const arma::mat& data, const std::string& file_path) {
    //    std::ifstream ifile(file_path);
    //    if (!ifile) {
    //        mlpack::data::Save(file_path, data, true); // true for no transpose
    //        std::cout << "File saved: '" << file_path << "'" << std::endl;
    //    } else {
    //        std::cout << "File already exists: '" << file_path << "'" << std::endl;
    //    }
    //};
    //
    //save_if_not_exists(data_training, training_data_file);
    //save_if_not_exists(labels_training, labels_training_file);
    //save_if_not_exists(data_testing, testing_data_file);
    //save_if_not_exists(labels_testing, labels_testing_file);

    return 0;
}
