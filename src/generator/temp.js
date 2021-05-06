global.emits = "";

/*
 * emit
 */
const emit = (source) => {
	emits += source + "\n";
};

module.exports = {
  emit,
};
