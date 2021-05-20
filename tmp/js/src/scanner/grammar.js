// Generated automatically by nearley, version 2.20.1
// http://github.com/Hardmath123/nearley
(function () {
  function id(x) {
    return x[0];
  }
  var grammar = {
    Lexer: undefined,
    ParserRules: [
      {
        name: "program",
        symbols: ["functions"],
        postprocess: (data) => {
          return {
            functions: data[0],
          };
        },
      },
      {
        name: "args",
        symbols: [{ literal: "(" }, "expressions", { literal: ")" }],
        postprocess: (data) => {
          return data[1];
        },
      },
      {
        name: "args",
        symbols: [{ literal: "(" }, { literal: ")" }],
        postprocess: (data) => {
          return [];
        },
      },
      {
        name: "data_type$string$1",
        symbols: [
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "8" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$1"], postprocess: id },
      {
        name: "data_type$string$2",
        symbols: [
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "1" },
          { literal: "6" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$2"], postprocess: id },
      {
        name: "data_type$string$3",
        symbols: [
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "3" },
          { literal: "2" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$3"], postprocess: id },
      {
        name: "data_type$string$4",
        symbols: [{ literal: "i" }, { literal: "n" }, { literal: "t" }],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$4"], postprocess: id },
      {
        name: "data_type$string$5",
        symbols: [
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "6" },
          { literal: "4" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$5"], postprocess: id },
      {
        name: "data_type$string$6",
        symbols: [
          { literal: "u" },
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "8" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$6"], postprocess: id },
      {
        name: "data_type$string$7",
        symbols: [
          { literal: "u" },
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "1" },
          { literal: "6" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$7"], postprocess: id },
      {
        name: "data_type$string$8",
        symbols: [
          { literal: "u" },
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "3" },
          { literal: "2" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$8"], postprocess: id },
      {
        name: "data_type$string$9",
        symbols: [
          { literal: "u" },
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$9"], postprocess: id },
      {
        name: "data_type$string$10",
        symbols: [
          { literal: "u" },
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
          { literal: "6" },
          { literal: "4" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$10"], postprocess: id },
      {
        name: "data_type$string$11",
        symbols: [
          { literal: "b" },
          { literal: "o" },
          { literal: "o" },
          { literal: "l" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$11"], postprocess: id },
      {
        name: "data_type$string$12",
        symbols: [
          { literal: "s" },
          { literal: "t" },
          { literal: "r" },
          { literal: "i" },
          { literal: "n" },
          { literal: "g" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$12"], postprocess: id },
      {
        name: "data_type$string$13",
        symbols: [
          { literal: "c" },
          { literal: "h" },
          { literal: "a" },
          { literal: "r" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "data_type", symbols: ["data_type$string$13"], postprocess: id },
      {
        name: "expressions",
        symbols: ["___", "expression", "___"],
        postprocess: (data) => [data[1]],
      },
      {
        name: "expressions",
        symbols: ["___", "expression", "___", { literal: "," }, "expressions"],
        postprocess: (data) => [data[1], ...data[4]],
      },
      {
        name: "functions",
        symbols: ["___", "function", "___"],
        postprocess: (data) => [data[1]],
      },
      {
        name: "functions",
        symbols: ["___", "function", "___", { literal: "\n" }, "functions"],
        postprocess: (data) => [data[1], ...data[4]],
      },
      {
        name: "function",
        symbols: ["identifier", "___", "args", "___", "block_statements"],
        postprocess: (data) => {
          return {
            type: "function",
            return: "int32",
            return_default: true,
            name: data[0],
            args: data[2],
            stmts: data[4],
          };
        },
      },
      {
        name: "function",
        symbols: [
          "data_type",
          "___",
          "identifier",
          "___",
          "args",
          "___",
          "block_statements",
        ],
        postprocess: (data) => {
          return {
            type: "function",
            return: data[0],
            name: data[2],
            args: data[4],
            stmts: data[6],
          };
        },
      },
      {
        name: "function",
        symbols: ["data_type", "___", "identifier", "___", "block_statements"],
        postprocess: (data) => {
          return {
            type: "function",
            return: data[0],
            name: data[2],
            args: [],
            stmts: data[4],
          };
        },
      },
      {
        name: "function",
        symbols: ["identifier", "___", "block_statements"],
        postprocess: (data) => {
          return {
            type: "function",
            return: "int32",
            return_default: true,
            name: data[0],
            args: [],
            stmts: data[2],
          };
        },
      },
      {
        name: "block_statements",
        symbols: [{ literal: "{" }, "statements", { literal: "}" }],
        postprocess: (data) => {
          return data[1];
        },
      },
      {
        name: "block_statements",
        symbols: [{ literal: "{" }, "___", { literal: "}" }],
        postprocess: (data) => {
          return [];
        },
      },
      {
        name: "statements",
        symbols: ["___", "statement", "___"],
        postprocess: (data) => [data[1]],
      },
      {
        name: "statements",
        symbols: ["___", "statement", "___", { literal: "\n" }, "statements"],
        postprocess: (data) => [data[1], ...data[4]],
      },
      { name: "statement", symbols: ["var_assignment"], postprocess: id },
      { name: "statement", symbols: ["print_statement"], postprocess: id },
      { name: "statement", symbols: ["while_loop"], postprocess: id },
      {
        name: "while_loop$string$1",
        symbols: [
          { literal: "w" },
          { literal: "h" },
          { literal: "i" },
          { literal: "l" },
          { literal: "e" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      {
        name: "while_loop",
        symbols: [
          "while_loop$string$1",
          "__",
          "binary_expression",
          "__",
          { literal: "{" },
          "_",
          { literal: "\n" },
          "statements",
          { literal: "\n" },
          { literal: "}" },
        ],
        postprocess: (data) => {
          return {
            type: "while_loop",
            condition: data[2],
            body: data[7],
          };
        },
      },
      {
        name: "print_statement$string$1",
        symbols: [
          { literal: "p" },
          { literal: "r" },
          { literal: "i" },
          { literal: "n" },
          { literal: "t" },
        ],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      {
        name: "print_statement",
        symbols: ["print_statement$string$1", "__", "expression"],
        postprocess: (data) => {
          return {
            type: "print_statement",
            expression: data[2],
          };
        },
      },
      { name: "expression", symbols: ["unary_expression"], postprocess: id },
      { name: "expression", symbols: ["binary_expression"], postprocess: id },
      { name: "unary_expression", symbols: ["number"], postprocess: id },
      { name: "unary_expression", symbols: ["identifier"], postprocess: id },
      { name: "operator", symbols: [{ literal: "+" }], postprocess: id },
      { name: "operator", symbols: [{ literal: "-" }], postprocess: id },
      { name: "operator", symbols: [{ literal: "*" }], postprocess: id },
      { name: "operator", symbols: [{ literal: "/" }], postprocess: id },
      {
        name: "operator$string$1",
        symbols: [{ literal: ">" }, { literal: "=" }],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "operator", symbols: ["operator$string$1"], postprocess: id },
      {
        name: "operator$string$2",
        symbols: [{ literal: "<" }, { literal: "=" }],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      { name: "operator", symbols: ["operator$string$2"], postprocess: id },
      { name: "operator", symbols: [{ literal: ">" }], postprocess: id },
      { name: "operator", symbols: [{ literal: "<" }], postprocess: id },
      { name: "operator", symbols: [{ literal: "=" }], postprocess: id },
      {
        name: "binary_expression",
        symbols: ["unary_expression", "_", "operator", "_", "expression"],
        postprocess: (data) => {
          return {
            type: "binary_expression",
            left: data[0],
            operator: data[2],
            right: data[4],
          };
        },
      },
      {
        name: "var_assignment$string$1",
        symbols: [{ literal: ":" }, { literal: "=" }],
        postprocess: function joiner(d) {
          return d.join("");
        },
      },
      {
        name: "var_assignment",
        symbols: [
          "identifier",
          "_",
          "var_assignment$string$1",
          "_",
          "expression",
        ],
        postprocess: (data) => {
          return {
            type: "var_assignment",
            varname: data[0],
            value: data[4],
          };
        },
      },
      { name: "identifier$ebnf$1", symbols: [/[a-z]/] },
      {
        name: "identifier$ebnf$1",
        symbols: ["identifier$ebnf$1", /[a-z]/],
        postprocess: function arrpush(d) {
          return d[0].concat([d[1]]);
        },
      },
      {
        name: "identifier",
        symbols: ["identifier$ebnf$1"],
        postprocess: (data) => data[0].join(""),
      },
      {
        name: "number",
        symbols: ["digits", { literal: "." }, "digits"],
        postprocess: (data) => Number(data[0] + "." + data[2]),
      },
      {
        name: "number",
        symbols: ["digits"],
        postprocess: (data) => Number(data[0]),
      },
      { name: "digits$ebnf$1", symbols: [/[0-9]/] },
      {
        name: "digits$ebnf$1",
        symbols: ["digits$ebnf$1", /[0-9]/],
        postprocess: function arrpush(d) {
          return d[0].concat([d[1]]);
        },
      },
      {
        name: "digits",
        symbols: ["digits$ebnf$1"],
        postprocess: (data) => data[0].join(""),
      },
      { name: "_$ebnf$1", symbols: [] },
      {
        name: "_$ebnf$1",
        symbols: ["_$ebnf$1", /[ \t]/],
        postprocess: function arrpush(d) {
          return d[0].concat([d[1]]);
        },
      },
      { name: "_", symbols: ["_$ebnf$1"] },
      { name: "__$ebnf$1", symbols: [/[ \t]/] },
      {
        name: "__$ebnf$1",
        symbols: ["__$ebnf$1", /[ \t]/],
        postprocess: function arrpush(d) {
          return d[0].concat([d[1]]);
        },
      },
      { name: "__", symbols: ["__$ebnf$1"] },
      { name: "___$ebnf$1", symbols: [] },
      {
        name: "___$ebnf$1",
        symbols: ["___$ebnf$1", /[ \t\n]/],
        postprocess: function arrpush(d) {
          return d[0].concat([d[1]]);
        },
      },
      { name: "___", symbols: ["___$ebnf$1"] },
    ],
    ParserStart: "program",
  };
  if (typeof module !== "undefined" && typeof module.exports !== "undefined") {
    module.exports = grammar;
  } else {
    window.grammar = grammar;
  }
})();
