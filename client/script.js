fetch("https://waifu.pics/api/nsfw/waifu", {
    headers: {
        "5": "sf"
    }
})
  .then(res => res.json())
  .then(json => console.log(json))
  .catch(err => console.log(err))