const { genIf } = require("./commands/if");
const { genWhile } = require("./commands/while");
const { genFor } = require("./commands/for");
const { genVariableDefine } = require("./commands/variable-define");

const genStatement = (stmt) => {
	console.log(stmt);
	switch(stmt.type) {
	case "if":
		return genVariableDefine(stmt);
	case "while":
		return genWhile(stmt);
	case "for":
		return genFor(stmt);
	case "var_assignment":
		return genVariableDefine(stmt);
	default:
		console.warn("Error: bad statement!");
		return null;
	}
};

module.exports = {
   genStatement,
};
