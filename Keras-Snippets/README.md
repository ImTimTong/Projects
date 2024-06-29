# Keras Snippets 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/Keras-Snippets)

## Overview
AI lab applying Keras to train a machine learning model to classify images of clothing from the FashionMNIST dataset. Model achieves 87% accuracy.

## Features
**Data Loading and Preprocessing**
- Loaded the Fashion MNIST dataset.
- Normalized the pixel values of the images to a range of [0, 1].

**Model Creation**
- Defined a sequential neural network using Keras.
- Added a Flatten layer to convert the 28x28 images into a 1D vector.
- Added a Dense layer with 512 neurons and ReLU activation.
- Added a Dense output layer with 10 neurons and softmax activation for classification.

**Model Compilation**
- Compiled the model using sparse categorical cross-entropy loss, Adam optimizer, and accuracy as a metric.

**Model Training**
- Trained the model for 5 epochs with a batch size of 32.

**Model Evaluation**
- Evaluated the model on the test dataset to compute the accuracy.
- Displayed the accuracy rate.

**Predictions and Visualization**
- Made predictions on the test dataset.
- Visualized each type of clothing in an image using Matplotlib.

**Confusion Matrix**
- Computed the confusion matrix for the test dataset predictions.
- Displayed the confusion matrix with labeled classes using Matplotlib.
