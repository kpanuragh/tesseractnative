
const tesseract=require("./index");

const fs=require('fs');
console.time('test');
try{
    let data=tesseract.str_hocr("C:/Users/ACODEZ/RD/tesseractnative_l/1550841254281-2017-financial-statements-en.pdf002.png");
    fs.writeFile("gp004.png.html",data,(err)=>{
        console.log(err);
    })
}
catch(e)
{
    console.log(e);
}


console.timeEnd('test');