const { genStatement } = require("./statement");

const genStatements = (stmts) => {
	for(let stmt of stmts) {
		// console.log(stmt);
		genStatement(stmt);
	}
};

module.exports = {
   genStatements,
};
