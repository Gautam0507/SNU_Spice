# SNU Spice

SNU Spice is an electronic circuit simulator designed for purely resistive circuits, handling voltage and current sources (both independent and dependent) along with resistors. This project is being developed as part of the Opportunities for Undergraduate Research Program (OUR) 2024 at Shiv Nadar University, under project code OUR20240023, and is carried out under the supervision of Prof. Venkatnarayan Hariharan. The simulator is inspired by the methodologies outlined in the book "[Circuit Simulation](https://onlinelibrary.wiley.com/doi/book/10.1002/9780470561218)" by Farid N. Najm.

## Table of Contents

- [Working](#working)
- [Installation and Running SNU Spice](#installation-and-running-SNU-Spice)
  - [Installation](#installation)
  - [Running](#running)
- [Accepted Syntax of Circuit Elements](#accepted-syntax-of-circuit-elements)
- [UML Diagrams](#uml-diagrams)
- [Constraints](#constraints)
- [List of Errors and Warnings](#list-of-errors-and-warnings)
  - [Errors](#errors)
  - [Warnings](#warnings)
- [Credits](#credits)

## Working

SNU Spice uses Modified Nodal Analysis (MNA) to find all the nodal voltages and required currents across the branches. It builds the MNA and RHS matrices in O(n) time complexity. It goes through the netlist, checks for any error in the netlist, and makes the matrices, on the fly, in linear time, using the element stamp of each component.

The contribution of every element to the matrix equation is described by employing an element stamp template. Every element has different stamps based on their contribution to the matrices and on which group they belong to.

The simulator uses the [Eigen](https://eigen.tuxfamily.org/) library to implement the solver. We have used LU factorization to solve the equation.

## Installation and Running SNU Spice

- Requirement: GCC Compiler (or any other C++ compiler)

### Installation

#### Manual

- Download the project from GitHub
- Compile all the files

#### Cmake

- Clone the repository
- Run the following commands in the terminal

```bash

mkdir build
cd build
cmake -S .. -B .
cmake --build .

```

### Running

- Type the netlist in the _circuit.sns_ file

- If the file is located in a different directory, provide the path to the file as a command-line argument when calling the function. 

- Run the executable file in the terminal from the project root to get all nodal voltages and required currents

Note: If built using Cmake, the executable file will be in the `build/src` directory

### Generating Documentation

- clone the repository
- Run the following comamnds in the terminal

```bash
mkdir build
cd build
cmake -S .. -B .
cmake --build . -t documentation

```

## Accepted Syntax of Circuit Elements

- Independent Current Source: `I<string> <node.+> <node.-> <value> [G2]`
- Dependent Current Source: `Ic<string> <node.+> <node.-> <factor> <variable> <circuitElement>`
- Independent Voltage Source: `V<string> <node.+> <node.-> <value>`
- Dependent Voltage Source: `Vc<string> <node.+> <node.-> <factor> <variable> <circuitElement>`
- Resistor: `R<string> <node.+> <node.-> <value> [G2]`
- Capacitor: `C<string> <node.+> <node.-> <value> [G2]`
- Inductor: `L<string> <node.+> <node.-> <value>`

`G2`, for group 2, is an optional field that tells the simulator that the user is interested in knowing the current across the circuit element. By default, all voltage sources are group 2.

Accepted values for `variable` are either `V` or `I`, which tell the simulator that the source is dependent on that particular variable of the `circuitElement`.

`<node.+>`, `<node.->` takes string and `value`, `factor` takes value in normal integer, decimal or exponential form but doesn't allow multiplier.

## UML Diagrams

This project contains one structure: _CircuitElement_, and three classes: _Parser_, _Edge_ and _Node_. Following is the UML diagram of each.

![CircuitElement Structure](/Class%20Diagram/CircuitElement.png)

![Parser Class](/Class%20Diagram/Parser.png)

![Node Class](/Class%20Diagram/Node.png)

![Edge Class](/Class%20Diagram/Edge.png)

## Constraints

- One of the nodes in the netlist must be 0 (string)

- Current controlling variable's element must be in group 2
- Controlling variable cannot be dependent on another dependent variable
- Values in the netlist cannot accept multipliers (give actual values or in exponential)
- Inline comments are best avoided (if required, explicitly state the group before commenting)
- Circuit element can't have a zero value or factor

## List of Errors and Warnings

### Errors

- Unknown element
- Circuit must contain ground (0)

- Checks whether the controlling element is present in the netlist
- Controlled source cannot be cascaded

- Reviews for legal input value or factor
- Illegal controlling variable argument

- Netlist not available

### Warnings

- Checks and makes sure that the controlled element is in group 2 if the controlling variable is current

- Two nodes of a component cannot be the same (Omits the component)
- Mention the correct group (by default, assigns group 1)

## Credits

I am thankful to the [Eigen](https://eigen.tuxfamily.org/) library team for developing and maintaining the library, because of which the matrix equation could be solved so efficiently.
