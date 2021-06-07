const { emit } = require("../temp");
const { genExpression } = require("./expression");

const genVariableDefine = (command) => {
  console.log("variable");
  const value = genExpression(command.value);
  // emit(`${command.varname};`);
  emit(`${command.varname} = ${value};`);
};

module.exports = {
  genVariableDefine,
};
