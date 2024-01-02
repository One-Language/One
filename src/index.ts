import { main as lexer_main } from "./lexer/index";
import { Lexer } from "./lexer/lexer";
import { Parser } from "./parser/parser";
import { Ast, MainAst } from "./parser/ast";

console.log("HEY");

const source_code = `
fn main {
    // return 110
}
`;

const lexer: Lexer = new Lexer(source_code);
console.log(lexer.tokens);

console.log(" =============================== PARSER =============================== ");
const parser: Parser = new Parser(lexer);
// console.log(parser);
console.log(parser.errors);

console.log(" =============================== AST =============================== ");
const ast : MainAst = parser.tree();
console.log(ast.ast);
