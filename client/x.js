const fetch = require("node-fetch")

fetch("https://google.com")
    .then(res => res.text())
    .then(text => {
        console.log(text)
    })