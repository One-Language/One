const { help, helpWrong } = require("./commands/help");
const { version } = require("./commands/version");
const { run } = require("./commands/run");

/*
 * main
 */
const main = (args) => {
  args.splice(0, 2); // [ '/usr/bin/node', '/home/maxb/Projects/One/src/one.js', 'run' ]

  // console.log(args);
  // console.log(args.length);

  if (args.length === 0) {
    help(args);
  } else {
    parseCLI(args);
  }
};

/*
 * removeFirst
 * arguments: args (Array of string)
 */
const removeFirst = (args) => {
  args.splice(0, 1);
  return args; // Not required!
};

/*
 * parseCLI
 * arguments: args (Array of string)
 * note: args.length is more then 0
 */
const parseCLI = (args) => {
  if (args[0] === "run") {
    removeFirst(args);
    run(args);
  } else if (args[0] === "version") {
    removeFirst(args);
    version(args);
  } else {
    helpWrong(args);
  }
};

module.exports = {
  main,
};
