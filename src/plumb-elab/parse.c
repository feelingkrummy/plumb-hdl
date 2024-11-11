
#include "common/kassert.h"

static int is_match(PlumbTokenType* type, PlumbTokenType* match_list, uint64_t len) {
	for ( uint64_t i = 0; i < len; i += 1 ) {
		if ( match_list[i] == type ) {
			return 1;
		}
	}
	return 0;
}

static void consume_token(PlumbParser* parser) {
	parser->token[0] = parser->token[1];
	parser->token[1] = plumb_lexer_next_token(&parser->lex);
}

PlumbExpr* plumb_parse_expr(PlumbParser* parser) {
	kassert(parser != NULL);
	return parse_logic_expr(parser);
}

static PlumbExpr* parse_logic_expr(PlumbParser* parser) {
	PlumbExpr* expr = parse_relational_expr(parser);
	if ( expr == NULL ) {
		return NULL;
	}
	while ( true ) {
		switch( parser->token[0].type ) {
			case PLUMB_TOKEN_AND:
			case PLUMB_TOKEN_NAND:
			case PLUMB_TOKEN_OR:
			case PLUMB_TOKEN_NOR:
			case PLUMB_TOKEN_XOR:
			case PLUMB_TOKEN_XNOR:
				PlumbExpr* new = calloc(1, sizeof(PlumbExpr));
				new->type = PLUMB_EXPR_BINARY;
				new->binary.left = expr;
				new->binary.op = token[0].type;
				consume_token(parser);
				new->binary.right = parse_relational_expr(parser);
				if ( new->binary.right == NULL ) {
					plumb_expr_free(new->binary.left);
					return NULL;
				}
				expr = new;
				break;
			default:
				return expr;
		}
	}
}

static PlumbExpr* parse_relational_expr(PlumbParser* parser) {
	PlumbExpr* expr = parse_add_sub_expr(parser);
	if ( expr == NULL ) {
		return NULL;
	}
	while ( true ) {
		switch ( parser->token[0].type ) {
			case PLUMB_TOKEN_EQUALEQUAL:
			case PLUMB_TOKEN_BANGEQUAL:
			case PLUMB_TOKEN_LEFTARROW:
			case PLUMB_TOKEN_LEFTARROWEQUAL:
			case PLUMB_TOKEN_RIGHTARROW:
			case PLUMB_TOKEN_RIGHTARROWEQUAL:
				PlumbExpr* new = calloc(1, sizeof(PlumbExpr));
				new->type = PLUMB_EXPR_BINARY;
				new->binary.left = expr;
				new->binary.op = token[0].type;
				consume_token(parser);
				new->binary.right = parse_add_sub_expr(parser);
				if ( new->binary.right == NULL ) {
					plumb_expr_free(new->binary.left);
					return NULL;
				}
				expr = new;
			default:
				return expr;
		}
	}
}

static PlumbExpr* parse_add_sub_expr(PlumbParser* parser) {
	PlumbExpr* expr = parse_mult_div_expr(parser);
	if ( expr == NULL ) {
		return NULL;
	}
	while ( true ) {
		if ( parser->token[0].type == PLUMB_TOKEN_PLUS || parser->token[0].type == PLUMB_TOKEN_MINUS ) {
			PlumbExpr* new = calloc(1, sizeof(PlumbExpr));
			new->type = PLUMB_EXPR_BINARY;
			new->binary.left = expr;
			new->binary.op = token[0].type;
			consume_token(parser);
			new->binary.right = parse_mult_div_expr(parser);
			if ( new->binary.right == NULL ) {
				plumb_expr_free(new->binary.left);
				return NULL;
			}
			expr = new;
		} else {
			return expr;
		}
	};
}

static PlumbExpr* parse_mult_div_expr(PlumbParser* parser) {
	PlumbExpr* expr = parse_power_expr(parser);
	if ( expr == NULL ) {
		return NULL;
	}
	while ( true ) {
		switch ( parser->token[0].type ) {
			case PLUMB_TOKEN_STAR:
			case PLUMB_TOKEN_SLASH:
			case PLUMB_TOKEN_MOD:
				PlumbExpr* new = calloc(1, sizeof(PlumbExpr));
				new->type = PLUMB_EXPR_BINARY;
				new->binary.left = expr;
				new->binary.op = token[0].type;
				consume_token(parser);
				new->binary.right = parse_power_expr(parser);
				if ( new->binary.right == NULL ) {
					plumb_expr_free(new->binary.left);
					return NULL;
				}
				expr = new;
			default:
				return expr;
		}
	}
}

static PlumbExpr* parse_power_expr(PlumbParser* parser) {
	PlumbExpr* expr = parse_unary_expr(parser);
	if ( expr == NULL ) {
		return NULL;
	}
	while ( true ) {
		if ( parser->token[0].type == PLUMB_TOKEN_POWER ) {
			PlumbExpr* new = calloc(1, sizeof(PlumbExpr));
			new->type = PLUMB_EXPR_BINARY;
			new->binary.left = expr;
			new->binary.op = token[0].type;
			consume_token(parser);
			new->binary.right = parse_unary_expr(parser);
			if ( new->binary.right == NULL ) {
				plumb_expr_free(new->binary.left);
				return NULL;
			}
			expr = new;
		} else {
			return expr;
		}
	};
}

static PlumbExpr* parse_unary_expr(PlumbParser* parser) {
	switch ( parser->token[0].type ) {
		case PLUMB_TOKEN_NOT:
		case PLUMB_TOKEN_MINUS:
		case PLUMB_TOKEN_AND:
		case PLUMB_TOKEN_NAND:
		case PLUMB_TOKEN_OR:
		case PLUMB_TOKEN_NOR:
		case PLUMB_TOKEN_XOR:
		case PLUMB_TOKEN_XNOR:
			PlumbExpr* new = calloc(1, sizeof(PlumbExpr));
			new->type = PLUMB_EXPR_UNARY;
			new->unary.op = parser->token[0].type;
			consume_token(parser);
			new->unary.right = parse_primary_expr(parser);
			if (new->unary.right == NULL) {
				free(new);
				return NULL;
			}
		default:
			return parse_primary_expr(parser);
	}
}

static PlumbExpr* parse_primary_expr(PlumbParser* parser) {
	if ( parse->token[0].type == PLUMB_TOKEN_IDENT ) {
		PlumbExpr* expr = calloc(1, sizeof(PlumbExpr));
		expr->type = PLUMB_EXPR_VARIABLE;
		expr->varaible.name = token[0].ident;
		consume_token(parser);
		return expr;
	}
	return NULL;
};
