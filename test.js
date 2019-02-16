
const tesseract=require("./index");

const fs=require('fs');
console.time("test");
let data=tesseract.str_hocr("C:/Users/ACODEZ/RD/tesseractnative/thres.png");
fs.writeFile("gp004.png.html",data,(err)=>{
    console.log(err);
})
console.timeEnd("test");