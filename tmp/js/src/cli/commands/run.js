const { parseFile } = require("../../scanner/parser");

/*
 * run
 */
const run = (args) => {
  console.log("Run");
  if (args.length === 0) {
    // Interactive environment
    return;
  }
  parseFile(args[0]);
};

module.exports = {
  run,
};
