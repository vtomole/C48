/*
 * expression.h
 * Definition of the structure used to build the syntax tree.
 */
#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

/**
 * @brief The operation type
 */
typedef enum tagEOperationType {
    eVALUE,
    number,
    symbol,
    string,
    multiply,
    plus
} EOperationType;

/**
 * @brief The expression structure
 */
typedef struct tagSExpression{
  EOperationType type;         
  int value;
  char* symbol;
  char *string;
  char character;
  struct tagSExpression *left;   
  struct tagSExpression *right; 
} SExpression;

/**
 * @brief It creates an identifier
 * @param value The number value
 * @return The expression or NULL in case of no memory
 */
SExpression *createNumber(int value);

/**
 * @brief It creates an operation
 * @param type The operation type
 * @param left The left operand
 * @param right The right operand
 * @return The expression or NULL in case of no memory
 */
SExpression *createOperation(EOperationType type, 
			     SExpression *left, SExpression *right);

/**
 * @brief Deletes a expression
 * @param b The expression
 */
void deleteExpression(SExpression *b);

#endif 
