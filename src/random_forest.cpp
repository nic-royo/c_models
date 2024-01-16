#include <iostream>

int main() {
    std::cout << "RF code will be here" << std::endl;
    return 0;
}


//  mlpack_random_forest --training_file /home/nicolas/Desktop/c_models/data/c_files/training_data.csv --labels_file /home/nicolas/Desktop/c_models/data/c_files/labels_training_data.csv --minimum_leaf_size 20 --num_trees 10 --output_model_file rf_model.bin --print_training_accuracy

// mlpack_random_forest --input_model_file rf_model.bin --test_file /home/nicolas/Desktop/c_models/data/c_files/testing_data.csv --test_labels_file /home/nicolas/Desktop/c_models/data/c_files/labels_testing_data.csv --predictions_file predictions.csv


