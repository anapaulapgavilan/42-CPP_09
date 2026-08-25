# CPP_09

![42](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white) ![Language](https://img.shields.io/badge/lang-C++98-blue?style=flat-square) ![Status](https://img.shields.io/badge/status-completed-success?style=flat-square)

42 School C++ module 09: advanced exercises using the STL.

## About This Project

### What It Does

This module is a set of three independent command-line data-processing tools, each solving a different classic problem.

Exercises in this module:
- ex00: BitcoinExchange reads a CSV of historical exchange rates and, for a given date/amount input file, prints the converted value for each entry (with date validation).
- ex01: RPN evaluates a Reverse Polish Notation arithmetic expression given as a single command-line argument.
- ex02: PmergeMe implements the merge-insertion sort (Ford-Johnson) algorithm on a sequence of positive integers, comparing performance across two different STL containers.

### Purpose

It evaluates the ability to pick and combine appropriate STL containers/algorithms under real constraints (parsing, error handling, and - for PmergeMe - algorithmic complexity) to solve concrete, non-toy problems.

## Stack

- School: 42
- Primary language: C++98
- Scope: one repository per project

## Structure

| Exercise | Path | Binary |
|---|---|---|
| ex00 | ./ex00 | btc |
| ex01 | ./ex01 | RPN |
| ex02 | ./ex02 | PmergeMe |

## How to Run

Prerequisites: `make` and a C++98-capable compiler (`g++` or `clang++`).

Compile and run each exercise separately:

### ex00

~~~bash
cd ex00
make
./btc
~~~

### ex01

~~~bash
cd ex01
make
./RPN
~~~

### ex02

~~~bash
cd ex02
make
./PmergeMe
~~~

## Testing

No dedicated testing scripts were detected at the project root.

## Notes

- This repository is part of the 42 portfolio.
- Commands are intended for local execution for review and evaluation.

## Author

anapaulapgavilan
