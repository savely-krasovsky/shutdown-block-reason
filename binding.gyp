{
  "targets": [
    {
      "target_name": "shutdown-block-reason",
      "sources": [ "src/addon.cc" ],
      "dependencies": ["<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except"],
    }
  ]
}
