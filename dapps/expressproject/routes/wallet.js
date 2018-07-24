var express = require('express');
var token_router = express.Router();
var bodyparser = require('body-parser')
var app = express()

Eos = require('eosjs')
fs = require('fs')
//var prettyjson = require('prettyjson')

app.use(bodyparser.json())
app.use(express.urlencoded({ extended: true }));


config = {
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
  keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'], // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
  expireInSeconds: 60,
  broadcast: true,
  verbose: false, // API activity
  sign: true
}

wif = '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'
pubkey = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'


config.binaryen = require("binaryen")
eos = Eos.Testnet(config)
token_router.post('/create',(req,res,next) =>{
eos.transaction(tr => {
  tr.newaccount({
    creator: 'eosio',
    name: req.body.acc_name,
    owner: pubkey,
    active: pubkey
  })
 
  tr.buyrambytes({
    payer: 'eosio',
    receiver: req.body.acc_name,
    bytes: 8192
  })
 
  tr.delegatebw({
    from: 'eosio',
    receiver:req.body.acc_name,
    stake_net_quantity: '100.0000 SYS',
    stake_cpu_quantity: '100.0000 SYS',
    transfer: 0
  })
}).then((da) =>{
        res.contentType('application/json');
        res.json(da);
 })
})

//Deploying the Contract For account

wasm = fs.readFileSync(`./contracts/sum/sum.wasm`)
abi = fs.readFileSync(`./contracts/sum/sum.abi`)


token_router.post('/wasm',(req,res) =>{

      var name = req.body.aname;
      eos.setcode(name, 0, 0, wasm,function(err,data){

        res.contentType('application/json');
        res.send(data)

})

})

token_router.post('/abi',(req,res) => {
eos.setabi(req.body.aname, JSON.parse(abi),(err,data) =>{
        res.contentType('application/json');
        res.send(data)

})

})

token_router.post('/sum', function(req, res, next) {

        eos.transaction("dsa", myaccount => {

          // Create the initial token with its max supply

          myaccount.add(10,20, { authorization: ["dsa"]})
        }).then((da) => {

                res.contentType('application/json');
                res.json(da);

        })


});


module.exports = token_router;


