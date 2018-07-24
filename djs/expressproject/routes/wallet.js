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
//pubkey = 'EOS5mgfKzUaNHRJgdp7n1TfEzDeEedJwSmquEBNcrVbbF86HNWPsq';

config.binaryen = require("binaryen")
eos = Eos.Localnet(config)

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

wasm = fs.readFileSync(`./contracts/hospital/hospital.wasm`)
abi = fs.readFileSync(`./contracts/hospital/hospital.abi`)


token_router.post('/wasm',(req,res) =>{

      eos.setcode(req.body.acc_name, 0, 0, wasm,function(err,data){

        res.contentType('application/json');
        res.send(data);

})

})

token_router.post('/abi',(req,res) => {
eos.setabi(req.body.acc_name, JSON.parse(abi),(err,data) =>{

        res.contentType('application/json');
        res.send(data);

})

})




token_router.post('/details', function(req, res, next) {

        eos.transaction(req.body.acc_name, myaccount => {



          myaccount.account(req.body.id,req.body.name, { authorization: [req.body.acc_name]})
        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});




token_router.post('/doc', function(req, res, next) {

               eos.getTableRows({ json:true, scope: req.body.scope, code: req.body.code, table: req.body.table}).then(data=>{res.send(data);});


});



token_router.post('/modi', function(req, res, next) {

        eos.transaction("t1a", myaccount => {



          myaccount.modify1(req.body.id,req.body.name, { authorization: ["t1a"]})
        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});




module.exports = token_router;















/*
var express = require('express');
var router = express.Router();

var bodyparser = require('body-parser')
var app = express()

Eos = require('eosjs')
fs = require('fs')

app.use(bodyparser.json())
app.use(express.urlencoded({ extended: true }));

initaPrivate = '5J8oWdHNAmsavRWVNwo7jRZ56MiAyhBSvfFQjb3hMpEZDjkq9bq'
initaPublic = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'
keyProvider = initaPrivate
app.disable('etag');

wif = '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'
pubkey = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'


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
eos = Eos.Testnet(config)


// to create the account

router.post('/create',(req,res,next) =>{
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


wasm = fs.readFileSync(`./contracts/user/user.wasm`)
abi = fs.readFileSync(`./contracts/user/user.abi`)


router.post('/wasm',(req,res) =>{

      var name = req.body.aname;
      eos.setcode(name, 0, 0, wasm,function(err,data){

        res.contentType('application/json');
        res.send(data)

})

})

router.post('/abi',(req,res) => {
eos.setabi(req.body.aname, JSON.parse(abi),(err,data) =>{
        res.contentType('application/json');
        res.send(data)

})

})




module.exports = router;
*/

