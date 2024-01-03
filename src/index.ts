import { main as lexer_main } from "./lexer/index";
import { Lexer } from "./lexer/lexer";
import { Parser } from "./parser/parser";
import { Ast, MainAst } from "./parser/ast";
import { Generator } from "./generator/generator";

console.log("HEY");

const source_code = `
fn test {
    ret;
}
fn hh() {}
fn main (a b) {
    ret;
    ret 110
    // ret "sallam"
    ret ;
    ret 3.14
    ret 1
    ret 100 + 10
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
if (parser.errors.length === 0) {
    const ast : MainAst = parser.tree();
    console.log(JSON.stringify(ast.ast, null, 4));
    // console.log(ast.ast);

    console.log(" =============================== GEN =============================== ");
    const generator: Generator = new Generator(ast);
    const c: string = generator.c();
    console.log(c);
}
