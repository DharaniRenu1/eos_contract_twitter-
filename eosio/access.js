Eos = require('eosjs')


config = {keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'], httpEndpoint: 'http://127.0.0.1:8888' 
         }
config.binaryen = require("binaryen")
eos = Eos.Localnet(config)

/*
const options = {
  broadcast: false,
  sign: true,
  scope: [ "helloworld" ],
  authorization: [{
      "account": "eosio",
      "permission": "active"
    } ]
}
*/

/*
eos.transaction('dharanirenu', myaccount => {
 
  // Create the initial token with its max supply
  // const options = {authorization: 'myaccount'} // default
  myaccount.create('dharanirenu', '1000.000 RNU', { authorization: ['dharanirenu']})
 
  // Issue some of the max supply for circulation into an arbitrary account
  myaccount.issue('dharanirenu', '1000.000 RNU', 'transfered',{authorization: ['dharanirenu']})
}).then((da) =>{

console.log(da);
})
*/

/*
eos.transaction('dharanirenu', da =>{
        da.transfer('dharanirenu','root','10.000 RNU@dharanirenu', { authorization: ['dharanirenu']});

})
*/

eos.getCurrencyBalance('dharanirenu', 'dharanirenu', 'RNU',(err,data) => {
if(err) throw err;
console.log(data);
})


/*
eos.getCurrencyBalance('dharanirenu', 'RNU', 'dharanirenu',(err,data) => {
if(err) throw err;
console.log(data);
})
*/

