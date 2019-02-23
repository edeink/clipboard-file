var clipboard = require('bindings')('clipboard');
const process = require('process');

// 没错，我就是傻逼：因为不会在C++处理字符串，所以搬到了前端处理
if(process.platform === 'darwin') {
    let getClipboardFiles = clipboard.getClipboardFiles;
    let array = getClipboardFiles();
    clipboard.getClipboardFiles = function() {
        let prePath = array[0]; // file:///Users/edeity/Desktop/img/
        if(prePath) {
            let names = array[1]; // 'xxx\aabb.docx';
            let pathArray = prePath.replace('file://', '').split('/');
            pathArray.pop();
            let realPath = pathArray.join('/');
            let nameArray = names.split('\r');
            return nameArray.map(function(eachName) {
                return realPath + '/' + eachName;
            })
        } else {
            return [];
        }
    }
}



/**
 * getClipboardFiles
 *  */ 
exports = module.exports = clipboard;