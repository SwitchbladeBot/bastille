fetch("https://waifu.pics/api/nsfw/waifu")
    .then(res => res.json())
    .then(text => {
        console.log(text)
    }).catch(err => {
        console.log(err)
    })