const { genIf } = require("./commands/if");
const { genWhile } = require("./commands/while");
const { genFor } = require("./commands/for");
const { genFunction } = require("./commands/function");
const { genVariableDefine } = require("./commands/variable-define");
// const { parseAst } = require("./vm");

// function generateJSExpression(expression) {
//   // console.log(expression);

//   const oepratorMap = {
//     "+": "+",
//     "-": "-",
//     "*": "*",
//     "/": "/",
//     ">=": ">=",
//     "<=": "<=",
//     ">": ">",
//     "<": "<",
//     "=": "==",
//   };

//   if (typeof expression === "object") {
//     if (expression.type === "binary_expression") {
//       const left = generateJSExpression(expression.left);
//       const right = generateJSExpression(expression.right);
//       const operator = oepratorMap[expression.operator];
//       return `${left} ${operator} ${right}`;
//     }
//   } else {
//     // identifier or number
//     return expression;
//   }
// }

// function generateJS(statements, declaredVariables) {
//   // console.log(declaredVariables);

//   const lines = [];
//   for (let statement of statements) {
//     if (statement.type === "var_assignment") {
//       const value = generateJSExpression(statement.value);
//       if (declaredVariables.indexOf(statement.varname) === -1) {
//         lines.push(`let ${statement.varname} = ${value};`);
//         declaredVariables.push(statement.varname);
//       } else {
//         lines.push(`${statement.varname} = ${value};`);
//       }
//     } else if (statement.type === "while_loop") {
//       const condition = generateJSExpression(statement.condition);
//       const body = generateJS(statement.body, declaredVariables)
//         .split("\n")
//         .map((line) => "    " + line)
//         .join("\n");
//       lines.push(`while(${condition}) {\n${body}\n}`);
//     } else if (statement.type === "print_statement") {
//       const expression = generateJSExpression(statement.expression);
//       lines.push(`console.log(${expression});`);
//     }
//   }
//   return lines.join("\n");
//   // return "console.log('Hello, World!');";
// }

module.exports = {
  genIf,
  genWhile,
  genFor,
  genFunction,
  genVariableDefine,
  // parseAst,
};
