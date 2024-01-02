import { main as lexer_main } from "./lexer/index";
import { Lexer } from "./lexer/lexer";
import { Parser } from "./parser/parser";
import { Ast } from "./parser/ast";

console.log("HEY");

const source_code = `
fn main {
    return 110
}
`;
const lexer: Lexer = new Lexer(source_code);

console.log(lexer.tokens);

const parser: Parser = new Parser(lexer);
const ast : Ast | null = parser.tree();
console.log(ast);
