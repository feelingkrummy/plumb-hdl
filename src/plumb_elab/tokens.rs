#[derive(Debug, PartialEq)]
pub enum TokenType<'src> {
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,

    Plus,
    Minus,
    Star,
    Slash,

    Colon,
    SemiColon,

    Equal,
    EqualEqual,
    Bang,
    BangEqual,
    LeftArrow,
    LeftArrowEqual,
    RightArrow,
    RightArrowEqual,


    // Literals
    Identifier { literal: &'src str },

    // Type Keywords
    Logic,

    // Keywords
    Begin,
    End,

    Module,
    Input,
    Output,

    Not,
    And,
    Nand,
    Or,
    Nor,
    Xor,
    Xnor,

    Lsl,
    Lsr,
    Asl,
    Asr,
    Rol,
    Ror,

    Eof,
}

#[derive(Debug, PartialEq)]
pub struct Token<'src> {
    pub token_type: TokenType<'src>,
    pub line: u64,
    pub col: u64,
    // pub file_id: u64,
}

