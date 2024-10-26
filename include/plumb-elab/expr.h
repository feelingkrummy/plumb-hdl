#ifndef PLUMB_EXPR_H_
#define PLUMB_EXPR_H_

typedef enum {
    PlumbExpr_Grouping,
    PlumbExpr_Binary,
    PlumbExpr_Unary,
    PlumbExpr_Variable
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
