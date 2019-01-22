# clipboard-file v0.01

A nodejs addons, reading file path from clipboard

## Installation

Using npm:

```
npm i clipboard-file --save
```

In Node.js

```javascript
var cf = requrie('clipboard-file');
console.log(cf.getClipboardFiles())
// if empty, return []
// else return ['filepath1', filepath2];
```

## Support

Only support Windows now...