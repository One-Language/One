import { main as lexer_main } from "./lexer/index";
import { Lexer } from "./lexer/lexer";
import { Parser } from "./parser/parser";
import { Ast, MainAst } from "./parser/ast";

console.log("HEY");

const source_code = `
fn main (a b) {
    (return
    return 110
    return "sallam"
    return ;
    // return 3.14
}
`;

const lexer: Lexer = new Lexer(source_code);
console.log(lexer.tokens);

console.log(" =============================== PARSER =============================== ");
const parser: Parser = new Parser(lexer);
// console.log(parser);
console.log("Errors");
console.log(parser.errors);

console.log(" =============================== AST =============================== ");
const ast : MainAst = parser.tree();
console.log(JSON.stringify(ast.ast, null, 4));
// console.log(ast.ast);