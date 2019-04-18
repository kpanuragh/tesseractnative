
const tesseract=require("./index");

const fs=require('fs');
console.time('test');
try{
    let data=tesseract.str_hocr("C:/Users/ACODEZ/RD/ml_project_implement/images/1555580181785/1555580185704-Telecommunication_company.pdf004.png");
    fs.writeFile("gp004.png.html",data,(err)=>{
        console.log(err);
    })
}
catch(e)
{
    console.log(e);
}


console.timeEnd('test');