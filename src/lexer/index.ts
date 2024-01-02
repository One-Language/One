import { Lexer } from './lexer';

export const main = () => {
    const source_code: string = `4 + 3
"hey:"`;
    const lexer: Lexer = new Lexer(source_code);
    
    console.log(lexer.tokens);
};
