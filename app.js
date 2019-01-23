'use strict';
const tessract = require('./build/Release/tessractnative.node');
console.log('Hello world');
console.log(tessract.str_hocr("Example-FS-7.jpg"));
