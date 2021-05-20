const { emit } = require("../temp");
const { genStatements } = require("../statements");

const genFunction = (command) => {
	console.log(command);
	emit(`${command.return} ${command.name}() {`);
	genStatements(command.stmts);
	emit(`}`);
};

module.exports = {
   genFunction,
};
