const fs = require("mz/fs");
const path = require("path");

const fileExists = (filepath) => {
  return fs.existsSync(filepath);
};

const fileReads = async (filepath) => {
  return (await fs.readFile(filepath)).toString();
};

module.exports = {
  fileExists,
  fileReads,
};
