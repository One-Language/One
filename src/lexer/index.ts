import { Lexer } from './lexer';

export const main = () => {
    const source_code: string = 
// `4 + 3
// // hey there!
// "hey:
// 123
// 345356456
// 3

//         dfgdfg
//         dfg
//         dfg
//             dfgdfg?"
            
// /*
//     fgdfkgdfgkod fkogdf+ c "dfgdfgsgdf gdfg d fg
//     q           dfgdfgdfg"
//     fdgdfg.. . . ???,.dfgd.fg,.df,gdfg */+/
//     5/3
`
fn main {
    return 110
}
`;
    const lexer: Lexer = new Lexer(source_code);
    
    console.log(lexer.tokens);
};
