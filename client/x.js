const fetch = require("node-fetch")

fetch("https://waifu.pics/api/nsfw/waifu")
    .then(res => console.log(res.status))