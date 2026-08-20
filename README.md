# Excursion

A neural network library written from scratch in C++ while I was in high school (2023). The only dependency is Eigen, used for matrix math. Everything else, forward pass, backpropagation, activation and loss functions, is implemented by hand.

## What's inside

- `Network`: sequential model with `add()`, `train()`, `predict_outputs()`, and JSON save/load of trained parameters
- Fully connected and activation layers with hand-derived gradients
- Activations: tanh, sigmoid, ReLU, leaky ReLU
- Losses: MSE, binary cross-entropy
- Examples: XOR and MNIST digit classification (raw IDX files parsed with a custom reader)

## Building

Windows with premake:

```
git clone --recursive https://github.com/LauriSarap/Excursion
GenerateProjects.bat
```

Then open the generated Visual Studio solution and run one of the example projects.
