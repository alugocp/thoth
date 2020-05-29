function generate_words(){
  if(Module){
    Module.ccall("generate");
    Module.ccall("get_word","string",["number"],[0]);
    let words = lst => lst.map(x => `<p>${Module.ccall("get_word","string",["number"],[x])}</p>`).reduce((acc,x) => acc+x);
    let wrapper=document.getElementsByClassName("words-wrapper")[0];
    wrapper.innerHTML=`<div>${words([0,1,2,3,4])}</div><div>${words([5,6,7,8,9])}</div>`;
  }else{
    wrapper.innerHTML="You don't have WebAssembly on your browser :(";
  }
}
