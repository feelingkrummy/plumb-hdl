#ifndef PLUMB_EXPR_H_
#define PLUMB_EXPR_H_

typedef enum {
	PLUMB_OP_PLUS, 
	PLUMB_OP_MINUS, 
	PLUMB_OP_DIV, 
	PLUMB_OP_MULT, 
	PLUMB_OP_POWER, 

	PLUMB_TOKEN_EQUAL, 
	PLUMB_TOKEN_EQUALEQUAL, 
} PlumbOp;

typedef enum {
	PLUMB_EXPR_GROUPING,
	PLUMB_EXPR_BINARY,
	PLUMB_EXPR_UNARY,
	PLUMB_EXPR_VARIABLE
} PlumbExprType;

typedef struct {
	PlumbExpr* expr;
} PlumbExprGrouping 

typedef struct {
	PlumbExpr* left;
	PlumbOp op;
	PlumbExpr* right;
} PlumbExprBinary;

typedef struct {
	PlumbOp op;
	PlumbExpr* right;
} PlumbExprUnary;

typedef struct {
	str8 name;
} PlumbExprVariable;

typedef struct {
	PlumbExprType type;
	union {
		PlumbExprGrouping group;
		PlumbExprBinary binary;
		PlumbExprUnary unary;
		PlumbExprVariable variable;
	}
} PlumbExpr;

#endif 
