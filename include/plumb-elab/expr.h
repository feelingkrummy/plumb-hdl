#ifndef PLUMB_EXPR_H_
#define PLUMB_EXPR_H_

typedef enum {
	PLUMB_EXPR_GROUPING,
	PLUMB_EXPR_BINARY,
	PLUMB_EXPR_UNARY,
	PLUMB_EXPR_VARIABLE
} PlumbExprType;

typedef struct PlumbExpr PlumbExpr;

typedef struct {
	PlumbExpr* expr;
} PlumbExprGrouping;

typedef struct {
	PlumbExpr* left;
	PlumbTokenType op;
	PlumbExpr* right;
} PlumbExprBinary;

typedef struct {
	PlumbTokenType op;
	PlumbExpr* right;
} PlumbExprUnary;

typedef struct {
	str8 name;
} PlumbExprVariable;

struct PlumbExpr {
	PlumbExprType type;
	union {
		PlumbExprGrouping group;
		PlumbExprBinary binary;
		PlumbExprUnary unary;
		PlumbExprVariable variable;
	};
};


void plumb_expr_free(PlumbExpr* expr);

#endif 
