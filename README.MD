# clipboard-file

A nodejs addons, reading file path from clipboard

## Installation

Using npm:

```
npm i clipboard-file --save
```

In Node.js

```javascript
const cf = requrie('clipboard-file');
cf.getClipboardFiles();
// if empty, return []
// else return [filepath1, filepath2];
```

## Support

Only support Windows & High Version MacOS(macOS 10_13)