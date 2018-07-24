Eos = require('eosjs')
fs= require('fs')
wif = '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'
pubkey = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'

config = {
  keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'], // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
}
config.binaryen = require("binaryen")

eos = Eos.Localnet(config)


wasm = fs.readFileSync(`hello.wasm`)
abi = fs.readFileSync(`hello.abi`)


eos.setcode('hello1', 0, 0, wasm,function(err,data){
console.log(data);
});
eos.setabi('hello1', JSON.parse(abi),(err,data)=> {
console.log(data);
});
