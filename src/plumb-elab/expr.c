#include <stdlib.h>

#include "plumb-elab/tokens.h"
#include "plumb-elab/expr.h"

void plumb_expr_free(PlumbExpr* expr) {
	switch(expr->type) {
		case PLUMB_EXPR_GROUPING:
			if (expr->group.expr != NULL) {
				plumb_expr_free(expr);
				expr->group.expr = NULL;
			}
			free(expr);
			return;
		case PLUMB_EXPR_BINARY:
			if (expr->binary.left != NULL) {
				plumb_expr_free(expr);
				expr->binary.left = NULL;
			}
			if (expr->binary.right != NULL) {
				plumb_expr_free(expr);
				expr->binary.right = NULL;
			}
			free(expr);
			return;
		case PLUMB_EXPR_UNARY:
			if (expr->unary.right != NULL) {
				plumb_expr_free(expr);
				expr->unary.right = NULL;
			}
			free(expr);
			return;
		case PLUMB_EXPR_VARIABLE:
			free(expr);
			return;
	}
}
