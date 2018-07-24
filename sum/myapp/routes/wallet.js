var express = require('express');
var router = express.Router();

var bodyparser = require('body-parser')
var app = express()

Eos = require('eosjs')
fs = require('fs')

app.use(bodyparser.json())
app.use(express.urlencoded({ extended: true }));

initaPrivate = '5J8oWdHNAmsavRWVNwo7jRZ56MiAyhBSvfFQjb3hMpEZDjkq9bq'
initaPublic = 'EOS6gN8XAeuFK8M9A1Lu1Ycnd8LSgzGnttwqUvMGhUFr7vgk2PdcT'
keyProvider = initaPrivate
app.disable('etag');

config = {
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
  keyProvider: ['5J8oWdHNAmsavRWVNwo7jRZ56MiAyhBSvfFQjb3hMpEZDjkq9bq'], // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
  expireInSeconds: 60,
  broadcast: true,
  verbose: false, // API activity
  sign: true
}

config.binaryen = require("binaryen")
eos = Eos.Localnet(config)


router.get('/sum', function(req, res, next) {
  
        eos.transaction("lal", myaccount => {
 
          // Create the initial token with its max supply

          myaccount.add(10,20, { authorization: ["lal"]})
        }).then((da) => {

                res.contentType('application/json');
                res.json(da);

        })


});

module.exports = router;

