var express = require('express');
var token_router = express.Router();
var bodyparser = require('body-parser')
var app = express()
Eos = require('eosjs')
fs = require('fs')
//var prettyjson = require('prettyjson')

app.use(bodyparser.json())
app.use(express.urlencoded({ extended: true }));

initaPrivate = '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'
initaPublic = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'
keyProvider = initaPrivate
app.disable('etag');

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
eos = Eos.Localnet(config)

/*
token_router.post('/acc_create',(req,res,next) =>{
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

/*
token_router.get('/sum',(req, res, next)=>
{

//var first = parse(req.body.f_n);
//var second = parse(req.body.l_n);
eos.transaction("laa",sum=>
{
sum.add(1,2,{ authorization: ["laa"]})


}).then((sum)=>
{

        res.contentType('application/json');
        res.send(sum);


})
});




module.exports = token_router;
*/

token_router.get('/sum', function(req, res, next) {

        eos.transaction("lal", myaccount => {



          myaccount.add(10,20, { authorization: ["lal"]})
        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});

module.exports = token_router;
