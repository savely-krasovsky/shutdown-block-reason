const addon = require('bindings')('shutdown-block-reason.node')

const create = addon.create;
const destroy = addon.destroy;

module.exports = {create, destroy}
