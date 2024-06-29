# PyTorch CNN

## [View Code](https://github.com/ImTimTong/Projects/tree/main/PyTorch-CNN)

## Overview

This repository contains a Convolutional Neural Network (CNN) implemented in PyTorch for classifying CIFAR-10 images. The model achieves high accuracy through data augmentation, batch normalization, dropout regularization, and a multi-layered architecture.

## Techniques Used

- **Data Augmentation**: Random crop, horizontal flip, and rotation for training set.
- **Normalization**: Pixel values normalized to enhance convergence.
- **Batch Normalization**: Applied before each convolutional layer for faster training.
- **Dropout**: Regularization technique to prevent overfitting.
- **Learning Rate Scheduling**: Adjusts learning rate based on model performance.

## Model Architecture

- **Layers**: 5 convolutional layers followed by max-pooling and ReLU activations.
- **Fully Connected Layers**: 3 fully connected layers with ReLU activations.
- **Output**: 10 classes corresponding to CIFAR-10 categories.

## Hyperparameters

- **Epochs**: 200
- **Batch Size**: 128
- **Learning Rate**: 0.01
- **Momentum**: 0.9
- **Weight Decay**: 1e-4

## Results

- Achieves over **90% accuracy** on the CIFAR-10 test set.
- Detailed accuracy metrics for each class provided.
