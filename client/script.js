fetch("https://waifu.pics/api/nsfw/waifu")
    .then(res => res.json())
    .then(json => console.log(json))
    .catch(err => console.log(err))

console.log("f")