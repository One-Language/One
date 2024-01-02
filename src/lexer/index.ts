import { Lexer } from './lexer';

export const main = () => {
    const source_code: string = `4 + 3
// hey there!
"hey:
123
345356456
3

        dfgdfg
        dfg
        dfg
            dfgdfg?"`;
    const lexer: Lexer = new Lexer(source_code);
    
    console.log(lexer.tokens);
};
