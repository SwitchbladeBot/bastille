fetch("https://waifu.pics/api/nsfw/waifu", {
    headers: {
        "key": "value"
    }
}).then(res => res.json())
  .then(json => console.log(json))
  .catch(err => console.log(err))