const load = require('node-gyp-build');
// This loads the addon from the build/Release directory
// or from the prebuilds folder.
const starkAddon = load(__dirname);

module.exports = starkAddon;
