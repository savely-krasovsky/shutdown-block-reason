const addon = require('bindings')('shutdown-block-reason.node');

module.exports = {
  create: addon.create,
  destroy: addon.destroy,
};
