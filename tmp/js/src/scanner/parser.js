const nearley = require('nearley');
const grammar = require('./grammar');
const fs = require('mz/fs');
const path = require('path');
const { fileExists, fileReads } = require('../cli/io/file');
const { parseAst } = require('../generator/vm');

const parser = new nearley.Parser(nearley.Grammar.fromCompiled(grammar));

parser.reportError = function (token) {
  var tokenDisplay = token.type ? token.type + ' token: ' : ''; // + JSON.stringify(token.value !== undefined ? token.value : token);
  var lexerMessage = this.lexer.formatError(token, 'Syntax error');
  // return `${lexerMessage}\n${tokenDisplay}`;
  return this.reportErrorCommon(lexerMessage, tokenDisplay);
};

const parseFile = async (filepath) => {
  if (fileExists(filepath) === true) {
    const code = await fileReads(filepath);
    console.log(code);
    console.log('----------------------------------');
    parseString(code);
  } else {
    console.warn(`Error: input source '${filepath}' is not readable!`);
  }
};

const parseString = async (code) => {
  try {
    // parser.feed("a:=3.14");
    parser.feed(code);

    const ast = parser.results[0];

    console.log('Parse succeeded.');
    // console.log(parser.results);

    parseAst(ast);
  } catch (e) {
    // console.log(e);
    console.log(`Parse failed: '${e.message}'`);
  }
};

module.exports = {
  parser,
  parseFile,
  parseString,
};
