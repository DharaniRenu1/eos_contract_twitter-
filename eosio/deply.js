Eos = require('eosjs')
fs = require('fs')

config = {keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'],
         }
config.binaryen = require("binaryen")
eos = Eos.Localnet(config)

wasm = fs.readFileSync(`eosio.token.wasm`)
abi = fs.readFileSync(`eosio.token.abi`)

eos.setcode("dharanirenu", 0, 0, wasm,function(err,data){
if(err) throw err;
console.log(data);
})

eos.setabi('dharanirenu', JSON.parse(abi),(err,data) =>{

if(err) throw err;
console.log(data)
});

