#include <iostream>

int main() {
    std::cout << "AdaBoost code will be here" << std::endl;
    return 0;
}

// mlpack_adaboost --training_file /home/nicolas/Desktop/c_models/data/c_files/training_data.csv --labels_file /home/nicolas/Desktop/c_models/data/c_files/labels_training_data.csv --output_model_file ab_model.bin --weak_learner perceptron

// mlpack_adaboost --input_model_file ab_model.bin --test_file /home/nicolas/Desktop/c_models/data/c_files/labels_testing_data.csv --predictions_file predictions_ab.csv
