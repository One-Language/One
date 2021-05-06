const helpMessage = `One is a General-purpose programming language.

Usage:

  one <command> [arguments]

The commands are:

  build       compile packages and dependencies
  install     compile and install packages and dependencies
  run         compile and run One program
  version     print One version

Use "one help <command>" for more information about a command.

`;

/*
 * version
 */
const help = (args) => {
  console.log(helpMessage);
};

const helpWrong = (args) => {
  console.log(`one ${args[0]}: unknown command`);
  console.log(`Run 'one help' for usage.`);
};

module.exports = {
  helpMessage,
  help,
  helpWrong,
};
