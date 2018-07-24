Eos = require('eosjs')
fs = require('fs')

wif = '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'
pubkey = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'

/*
config = {
  chain :
  keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'], // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
}
*/


config = {
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
  keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'], // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
  expireInSeconds: 60,
  broadcast: true,
  verbose: false, // API activity
  sign: true
}

eos = Eos.Localnet(config)

/*
eos.transaction(tr => {
  tr.newaccount({
    creator: 'eosio',
    name: 'lo1',
    owner: pubkey,
    active: pubkey
  })

  tr.buyrambytes({
    payer: 'eosio',
    receiver: 'lo1',
    bytes: 8192
  })

  tr.delegatebw({
    from: 'eosio',
    receiver: 'eo1',
    stake_net_quantity: '10.0000 SYS',
    stake_cpu_quantity: '10.0000 SYS',
    transfer: 0
  })
})

*/

/*


wasm = fs.readFileSync(`hospital.wasm`)
abi = fs.readFileSync(`hospital.abi`)


eos.setcode('lo1', 0, 0, wasm,function(err,data){
console.log(data);
});
eos.setabi('lo1', JSON.parse(abi),(err,data)=> {
console.log(data);
});


*/

eos.contract('hh1')
  .then((doc) => {
    doc.modify1(7,"as",{authorization: "hh1"})
}).then((da) => {
	console.log(da);
})




/*

eos.getTableRows({ json:true, scope: 'hh1', code: 'hh1', table: 'doctors'}).then(data=>{console.log(data)});
*/
