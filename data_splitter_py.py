import pandas as pd
import os

# Load the dataset
training_file_name = '/home/nicolas/Desktop/mlpack/data/train_tv_activity.csv' 
data_training = pd.read_csv(training_file_name)
testing_file_name = '/home/nicolas/Desktop/mlpack/data/test_tv_activity.csv'  
data_testing = pd.read_csv(testing_file_name)

# Split the dataset
labels_training = data_training[['Activity']]
training_data = data_training.drop('Activity', axis=1)
labels_testing = data_testing[['Activity']]
testing_data = data_testing.drop('Activity', axis=1)

# File paths for saving
training_data_file = '/home/nicolas/Desktop/mlpack/data/c_files/training_data.csv'
labels_training_file = '/home/nicolas/Desktop/mlpack/data/c_files/labels_training_data.csv'
testing_data_file = '/home/nicolas/Desktop/mlpack/data/c_files/testing_data.csv'
labels_testing_file = '/home/nicolas/Desktop/mlpack/data/c_files/labels_testing_data.csv'

# Save the new datasets if they don't exist
if not os.path.exists(training_data_file):
    training_data.to_csv(training_data_file, index=False)
    print("File saved: 'training_data.csv'")
else:
    print("File already exists: 'training_data.csv'")

if not os.path.exists(labels_training_file):
    labels_training.to_csv(labels_training_file, index=False)
    print("File saved: 'labels_training_data.csv'")
else:
    print("File already exists: 'labels_training_data.csv'")

if not os.path.exists(testing_data_file):
    testing_data.to_csv(testing_data_file, index=False)
    print("File saved: 'testing_data.csv'")
else:
    print("File already exists: 'testing_data.csv'")

if not os.path.exists(labels_testing_file):
    labels_testing.to_csv(labels_testing_file, index=False)
    print("File saved: 'labels_testing_data.csv'")
else:
    print("File already exists: 'labels_testing_data.csv'")
