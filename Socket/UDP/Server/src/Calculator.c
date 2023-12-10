/*
 * Calculator.c
 *
 *  Calculator Implementation file
 *  Created on: 9 nov 2023
 *  Author: Leonardo Birardi
 */

#include "Calculator.h"

/**
 * Performs addition operation.
 *
 * @param a The first operand.
 * @param b The second operand.
 * @return The result of the addition operation.
 */
double add(double a, double b) {
    return a + b;
}

/**
 * Performs multiplication operation.
 *
 * @param a The first operand.
 * @param b The second operand.
 * @return The result of the multiplication operation.
 */
double mult(double a, double b) {
    return a * b;
}

/**
 * Performs subtraction operation.
 *
 * @param a The first operand.
 * @param b The second operand.
 * @return The result of the subtraction operation.
 */
double sub(double a, double b) {
    return a - b;
}

/**
 * Performs division operation.
 *
 * @param a The numerator.
 * @param b The denominator.
 * @return The result of the division operation, or 0.0 if division by zero.
 */
double division(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        return 0.0; // Error handling: Division by zero
    }
}


