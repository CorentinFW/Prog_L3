const mongoose = require("mongoose");
const Win = require('./win.js');
const joueur = ["Azou","Pablo","Hercule"];
(async () => {
    try {
        await mongoose.connect("mongodb://localhost:27017/test");
        console.log("Connection réussi");

        const gagnant = new Win({
            J1 : joueur[0],
            J2 : joueur[1]
        });
        const result = await gagnant.save();
        console.log(result);

    }catch(error){
        console.log(error.message);
    }
})();