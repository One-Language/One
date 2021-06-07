const { fileSave } = require("../cli/io/file");
const generator = require("../generator/");

const tempFilename = "input.c";
const astFilename = "input.ast";

const astToStr = (ast) => {
  return JSON.stringify(ast, null, 2);
};

const saveAst = async (ast) => {
  const log = astToStr(ast);
  await fileSave(astFilename, log);

  // const jsCode = generateJS(ast, []);
  // await fs.writeFile(outputFilename, jsCode);
};

const saveTemp = async () => {
  console.log(emits);
  console.log(tempFilename);
  await fileSave(tempFilename, emits);
};

const parseAst = (ast) => {
  // console.log(ast);
  for (let func of ast.functions) {
    generator.genFunction(func);
  }
  saveAst(ast);
  saveTemp();
};

module.exports = {
  parseAst,
};
