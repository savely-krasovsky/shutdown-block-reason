const {platform} = require('node:os');
const {spawnSync} = require("node:child_process");

if (platform() === 'win32') {
  spawnSync('node-gyp.cmd', ['rebuild'], {
    shell: true,
    input: 'win32 detected. Build native module.',
    stdio: 'inherit'
  });
}
