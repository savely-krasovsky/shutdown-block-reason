const {platform, endianness} = require("node:os");

// Load addon only on Windows
let addon;
if (platform() === 'win32') {
  addon = require('bindings')('shutdown-block-reason.node');
} else {
  addon = {
    create: () => {},
    destroy: () => {}
  };
}

function bufferToNumber(buf) {
  if (endianness() === 'LE') {
    return buf.readInt32LE()
  } else {
    return buf.readInt32BE()
  }
}

/**
 * @param {Buffer | number} hwnd
 * @param {string} reason
 */
function create(hwnd, reason) {
  if (Buffer.isBuffer(hwnd)) {
    addon.create(bufferToNumber(hwnd), reason)
    return
  }

  addon.create(hwnd, reason)
}

/**
 * @param {Buffer | number} hwnd
 */
function destroy(hwnd) {
  if (Buffer.isBuffer(hwnd)) {
    addon.destroy(bufferToNumber(hwnd))
    return
  }

  addon.destroy(hwnd)
}

module.exports = { create, destroy };
