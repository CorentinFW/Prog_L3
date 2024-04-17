const mongoose = require('mongoose');

const WinSch = mongoose.Schema({
    J1 : String,
    J2 : String
});

const model = mongoose.model("Win",WinSch);

module.exports = model;