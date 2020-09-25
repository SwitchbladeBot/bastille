require('dotenv').config()

const hound = require('hound')
const fetch = require('node-fetch')
const fs = require('fs')
const chalk = require('chalk')

let watcher = hound.watch('script.js')

console.clear()

const LogType = {
    LOG: 'log',
    INFO: 'info',
    ERROR: 'error',
    WARN: 'warn',
    DEBUG: 'debug'
}

watcher.on('change', () => {
    fs.readFile(process.env.SCRIPT, 'utf8', (err, data) => {
        if (err) {
            return console.log(err)
        }
        console.clear()

        logb(`script modified, executing`)

        let start = Date.now()

        fetch(`${process.env.API_URL}/run`, {
            method: 'POST',
            body: JSON.stringify({
                script: data
            })
        }).then(res => res.json()).then(output => {
            console.clear()
            logb(`script executed, took ${Date.now()-start}ms`)
            if (output.length != 0) {
                console.log(chalk.gray('\nBegin console output\n'))
            }
            output.forEach(single => {
                switch(single.type) {
                    case LogType.LOG:
                        try {
                            console.log(JSON.parse(single.message))
                        } catch {
                            console.log(single.message)
                        }
                        break;
                    case LogType.ERROR:
                        console.log(chalk.red(`[${single.line}] ${single.message}`))
                        break;
                }
            })
            if (output.length != 0) {
                console.log(chalk.gray('\nEnd console output\n'))
            }
        }).catch(() => {
            console.clear()
            logb(chalk.red("There was an error processing this request"))
        })
    })
})

function logb(str) {
    console.log(`[${chalk.blueBright("Bastille")}] ${str}`)
}