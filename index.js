var clipboard = require('bindings')('clipboard');

exports = module.exports = {
    getClipboardFiles: clipboard.getClipboardFiles
};