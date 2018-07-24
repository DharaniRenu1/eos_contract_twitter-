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
    chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca', // Jungle Testnet  http://dev.cryptolions.io:38888/v1/chain/get_info
    keyProvider: ['5J9CoSF9pErmFzjKreu2WHjqc6NxPW7Peme5owQa3V9wtVA1hZu'], // <----- existing account (active) private key that has ram cpu and bandwidth already purchased
    httpEndpoint: 'http://159.65.214.148:8888', // jungle testnet
    expireInSeconds: 60,
    broadcast: true,
    debug: true,
    sign: true
}

wif = '5J9CoSF9pErmFzjKreu2WHjqc6NxPW7Peme5owQa3V9wtVA1hZu'
pubkey = 'EOS7oscLTDqSPtYhMrXKMMfyYQLuuCxTKJKCtjPM2WJzVpVwStF3j'

config.binaryen = require("binaryen")
eos = Eos.Testnet(config)

token_router.post('/create',(req,res,next) =>{
eos.transaction(tr => {
  tr.newaccount({
    creator: 'tamilrenu123',
    name: req.body.acc_name,
    owner: pubkey,
    active: pubkey
  })

  tr.buyrambytes({
    payer: 'tamilrenu123',
    receiver: req.body.acc_name,
    bytes:20040238
  })

  tr.delegatebw({
    from: 'tamilrenu123',
    receiver:req.body.acc_name,
    stake_net_quantity: '100.0000 EOS',
    stake_cpu_quantity: '100.0000 EOS',
    transfer: 0
  })
}).then((da) =>{
        res.contentType('application/json');
        res.json(da);
})


})

//Deploying the Contract For account

wasm = fs.readFileSync(`./contracts/register/register.wasm`)
abi = fs.readFileSync(`./contracts/register/register.abi`)


token_router.post('/wasm',(req,res) =>{

      eos.setcode(req.body.acc_name, 0, 0, wasm,function(err,data){

if(err){
        res.contentType('application/json');
        res.send("Already the Contract is deployed" + err)

}
else{

        res.contentType('application/json');
        res.send(data)
}


})



})

token_router.post('/abi',(req,res) => {
eos.setabi(req.body.acc_name, JSON.parse(abi),(err,data) =>{

if(err){
        res.contentType('application/json');
        res.send("Already the Contract is deployed" + err)

}
else{

        res.contentType('application/json');
        res.send(data)
}


})

})


token_router.post('/register', function(req, res, next) {

        eos.transaction(req.body.acc_name, myaccount => {


          myaccount.tregister(req.body.aname,req.body.pass,req.body.skey, { authorization: [req.body.acc_name]})
        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});


token_router.post('/change', function(req, res, next) {

        eos.transaction(req.body.acc_name, myaccount => {


          myaccount.modifyreg(req.body.aname1,req.body.pass1,req.body.skey1, { authorization: [req.body.acc_name]})
        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});

token_router.post('/chating', function(req, res, next) {

        eos.transaction(req.body.acc_name, myaccount => {


          myaccount.chat(req.body.name1,req.body.chat, { authorization: [req.body.acc_name]})

        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});

token_router.post('/private', function(req, res, next) {

        eos.transaction(req.body.acc_name, myaccount => {


          myaccount.personal(req.body.fname,req.body.tname,req.body.person, { authorization: [req.body.acc_name]})

        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});


token_router.post('/de_register', function(req, res, next) {

       eos.transaction(req.body.acc_name, myaccount => {


         myaccount.del(req.body.dac, { authorization: [req.body.acc_name]})
       }).then((data) => {

               res.contentType('application/json');
               res.json(data);

       })


});

token_router.post('/follow', function(req, res, next) {

        eos.transaction(req.body.acc_name, myaccount => {


          myaccount.follower(req.body.name,req.body.namef, { authorization: [req.body.acc_name]})
        }).then((data) => {

                res.contentType('application/json');
                res.json(data);

        })


});



token_router.post('/doc', function(req, res, next) {

               eos.getTableRows({ json:true, scope: req.body.scope, code: req.body.code, table: req.body.table}).then(data=>{res.send(data);});


});


module.exports = token_router;


